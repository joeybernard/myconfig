/*
   GNSS Receiver Communication SDK for C++ and Qt
   For connecting to and communicating with a Septentrio GNSS receiver, using C++/Qt

   \par Copyright:
     (c) 2012-2015 Copyright Septentrio NV/SA. All rights reserved.
*/

#include <iostream>
#include <QCoreApplication>
#include <QStringList>
#include "ssnrx.h"
#include "commandsender.h"

/**
 * @brief Displays instructions on how to invoke this application.
 */
void printHelp()
{
  std::cout << "Usage: sendcommand [--help] [--method=<serial or tcp>] [settings] [--command=<command>]" << std::endl;
  std::cout << std::endl;
#if defined(Q_OS_WIN)
  std::cout << "Example: sendcommand --method=serial --port=COM3 --set=9600,8,N,1 --command=\"exeResetReceiver,hard,all\"" << std::endl;
#else
  std::cout << "Example: sendcommand --method=serial --port=/dev/ttyS0 --set=9600,8,N,1 --command=\"exeResetReceiver,hard,all\"" << std::endl;
#endif
  std::cout << "Example: sendcommand --method=tcp --host=123.456.789.012 --port=28784 --command=\"exeResetReceiver,hard,all\"" << std::endl;
}

/**
 * @brief Main function
 *
 * @param argc  number of arguments
 * @param argv  arguments
 */
int main(int argc, char *argv[])
{
  using SSN::SsnRx;

  QCoreApplication app(argc, argv); // provides the event loop for the application

  // preprocess arguments
  // store arguments and their values in a hash
  // arguments are of the form <key>=<value> or <key>
  QHash<QString, QString> argHash;
  foreach (const QString& arg, app.arguments())
  {
    QString key, value;
    switch (arg.count('='))
    {
    case 0:
      key = arg;
      break;
    case 1:
      key = arg.split('=').at(0);
      value = arg.split('=').at(1);
      break;
    default:
      printHelp();
      return 0;
    }
    argHash.insert(key, value);
  }

  std::cout << "SsnRx send command example" << std::endl;
  std::cout << std::endl;

  SsnRx* rx = new SsnRx();

  // initiate connection based on arguments
  QString method = argHash.value("--method");
  if (method == "serial")
  {
#if defined(Q_OS_WIN)
    QString serialPortName = argHash.value("--port", "COM1");
#else
    QString serialPortName = argHash.value("--port", "/dev/ttyS0");
#endif
    QString serialPortSettings = argHash.value("--set", "115200,8,n,1");

    if (!rx->connectSerial(serialPortName, serialPortSettings))
    {
      qFatal("Cannot open serial port %s. Exiting..", qPrintable(serialPortName));
    }
  }
  else if (method == "tcp")
  {
    QString tcpHostName = argHash.value("--host");
    bool ok;
    int p = argHash.value("--port", "28784").toInt(&ok);
    if (tcpHostName.isEmpty() || !ok || p < 0)
    {
      printHelp();
      return 0;
    }
    rx->connectTcp(tcpHostName, quint16(p));
  }
  else
  {
    printHelp();
    return 0;
  }

  QString command = argHash.value("--command");
  if (command.isEmpty())
  {
    printHelp();
    return 0;
  }

  CommandSender* cs = new CommandSender(rx, command);
  // cs will delete itself upon completion/failure
  QObject::connect(cs, SIGNAL(destroyed()), &app, SLOT(quit()));
  cs->send();

  // enter main application event loop.
  // All communication is handled in this event loop.
  app.exec();

  // cleanup
  delete rx;
  return 0;
}