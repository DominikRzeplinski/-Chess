#include "FigurePawn.h"

FigurePawn::FigurePawn(QGraphicsItem *parent):FigureBase(parent)
{
  setPixmap(QPixmap(":/File_Chess_plt45.svg"));
}
