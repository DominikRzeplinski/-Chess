#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H
#include "QGraphicsPixmapItem"
#include "QEvent"
#include "QObject"
#include "FigureBase.h"

class FigureView: public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  FigureView(FigureBase* figure = 0,QGraphicsItem *parent = 0);
  FigureBase* figureBase;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  QPointF m_translatePoint;
signals:
  void figurePromotionSelected(int positionX, int positionY);
  void figureSelected(int positionX, int positionY);
  void figureDeselected();
  void figureMoved(int positionX, int positionY);
};

#endif // FIGUREVIEW_H
