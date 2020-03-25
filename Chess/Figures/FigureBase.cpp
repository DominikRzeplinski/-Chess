#include "FigureBase.h"
#include "QGraphicsItem"
#include "QGraphicsSceneDragDropEvent"
#include "QDrag"
#include "QCursor"
#include "QMimeData"
#include "QPainter"
#include "QWidget"
#include "QObject"

bool FigureBase::m_leftSideTurn = true;

FigureBase::FigureBase(bool side,int x, int y, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
  m_leftSide = side;
  m_positionX =x;
  m_positionY =y;
  m_firstMove = true;
  m_leftSideTurn = true;
}

void FigureBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (m_leftSideTurn != m_leftSide)
    {
    return;
    }
    m_translatePoint = mapToScene(event->pos()) - pos();
    setZValue(1);
    setCursor(Qt::ClosedHandCursor);
    emit figureSelected(m_positionX,m_positionY);
}

void FigureBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
  if (m_leftSideTurn != m_leftSide)
    {
    return;
    }
    setZValue(0);
    setCursor(Qt::OpenHandCursor);
    emit figureDeselected();
    emit figureMoved(m_positionX,m_positionY);
}

void FigureBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (m_leftSideTurn != m_leftSide)
    {
    return;
    }
    this->setPos(mapToScene(event->pos()) - m_translatePoint);
}
