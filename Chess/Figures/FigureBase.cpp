#include "FigureBase.h"
#include "QGraphicsItem"
#include "QGraphicsSceneDragDropEvent"
#include "QDrag"
#include "QCursor"
#include "QMimeData"
#include "QPainter"
#include "QWidget"
#include "QObject"

FigureBase::FigureBase(bool side,int x, int y, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
  LeftSide = side;
  m_positionX =x;
  m_positionY =y;
}

void FigureBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_translatePoint = mapToScene(event->pos()) - pos();
    setZValue(1);
    setCursor(Qt::ClosedHandCursor);
    emit figureSelected(m_positionX,m_positionY);
}

void FigureBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setZValue(0);
    setCursor(Qt::OpenHandCursor);
    emit figureDeselected();
}

void FigureBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()) - m_translatePoint);
}
