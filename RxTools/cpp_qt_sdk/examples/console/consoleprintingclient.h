/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#ifndef CONSOLEPRINTINGCLIENT_H
#define CONSOLEPRINTINGCLIENT_H

#include <QObject>

#include "ssnrx.h"

/**
 * @brief The ConsolePrintingClient class is an example SsnRx client displaying its output on the text console.
 *
 * It displays messages on the textual console representing the communication with the receiver.
 * This class defines a range of slots that are connected to the correponding signals
 * defined in SsnRx, and that display the corresponding information to the user.
 */

class ConsolePrintingClient : public QObject
{
  Q_OBJECT
public:

  /**
   * @brief Constructor
   *
   * @param rx  SsnRx instance
   * @param parent parent QObject
   */
  explicit ConsolePrintingClient(SSN::SsnRx* rx, QObject* parent = 0);
  
private slots:

    /**
   * @brief Slot called when the SsnRx object enters the connected state.
   *
   * A message is displayed in the console.
   */
  void onConnected();

  /**
   * @brief Slot called when the SsnRx object reports a communication error.
   *
   * A message is displayed in the console.
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
   * @brief Slot called when the SsnRx object reports that a number of received bytes have been discarded.
   *
   * A message is displayed in the console.
   *
   * @param nrOfBytes  the number of discarded bytes
   */
  void onDiscardedBytes(int nrOfBytes);

  /**
   * @brief Slot called when the SsnRx object reports that a prompt has been received.
   *
   * A message is displayed in the console.
   *
   * @param prompt  the prompt
   */
  void onNewPrompt(const QString& prompt);

  /**
   * @brief Slot called when the SsnRx object reports that the connection descriptor has changed.
   *
   * A message is displayed in the console.
   *
   * @param connectionDescriptor  the connection descriptor
   */
  void onNewConnectionDescriptor(const QString& connectionDescriptor);

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
   * @brief Slot called when the SsnRx object reports that a valid SBF block has been received.
   *
   * A message is displayed in the console.
   *
   * @param block  the raw SBF block data
   */
  void onNewSBFBlock(const QByteArray& block);

  /**
   * @brief Slot called when the SsnRx object reports that a CRC error has been detected while processing an SBF block.
   *
   * A message is displayed in the console.
   */
  void onSBFCRCError();

  /**
   * @brief Slot called when the SsnRx object reports that a new ASCII display has been received.
   *
   * A message is displayed in the console.
   *
   * @param asciiDisplay  the contents of the ASCII display
   */
  void onNewASCIIDisplay(const QString& asciiDisplay);

  /**
   * @brief Slot called when the SsnRx object reports that a new event has been received.
   *
   * A message is displayed in the console.
   *
   * @param event  the event string
   */
  void onNewEvent(const QString& event);

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

};

#endif // CONSOLEPRINTINGCLIENT_H
