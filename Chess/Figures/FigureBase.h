#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QImage"

enum class FigureType { Alive,
                        Killed,
                        Promotion
};

class FigureBase
{
public:
  FigureBase(bool side = true, FigureType type = FigureType::Alive, int x =0, int y =0);
  bool virtual ValidatePosition(int PositionX, int PositionY) =0;
  bool virtual ValidateStrikePosition(int PositionX, int PositionY) =0;
  void setPosition(int Posx, int Posy);
  bool canSelect();
  bool canMove();
  int m_positionX;
  int m_positionY;
  bool m_stopOnOtherFigure;
  bool m_firstMove;
  bool m_leftSide;
  static bool m_leftSideTurn;
  static bool m_promotionActive;
  FigureType m_type;
  QImage m_image;
protected:
  bool m_dragOver = false;
};

#endif // FIGUREBASE_H
