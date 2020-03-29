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
  void setPosition(QPointF position, int PosX, int PosY);
  FigureBase* figureBase;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  bool m_dragOver = false;
  QImage m_image;
  QColor color;
  QPointF m_translatePoint;
signals:
  void figurePromotionSelected(int PositionX, int PositionY);
  void figureSelected(int PositionX, int PositionY);
  void figureDeselected();
  void figureMoved(int PositionX, int PositionY);
};

#endif // FIGUREVIEW_H
