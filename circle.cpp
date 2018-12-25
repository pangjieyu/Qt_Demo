#include "circle.h"
Circle::Circle()
{

}

Circle::Circle(QPoint p0, int r, QColor color):p0(p0),r(r),color(color) {

}



void Circle::showCircle(QPainter& ptr) {
  /********************************************/
  //系统函数
  if(r<1) {
          return;
      } else {
          ptr.save();
          ptr.setRenderHint(QPainter::Antialiasing, true);
          ptr.setPen(color);
          ptr.setBrush(Qt::NoBrush);
          ptr.drawEllipse(p0.x()-r, p0.y()-r, r*2, r*2);
          ptr.restore();
      }

  /********************************************/
//中点画圆
  if(r<1) {
      return;
    }
  int x, y;
  int e=1-r;
  x=0;
  y=r;
  while(x<y)
      {
          draw8th(QPoint(x, y), ptr);
          if(e<=0)
              e=e+2*x+3;
          else
              {
                  e=e+2*x-2*y+5;
                  y--;
              }
          x++;
      }

}

void Circle::draw8th(QPoint p, QPainter &ptr) {
      ptr.save();
      ptr.setPen(color);
      ptr.drawPoint(p.x() +p0.x(), p.y()+p0.y());
      ptr.drawPoint(p.y() +p0.x(), p.x()+p0.y());
      ptr.drawPoint(-p.y()+p0.x(), p.x()+p0.y());
      ptr.drawPoint(-p.x()+p0.x(), p.y()+p0.y());
      ptr.drawPoint(p.y() +p0.x(),-p.x()+p0.y());
      ptr.drawPoint(p.x() +p0.x(),-p.y()+p0.y());
      ptr.drawPoint(-p.x()+p0.x(),-p.y()+p0.y());
      ptr.drawPoint(-p.y()+p0.x(),-p.x()+p0.y());
      ptr.restore();
}


