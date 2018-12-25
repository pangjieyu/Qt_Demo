#include "polygon.h"

Polygon::Polygon(QObject *parent) : QObject(parent)
{

}

Polygon::Polygon(QVector<QPoint> points, QColor color):points(points), color(color) {

}

int Polygon::getMaxX()
{
    int max = 0;
    QVector<QPoint>::iterator iter;
    for (iter=points.begin(); iter!=points.end(); iter++)
        if (iter->x() > max)
            max = iter->x();
    return max;
}

int Polygon::getMinX()
{
    int min = getMaxX();
    QVector<QPoint>::iterator iter;
    for (iter=points.begin(); iter!=points.end(); iter++)
        if (iter->x() < min)
            min = iter->x();
    return min;
}

int Polygon::getMaxY()
{
    int max = 0;
    QVector<QPoint>::iterator iter;
    for (iter=points.begin(); iter!=points.end(); iter++)
        if (iter->y() > max)
            max = iter->y();
    return max;
}

int Polygon::getMinY()
{
    int min = getMaxY();
    QVector<QPoint>::iterator iterPos;
    for (iterPos=points.begin(); iterPos!=points.end(); iterPos++)
        if (iterPos->y() < min)
            min = iterPos->y();
    return min;
}

void Polygon::show(QPainter &ptr) {
  /************************************************************/
  //多边形填充有序边表法
 /* if(points.size()<3) {
      if(points.size() == 2) {
          ptr.drawLine(points[0],points[1]);
        }
      return;
    }
      int i=0, j=0;
      int x0=0, x1=0, y=0, tx=0;

      int scanLines;//扫描线数量
      int min;//最低扫描线号
      int max;//最高扫描线号

      QVector<QList<Edge>> ET;//边表
      QList<Edge> AET;//活化边表
      QVector<double> arr;//扫描线与各边交点表

      QPoint p0;//边的起点
      QPoint p1;//边的终点
      QPoint temp;//保存位置变量
      Edge* pNode;//边结点指针

      QList<Edge>::iterator iterEdge;//边链表迭代器

      min = getMinY();
      max = getMaxY();
      scanLines = max - min;

      //建立边表ET
      ET.resize(scanLines);
      //逐边进行处理，将每一条边的信息插入到ET中
      for(i=0; i<points.size(); i++)
      {
          if(i < points.size()-1)
          {
              p0 = points[i];
              p1 = points[i+1];
          }
          else
          {
              p0 = points[i];
              p1 = points[0];
          }

          if(p0.y()>p1.y())//将p0设为边的起点坐标，y坐标较小
          {
              temp = p0;
              p0 = p1;
              p1 = temp;
          }

          if(p0.y() != p1.y())//非水平边
          {
              pNode = new Edge;
              pNode->setX(static_cast<double>(p0.x()));
              pNode->setDx(static_cast<double>(p1.x()-p0.x())/(p1.y()-p0.y()));
              pNode->setYmax(p1.y()-1);//下闭上开
              ET[p0.y()-min].append(*pNode);
          }
      }//所有边都已插入到ET中

      for (i=0; i<scanLines; i++)// 开始扫描，各边依次加入到AET中
      {
          y = i + min;//当前扫描线y坐标
          if(!ET[i].isEmpty())//有边加入AET
          {
              for(iterEdge=ET[i].begin(); iterEdge!=ET[i].end(); iterEdge++)
                  AET.append(*iterEdge);
          }
          ET[i].clear();//边结点已取出加入AET，无需保留

          //处理活化边表AET
          if(!AET.isEmpty())//首先删除扫描线以下的边
          {
              for(iterEdge=AET.begin(); iterEdge!=AET.end(); iterEdge++)
              {
                  if(iterEdge->getYmax()<y){
                      AET.erase(iterEdge);
                      iterEdge=AET.begin();
                 }
              }
          }

          if(!AET.isEmpty())//活化边表非空，求出交点，排序，画线
          {
              for(iterEdge=AET.begin(); iterEdge!=AET.end(); iterEdge++)
              {
                  arr.append(iterEdge->getX());//取出所有交点
                  iterEdge->setX(iterEdge->getX() + iterEdge->getDx());
              }
              std::sort(arr.begin(), arr.end());//交点排序
              for(j=0; j<arr.size(); j++)
              {
                  if(j%2 == 0)
                  {
                      tx = static_cast<int>(arr[j]);// 左边交点向右取整
                      if(arr[j]-tx)
                          x0 = tx + 1;
                      else
                          x0 = tx;
                      x1 = static_cast<int>(arr[j + 1]);// 右边交点向左取整
                  }
                  ptr.save();
                  ptr.setPen(color);
                  ptr.drawLine(QPoint(x0, y),QPoint(x1, y));
                  ptr.restore();
              }
              arr.clear();
          }
      }//所有扫描线处理完毕
      ET.clear();*/
  /************************************************************/
  /************************************************************/
      //边标志填充法
  if(points.size()<3){
      if(points.size() == 2) {
          ptr.drawLine(points[0],points[1]);
        }
      return;
    }
      ptr.save();
      ptr.setPen(color);

      //获取多边形最小包围盒
      int minx, maxx, miny, maxy;
      minx = getMinX();
      maxx = getMaxX();
      miny = getMinY();
      maxy = getMaxY();

      //设置一个标志矩阵
      int m = maxy - miny;
      int n = maxx - minx;
      bool MF[m][n];
      int i,j;
      for(i=0; i<m; i++)
          for(j=0; j<n; j++)
              MF[i][j] = false;

      //对于多边形每一条边，从这条边向右直到包围盒右边界进行扫描
      QPoint p0, p1, temp;
      double dx, tx;
      int x;
      int k;
      int vertics = points.size();

      for(k=0; k<vertics; k++)
      {
          //获取一条边p0p1
          if(k == vertics-1)
          {
              p0 = points[k];
              p1 = points[0];
          }
          else
          {
              p0 = points[k];
              p1 = points[k+1];
          }

          if(p0.y()>p1.y())//将p0设为边的起点坐标，y坐标较小
          {
              temp = p0;
              p0 = p1;
              p1 = temp;
          }

          //对于一条边，从左至右对标志位求反
          if(p0.y() != p1.y())//非水平边
          {
              dx =static_cast<double>(p1.x()-p0.x())/(p1.y()-p0.y());
              //对于一条边，y每次递增1,x每次递增dx
              x = p0.x();
              tx = x;
              for(i=p0.y(); i<p1.y(); i++)
              {
                  x = static_cast<int>(tx);
                  for(j=x; j<maxx; j++)
                      MF[i-miny][j-minx] = !MF[i-miny][j-minx];
                  tx = tx+dx;
              }
          }
      }
      //对整个包围盒扫描，为true，用前景色绘制
      for(i=0; i<m; i++)
          for(j=0; j<n; j++)
              if(MF[i][j])
                  ptr.drawPoint(j+minx, i+miny);
      ptr.restore();
  /************************************************************/




}
