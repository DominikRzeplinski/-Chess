#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QGraphicsPixmapItem"
#include "QEvent"
#include "QObject"
class FigureBase :public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
  FigureBase(bool side = true, int x =0, int y =0, QGraphicsItem *parent = 0);
  bool virtual ValidatePosition(int PositionX, int PositionY) =0;
  int m_positionX;
  int m_positionY;
  bool m_stopOnOtherFigure;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  bool LeftSide;
  bool m_dragOver = false;
  QImage m_image;
  QColor color;
  QPointF m_translatePoint;
signals:
    void figureSelected(int PositionX, int PositionY);
    void figureDeselected();
    void figureMoved(int PositionX, int PositionY);
};

#endif // FIGUREBASE_H
