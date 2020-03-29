#ifndef CHESSBOARDSIDEPANEL_H
#define CHESSBOARDSIDEPANEL_H

#include "QGraphicsRectItem"

/*!
 * \brief The ChessBoardSidePanel class represents side view for player
 */
class ChessBoardSidePanel: public QGraphicsRectItem
{
public:
  /*!
   * \brief ChessBoardSidePanel constructor
   * \param left side of player
   * \param parent QGraphicsItem
   */
  ChessBoardSidePanel(bool left = true, QGraphicsItem *parent=0);
  /*!
   * \brief getFreeSlotPos return position of next free slot for killed figure
   * \return QPointF position of free slot
   */
  QPointF getFreeSlotPos();
  /*!
   * \brief setSlotPos consume used slot
   */
  void setSlotPos();
  /*!
   * \brief resetSlot free all slots
   */
  void resetSlot();
private:
  /*!
   * \brief freeSlotX coordinates of free slot
   */
  int freeSlotX;
  /*!
   * \brief freeSlotY coordinates of free slot
   */
  int freeSlotY;
  /*!
   * \brief leftSifde side of panel for player
   */
  bool leftSifde;
};

#endif // CHESSBOARDSIDEPANEL_H
