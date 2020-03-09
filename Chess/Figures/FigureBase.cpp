#include "FigureBase.h"

FigureBase::FigureBase(bool side,int x, int y, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  LeftSide = side;
  PositionX =x;
  PositionY =y;
}


