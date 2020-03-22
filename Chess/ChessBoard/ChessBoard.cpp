#include "ChessBoard.h"
#include "Figures/FigureKing.h"
#include "Figures/FigureBishop.h"
#include "Figures/FigureKnight.h"
#include "Figures/FigurePawn.h"
#include "Figures/FigureQueen.h"
#include "Figures/FigureRook.h"
#include <QGraphicsScene>

ChessBoard::ChessBoard()
{
  m_panelLeft = NULL;
  m_panelRight = NULL;
  Reset();
}

void ChessBoard::CleanScene()
{
  m_boxes.clear();
  m_figures.clear();
  if (m_panelLeft)
    delete m_panelLeft;
  if (m_panelRight)
    delete m_panelRight;
  m_panelLeft = NULL;
  m_panelRight = NULL;
}

void ChessBoard::Reset()
{
  CleanScene();
  FigureBase * figureBase;
  ChessBoardBox *box;
  for(int y = 0; y < 8; y++) {
      for(int x = 0; x < 8; x++)
      {
          box = new ChessBoardBox(x,y);
          m_boxes.append(box);
          if (x <= 1 || x >=6)
          {
          if (x ==0 )
          {
              if (y == 0 || y == 7)
                figureBase = new FigureRook(true, x,y);
              if (y==1 || y== 6)
                figureBase = new FigureKnight(true, x,y);
              if (y==2 || y==5)
                figureBase = new FigureBishop(true, x,y);
              if (y ==3)
                figureBase = new FigureQueen(true,x,y);
              if (y==4)
                figureBase = new FigureKing(true,x,y);
          }
          else if (x == 1)
          {
              figureBase = new FigurePawn(true,x,y);
          }
          else if (x == 6)
          {
              figureBase = new FigurePawn(false,x,y);
          }
          else if (x == 7)
          {
              if (y == 0 || y == 7)
                figureBase = new FigureRook(false, x,y);
              if (y==1 || y== 6)
                figureBase = new FigureKnight(false, x,y);
              if (y==2 || y==5)
                figureBase = new FigureBishop(false, x,y);
              if (y ==3)
                figureBase = new FigureQueen(false,x,y);
              if (y==4)
                figureBase = new FigureKing(false,x,y);

          }
          figureBase->setPos(box->pos());
          m_figures.append(figureBase);
          QObject::connect(figureBase, &FigureBase::figureSelected,
                               this, &ChessBoard::validMoves);
          QObject::connect(figureBase, &FigureBase::figureDeselected,
                               this, &ChessBoard::clearMoves);
          }
      }
  }
  m_panelLeft = new ChessBoardSidePanel();
  m_panelRight = new ChessBoardSidePanel(false);
}

void ChessBoard::validMoves(int PositionX, int PositionY)
{
  for (int i =0; i < m_figures.count(); ++i)
    {
      if (m_figures.at(i)->PositionX == PositionX && m_figures.at(i)->PositionY == PositionY)
        {
          for (int j=0;j<m_boxes.count();++j)
            {
              if (m_figures.at(i)->ValidatePosition(m_boxes.at(j)->PositionX, m_boxes.at(j)->PositionY))
                m_boxes.at(j)->setBrush(Qt::green);
            }
          break;
        }
    }
}

void ChessBoard::clearMoves()
{
          for (int j=0;j<m_boxes.count();++j)
            {
              m_boxes.at(j)->ResetBrush();
            }
}
