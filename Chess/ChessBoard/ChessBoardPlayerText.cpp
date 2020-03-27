#include "ChessBoardPlayerText.h"

ChessBoardPlayerText::ChessBoardPlayerText(bool leftSide, QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    if(leftSide)
      {
        setPos(300,50);
      }
    else
      {
        setPos(300,550);
      }
    setZValue(3);

    setDefaultTextColor(Qt::red);
    setTextWidth(50);

}
