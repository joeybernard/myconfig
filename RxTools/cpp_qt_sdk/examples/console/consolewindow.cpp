/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#include <QVBoxLayout>
#include "consolewindow.h"

using namespace SSN;

ConsoleWindow::ConsoleWindow(SsnRx* rx, QWidget *parent) :
  QMainWindow(parent), mRx(rx)
{
  // set up widgets
  setCentralWidget(new QWidget);
  QVBoxLayout* mainLayout = new QVBoxLayout;
  centralWidget()->setLayout(mainLayout);
  mOutput = new QTextEdit;
  mOutput->setReadOnly(true);
  mainLayout->addWidget(mOutput);
  mCommandLine = new QLineEdit;
  mainLayout->addWidget(mCommandLine);

  // set up signal/slot connection for when the user presses enter in the command line edit
  connect(mCommandLine, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));

  // connect the signals that are emitted by the SsnRx object to the corresponing slots
  // of this ConsoleWindow object
  connect(rx, SIGNAL(connected()), this, SLOT(onConnected()));
  connect(rx, SIGNAL(communicationError(QString)), this, SLOT(onCommunicationError(QString)));
  connect(rx, SIGNAL(connectionClosed()), this, SLOT(onConnectionClosed()));

  connect(rx, SIGNAL(discardedBytes(int)), this, SLOT(onDiscardedBytes(int)));
  connect(rx, SIGNAL(newPrompt(const QString&)), this, SLOT(onNewPrompt(const QString&)));
  connect(rx, SIGNAL(newConnectionDescriptor(const QString&)), this, SLOT(onNewConnectionDescriptor(const QString&)));
  connect(rx, SIGNAL(newCommandReply(const QString&, bool)), this, SLOT(onNewCommandReply(const QString&, bool)));
  connect(rx, SIGNAL(stopReceived()), this, SLOT(onStopReceived()));
  connect(rx, SIGNAL(newFormattedInformationBlock(const QString&, int, int)), this, SLOT(onNewFormattedInformationBlock(const QString&,int,int)));
  connect(rx, SIGNAL(newSBFBlock(const QByteArray&)), this, SLOT(onNewSBFBlock(const QByteArray&)));
  connect(rx, SIGNAL(sbfCRCError()), this, SLOT(onSBFCRCError()));
  connect(rx, SIGNAL(newASCIIDisplay(const QString&)), this, SLOT(onNewASCIIDisplay(const QString&)));
  connect(rx, SIGNAL(newEvent(const QString&)), this, SLOT(onNewEvent(const QString&)));
  connect(rx, SIGNAL(sentASCIICommand(const QString&)), this, SLOT(onSentASCIICommand(const QString&)));

  // The ASCII display widget will be created upon need.
  mASCIIDisplay = 0;
}

ConsoleWindow::~ConsoleWindow()
{
  if (mASCIIDisplay != 0)
  {
    delete mASCIIDisplay;
  }
}

void ConsoleWindow::onReturnPressed()
{
  mRx->sendASCIICommand(mCommandLine->text());
  mCommandLine->clear();
}

void ConsoleWindow::addToOutput(QString text)
{
  mOutput->append(text + "\n");
}

void ConsoleWindow::onConnected()
{
  addToOutput("[Connected]");
}

void ConsoleWindow::onCommunicationError(QString errorString)
{
  addToOutput("[Connection error: " + errorString + "]");
}

void ConsoleWindow::onConnectionClosed()
{
  addToOutput("[Connection closed]");
}

void ConsoleWindow::onDiscardedBytes(int nrOfBytes)
{
  addToOutput(QString("[Discarded %1 bytes]").arg(nrOfBytes));
}

void ConsoleWindow::onNewPrompt(const QString& prompt)
{
  addToOutput(QString("[Received prompt %1]").arg(prompt));
}

void ConsoleWindow::onNewConnectionDescriptor(const QString& connectionDescriptor)
{
  addToOutput(QString("[New connection descriptor %1]").arg(connectionDescriptor));
}

void ConsoleWindow::onNewCommandReply(const QString& reply, bool error)
{
  addToOutput(QString("[Command reply (%1):]").arg(error ? "error":"success"));
  addToOutput(reply);
}

void ConsoleWindow::onStopReceived()
{
  addToOutput("[Received 'STOP>']");
}

void ConsoleWindow::onNewFormattedInformationBlock(const QString& contents, int index, int count)
{
  addToOutput(QString("[Received formatted information block (%1 of %2):]").arg(index).arg(count));
  addToOutput(contents);
}


void ConsoleWindow::onNewSBFBlock(const QByteArray& block)
{
  static int messageCounter = 1;

  quint16 id = SsnRx::getQuint16(block, 4);
  quint16 revision = id >> 13;
  quint16 blockNumber = id & 0x1FFF;

  addToOutput(QString("[Received SBF message %1 of length %2 (block %3 rev. %4)]")
              .arg(messageCounter++).arg(block.size()).arg(blockNumber).arg(revision));
}

void ConsoleWindow::onSBFCRCError()
{
  addToOutput("[CRC error]");
}

void ConsoleWindow::onNewASCIIDisplay(const QString& asciiDisplay)
{
  addToOutput("[Received ASCII display]");
  if (mASCIIDisplay == 0)
  {
    mASCIIDisplay = new QTextEdit;
    mASCIIDisplay->setReadOnly(true);
    mASCIIDisplay->setWordWrapMode(QTextOption::NoWrap);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    mASCIIDisplay->setFont(font);
    mASCIIDisplay->resize(650,650);
  }
  mASCIIDisplay->setVisible(true);
  mASCIIDisplay->setText(asciiDisplay);
}

void ConsoleWindow::onNewEvent(const QString& event)
{
  addToOutput(QString("[Received event: %1]").arg(event));
}

void ConsoleWindow::onSentASCIICommand(const QString& command)
{
  addToOutput(QString("[Sent ASCII command: %1]").arg(command));
}
