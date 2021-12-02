#include "tooltip.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMutex>

//这句一定要写,因为self是静态变量,必须要初始化值
Tooltip* Tooltip::self = NULL;

Tooltip *Tooltip::getInstance()
{
    //判断是否是第一次调用
    //假如不为NULL,会直接return
    if (self == NULL) {

        //防止多进程同时调用创建2个对象的问题
        //原理是因为是静态变量只会定义一次
        static QMutex mutex;

        //上锁  QMutexLocker会锁住mutex，当QMutexLocker 被释放的时候会自动解锁
        //locker是局部变量，所以getInstance（）函数结束之后会自动解锁
        QMutexLocker locker(&mutex);

        //在判断一次,防止其它进程抢先new过了
        if (self == NULL) {
            self = new Tooltip(nullptr);
        }
    }

    return self; //返回指针
}

Tooltip::Tooltip(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlag(Qt::Popup);
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setFocusPolicy(Qt::NoFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    label_ = new QLabel(this);
    QHBoxLayout *mLayout = new QHBoxLayout(this);
    mLayout->addWidget(label_);

    this->installEventFilter(this);
    this->setStyleSheet("QWidget { background:white;font-size:12px;padding:2px; }");
}

Tooltip::~Tooltip()
{
}

void Tooltip::setText(const QString &text)
{
    label_->setText(text);
}

bool Tooltip::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == this){
        if (QEvent::WindowDeactivate == e->type() || QEvent::Leave == e->type()){
            Tooltip *t = Tooltip::getInstance();
            t->close();
            e->accept();
            return true;
        }
    }
    return QWidget::eventFilter(obj, e);
}

void Tooltip::popup(QPoint pos, const QString &text)
{
    Tooltip *t = Tooltip::getInstance();
    t->setText(text);
    t->show();
    t->move(pos);
}

void Tooltip::hide()
{
    Tooltip *t = Tooltip::getInstance();
    t->close();
}
