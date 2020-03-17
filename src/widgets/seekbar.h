#ifndef SEEKBAR_H
#define SEEKBAR_H

#include <QMouseEvent>
#include <QPaintEvent>
#include <QList>

#include "customslider.h"
#include "mpvHandler.h"

class SeekBar : public CustomSlider
{
    Q_OBJECT
public:
    explicit SeekBar(QWidget *parent = 0);

public slots:
    void setTracking(MpvHandler *_mpv, int _totalTime);
    void setTicks(QList<int> values);

protected:
    QString formatTrackingTime(int _time);

    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QList<int> ticks;
    bool tickReady;
    int totalTime;
    int seekTime;
    MpvHandler *mpv;
};

#endif // SEEKBAR_H
