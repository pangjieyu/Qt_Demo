#ifndef POLYGON_H
#define POLYGON_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QtMath>
#include <QVector>
#include <QPainter>
#include <edge.h>
#include <QList>
#include <algorithm>


class Polygon : public QObject
{
  Q_OBJECT

private:
  QVector<QPoint> points;
  int n;
  QColor color;
  int getMaxX();
  int getMinX();
  int getMaxY();
  int getMinY();


public:
  explicit Polygon(QObject *parent = nullptr);
  Polygon(QVector<QPoint> points, QColor color);
  void show(QPainter &ptr);

signals:

public slots:
};

#endif // POLYGON_H
