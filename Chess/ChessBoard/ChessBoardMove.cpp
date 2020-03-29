#include "ChessBoardMove.h"

ChessBoardMove::ChessBoardMove(int posX, int posY, int newPosX, int newPosY, bool promo)
{
  promotion = promo;
  positionX = posX;
  positionY = posY;
  newPositionX = newPosX;
  newPositionY = newPosY;
}
