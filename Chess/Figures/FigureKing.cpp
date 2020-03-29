#include "FigureKing.h"
#include "QtMath"

FigureKing::FigureKing(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if (side)
    image.load(":/Chess_kdt45.svg");
  else
    image.load(":/Chess_klt45.svg");
  stopOnOtherFigure = true;
}

bool FigureKing::validatePosition(int PositionX, int PositionY)
{
  if (qFabs(positionX - PositionX) <= 1 && qFabs(positionY - PositionY)<=1)
    return true;
  return false;
}

bool FigureKing::validateStrikePosition(int PositionX, int PositionY)
{
  return validatePosition(PositionX,PositionY);
}
