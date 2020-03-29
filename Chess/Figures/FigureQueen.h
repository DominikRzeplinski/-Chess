#ifndef FIGUREQUEEN_H
#define FIGUREQUEEN_H
#include "FigureBase.h"


class FigureQueen: public FigureBase
{
public:
  FigureQueen(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  bool validatePosition(int PositionX, int PositionY);
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREQUEEN_H
