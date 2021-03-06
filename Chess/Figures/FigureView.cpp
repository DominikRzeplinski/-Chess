#include "FigureView.h"
#include "QCursor"
#include "QGraphicsSceneDragDropEvent"

FigureView::FigureView(FigureBase* figure,QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  figureBase = figure;
  setPixmap(QPixmap::fromImage(figureBase->getImage()));
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
  emit figureSelected(figureBase->getPositionX(),figureBase->getPositionY());
  emit figurePromotionSelected(figureBase->getPositionX(),figureBase->getPositionY());
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
  emit figureMoved(figureBase->getPositionX(),figureBase->getPositionY());
}

void FigureView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (!figureBase->canSelect())
    return;
  if (!figureBase->canMove())
    return;
  setPos(mapToScene(event->pos()) - m_translatePoint);
}
