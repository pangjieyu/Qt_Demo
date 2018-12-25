#include "edge.h"

Edge::Edge()
{

}

Edge::Edge(double x, double dx, int ymax)
    :x(x), dx(dx), ymax(ymax)
{

}

void Edge::setX(double x)
{
    this->x = x;
}

void Edge::setDx(double dx)
{
    this->dx = dx;
}

void Edge::setYmax(int ymax)
{
    this->ymax = ymax;
}

double Edge::getX() const
{
    return x;
}

double Edge::getDx() const
{
    return dx;
}

int Edge::getYmax() const
{
    return ymax;
}
