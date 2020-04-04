#include "FigureBase.h"

bool FigureBase::leftSideTurn = false;

FigureBase::FigureBase(bool side,FigureType type, int x, int y)
{
  leftSide = side;
  positionX =x;
  positionY =y;
  this->type = type;
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

int FigureBase::getPositionX(){ return positionX;}
int FigureBase::getPositionY(){ return positionY;}
bool FigureBase::isLeftSide() {return leftSide;}
bool FigureBase::isFirstMove(){return firstMove;}
FigureType FigureBase::getType(){return type;}
void FigureBase::setType(FigureType figureType){type =figureType;}
bool FigureBase::getStopOnOtherFigure(){return stopOnOtherFigure;}
QImage FigureBase::getImage(){return image;}
