#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QObject>
#include "ui/mainwindow.h"

class QWidget;
class QLocalServer;

class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    SingleApplication(int &argc, char **argv);
    bool isRunning();
    MainWindow *mainWindow;

private slots:
    void newLocalConnection();

private:
    void initLocalConnection();
    void newLocalServer();
    bool bRunning; 
    QLocalServer *localServer;
    QString serverName;
};

#endif // SINGLEAPPLICATION_H
