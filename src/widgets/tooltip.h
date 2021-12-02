#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QDialog>

class QLabel;
class Tooltip : public QDialog
{
    Q_OBJECT     //这个宏必须要声明

public:
    //通过它获取self指针,这个函数是静态调用,不需要创建对象就可以访问
    static Tooltip *getInstance();

    Tooltip(QWidget *parent = nullptr);
    ~Tooltip();

    void setText(const QString &text);
    static void popup(QPoint pos, const QString &text);
    static void hide();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    static Tooltip *self; //静态指针
    QLabel *label_;
};

#endif // TOOLTIP_H
