#ifndef FIGUREKNIGHT_H
#define FIGUREKNIGHT_H
#include "FigureBase.h"


class FigureKnight: public FigureBase
{
public:
  FigureKnight(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  bool validatePosition(int PositionX, int PositionY);
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREKNIGHT_H
