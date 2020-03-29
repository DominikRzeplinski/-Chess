#ifndef FIGUREPAWN_H
#define FIGUREPAWN_H
#include "FigureBase.h"


class FigurePawn: public FigureBase
{
public:
  FigurePawn(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  bool validatePosition(int PositionX, int PositionY);
  bool validateStrikePosition(int PositionX, int PositionY);
private:
  bool moveEnemyDirection(int PositionX);
};

#endif // FIGUREPAWN_H
