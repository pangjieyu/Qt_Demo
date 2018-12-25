#ifndef WIDGETDRAW_H
#define WIDGETDRAW_H

#include <QWidget>
#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QVector>
#include <QPolygon>
#include <QRect>
#include <QtMath>
#include <polygon.h>
#include <circle.h>


class WidgetDraw : public QWidget
{
    Q_OBJECT
private:
        QVector<QPoint> points;
        int n;
        QColor colorOne, colorTwo;
        //剪裁参数
        QRect clipRect;
        bool CLIP;
        //圆参数
        QPoint c;
        int r;

public:
        int ang;

        explicit WidgetDraw(QWidget *parent = nullptr);

        void paintEvent(QPaintEvent*);

        void setPoints(QVector<QPoint> points);//让mainWindow设置points

        void setColorOne(QColor color);

        void setColorTwo(QColor color);

        double getAngle(QPoint origin, QPoint start, QPoint end); //获取以origin为顶点的角度
        /**
         * @brief rotatePoints 旋转所有points中的点
         * @param centerPoint 旋转轴
         * @param p1 旋转前的参考点
         * @param p2 旋转后的参考点
         * @param pointsNew 旋转后的点用pointsNew存放
         */
        void rotatePoints(QPoint centerPoint, QPoint p1, QPoint p2, QVector<QPoint> &pointsNew);
        /**
         * @brief rotatePoints 旋转函数已知角度用法
         * @param centerPoint 旋转轴
         * @param angle 旋转角度（弧度值，顺时针为正，逆时针为负）
         * @param pointsNew 存放新的点
         */
        void rotatePoints(QPoint centerPoint, double angle, QVector<QPoint> &pointsNew);

        /**
         * @brief polyClip    矩形剪裁多边形
         * @param poly1   被剪裁多边形
         * @param rect1   剪裁窗口
         * @return 返回剪裁后的多边形
         */
        QPolygon polyClip(QPolygon poly1, QRect &rect1);

        QPolygon edgeClip(QPolygon poly1, QPoint p0, QPoint p1);

        bool isInsideEdge(QPoint p, QPoint p0, QPoint p1);

        QPoint intersect(QPoint s, QPoint p, QPoint p0, QPoint p1);

        void setClip(bool);

        void setClipRect(QRect rect);

        //设置圆
        void setC(QPoint point);
        void setR(int r);

signals:

public slots:
};

#endif // WIDGETDRAW_H
