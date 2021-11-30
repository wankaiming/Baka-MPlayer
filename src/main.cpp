#include "ui/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QString>
#include <QMessageBox>
#include <QProxyStyle>

#include <locale.h>

#if defined(Q_OS_WIN)
#include <windows.h>
#include "psapi.h"
#include <tlhelp32.h>
#endif


class ProxyStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;
    int styleHint(StyleHint hint, const QStyleOption* option = nullptr, const QWidget* widget = nullptr, QStyleHintReturn* returnData = nullptr) const override
    {
        if (hint == QStyle::SH_ToolTip_WakeUpDelay || hint == QStyle::SH_ToolTip_FallAsleepDelay)
            return 0;
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};


int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    FreeConsole();
#endif

    QApplication a(argc, argv);
    QApplication::setStyle(new ProxyStyle(QApplication::style()));

    setlocale(LC_NUMERIC, "C"); // for mpv

    QString exeName = a.applicationFilePath().split("/").last();
    DWORD pid = GetCurrentProcessId();

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    bool bMore = ::Process32First(hProcessSnap, &pe32);
    while(bMore)
    {
        QString strProcessName = QString::fromWCharArray(pe32.szExeFile);
        if(strProcessName == exeName && pe32.th32ProcessID != pid)
        {
            int ID = pe32.th32ProcessID;
            HANDLE hProcess;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ID);
            TerminateProcess(hProcess, 0);
        }
        bMore = ::Process32Next(hProcessSnap, &pe32);
    }


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

}



