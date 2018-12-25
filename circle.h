#ifndef CIRCLE_H
#define CIRCLE_H
#include <QPoint>
#include <QPainter>
#include <QColor>


class Circle
{
private:
  QPoint p0;
  int r;
  QColor color;
  void draw8th(QPoint p, QPainter &ptr);
public:
  Circle();
  Circle(QPoint p0, int r, QColor color);
  void showCircle(QPainter &ptr);
};

#endif // CIRCLE_H
