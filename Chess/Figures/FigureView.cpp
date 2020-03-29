#include "FigureView.h"
#include "QCursor"
#include "QGraphicsSceneDragDropEvent"

FigureView::FigureView(FigureBase* figure,QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
  figureBase = figure;
  setPixmap(QPixmap::fromImage(figureBase->m_image));
  setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
}

void FigureView::setPosition(QPointF position, int PosX, int PosY)
{
  setPos(position);
  figureBase->setPosition(PosX,PosY);
}

void FigureView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (!figureBase->canSelect())
    return;
    m_translatePoint = mapToScene(event->pos()) - pos();
    setZValue(1);
    setCursor(Qt::ClosedHandCursor);
    emit figureSelected(figureBase->m_positionX,figureBase->m_positionY);
    emit figurePromotionSelected(figureBase->m_positionX,figureBase->m_positionY);
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
    emit figureMoved(figureBase->m_positionX,figureBase->m_positionY);
}

void FigureView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (!figureBase->canSelect())
    return;
  if (!figureBase->canMove())
    return;
    setPos(mapToScene(event->pos()) - m_translatePoint);
}
