#include "seekbar.h"

#include <QTime>
#include <QToolTip>
#include <QPainter>
#include <QRect>
#include <QStyle>

#include "util.h"
#include "tooltip.h"

SeekBar::SeekBar(QWidget *parent):
    CustomSlider(parent),
    tickReady(false),
    totalTime(0)
{
    this->installEventFilter(this);
}

void SeekBar::setTracking(int _totalTime)
{
    if(_totalTime != 0)
    {
        totalTime = _totalTime;
        // now that we've got totalTime, calculate the tick locations
        // we need to do this because totalTime is obtained after the LOADED event is fired--we need totalTime for calculations
        for(auto &tick : ticks)
            tick = ((double)tick/totalTime)*maximum();
        if(ticks.length() > 0)
        {
            tickReady = true; // ticks are ready to be displayed
            repaint(rect());
        }
        setMouseTracking(true);
    }
    else
        setMouseTracking(false);
}

void SeekBar::setTicks(QList<int> values)
{
    ticks = values; // just set the values
    tickReady = false; // ticks need to be converted when totalTime is obtained
}

void SeekBar::mouseMoveEvent(QMouseEvent* event)
{
    if(totalTime != 0)
    {
        Tooltip::popup(QPoint(event->globalX()-20, mapToGlobal(rect().topLeft()).y()-30), Util::FormatTime((double)QStyle::sliderValueFromPosition(minimum(), maximum(), event->x(), width())/maximum()*totalTime, totalTime));
    }
    QSlider::mouseMoveEvent(event);
}

void SeekBar::paintEvent(QPaintEvent *event)
{
    CustomSlider::paintEvent(event);
}

bool SeekBar::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this)
    {
        if(event->type() == QEvent::Leave)
        {
            Tooltip::hide();
            return true;
        }
    }
    return CustomSlider::eventFilter(obj, event);
}
