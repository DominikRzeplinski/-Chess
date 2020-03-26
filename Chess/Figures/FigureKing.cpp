#include "FigureKing.h"
#include "QtMath"

FigureKing::FigureKing(bool side,FigureType type,int x, int y,QGraphicsItem *parent):FigureBase(side,type,x,y,parent)
{
  if (side)
  {
    setPixmap(QPixmap(":/Chess_kdt45.svg"));
    m_image.load(":/Chess_kdt45.svg");
  }
  else
  {
    setPixmap(QPixmap(":/Chess_klt45.svg"));
    m_image.load(":/Chess_klt45.svg");
  }
  m_stopOnOtherFigure = true;
}

bool FigureKing::ValidatePosition(int PositionX, int PositionY)
{
  if (qFabs(m_positionX - PositionX) <= 1 && qFabs(m_positionY - PositionY)<=1)
    return true;
  return false;
}

bool FigureKing::ValidateStrikePosition(int PositionX, int PositionY)
{
  return ValidatePosition(PositionX,PositionY);
}
