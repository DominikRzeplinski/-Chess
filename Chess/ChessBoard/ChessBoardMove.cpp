#include "ChessBoardMove.h"

ChessBoardMove::ChessBoardMove(int posX, int posY, int newPosX, int newPosY, bool promo)
{
  promotion = promo;
  positionX = posX;
  positionY = posY;
  newPositionX = newPosX;
  newPositionY = newPosY;
}

bool ChessBoardMove::getPromotion() const
{
    return promotion;
}

int ChessBoardMove::getPositionX() const
{
    return positionX;
}

int ChessBoardMove::getPositionY() const
{
    return positionY;
}

int ChessBoardMove::getNewPositionX() const
{
    return newPositionX;
}

int ChessBoardMove::getNewPositionY() const
{
    return newPositionY;
}
