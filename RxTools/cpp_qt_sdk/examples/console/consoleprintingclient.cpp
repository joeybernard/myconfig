/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#include "consoleprintingclient.h"

#include <iostream>
#include <QStringList>

using namespace SSN;

ConsolePrintingClient::ConsolePrintingClient(SsnRx *rx, QObject* parent) :
  QObject(parent), mRx(rx)
{
  // connect the signals that are emitted by the SsnRx object to the corresponing slots
  // of this ConsolePrintingClient object
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
}

void ConsolePrintingClient::onConnected()
{
  std::cout << "Connected" << std::endl;
  std::cout << "Requesting prompt" << std::endl;
  mRx->sendPromptRequest();
}

void ConsolePrintingClient::onCommunicationError(QString errorString)
{
  std::cout << "Connection error: " << qPrintable(errorString) << std::endl;
}

void ConsolePrintingClient::onConnectionClosed()
{
  std::cout << "Connection closed" << std::endl;
}

void ConsolePrintingClient::onDiscardedBytes(int nrOfBytes)
{
  std::cout << "Discarded " << nrOfBytes << " bytes" << std::endl;
}

void ConsolePrintingClient::onNewPrompt(const QString& prompt)
{
  std::cout << "Received prompt: " << qPrintable(prompt) << std::endl;
}

void ConsolePrintingClient::onNewConnectionDescriptor(const QString& connectionDescriptor)
{
  std::cout << "New connection descriptor: " << qPrintable(connectionDescriptor) << std::endl;

  // when the connection description has been received, we know the receiver's port
  // to which we are connected, and we can command the receiver to output certain
  // SBF messages to that port.
  std::cout << "Requesting EndOfPVT @ 1 Hz over connection + some lif's" << std::endl;
  // ensure that the output of sbf is enabled for the rx port:
  mRx->sendASCIICommand("sdio,stream1,"+connectionDescriptor+",,+sbf");
  // request PVTGeodetic @ 1 Hz
  mRx->sendASCIICommand("sso,stream1,"+connectionDescriptor+", pvtgeodetic, sec1");
  // list identifications
  mRx->sendASCIICommand("lif,identification");
  // list permissions
  mRx->sendASCIICommand("lif,permissions");
}

void ConsolePrintingClient::onNewCommandReply(const QString& reply, bool error)
{
  std::cout << "Received command reply(" << (error ? "error":"success") << "): " << std::endl << qPrintable(reply) << std::endl;
}

void ConsolePrintingClient::onStopReceived()
{
  std::cout << "Received 'STOP>'" << std::endl;
}

void ConsolePrintingClient::onNewFormattedInformationBlock(const QString& contents, int index, int count)
{
  std::cout << "Received formatted information block (" << index << " of " << count << "):" << std::endl;
  std::cout << qPrintable(contents) << std::endl;
}


void ConsolePrintingClient::onNewSBFBlock(const QByteArray& block)
{
  static int messageCounter = 1;
  quint16 id = SsnRx::getQuint16(block, 4);
  quint16 revision = id >> 13;
  quint16 blockNumber = id & 0x1FFF;

  std::cout << "Received SBF message " << messageCounter++ <<
               " of length " << block.size() <<
               " (blocknumber " << blockNumber << " rev. " << revision << ")" << std::endl;
}

void ConsolePrintingClient::onSBFCRCError()
{
  std::cout << "SBF CRC error" << std::endl;
}

void ConsolePrintingClient::onNewASCIIDisplay(const QString& asciiDisplay)
{
  std::cout << "Received Ascii Display, first line: " << std::endl << qPrintable(asciiDisplay.split("\r\n").first()) << std::endl;
}

void ConsolePrintingClient::onNewEvent(const QString& event)
{
  std::cout << "Received event: " << qPrintable(event) << std::endl;
}

void ConsolePrintingClient::onSentASCIICommand(const QString& command)
{
  std::cout << "Sent ASCII command: " << qPrintable(command) << std::endl;
}
