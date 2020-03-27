#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QGraphicsPixmapItem"
#include "QEvent"
#include "QObject"

enum class FigureType { Alive,
                        Killed,
                        Promotion
};

class FigureBase :public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
  FigureBase(bool side = true, FigureType type = FigureType::Alive, int x =0, int y =0, QGraphicsItem *parent = 0);
  bool virtual ValidatePosition(int PositionX, int PositionY) =0;
  bool virtual ValidateStrikePosition(int PositionX, int PositionY) =0;
  void setPosition(QPointF position, int Posx, int Posy);
  int m_positionX;
  int m_positionY;
  bool m_stopOnOtherFigure;
  bool m_firstMove;
  bool m_leftSide;
  static bool m_leftSideTurn;
  static bool m_promotionActive;
  FigureType m_type;
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
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
