#ifndef FIGUREBISHOP_H
#define FIGUREBISHOP_H
#include "FigureBase.h"


class FigureBishop: public FigureBase
{
public:
  FigureBishop(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  bool validatePosition(int PositionX, int PositionY);
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREBISHOP_H
