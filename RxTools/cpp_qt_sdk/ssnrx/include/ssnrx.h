/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#ifndef SSNRX_H__
#define SSNRX_H__

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QRegExp>
#include <QQueue>
#include "qserialport.h"
#include "ssnrx_export.h"

namespace SSN {

/**
 * @brief SsnRx realizes connection and communication with a Septentrio receiver.
 *
 * The following connection types are supported:
 * - connection over serial port, including the virtual serial ports offered by
 *   the Septentrio USB driver when connecting a receiver using USB.
 * - connection over TCP/IP
 *
 * SsnRx supports parsing of the following Septentrio proprietary messages coming
 * from the receiver:
 * - ASCII command replies and command error notification
 * - ASCII display generated by the receiver
 * - Event notifications
 * - Formatted information blocks
 * - SBF
 *
 * SsnRx is a sub class of QObject, and uses the Qt Signal and Slot mechanism
 * to report its state changes. Client code can react upon relevant state changes
 * by connecting its slots to the signals of the SsnRx object.
 *
 * Methods to send an ASCII command or to connect over TCP are currently asynchronous.
 * This means that they return immediately, but the actual sending or the actual establishment
 * of the connection happens later. These latter state changes can be detected by connecting to
 * the corresponding signal.
 *
 * In the current version, the SsnRx object is not thread safe, and thus needs to reside in the
 * same thread as the client code (typically the main thread). Linewise, for its functioning, it is required that
 * that thread enters an event loop (i.e. the exec() method is called on the Q(Core)Application instance).
 */
class SSNRX_EXPORT SsnRx : public QObject
{
Q_OBJECT


///////////////////////////////////
// Constructor/Destructor
///////////////////////////////////

public:


  /**
   * @brief Constructor.
   *
   * @param parent the parent QObject
   */
  explicit SsnRx(QObject *parent = 0);

  /**
   * @brief Destructor.
   *
   * If a connection is open, it is closed.
   */
  ~SsnRx();

///////////////////////////////////
// Connecting/Connection
///////////////////////////////////

public:

  /**
   * @brief Connect over the given serial port.
   *
   * The connection settings can specify in a comma-separated way:
   * - the baudrate (115200 by default)
   * - the number of data bits (8 by default)
   * - the parity (none by default)
   * - the number of stop bits (1 by default)
   * - the flow control (off by default)
   *
   * The default settings match the default settings on the receiver for its COM ports,
   * and equally apply for the virtual COM ports when communicating over USB.
   *
   * If the connection is already open, it is closed first.
   *
   * @param portName  the port name (e.g. "COM1" on Windows/WinCE, "/dev/ttyS0" on Unix/Linux/Embedded Linux)
   * @param settings  the settings (e.g. "115200,8,n,1")
   * @return true iff connection was successful
   */
  bool connectSerial(const QString&  portName, const QString&  settings = "115200");

  /**
   * @brief Connect over TCP/IP.
   *
   * This method returns immediately, without returning an indication of success or failure.
   * See the connection related signals for following up.
   *
   * If the connection is already open, it is closed first.
   *
   * @param hostName  the host name (or IP address) of the receiver
   * @param port      the port number
   */
  void connectTcp(const QString& hostName, quint16 port = 28784);

  /**
   * @brief Close the connection.
   *
   * If no connection is open, this method has no effect.
   */
  void closeConnection();

  /**
   * @brief Returns whether a connection is open.
   *
   * @return true iff a connection is open
   */
  bool isConnected();

signals:

  /**
   * @brief Emitted when the connection is established.
   */
  void connected();

  /**
   * @brief Emitted when a communication error occurs.
   *
   * @param errorString  error message
   */
  void communicationError(QString errorString);

  /**
   * @brief Emitted when the connection is closed.
   */
  void connectionClosed();

private slots:

  /**
   * @brief Slot called when the underlying TcpSocked emits the connected signal.
   *
   * Records the state change and emits connected.
   */
  void onTcpSocketConnected();

  /**
   * @brief Slot called when the underlying TcpSocket emits the error signal.
   *
   * Emits communicationError.
   *
   * @param socketError the socket error
   */
  void onTcpSocketError(QAbstractSocket::SocketError socketError);

  /**
   * @brief Slot called when the underlying TcpSocket emits the disconnected signal.
   *
   * Records the state change and emits connectionClosed.
   */
  void onTcpSocketDisconnected();

private:

  bool mIsConnected; ///< state as exposed to client

////////////////////////////////////
// Communication
////////////////////////////////////

private slots:

  /**
   * @brief Slot called when the underlying QIODevice (i.e. QSerialPort or TcpSocket) emits readyRead.
   *
   * The data that is available for reading is read and processed (see parse()).
   */
  void onDataReceived();

private:

  QByteArray mBuffer; ///< buffer storing the received data that still needs to be processed

////////////////////////////////////
// Port
////////////////////////////////////

private:

  QIODevice *mIODevice; ///< abstraction, pointing to the serial port or TcpSocket depending on which is used.
  TNX::QSerialPort *mSerialPort; ///< serial port, if connection is through serial/
                                 ///< Septentrio virtual COM ports over USB
  QTcpSocket *mTcpSocket; ///< TCP Socket, if connection is through TCP.

////////////////////////////////////
// Parsing data received from receiver
////////////////////////////////////

signals:

  /**
   * @brief Signal emitted when a number of received bytes could not be interpreted by the parser.
   *
   * @param nrOfBytes number of discarded bytes
   */
  void discardedBytes(int nrOfBytes);

  /**
   * @brief Signal emitted when a new prompt has received.
   *
   * If command input is enabled on the receiver connection descriptor to which the
   * SsnRx instance is connected, the receiver sends a prompt when its is ready to receive
   * an ASCII command. This can be when concluding the reply to a previous command (or an empty line
   * sent to the receiver) or after sending the last of a series of formatted information blocks.
   *
   * A prompt is always sent as a response to commands sent to the receiver.
   *
   * A prompt is of the following form: "XXXN>", where XXX indicates the type of connection, and
   * N is the connection index.
   *
   * For example:
   * - "COM1>" is the prompt the receiver sends over its COM1 port.
   * - "USB1>", "IP10>", ...
   *
   * @param prompt  the prompt string
   */
  void newPrompt(const QString& prompt);

  /**
   * @brief Signal emitted when the connection description has changed.
   *
   * Most typically, this signal is emitted when the first prompt is received after connecting,
   * and the connection description has changed from empty to the actual connection description
   * of the receiver port to which we are connected.
   *
   * @param connectionDescriptor
   */
  void newConnectionDescriptor(const QString& connectionDescriptor);

  /**
   * @brief Signal emitted when an ASCII command reply has been received.
   *
   * @param reply  the reply (not including the prompt or end sequence that concludes it)
   * @param error  flag indicating whether the reply denotes an error
   */
  void newCommandReply(const QString& reply, bool error);

  /**
   * @brief Signal emitted when "STOP>" is received.
   *
   * The receiver sends "STOP>" to conclude the reply to a command that instruct the
   * receiver to halt or reset.
   */
  void stopReceived();

  /**
   * @brief Signal emitted when a new formatted information block is received.
   *
   * Certain commands produce one or more blocks of formatted text
   * that are sent in order and that must be concatenated to obtain the full resonse.
   *
   * @param contents  the contents of this block (without start or end sequence)
   * @param index     index of this block
   * @param count     total number of blocks
   */
  void newFormattedInformationBlock(const QString& contents, int index, int count);

  /**
   * @brief Signal emitted when a new SBF block has been received.
   *
   * This signal is only emitted if the CRC was correct.
   *
   * @param block the raw sbf block data
   */
  void newSBFBlock(const QByteArray& block);

  /**
   * @brief Signal emitted when processing an SBF block has failed because the CRC did not match.
   */
  void sbfCRCError();

  /**
   * @brief Signal emitted when a new ASCII display has been received.
   *
   * @param asciiDisplay
   */
  void newASCIIDisplay(const QString& asciiDisplay);

  /**
   * @brief Signal emitted when a new event has been received.
   *
   * @param event
   */
  void newEvent(const QString& event);

private:

  /**
   * @brief Parse the current contents of mBuffer.
   *
   * If data has been processed, it is removed from the buffer and corresponding signals are emitted.
   * For more information on how the data is parsed, refer to the inline comments in the implementation.
   */
  void parse();

    ///////////////////
    // Prompt
    ///////////////////

public:

  /**
   * \brief Returns whether there is currently a prompt.
   *
   * If so, the receiver is ready to receive commands.
   * This is not the case if the receiver is not set up to receive commands over its current connection.
   * This is also not the case after sending a command, until this command has been fully completed
   * (including reply and formatted information blocks if any).
   */
  bool hasPrompt() const;

  /**
   * @brief Returns whether the connection descriptor is known.
   */
  bool hasConnectionDescriptor() const;

  /**
   * @brief Return the connection descriptor.
   *
   * The connection descriptor denotes the receiver port to which we are connected.
   * It consist of 3 characters indicating the type of the port, and 1 digit indicating the port index.
   * E.g. "COM1", "COM2", ..., "USB1", "USB2", ..., "IP10", "IP11", ...
   *
   * If the connection descriptor is not available, an empty string is returned.
   *
   * Note that the connection descriptor denotes the port on the receiver, and is not to be confused
   * with the port on the device that is used to connect to the receiver. If the "COM1" port of your PC
   * is connected to the "COM4" port of the receiver, the connection descriptor will be "COM4".
   */
  QString getConnectionDescriptor() const;

  /**
   * @brief Triggers the receiver to send a prompt.
   *
   * At its first attempt, this method sends an empty line.
   * If this times out (e.g. because the receiver is not configured to receive ASCII commands over
   * this connection), consequent attempts will send the "SSSSSSSSSS" sequence. This sequence
   * forces the receiver to accept ASCII commands.
   */
  void sendPromptRequest();

private slots:

  /**
   * @brief Slot called when waiting for a prompt times out.
   *
   * Causes a new prompt request to be sent.
   */
  void onPromptTimeOut();

private:

  /**
   * @brief Tries to find a prompt in the input buffer, ending at the given position.
   *
   * @param index the end index
   * @return The prompt, or an empty string if no prompt is found.
   */
  QString getPromptEndingAt(int index) const;

  /**
   * \brief Set the received prompt.
   *
   * Note that this is only called for valid prompts. Not for e.g. "---->".
   * If the ASCII command queue is not empty, the sending of a next command is
   * triggered.
   *
   * \param prompt a valid prompt
   */
  void setPrompt(const QString& prompt);

  /**
   * \brief Searches in mBuffer for the end of an Ascii message.
   *
   * ASCII messages (command reply, formatted information block, ASCII
   * display) are terminated by a sequence xxxx>, following a carriage return
   * and a line feed. This can take the following forms:
   * - a prompt, like "COM1>", ending a command reply
   * - "---->", ending a formatted information block
   * - "####>", ending an ASCII display
   * - "STOP>", ending a command reply, if the receiver consequently stops processing commands
   *
   * \param startIndex position in buffer where the search must start
   * \param maxLength the maximum number of bytes to consider
   * \param outNotEnoughData output argument in which true is stored if there is not enough data,
   *                         i.e. from startIndex the buffer does not contain maxLength bytes and
   *                         a valid end sequence was not found
   *
   * \return index in the buffer after the ending sequence, i.e. after '>', or -1 if not found
   */
  int searchEndOfAsciiMessage(int startIndex, int maxLength, bool* outNotEnoughData);

  QString mConnectionDescriptor; ///< the connection descriptor
  bool mHasPrompt; ///< flag indicating whether in the current state a prompt is available

  QTimer mPromptTimer; ///< timer timing out when waiting for a new prompt takes too long
  int mPromptRequestAttemptCounter; ///< counts the number of repeated prompt requests (reset when a prompt is received)

  static QRegExp sPromptRegExp; ///< regular expression defining what a prompt looks like
  static const int sPromptLength = 5; ///< length of a prompt

  ///////////////////
  // Command Reply
  ///////////////////

private:

  /**
   * @brief Try to parse the data in the buffer, starting at the given index, as an ASCII command reply.
   *
   * If the parsing is successful, the related signal(s) are emitted, and the number of processed bytes
   * is returned.
   *
   * Otherwise, -1 is returned. This can be because not enough data has been received already, or because
   * the data does not conform to an ASCII command reply.
   *
   * The buffer is left unmodified.
   *
   * @param startIndex the exact start index of the command reply
   * @param outNotEnoughData
   * @return the number of processed bytes, or -1 upon failure
   */
  int parseASCIICommandReply(int startIndex, bool* outNotEnoughData);

  static const int sMaxASCIICommandReplySize = 4096; ///< the maximum size of an ASCII command reply

  ///////////////////
  // Formatted Information Blocks
  ///////////////////

private:

  /**
   * @brief Try to parse the data in the buffer, starting at the given index, as a formatted information block.
   *
   * If the parsing is successful, the related signal(s) are emitted, and the number of processed bytes
   * is returned.
   *
   * Otherwise, -1 is returned. This can be because not enough data has been received already, or because
   * the data does not conform to a formatted information block.
   *
   * The buffer is left unmodified.
   *
   * @param startIndex the exact start index of the formatted information block
   * @param outNotEnoughData
   * @return the number of processed bytes, or -1 upon failure
   */
  int parseFormattedInformationBlock(int startIndex, bool* outNotEnoughData);

  static const int sMaxFormattedInformationBlockSize = 4096; ///< the maximum size of an formatted information block


  ///////////////////
  // SBF
  ///////////////////

private:

  /**
   * @brief Try to parse the data in the buffer, starting at the given index, as an SBF block.
   *
   * If the parsing is successful (including correct CRC), the related signal(s) are emitted,
   * and the number of processed bytes is returned.
   *
   * Otherwise, -1 is returned. This can be because not enough data has been received already, or because
   * the data does not conform to an SBF block.
   *
   * The buffer is left unmodified.
   *
   * @param startIndex the exact start index of the SBF block
   * @param outNotEnoughData
   * @return the number of processed bytes, or -1 upon failure
   */
  int parseSBF(int startIndex, bool* outNotEnoughData);

  ///////////////////
  // ASCII display
  ///////////////////

private:

  /**
   * @brief Try to parse the data in the buffer, starting at the given index, as an ASCII display.
   *
   * If the parsing is successful, the related signal(s) are emitted, and the number of processed bytes
   * is returned.
   *
   * Otherwise, -1 is returned. This can be because not enough data has been received already, or because
   * the data does not conform to an ASCII display.
   *
   * The buffer is left unmodified.
   *
   * @param startIndex the exact start index of the ASCII display
   * @param outNotEnoughData
   * @return the number of processed bytes, or -1 upon failure
   */
  int parseASCIIDisplay(int startIndex, bool* outNotEnoughData);

  static const int sMaxASCIIDisplaySize = 16384; ///< the maximum size of an ASCII display
                                                 //TODO find out actual spec value

  ///////////////////
  // Event
  ///////////////////

private:

  /**
   * @brief Try to parse the data in the buffer, starting at the given index, as an event.
   *
   * If the parsing is successful, the related signal(s) are emitted, and the number of processed bytes
   * is returned.
   *
   * Otherwise, -1 is returned. This can be because not enough data has been received already, or because
   * the data does not conform to an event.
   *
   * The buffer is left unmodified.
   *
   * @param startIndex the exact start index of the event
   * @param outNotEnoughData
   * @return the number of processed bytes, or -1 upon failure
   */
  int parseEvent(int startIndex, bool* outNotEnoughData);

  static const int sMaxEventSize = 256; ///< the maximum size of an event
                                        // TODO find out actual spec value

///////////////////
// Sending ASCII commands to the receiver
///////////////////

public:

  /**
   * \brief Send the given ASCII command, or queue it for later sending.
   *
   * As the receiver is only ready to receive ASCII commands if a prompt is present,
   * the command will be queued if no prompt is present.
   *
   * \param command the command to be sent
   */
  void sendASCIICommand(const QString& command);

signals:

  /**
   * @brief Signal emitted when an ASCII command has actually been sent.
   *
   * @param command the command that has been sent
   */
  void sentASCIICommand(const QString& command);

private slots:

  /**
   * @brief Attempts to send the next command in the queue.
   *
   * If a prompt is present, the first command from the queue is sent.
   * Commands are sent one by one. If more than one command is in the queue, the other commands
   * will be send upon later invocations of sendNextASCIICommand.
   *
   * If a prompt is not present, and if a prompt request is not yet pending, a prompt request is sent.
   *
   * This method is called either by sendASCIICommand, or upon receiving a prompt indicating that the receiver
   * is ready to receive the next command.
   */
  void sendNextASCIICommand();

private:

  QQueue<QString> mASCIICommandQueue; ///< the ASCII command queue

///////////////////
// Utils
///////////////////

public:

  /**
   * @brief Auxiliary function to get a unsigned 16 bit integer encoded with little endianess from a buffer.
   *
   * @param byteArray the byte array to extract from
   * @param index     the index at which the value must be extracted
   */
  static quint16 getQuint16(const QByteArray& byteArray, int index);


};

} // namespace

#endif // SSNRX_H__