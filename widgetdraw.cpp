#include "widgetdraw.h"

WidgetDraw::WidgetDraw(QWidget *parent) : QWidget(parent)
{
}

void WidgetDraw::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(colorOne);
    painter.drawPolygon(points);
    Circle circle(c,r,Qt::blue);
    circle.showCircle(painter);
//    Polygon polygon(points,colorOne);
//    polygon.show(painter);
    QVector<QPoint> rotatedPoints;
    painter.setBrush(colorTwo);
    painter.drawPoint(QPoint(0,height()));
    rotatePoints(QPoint(0,height()),-3.14159265*45.0/180.0, rotatedPoints);
    painter.drawPolygon(rotatedPoints);

    if(CLIP) {
        painter.save();
        painter.setPen(Qt::black);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(clipRect);
        painter.setBrush(colorTwo);

        QPolygon oldPolygon(points);
        QPolygon newPolygon = polyClip(oldPolygon,clipRect);
        painter.drawPolygon(newPolygon);
        painter.restore();

      }


}

void WidgetDraw::setC(QPoint point) {
  this->c = point;
}

void WidgetDraw::setR(int r) {
  this->r = r;
}

void WidgetDraw::setClip(bool f) {
  this->CLIP = f;
}

void WidgetDraw::setClipRect(QRect rect) {
    this->clipRect = rect;
}

void WidgetDraw::setColorOne(QColor color) {
    this->colorOne = color;
}

void WidgetDraw::setColorTwo(QColor color) {
    this->colorTwo = color;
}

void WidgetDraw::setPoints(QVector<QPoint> points) {
    this->points = points;
}


double WidgetDraw::getAngle(QPoint origin, QPoint start, QPoint end) {
    int aa = (start.y() - origin.y())*(start.y() - origin.y()) + (start.x() - origin.x())*(start.x() - origin.x());
    int bb = (end.y() - origin.y())*(end.y() - origin.y()) + (end.x() - origin.x())*(end.x() - origin.x());
    int cc = (end.y() - start.y())*(end.y() - start.y()) + (end.x() - start.x())*(end.x() - start.x());

    double cosagl = (aa + bb - cc) / (2 * qSqrt(aa)*qSqrt(bb));//使用余弦定理计算角度
    int flag = 1;//角度正负系数，在屏幕坐标系中，顺时针为正，逆时针为负
    if (start.x() == origin.x())//起始边垂直
    {
        flag = (start.y()>origin.y()) ? 1 : -1;//起始边向量方向(origin->start)，下正上负
        flag = (end.x()<start.x()) ? flag : -flag;//终点在起始边向量的右边为正左边为负
    }
    else//起始边不垂直
    {
        double k = (start.y() - origin.y()) / (double)(start.x() - origin.x());//起始边斜率
        double t = (end.y() - start.y()) - k*(end.x() - start.x());//终点相对于起始边的位置

        flag = (start.x()>origin.x()) ? 1 : -1;//起始边向量方向，右正左负
        flag = t>0 ? flag : -flag;//终点在起始边向量的右边为正左边为负
    }

    return flag*qAcos(cosagl);

}

void WidgetDraw::rotatePoints(QPoint centerPoint, QPoint p1, QPoint p2, QVector<QPoint> &pointsNew) {
    /**
     * @brief rotatePoints 旋转所有points中的点
     * @param centerPoint 旋转轴
     * @param p1 旋转前的参考点
     * @param p2 旋转后的参考点
     * @param pointsNew 旋转后的点用pointsNew存放
     */
    if(!pointsNew.empty())
        pointsNew.clear();
    double agl = getAngle(centerPoint, p1, p2);//获取偏角
    double R[3][3];//构造旋转矩阵
    R[0][0] = qCos(agl);
    R[0][1] = -qSin(agl);
    R[0][2] = centerPoint.x()*(1 - qCos(agl)) + centerPoint.y()*qSin(agl);
    R[1][0] = qSin(agl);
    R[1][1] = qCos(agl);
    R[1][2] = centerPoint.y()*(1 - qCos(agl)) - centerPoint.x()*qSin(agl);
    R[2][0] = 0;
    R[2][1] = 0;
    R[2][2] = 1;

    for(int i=0; i<points.size(); ++i) {
        pointsNew.append(
                         QPoint(
                                (int)(R[0][0] * points[i].x() + R[0][1] * points[i].y() + R[0][2]),
                                (int)(R[1][0] * points[i].x() + R[1][1] * points[i].y() + R[1][2])
                               )
                        );
    }
}

void WidgetDraw::rotatePoints(QPoint centerPoint, double angle, QVector<QPoint> &pointsNew) {
    /**
     * @brief rotatePoints 旋转函数已知角度用法
     * @param centerPoint 旋转轴
     * @param angle 旋转角度（弧度值，顺时针为正，逆时针为负）
     * @param pointsNew 存放新的点
     */

    if(!pointsNew.empty())
        pointsNew.clear();
    double agl = angle;
    double R[3][3];//构造旋转矩阵
    R[0][0] = qCos(agl);
    R[0][1] = -qSin(agl);
    R[0][2] = centerPoint.x()*(1 - qCos(agl)) + centerPoint.y()*qSin(agl);
    R[1][0] = qSin(agl);
    R[1][1] = qCos(agl);
    R[1][2] = centerPoint.y()*(1 - qCos(agl)) - centerPoint.x()*qSin(agl);
    R[2][0] = 0;
    R[2][1] = 0;
    R[2][2] = 1;

    for(int i=0; i<points.size(); ++i) {
        pointsNew.append(
                         QPoint(
                                (int)(R[0][0] * points[i].x() + R[0][1] * points[i].y() + R[0][2]),
                                (int)(R[1][0] * points[i].x() + R[1][1] * points[i].y() + R[1][2])
                               )
                        );
    }
}

QPolygon WidgetDraw::polyClip(QPolygon poly1, QRect &rect1) {
    /**
     * @brief polyClip    矩形剪裁多边形
     * @param poly1   被剪裁多边形
     * @param rect1   剪裁窗口
     * @return 返回剪裁后的多边形
     */

    int x0, y0, x1, y1;
    QPolygon py0, py1, py2, py3;
    //裁剪左边
    x0 = rect1.x();
    y0 = rect1.y()+rect1.height();
    x1 = rect1.x();
    y1 = rect1.y();
    py0 = edgeClip(poly1, QPoint(x0,y0), QPoint(x1,y1));
    //裁剪下边
    x0 = rect1.x()+rect1.width();
    y0 = rect1.y()+rect1.height();
    x1 = rect1.x();
    y1 = rect1.y()+rect1.height();
    py1 = edgeClip(py0, QPoint(x0,y0), QPoint(x1,y1));
    //裁剪右边
    x0 = rect1.x()+rect1.width();
    y0 = rect1.y();
    x1 = rect1.x()+rect1.width();
    y1 = rect1.y()+rect1.height();
    py2 = edgeClip(py1, QPoint(x0,y0), QPoint(x1,y1));
    //裁剪上边
    x0 = rect1.x();
    y0 = rect1.y();
    x1 = rect1.x()+rect1.width();
    y1 = rect1.y();
    py3 = edgeClip(py2, QPoint(x0,y0), QPoint(x1,y1));
    return py3;
}

QPolygon WidgetDraw::edgeClip(QPolygon poly1, QPoint p0, QPoint p1) {
    QVector<QPoint> v;
    int i;
    int m = poly1.length();
    QPoint s, p;
    QPoint pt;
    s = poly1.point(m-1);
    for(i=0; i<m; i++)
    {
        p = poly1.point(i);
        if(isInsideEdge(p,p0,p1))//点p在边(p0,p1)的内侧
        {
            if(isInsideEdge(s,p0,p1))//情况1
                v.append(p);
            else//情况4
            {
                pt = intersect(s,p,p0,p1);
                v.append(pt);
                v.append(p);
            }
        }
        else if(isInsideEdge(s,p0,p1)){//情况2
            pt = intersect(s,p,p0,p1);
            v.append(pt);
        }//情况3没有输出
        s=p;
    }
    return QPolygon(v);
}

bool WidgetDraw::isInsideEdge(QPoint p, QPoint p0, QPoint p1) {
    if(p0.x()>p1.x())//裁剪边为窗口的下边
    {
        if(p.y()<=p0.y())
            return true;
    }
    else if(p0.x()<p1.x())//裁剪边为窗口的上边
    {
        if(p.y()>=p0.y())
            return true;
    }
    else if(p0.y()<p1.y())//裁减边为窗口的右边
    {
        if(p.x()<=p0.x())
            return true;
    }
    else if(p0.y()>p1.y())//裁减边为窗口的左边
    {
        if(p.x()>=p0.x())
            return true;
    }
    return false;
}

QPoint WidgetDraw::intersect(QPoint s, QPoint p, QPoint p0, QPoint p1) {
    double m;
    int x,y;
    if(p0.y()==p1.y())//水平裁剪边
    {
        m=(double)(p.x()-s.x())/(double)(p.y()-s.y());
        x=s.x()+(int)((p0.y()-s.y())*m);
        y=p0.y();
    }
    else//竖直裁剪边
    {
        m=(double)(p.y()-s.y())/(double)(p.x()-s.x());
        x = p0.x();
        y=s.y()+(int)((p0.x()-s.x())*m);
    }
    return QPoint(x,y);
}
