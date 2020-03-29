#include "FigureView.h"
#include "QCursor"
#include "QGraphicsSceneDragDropEvent"

FigureView::FigureView(FigureBase* figure,QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  figureBase = figure;
  setPixmap(QPixmap::fromImage(figureBase->image));
  setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
}


void FigureView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (!figureBase->canSelect())
    return;
  m_translatePoint = mapToScene(event->pos()) - pos();
  setZValue(1);
  setCursor(Qt::ClosedHandCursor);
  emit figureSelected(figureBase->positionX,figureBase->positionY);
  emit figurePromotionSelected(figureBase->positionX,figureBase->positionY);
}

void FigureView::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
  if (!figureBase->canSelect())
    return;
  setZValue(0);
  setCursor(Qt::OpenHandCursor);
  emit figureDeselected();
  if (!figureBase->canMove())
    return;
  emit figureMoved(figureBase->positionX,figureBase->positionY);
}

void FigureView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (!figureBase->canSelect())
    return;
  if (!figureBase->canMove())
    return;
  setPos(mapToScene(event->pos()) - m_translatePoint);
}
