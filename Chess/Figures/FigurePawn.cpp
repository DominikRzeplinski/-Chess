#include "FigurePawn.h"
#include "QtMath"

FigurePawn::FigurePawn(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if(side)
    image.load(":/File_Chess_pdt45.svg");
  else
    image.load(":/File_Chess_plt45.svg");
  stopOnOtherFigure = true;
}

bool FigurePawn::validatePosition(int positionX, int positionY)
{
  if (!moveEnemyDirection(positionX))
    return false;

  if (qFabs(positionX - positionX) == 1 && (positionY == positionY))
    return true;

  if (qFabs(positionX - positionX) == 2 && (positionY == positionY) && firstMove)
    return true;

  return false;
}

bool FigurePawn::validateStrikePosition(int PositionX, int PositionY)
{
  if (!moveEnemyDirection(PositionX))
    return false;
  if (qFabs(positionX - PositionX) == 1 && qFabs(positionY - PositionY) ==1)
    return true;
  return false;
}

bool FigurePawn::moveEnemyDirection(int PositionX)
{
  if (leftSide)
    {
      if (PositionX < positionX)
        return false;
    }
  else
    {
      if (PositionX > positionX)
        return false;
    }
  return true;
}

