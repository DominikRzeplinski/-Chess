#include "FigureBase.h"

bool FigureBase::m_leftSideTurn = true;

FigureBase::FigureBase(bool side,FigureType type, int x, int y)
{
  m_leftSide = side;
  m_positionX =x;
  m_positionY =y;
  m_type = type;
  m_firstMove = true;
}

void FigureBase::setPosition(int PosX, int PosY)
{
  m_positionX = PosX;
  m_positionY = PosY;
  m_firstMove = false;
}

bool FigureBase::canSelect()
{

  if (m_leftSideTurn != m_leftSide)
    {
    return false;
    }
  if (m_type == FigureType::Killed)
    return false;
  return true;
}

bool FigureBase::canMove()
{
  if (m_type != FigureType::Alive)
    return false;
  return true;
}
