#ifndef METERCIFERBLAT_H
#define METERCIFERBLAT_H
#include<QWidget>
#include<QPushButton>
#include<QPainter>
#include<QPaintEvent>
#include<QTime>
#include<QTimer>
#include<kirhgofcount.h>
class MyClock : public QWidget
{
    Q_OBJECT

public:
    MyClock(QWidget *parent = 0);
    qreal k;
protected:
    void paintEvent(QPaintEvent *event);
};
inline MyClock::MyClock(QWidget *parent)
    : QWidget(parent)
{
  resize(150, 150);
}
inline void MyClock::paintEvent(QPaintEvent *)
 {
     static const QPoint minuteHand[3] = {
         QPoint(7, 8),
         QPoint(-7, 8),
         QPoint(0, -70)
     };
     QColor minuteColor(Qt::red);

     QPainter painter(this);//отрисовка
     painter.setRenderHint(QPainter::Antialiasing);
     int side = qMin(width(), height());
     painter.translate(width() / 2, height() / 2);
     painter.scale(side / 200.0, side / 200.0);

     painter.setPen(Qt::NoPen);//поворот стрелки
     painter.setBrush(minuteColor);
     painter.save();
     if(k>90)painter.rotate(90);
     else if(k<-90)painter.rotate(-90);
     else painter.rotate(k);
     painter.drawConvexPolygon(minuteHand, 3);
     painter.restore();
     painter.setPen(minuteColor);

          for (int j = 0; j < 30; ++j) {
              painter.drawLine(92, 0, 96, 0);
              painter.rotate(-6.0);
          }
      }
#endif // METERCIFERBLAT_H

