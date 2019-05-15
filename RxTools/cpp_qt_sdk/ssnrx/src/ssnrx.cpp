#include "ssnrx.h"
extern "C"
{
#include "crc.h"
}

namespace SSN {

SsnRx::SsnRx(QObject *parent)
  : QObject(parent)
{
  mIODevice = 0;
  mSerialPort = 0;
  mTcpSocket = 0;
  mIsConnected = false;
  mHasPrompt = false;
  mPromptTimer.setSingleShot(true);
  mPromptTimer.setInterval(5000);
  mPromptRequestAttemptCounter = 0;
  connect(&mPromptTimer, SIGNAL(timeout()), this, SLOT(onPromptTimeOut()));
}

SsnRx::~SsnRx()
{
  closeConnection();
}

///////////////////////////////////
// Connecting/Connection
///////////////////////////////////

bool SsnRx::connectSerial(const QString& portName, const QString& settings)
{
  using TNX::QSerialPort;
  closeConnection();

  mIODevice = mSerialPort = new QSerialPort(portName, settings);
  connect(mSerialPort, SIGNAL(readyRead()), SLOT(onDataReceived()));

  if (!mSerialPort->setCommTimeouts(QSerialPort::CtScheme_NonBlockingRead))
  {
    emit communicationError(QString("Cannot set communications timeout values at port %1.").arg(portName));
  }
  if (mSerialPort->open())
  {
    mIsConnected = true;
    emit connected();
    return true;
  }
  else
  {
    emit communicationError(QString("Failed to open serial connection at port %1.").arg(portName));
    closeConnection();
    return false;
  }
}

void SsnRx::connectTcp(const QString& hostName, quint16 port)
{

  closeConnection();

  mIODevice = mTcpSocket = new QTcpSocket(this);
  connect(mTcpSocket, SIGNAL(readyRead()), SLOT(onDataReceived()));
  connect(mTcpSocket, SIGNAL(connected()), SLOT(onTcpSocketConnected()));
  connect(mTcpSocket, SIGNAL(disconnected()), SLOT(onTcpSocketDisconnected()));
  connect(mTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onTcpSocketError(QAbstractSocket::SocketError)));

  mTcpSocket->connectToHost(hostName, port);
}


void SsnRx::closeConnection()
{
  if (mIODevice != 0)
  {
    if (mIODevice->isOpen())
    {
      mIODevice->close();
      if (mTcpSocket != 0)
      {
        disconnect(mTcpSocket, SIGNAL(disconnected()));
      }
    }
    mIODevice->deleteLater();
  }
  mIODevice = 0;
  mSerialPort = 0;
  mTcpSocket = 0;
  mConnectionDescriptor = QString();
  mHasPrompt = false;
  mPromptRequestAttemptCounter = 0;
  mPromptTimer.stop();
  mASCIICommandQueue.clear();

  if (mIsConnected)
  {
    mIsConnected = false;
    emit connectionClosed();
  }
}

bool SsnRx::isConnected()
{
  // mIsConnected is used to keep the state w.r.t. emission of connected/connectionClosed signals
  // but for isConnected we inspect the underlying device object.
  return (mIODevice != 0 && mIODevice->isOpen());
}

void SsnRx::onTcpSocketConnected()
{
  mIsConnected = true;
  emit connected();
}

void SsnRx::onTcpSocketError(QAbstractSocket::SocketError /*socketError*/)
{
  emit communicationError(mTcpSocket->errorString());
}

void SsnRx::onTcpSocketDisconnected()
{
  closeConnection();
}


////////////////////////////////////
// Communication
////////////////////////////////////


void SsnRx::onDataReceived()
{
  while (mIODevice->bytesAvailable() > 0)
  {
    QByteArray data = mIODevice->read(2048);
    mBuffer.append(data);
    parse();
    // TODO avoid starvation due to bytes coming in faster than they are processed:
    // break once in a while and make sure to process events + schedule a new onDataRecceived
    // or alternatively (?) only process the bytes that are available upon calling of this slot?
  }
}

////////////////////////////////////
// Parsing data received from receiver
////////////////////////////////////

void SsnRx::parse()
{
  bool done = false;
  while (!done)
  {
    // We are looking for either
    // - a prompt (which may be caused by sending [Enter])
    // - a message, starting with '$', and followed by a character
    //   indicating the kind of message
    int size = mBuffer.size();
    int index;
    for (index = 0; index < size; index++)
    {
      if (mBuffer.at(index) == '>' ||
          mBuffer.at(index) == '$')
      {
        break;
      }
    }

    if (index < size)
    {
      if (mBuffer.at(index) == '>')
      {
        // '>' terminates a prompt
        QString prompt = getPromptEndingAt(index);
        if (!prompt.isEmpty())
        {
          int promptStartIndex = index - prompt.length() + 1;
          if (promptStartIndex > 0)
          {
            emit discardedBytes(promptStartIndex);
          }
          setPrompt(prompt);
        }
        else
        {
          emit discardedBytes(index);
        }
        mBuffer = mBuffer.mid(index + 1);
      }
      else // '$' was found
      {
        if (index > 0)
        {
          emit discardedBytes(index);
          mBuffer = mBuffer.mid(index);
        }
        if (mBuffer.size() >= 2)
        {
          if (mBuffer.at(1) == '@' ||
              mBuffer.at(1) == 'R' ||
              mBuffer.at(1) == 'T' ||
              mBuffer.at(1) == '-')
          {
            bool notEnoughData = false;
            int processedBytes = 0;
            if (mBuffer.at(1) == '@')
            {
              processedBytes = parseSBF(0,&notEnoughData);
            }
            else if (mBuffer.at(1) == 'R')
            {
              processedBytes = parseASCIICommandReply(0,&notEnoughData);
            }
            else if (mBuffer.at(1) == 'T')
            {
              if (mBuffer.size() < 3)
              {
                notEnoughData = true;
              }
              else
              {
                if (mBuffer.at(2) == 'D')
                {
                  processedBytes = parseASCIIDisplay(0, &notEnoughData);
                }
                else if (mBuffer.at(2) == 'E')
                {
                  processedBytes = parseEvent(0, &notEnoughData);
                }
              }
            }
            else if (mBuffer.at(1) == '-')
            {
              processedBytes = parseFormattedInformationBlock(0, &notEnoughData);
            }

            if (processedBytes > 0)
            {
              mBuffer = mBuffer.mid(processedBytes);
            }
            else
            {
              if (notEnoughData)
              {
                // the buffer does not yet contain enough data to parse the message
                // so we return control, and parsing will be reattempted upon receiving more data
                done = true;
              }
              else
              {
                // an error has occured when trying to parse the message
                mBuffer = mBuffer.mid(2);
                emit(discardedBytes(2));
              }
            }
          }
          else
          {
            mBuffer = mBuffer.mid(1);
            emit(discardedBytes(1));
          }
        }
        else
        {
          // the '$' was not followed yet by a byte indicating the type of message
          // so we return control, and parsing will be reattempted upon receiving more data
          done = true;
        }
      }
    }
    else // i.e. index == size
    {
      // nothing found, discard all data, except for the last sMaxPromptLength-1,
      // because they may be the start of a new prompt
      done = true;
      mBuffer = mBuffer.right(sPromptLength - 1);
      int discarded = size - mBuffer.size();
      if (discarded > 0)
      {
        emit discardedBytes(size - mBuffer.size());
      }
    }
  }
}

///////////////////
// Prompt
///////////////////

bool SsnRx::hasPrompt() const
{
  return mHasPrompt;
}


bool SsnRx::hasConnectionDescriptor() const
{
  return !mConnectionDescriptor.isEmpty();
}


QString SsnRx::getConnectionDescriptor() const
{
  return mConnectionDescriptor;
}

void SsnRx::sendPromptRequest()
{
  if (isConnected())
  {
    mPromptRequestAttemptCounter++;
    if (mPromptRequestAttemptCounter == 1)
    {
      // If the Receiver is already configured to accept CMD input
      // on the connected port. Sending an "Enter" to the receiver will
      // trigger the receiver to send a prompt back.
      mIODevice->write("\r\n");
      mPromptTimer.start();
    }
    else if (mPromptRequestAttemptCounter == 2)
    {
      // If the above failed (i.e. waiting for the prompt timed out)
      // sending "SSSSSSSSSS" should force the receiver to accept CMD input,
      // and trigger the receiver to send a prompt.
      mIODevice->write("SSSSSSSSSS\r\n");
      mPromptTimer.start();
    }
    else
    {
      emit communicationError("Failed to obtain ASCII prompt.");
    }
  }
  else
  {
    emit communicationError("Failed to send ASCII prompt request: not connected.");
  }
}

void SsnRx::onPromptTimeOut()
{
  sendPromptRequest();
}

QString SsnRx::getPromptEndingAt(int index) const
{
  QString result;
  if (index + 1 >= sPromptLength)
  {
    QString s = QString(mBuffer.mid(index - sPromptLength + 1, sPromptLength));
    if (sPromptRegExp.exactMatch(s))
    {
      result = s;
    }
  }
  return result;
}

void SsnRx::setPrompt(const QString& prompt)
{
  mPromptTimer.stop();
  mPromptRequestAttemptCounter = 0;
  QString cd = prompt;
  cd.chop(1); // remove the trailing '>'
  bool newCD = (mConnectionDescriptor != cd);
  if (newCD)
  {
    mConnectionDescriptor = cd;
  }
  mHasPrompt = true;
  emit newPrompt(prompt);
  if (newCD)
  {
    emit newConnectionDescriptor(cd);
  }
  if (!mASCIICommandQueue.isEmpty())
  {
    QTimer::singleShot(0, this, SLOT(sendNextASCIICommand()));
  }
}

QRegExp SsnRx::sPromptRegExp("COM\\d>|USB\\d>|IP1\\d>");

///////////////////
// Command Reply
///////////////////

int SsnRx::parseASCIICommandReply(int startIndex, bool* outNotEnoughData)
{
  *outNotEnoughData = false;
  if (mBuffer.mid(startIndex, 2) != "$R")
  {
    return -1;
  }
  mPromptTimer.start();  // restart timer (from zero again)
  mHasPrompt = false;
  int endIndex = searchEndOfAsciiMessage(startIndex, sMaxASCIICommandReplySize, outNotEnoughData);
  if (endIndex != -1)
  {
    QString prompt = mBuffer.mid(endIndex - sPromptLength, sPromptLength);
    bool error = (mBuffer.at(startIndex + 2) == '?');
    emit newCommandReply(mBuffer.mid(startIndex, endIndex - startIndex - prompt.size() - 2), error);

    if (prompt == "STOP>")
    {
      emit stopReceived();
      mPromptTimer.stop();
    }
    else if (prompt != "---->")
    {
      setPrompt(prompt);
    }

    // consume "\r\n" if present
    if ((mBuffer.size() > endIndex) && (mBuffer.at(endIndex) == '\r'))
    {
      endIndex++;
      if ((mBuffer.size() > endIndex) && (mBuffer.at(endIndex) == '\n'))
      {
        endIndex++;
      }
    }

    return endIndex - startIndex;
  }
  else
  {
    return -1;
  }
}

int SsnRx::searchEndOfAsciiMessage(int startIndex, int maxLength, bool* outNotEnoughData)
{
  *outNotEnoughData = false;
  int index = mBuffer.indexOf("\r\n", startIndex);
  bool found = false;
  while (index != -1 && index <= startIndex + maxLength - sPromptLength)
  {
    index += 2; // consume the "\r\n" sequence
    if ((mBuffer.size() > index + sPromptLength - 1) &&
        (mBuffer.at(index + sPromptLength - 1) == '>'))
    {
      QString endSequence = mBuffer.mid(index, sPromptLength);
      if (endSequence == "STOP>" ||
          endSequence == "---->" ||
          endSequence == "####>" ||
          sPromptRegExp.exactMatch(endSequence))
      {
        index += sPromptLength;
        found = true;
        break;
      }
    }

    // no prompt found, so try to consume a line
    index = mBuffer.indexOf("\r\n", index);
  }
  if (found)
  {
    return index;
  }
  else
  {
    if (index == -1 && mBuffer.size() < startIndex + maxLength)
    {
      *outNotEnoughData = true;
    }
    return -1;
  }
}


///////////////////
// Formatted Information Blocks
///////////////////

int SsnRx::parseFormattedInformationBlock(int startIndex, bool* outNotEnoughData)
{
  *outNotEnoughData = false;
  mHasPrompt = false;
  mPromptTimer.start(); // restart timer (from zero again)

  // try to parse the first line as "<-- BLOCK I / N\r\n"
  int indexOfEOL = mBuffer.indexOf("\r\n", startIndex);
  if (indexOfEOL == -1)
  {
    if ((mBuffer.size() - startIndex) < 30)
    {
      // 30 is taken (arbitrarily) as a reasonable small maximum lenght
      // for the first line of the formatted information block reply.
      *outNotEnoughData = true;
    }
    return -1;
  }
  else
  {
    static QRegExp blockHeaderRegExp("\\$-- BLOCK (\\d+) / (\\d+)"); // (greedy by default)
    QString firstLine = mBuffer.mid(startIndex, indexOfEOL - startIndex);
    if (blockHeaderRegExp.indexIn(firstLine) != 0)
    {
      // the first line should immediately start matching the given regular expression
      return -1;
    }
    else
    {
      int blockIndex = blockHeaderRegExp.cap(1).toInt();
      int nrOfBlocks = blockHeaderRegExp.cap(2).toInt();

      // now search for the end of the block
      int endIndex = searchEndOfAsciiMessage(startIndex, sMaxFormattedInformationBlockSize, outNotEnoughData);
      if (endIndex != -1)
      {
        QString prompt = mBuffer.mid(endIndex - sPromptLength, sPromptLength);
        emit newFormattedInformationBlock(mBuffer.mid(startIndex, endIndex - startIndex - prompt.size() - 2), blockIndex, nrOfBlocks);

        if (prompt == "STOP>")
        {
          emit stopReceived();
        }
        else if (prompt != "---->")
        {
          setPrompt(prompt);
        }
        return endIndex - startIndex;
      }
      else
      {
        return -1;
      }
    }
  }
}

///////////////////
// SBF
///////////////////

int SsnRx::parseSBF(int startIndex, bool* outNotEnoughData)
{
  int bufferSize = mBuffer.size();
  *outNotEnoughData = false;
  if (mBuffer.mid(startIndex, 2) != "$@")
  {
    return -1;
  }
  if (bufferSize - startIndex < 8)
  {
    *outNotEnoughData = true;
    return -1;
  }

  // get the lenght field from the SBF header
  quint16 length = getQuint16(mBuffer, startIndex + 6);
  if (length < 8)
  {
    emit communicationError("Invalid SBF block length.");
    return -1;
  }
  if (length > bufferSize - startIndex)
  {
    *outNotEnoughData = true;
    return -1;
  }

  // check the CRC
  quint16 expectedCRC = getQuint16(mBuffer, startIndex + 2);
  quint16 actualCRC = CRC_compute16CCITT(mBuffer.constData() + startIndex + 4, length - 4);

  if (actualCRC != expectedCRC)
  {
    emit communicationError("SBF CRC error.");
    emit sbfCRCError();
    return -1;
  }
  emit newSBFBlock(mBuffer.mid(startIndex, length));
  return length;
}

///////////////////
// ASCII display
///////////////////

int SsnRx::parseASCIIDisplay(int startIndex, bool* outNotEnoughData)
{
  *outNotEnoughData = false;
  if (mBuffer.size() - startIndex < 3)
  {
    *outNotEnoughData = true;
    return -1;
  }
  if (mBuffer.mid(startIndex, 3) != "$TD")
  {
    return -1;
  }

  int endIndex = mBuffer.indexOf("\r\n####>\r\n", startIndex);
  if (endIndex != -1 && (endIndex < startIndex + sMaxASCIIDisplaySize))
  {
    // the $TD is followed by \r\n, which is also stripped
    QString asciiDisplayContents = mBuffer.mid(startIndex + 5, endIndex - (startIndex+5));
    emit newASCIIDisplay(asciiDisplayContents);
    return endIndex + 9 - startIndex; // total processed bytes, including start and end delimiters
  }
  else
  {
    if (endIndex == -1 && (mBuffer.size() < startIndex + sMaxASCIIDisplaySize))
    {
      *outNotEnoughData = true;
    }
    else
    {
      // maximum length of ASCII display exceeded without finding the end
      *outNotEnoughData = false;
    }
    return -1;
  }
}

///////////////////
// Event
///////////////////

int SsnRx::parseEvent(int startIndex, bool* outNotEnoughData)
{
  *outNotEnoughData = false;
  if (mBuffer.size() - startIndex < 3)
  {
    *outNotEnoughData = true;
    return -1;
  }
  if (mBuffer.mid(startIndex, 3) != "$TE")
  {
    return -1;
  }

  int endIndex = mBuffer.indexOf("\r\n", startIndex);
  if (endIndex != -1 && (endIndex < startIndex + sMaxEventSize))
  {
    QString event = mBuffer.mid(startIndex + 4, endIndex - (startIndex+4));
    emit newEvent(event);
    return endIndex + 2 - startIndex; // total processed bytes, including start and end delimiters
  }
  else
  {
    if (endIndex == -1 && (mBuffer.size() < startIndex + sMaxEventSize))
    {
      *outNotEnoughData = true;
    }
    else
    {
      // maximum length of event line exceeded without finding the end
      *outNotEnoughData = false;
    }
    return -1;
  }
}

///////////////////
// Sending ASCII commands to the receiver
///////////////////

void SsnRx::sendASCIICommand(const QString& command)
{
  if (!isConnected())
  {
    emit communicationError("Failed to send ASCII command: not connected.");
  }
  else
  {
    mASCIICommandQueue.enqueue(command);
    sendNextASCIICommand();
  }
}

void SsnRx::sendNextASCIICommand()
{
  if (!mASCIICommandQueue.isEmpty())
  {
    if (!isConnected())
    {
      emit communicationError("Failed to send ASCII command: not connected.");
    }
    else if (hasPrompt())
    {
      QString command = mASCIICommandQueue.dequeue();
      mIODevice->write(qPrintable(command + "\r\n"));
      // will normally trigger a new prompt to be received,
      //upon which extra commands in the queueu will be sent

      mHasPrompt = false;
      mPromptTimer.start();
      emit sentASCIICommand(command);
    }
    else
    {
      if (!mPromptTimer.isActive())
      {
        sendPromptRequest();
      }
      // else we are already expecting a prompt,
      // which will trigger sendingNextASCIICommand if any
    }
  }
}

///////////////////
// Utils
///////////////////

quint16 SsnRx::getQuint16(const QByteArray& byteArray, int index)
{
  quint8 lsb = *((quint8*)(byteArray.constData() + index));
  quint8 msb = *((quint8*)(byteArray.constData() + index + 1));
  return quint16(lsb) + (quint16(msb) << 8);
}

} // namespace
