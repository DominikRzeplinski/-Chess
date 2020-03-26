#include "FigureQueen.h"
#include "QtMath"

FigureQueen::FigureQueen(bool side,FigureType type,int x, int y,QGraphicsItem *parent):FigureBase(side,type,x,y,parent)
{
  if (side)
  {
    setPixmap(QPixmap(":/Chess_qdt45.svg"));
    m_image.load(":/Chess_qdt45.svg");
  }
  else
  {
    setPixmap(QPixmap(":/Chess_qlt45.svg"));
    m_image.load(":/Chess_qlt45.svg");
  }
  m_stopOnOtherFigure = true;
}

bool FigureQueen::ValidatePosition(int PositionX, int PositionY)
{
  if (qFabs(m_positionX - PositionX) == qFabs(m_positionY - PositionY))
    return true;

  if (m_positionX == PositionX || m_positionY == PositionY)
    return true;

  return false;
}

bool FigureQueen::ValidateStrikePosition(int PositionX, int PositionY)
{
  return ValidatePosition(PositionX,PositionY);
}
