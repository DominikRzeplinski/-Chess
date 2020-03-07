#include "FigureBase.h"

FigureBase::FigureBase(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  PositionX =0;
  PositionY =0;
}

bool FigureBase::ValidatePosition()
{
  return true;
}

