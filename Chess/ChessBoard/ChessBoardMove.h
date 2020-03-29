#ifndef CHESSBOARDMOVE_H
#define CHESSBOARDMOVE_H

/*!
 * \brief The ChessBoardMove class represent move that was done by player in game
 */
class ChessBoardMove
{
public:
  /*!
   * \brief ChessBoardMove  constructor
   * \param posX coordinates of figure
   * \param posY coordinates of figure
   * \param newPosX new coordinates of figure
   * \param newPosY new coordinates of figure
   * \param promo flag tell if this is promotion of pawn or normal move of figure
   */
  ChessBoardMove(int posX, int posY, int newPosX, int newPosY, bool promo = false);
  /*!
   * \brief promotion of pawn
   */
  bool promotion;
  /*!
   * \brief positionX coordinates of figure
   */
  int positionX;
  /*!
   * \brief positionY coordinates of figure
   */
  int positionY;
  /*!
   * \brief newPositionX new coordinates of figure
   */
  int newPositionX;
  /*!
   * \brief newPositionY new coordinates of figure
   */
  int newPositionY;
};

#endif // CHESSBOARDMOVE_H
