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
  bool virtual validatePosition(int PositionX, int PositionY) =0;
  bool virtual validateStrikePosition(int PositionX, int PositionY) =0;
  void setPosition(int Posx, int Posy);
  bool canSelect();
  bool canMove();
  int positionX;
  int positionY;
  bool leftSide;
  static bool leftSideTurn;
  FigureType type;
  bool firstMove;
  bool stopOnOtherFigure;
  QImage image;
};

#endif // FIGUREBASE_H
