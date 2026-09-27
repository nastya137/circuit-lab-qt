#ifndef REOSTAT_H
#define REOSTAT_H
#include<QPainter>
#include<QPaintEvent>
#include <QWheelEvent>
#include<QPushButton>
#include<QLabel>
#include<QPixmap>
#include<QTimer>
#include<QTime>
#include<kirhgofcount.h>
class reostat : public QWidget
{
    Q_OBJECT

public:
    reostat(QWidget *parent = 0);
    QPixmap pic;
    int numDegrees;
    double k;
    void paintEvent(QPaintEvent*);
   // void wheelEvent(QWheelEvent*);
};
inline reostat::reostat(QWidget *parent)
    : QWidget(parent)
{
  numDegrees=0;
  k=0;
  pic.load(":/startmenu/reostat.png");
}
inline void reostat::paintEvent(QPaintEvent *)
 {
     int side = qMin(width(), height());

     QPainter painter(this);//отрисовка
     painter.setRenderHint(QPainter::Antialiasing);
     painter.translate(width() /2, height()/2);
     painter.scale(side / 200.0, side / 200.0);
     QPointF center(pic.width() / 2, pic.height() / 2);
     painter.rotate(-135);
     painter.rotate(numDegrees);
     painter.drawPixmap(-center, pic);
     this->update();

}

#endif // REOSTAT_H

