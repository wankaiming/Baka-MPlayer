#include "ui/mainwindow.h"
#include "singleapplication.h"

#include <QLocale>
#include <QString>

#include <locale.h>

#if defined(Q_OS_WIN)
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    FreeConsole();
#endif
    /*
    QApplication a(argc, argv);
    setlocale(LC_NUMERIC, "C"); // for mpv

    MainWindow w;
    w.show();

    // parse command line
    QStringList args = QApplication::arguments();
    QStringList::iterator arg = args.begin();
    if(++arg != args.end())
        w.Load(*arg);
    else
        w.Load();

    return a.exec();
    */

    //单实例进程，或者说防止程序多开
    SingleApplication a(argc, argv);

    if (!a.isRunning())
    {
        MainWindow w;
        a.mainWindow = &w;
        w.show();

        // parse command line
        QStringList args = SingleApplication::arguments();
        QStringList::iterator arg = args.begin();
        if(++arg != args.end())
            w.Load(*arg);
        else
            w.Load();

        return a.exec();
    }
    return 0;
}
