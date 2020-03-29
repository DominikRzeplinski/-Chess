#include "FigureRook.h"
#include "QtMath"
FigureRook::FigureRook(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if (side)
    m_image.load(":/File_Chess_rdt45.svg");
  else
    m_image.load(":/File_Chess_rlt45.svg");

  m_stopOnOtherFigure = true;
}

bool FigureRook::ValidatePosition(int PositionX, int PositionY)
{
  if (m_positionX == PositionX || m_positionY == PositionY)
    return true;
  return false;
}

bool FigureRook::ValidateStrikePosition(int PositionX, int PositionY)
{
  return ValidatePosition(PositionX,PositionY);
}
