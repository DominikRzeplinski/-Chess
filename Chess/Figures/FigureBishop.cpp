#include "FigureBishop.h"
#include "QtMath"

FigureBishop::FigureBishop(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if (side)
    image.load(":/File_Chess_bdt45.svg");
  else
    image.load(":/File_Chess_blt45.svg");
  stopOnOtherFigure = true;
}

bool FigureBishop::validatePosition(int positionX, int positionY)
{
  if (qFabs(this->positionX - positionX) == qFabs(this->positionY - positionY))
    return true;

  return false ;
}

bool FigureBishop::validateStrikePosition(int PositionX, int PositionY)
{
  return validatePosition(PositionX,PositionY);
}
