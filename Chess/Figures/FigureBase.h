#ifndef FIGUREBASE_H
#define FIGUREBASE_H

class FigureBase{
public:
  FigureBase();
  ~FigureBase();
  bool ValidatePosition();
protected:
  int PositionX;
  int PositionY;
};

#endif // FIGUREBASE_H
