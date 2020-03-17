#include "singleapplication.h"
#include "ui/mainwindow.h"
#include "windows.h"

#include <QWidget>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>
#include <QFileInfo>
#include <QLibrary>
#include <QDebug>


SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , bRunning(false)
    , localServer(NULL)
    , mainWindow(NULL)
{
    serverName = QFileInfo(SingleApplication::applicationFilePath()).fileName();
    initLocalConnection();
}

bool SingleApplication::isRunning()
{
    return bRunning;
}

void SingleApplication::newLocalConnection()
{
    QLocalSocket *socket = localServer->nextPendingConnection();
    if (!socket)
        return;
    socket->waitForReadyRead(1000);
    QTextStream stream(socket);

    QString readMsg;
    readMsg = stream.readAll();

    delete socket;
    if (mainWindow != NULL)
    {
        if (mainWindow->isMinimized())
        {
            mainWindow->showNormal();
        }

        ::SetWindowPos(HWND(mainWindow->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ::SetWindowPos(HWND(mainWindow->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		
        mainWindow->show();
        mainWindow->activateWindow();

        mainWindow->playFile(readMsg);
    }
}

void SingleApplication::initLocalConnection()
{
    bRunning = false;
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(500))
    {
        bRunning = true;
		
        QTextStream stream(&socket);
        QStringList args = SingleApplication::arguments();
        if (args.count() > 1)
            stream << args.last();
        else
            stream << QString();
        stream.flush();
        socket.waitForBytesWritten();

        return;
    }

    newLocalServer();
}

void SingleApplication::newLocalServer()
{
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if(!localServer->listen(serverName))
    {
        if(localServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            QLocalServer::removeServer(serverName);
            localServer->listen(serverName);
        }
    }
}
