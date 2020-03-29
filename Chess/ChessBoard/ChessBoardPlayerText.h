#ifndef CHESSBOARDPLAYERTEXT_H
#define CHESSBOARDPLAYERTEXT_H
#include "QGraphicsTextItem"

/*!
 * \brief The ChessBoardPlayerText class represent View for communicats for player
 */
class ChessBoardPlayerText: public QGraphicsTextItem
{
public:
  /*!
   * \brief ChessBoardPlayerText constructor
   * \param leftSide side of player
   * \param parent QGraphicsItem
   */
  ChessBoardPlayerText(bool leftSide, QGraphicsItem *parent=0);
};

#endif // CHESSBOARDPLAYERTEXT_H
