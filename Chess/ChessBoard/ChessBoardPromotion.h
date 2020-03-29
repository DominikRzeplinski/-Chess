#ifndef CHESSBOARDPROMOTION_H
#define CHESSBOARDPROMOTION_H

#include "QGraphicsRectItem"

/*!
 * \brief The ChessBoardPromotion class represent box to store promotion figures
 */
class ChessBoardPromotion: public QGraphicsRectItem
{
public:
  /*!
   * \brief ChessBoardPromotion contructor
   * \param parent QGraphicsItem
   */
  ChessBoardPromotion(QGraphicsItem *parent=0);
};

#endif // CHESSBOARDPROMOTION_H
