#ifndef FIGUREPAWN_H
#define FIGUREPAWN_H
#include "FigureBase.h"


class FigurePawn: public FigureBase
{
public:
  FigurePawn(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  bool ValidatePosition(int PositionX, int PositionY);
  bool ValidateStrikePosition(int PositionX, int PositionY);
  void Promote();
private:
  bool moveEnemyDirection(int PositionX);
};

#endif // FIGUREPAWN_H
