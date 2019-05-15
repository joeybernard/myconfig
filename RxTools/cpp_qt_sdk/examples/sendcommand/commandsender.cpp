/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#include "commandsender.h"

#include <iostream>

using namespace SSN;

CommandSender::CommandSender(SsnRx *rx, QString command, QObject* parent) :
  QObject(parent), mRx(rx), mCommand(command)
{
  mSendAlreadyCalled = false;
  mSendAlreadyCalledOnSsnRx = false;

  // connect the relevant signals that are emitted by the SsnRx object to the corresponing slots
  // of this CommandSender object
  connect(rx, SIGNAL(connected()), this, SLOT(onConnected()));
  connect(rx, SIGNAL(communicationError(QString)), this, SLOT(onCommunicationError(QString)));
  connect(rx, SIGNAL(connectionClosed()), this, SLOT(onConnectionClosed()));
  connect(rx, SIGNAL(newCommandReply(const QString&, bool)), this, SLOT(onNewCommandReply(const QString&, bool)));
  connect(rx, SIGNAL(stopReceived()), this, SLOT(onStopReceived()));
  connect(rx, SIGNAL(newFormattedInformationBlock(const QString&, int, int)), this, SLOT(onNewFormattedInformationBlock(const QString&,int,int)));
  connect(rx, SIGNAL(sentASCIICommand(const QString&)), this, SLOT(onSentASCIICommand(const QString&)));
}

void CommandSender::send()
{
  if (mSendAlreadyCalled)
  {
    // the purpose of this class is to send a given command once
      std::cout << "Duplicate call of CommandSender::send()!" << std::endl;
  }
  else
  {
    mSendAlreadyCalled = true;
    if (mRx->isConnected())
    {
      // immediately pass the command to the SsnRx instance
      mRx->sendASCIICommand(mCommand);
      mSendAlreadyCalledOnSsnRx = true;
    }
    // else the command will be sent when the SsnRx goes to the connected state
    // see onConnected()
  }
}

void CommandSender::onConnected()
{
  if (mSendAlreadyCalled && !mSendAlreadyCalledOnSsnRx)
  {
    // when send() was called, the SsnRx was not yet in connected state, and
    // passign the command was postponed.

    // now the SsnRx went to connected state, and we can pass the command
    mRx->sendASCIICommand(mCommand);
    mSendAlreadyCalledOnSsnRx = true;
  }
}

void CommandSender::onCommunicationError(QString errorString)
{
  std::cout << "Communication error: " << qPrintable(errorString) << std::endl;
  // all communication errors are considered fatal
  deleteLater();
}

void CommandSender::onConnectionClosed()
{
  std::cout << "Connection closed" << std::endl;
  deleteLater();
}

void CommandSender::onNewCommandReply(const QString& reply, bool error)
{
  if (error)
  {
    std::cout << "Command failed" << std::endl;
  }
  else
  {
    std::cout << "Command successful" << std::endl;
  }
  std::cout << "Reply: " << std::endl << qPrintable(reply) << std::endl;
  deleteLater();
  // TODO if the command was a list command, or otherwise is to be followed
  // by formatted information blocks, these should still be processed

}

void CommandSender::onStopReceived()
{
  std::cout << "Received 'STOP>'" << std::endl;
  deleteLater();
}

void CommandSender::onNewFormattedInformationBlock(const QString& contents, int index, int count)
{
  std::cout << "Received formatted information block (" << index << " of " << count << "):" << std::endl;
  std::cout << qPrintable(contents) << std::endl;
}

void CommandSender::onSentASCIICommand(const QString& command)
{
  std::cout << "Command sent to receiver: " << qPrintable(command) << std::endl;
}
