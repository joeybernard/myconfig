/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include <QObject>

#include "ssnrx.h"

/**
 * @brief The CommandSender class is an example SsnRx client interacting with
 *        the receiver to send a command.
 *
 * Purpose of this example is to illustrate a simple interaction with the
 * receiver. It assumes that this is the only interaction that is going on
 * with the receiver.
 *
 * When done, the object is automatically deleted.
 */
class CommandSender : public QObject
{
  Q_OBJECT

public:

  /**
   * @brief Constructor
   *
   * @param rx  SsnRx instance
   * @param command  command to be send
   * @param parent parent QObject
   */
  explicit CommandSender(SSN::SsnRx* rx, QString command, QObject* parent = 0);

  /**
   * @brief Send the command.
   *
   * If not yet connected, the command will be sent when the connection is established.
   * Notice that this method returns immediately, and that the actual sending
   * of the message is done later.
   */
  void send();
  
private slots:

  /**
   * @brief Slot called when the SsnRx object enters the connected state.
   *
   * This slot is only used if the command was not yet sent because
   * the receiver was not yet connected when send was called.
   */
  void onConnected();

  /**
   * @brief Slot called when the SsnRx object reports a communication error.
   *
   * @param errorString textual representation of the error
   */
  void onCommunicationError(QString errorString);

  /**
   * @brief Slot called when the SsnRx object enters the disconnected state.
   *
   * A message is displayed in the console.
   */
  void onConnectionClosed();

  /**
   * @brief Slot called when the SsnRx object reports that a command reply has been received.
   *
   * A message is displayed in the console.
   *
   * @param reply  the reply
   * @param error  flag indicating whether the command has triggered an error
   */
  void onNewCommandReply(const QString& reply, bool error);

  /**
   * @brief Slot called when the SsnRx object reports that 'STOP>' has been received.
   *
   * A message is displayed in the console.
   */
  void onStopReceived();

  /**
   * @brief Slot called when the SsnRx object reports that a new formated information block has been received.
   *
   * A message is displayed in the console, together with the contents of the block.
   *
   * @param contents  contents of the block
   * @param index     index of the block
   * @param count     total number of blocks to be received
   */
  void onNewFormattedInformationBlock(const QString& contents, int index, int count);


  /**
   * @brief Slot called when the SsnRx object reports that an ASCII command has been sent to the receiver.
   *
   * A message is displayed in the console.
   *
   * @param command the command that is sent
   */
  void onSentASCIICommand(const QString& command);

private:

  SSN::SsnRx* mRx; ///< the receiver
  QString mCommand; ///< the command to be send
  bool mSendAlreadyCalled; ///< flag indicating whether the send method has already been called
  bool mSendAlreadyCalledOnSsnRx; ///< flag indicating whether the send method has already been called on the SsnRx instance

};

#endif // COMMANDSENDER_H
