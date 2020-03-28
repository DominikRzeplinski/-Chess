#include "FigureKnight.h"
#include "QtMath"

FigureKnight::FigureKnight(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if(side)
    m_image.load(":/File_Chess_ndt45.svg");
  else
    m_image.load(":/File_Chess_nlt45.svg");
  m_stopOnOtherFigure = false;
}

bool FigureKnight::ValidatePosition(int PositionX, int PositionY)
{
  if ((qFabs(m_positionX - PositionX) + qFabs(m_positionY - PositionY))== 3 && qFabs(m_positionX - PositionX) > 0 && qFabs(m_positionY - PositionY)>0)
    return true;
  return false;
}

bool FigureKnight::ValidateStrikePosition(int PositionX, int PositionY)
{
  return ValidatePosition(PositionX,PositionY);
}
