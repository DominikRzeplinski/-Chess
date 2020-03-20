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
  PositionX =x;
  PositionY =y;
}

void FigureBase::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::ClosedHandCursor);
}

void FigureBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}

void FigureBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(event->pos());
}
