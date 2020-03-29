#include "FigureRook.h"
#include "QtMath"
FigureRook::FigureRook(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if (side)
    image.load(":/File_Chess_rdt45.svg");
  else
    image.load(":/File_Chess_rlt45.svg");

  stopOnOtherFigure = true;
}

bool FigureRook::validatePosition(int PositionX, int PositionY)
{
  if (positionX == PositionX || positionY == PositionY)
    return true;
  return false;
}

bool FigureRook::validateStrikePosition(int PositionX, int PositionY)
{
  return validatePosition(PositionX,PositionY);
}
