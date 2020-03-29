#ifndef CHESSBOARDBOX_H
#define CHESSBOARDBOX_H
#include "QGraphicsRectItem"
#include "QGraphicsLayoutItem"

/*!
 * \brief The ChessBoardBox class represents View of single box on board
 */
class ChessBoardBox: public QGraphicsRectItem
{
public:
  /*!
   * \brief positionX coordinate of box
   */
  int positionX;
  /*!
   * \brief positionY coordinate of box
   */
  int positionY;
  /*!
   * \brief ChessBoardBox constructor
   * \param xPos coordinate of new box
   * \param yPos coordinate of new box
   * \param parent QGraphicsItem
   */
  ChessBoardBox(int xPos, int yPos, QGraphicsItem *parent=0);
  /*!
   * \brief ResetBrush set defoult brush for box
   */
  void ResetBrush();
private:
  /*!
   * \brief sizeOfBox size of box in pixels
   */
  int const sizeOfBox = 50;
  /*!
   * \brief leftOfBoard left position of first box in pixels
   */
  int const leftOfBoard = 200;
  /*!
   * \brief topOfBoard top position of first box in pixels
   */
  int const topOfBoard = 100;
};

#endif // CHESSBOARDBOX_H
