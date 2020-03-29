#include "FigureKnight.h"
#include "QtMath"

FigureKnight::FigureKnight(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if(side)
    image.load(":/File_Chess_ndt45.svg");
  else
    image.load(":/File_Chess_nlt45.svg");
  stopOnOtherFigure = false;
}

bool FigureKnight::validatePosition(int PositionX, int PositionY)
{
  if ((qFabs(positionX - PositionX) + qFabs(positionY - PositionY))== 3 && qFabs(positionX - PositionX) > 0 && qFabs(positionY - PositionY)>0)
    return true;
  return false;
}

bool FigureKnight::validateStrikePosition(int PositionX, int PositionY)
{
  return validatePosition(PositionX,PositionY);
}
