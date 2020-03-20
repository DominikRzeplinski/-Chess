#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QGraphicsPixmapItem"
#include "QEvent"

class FigureBase :public QGraphicsPixmapItem
{
public:
  FigureBase(bool side = true, int x =0, int y =0, QGraphicsItem *parent = 0);
  bool virtual ValidatePosition() =0;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  bool LeftSide;
  int PositionX;
  int PositionY;
  bool m_dragOver = false;
  QImage m_image;
  QColor color;
};

#endif // FIGUREBASE_H
