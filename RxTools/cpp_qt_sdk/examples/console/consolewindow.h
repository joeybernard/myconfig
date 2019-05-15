/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/


#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include "ssnrx.h"

/**
 * @brief The ConsoleWindow class is an example SsnRx client that offers a simple GUI window to interact with a receiver.
 *
 * On one hand, the user can type in ASCII commands in a command-line widget. Pressing enter causes the
 * command to be sent to the receiver.
 * On the other hand, this class defines a range of slots that are connected to the correponding signals
 * defined in SsnRx, and that display the corresponding information to the user.
 */
class ConsoleWindow : public QMainWindow
{
  Q_OBJECT
public:

  /**
   * @brief Constructor
   *
   * @param rx  SsnRx instance
   * @param parent parent QObject
   */
  explicit ConsoleWindow(SSN::SsnRx* rx, QWidget * parent = 0);

  /**
   * @brief Destructor.
   */
  ~ConsoleWindow();
  
private slots:

  /**
   * @brief Slot called when the return key is pressed in the command line widget.
   *
   * Triggers the typed-in command to be sent to the receiver.
   */
  void onReturnPressed();

  /**
   * @brief Slot called when the SsnRx object enters the connected state.
   *
   * A message is displayed in the console area.
   */
  void onConnected();

  /**
   * @brief Slot called when the SsnRx object reports a communication error.
   *
   * A message is displayed in the console area.
   *
   * @param errorString textual representation of the error
   */
  void onCommunicationError(QString errorString);

  /**
   * @brief Slot called when the SsnRx object enters the disconnected state.
   *
   * A message is displayed in the console area.
   */
  void onConnectionClosed();

  /**
   * @brief Slot called when the SsnRx object reports that a number of received bytes have been discarded.
   *
   * A message is displayed in the console area.
   *
   * @param nrOfBytes  the number of discarded bytes
   */
  void onDiscardedBytes(int nrOfBytes);

  /**
   * @brief Slot called when the SsnRx object reports that a prompt has been received.
   *
   * A message is displayed in the console area.
   *
   * @param prompt  the prompt
   */
  void onNewPrompt(const QString& prompt);

  /**
   * @brief Slot called when the SsnRx object reports that the connection descriptor has changed.
   *
   * A message is displayed in the console area.
   *
   * @param connectionDescriptor  the connection descriptor
   */
  void onNewConnectionDescriptor(const QString& connectionDescriptor);

  /**
   * @brief Slot called when the SsnRx object reports that a command reply has been received.
   *
   * A message is displayed in the console area.
   *
   * @param reply  the reply
   * @param error  flag indicating whether the command has triggered an error
   */
  void onNewCommandReply(const QString& reply, bool error);

  /**
   * @brief Slot called when the SsnRx object reports that 'STOP>' has been received.
   *
   * A message is displayed in the console area.
   */
  void onStopReceived();

  /**
   * @brief Slot called when the SsnRx object reports that a new formated information block has been received.
   *
   * A message is displayed in the console area, together with the contents of the block.
   *
   * @param contents  contents of the block
   * @param index     index of the block
   * @param count     total number of blocks to be received
   */
  void onNewFormattedInformationBlock(const QString& contents, int index, int count);

  /**
   * @brief Slot called when the SsnRx object reports that a valid SBF block has been received.
   *
   * A message is displayed in the console area.
   *
   * @param block  the raw SBF block data
   */
  void onNewSBFBlock(const QByteArray& block);

  /**
   * @brief Slot called when the SsnRx object reports that a CRC error has been detected while processing an SBF block.
   *
   * A message is displayed in the console area.
   */
  void onSBFCRCError();

  /**
   * @brief Slot called when the SsnRx object reports that a new ASCII display has been received.
   *
   * A message is displayed in the console area, and the ASCII display contents are shown in a separate window.
   *
   * @param asciiDisplay  the contents of the ASCII display
   */
  void onNewASCIIDisplay(const QString& asciiDisplay);

  /**
   * @brief Slot called when the SsnRx object reports that a new event has been received.
   *
   * A message is displayed in the console area.
   *
   * @param event  the event string
   */
  void onNewEvent(const QString& event);

  /**
   * @brief Slot called when the SsnRx object reports that an ASCII command has been sent to the receiver.
   *
   * A message is displayed in the console area.
   *
   * @param command the command that is sent
   */
  void onSentASCIICommand(const QString& command);


private:

  /**
   * @brief Adds the given text to the console area.
   *
   * @param text  text to add
   */
  void addToOutput(QString text);

  SSN::SsnRx* mRx; ///< the receiver

  QLineEdit* mCommandLine; ///< single line edit in which commands can be entered
  QTextEdit* mOutput; ///< text area in which the receiver output is displaye
  QTextEdit* mASCIIDisplay; ///< text area in a separate window displaying the ASCII display
};

#endif // CONSOLEWINDOW_H
