#ifndef CHESSBOARDMOVE_H
#define CHESSBOARDMOVE_H


class ChessBoardMove
{
public:
  ChessBoardMove(int posX, int posY, int newPosX, int newPosY, bool promo = false);
  bool promotion;
  int positionX;
  int positionY;
  int newPositionX;
  int newPositionY;
private:
};

#endif // CHESSBOARDMOVE_H
