#include "FigureKnightBishop.h"
#include "QtMath"

FigureKnightBishop::FigureKnightBishop(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if (side)
    image.load(":/File_Chess_pdt45.svg");
  else
    image.load(":/File_Chess_plt45.svg");
  stopOnOtherFigure = true;
}

bool FigureKnightBishop::validatePosition(int PositionX, int PositionY)
{
  if (qFabs(positionX - PositionX) == qFabs(positionY - PositionY))
    return true;

  if ((qFabs(positionX - PositionX) + qFabs(positionY - PositionY))== 3 && qFabs(positionX - PositionX) > 0 && qFabs(positionY - PositionY)>0)
    return true;

  return false ;
}

bool FigureKnightBishop::validateStrikePosition(int PositionX, int PositionY)
{
  return validatePosition(PositionX,PositionY);
}

