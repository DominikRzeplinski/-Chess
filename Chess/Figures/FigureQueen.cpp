#include "FigureQueen.h"
#include "QtMath"

FigureQueen::FigureQueen(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if (side)
    image.load(":/Chess_qdt45.svg");
  else
    image.load(":/Chess_qlt45.svg");
  stopOnOtherFigure = true;
}

bool FigureQueen::validatePosition(int PositionX, int PositionY)
{
  if (qFabs(positionX - PositionX) == qFabs(positionY - PositionY))
    return true;

  if (positionX == PositionX || positionY == PositionY)
    return true;

  return false;
}

bool FigureQueen::validateStrikePosition(int PositionX, int PositionY)
{
  return validatePosition(PositionX,PositionY);
}
