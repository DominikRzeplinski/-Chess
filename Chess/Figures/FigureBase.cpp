#include "FigureBase.h"

bool FigureBase::leftSideTurn = true;

FigureBase::FigureBase(bool side,FigureType type, int x, int y)
{
  leftSide = side;
  positionX =x;
  positionY =y;
  type = type;
  firstMove = true;
}

void FigureBase::setPosition(int PosX, int PosY)
{
  positionX = PosX;
  positionY = PosY;
  firstMove = false;
}

bool FigureBase::canSelect()
{

  if (leftSideTurn != leftSide)
    {
      return false;
    }
  if (type == FigureType::Killed)
    return false;
  return true;
}

bool FigureBase::canMove()
{
  if (type != FigureType::Alive)
    return false;
  return true;
}
