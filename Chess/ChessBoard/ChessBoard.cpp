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
          box->m_bHasFigure = false;

          if (x <= 1 || x >=6)
          {
              box->m_bHasFigure = true;
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

          m_boxes.append(box);
      }
  }
  m_panelLeft = new ChessBoardSidePanel();
  m_panelRight = new ChessBoardSidePanel(false);
}

void ChessBoard::validMoves(int positionX, int positionY)
{

  for (int i =0; i < m_figures.count(); ++i)
    {
      if (m_figures.at(i)->m_positionX == positionX && m_figures.at(i)->m_positionY == positionY)
        {
          bool bBreake = false;
          for (int x=positionX;x<8;++x)
          {
              for (int y=positionY; y<8;++y)
              {
                  if (x == positionX && y == positionY)
                    continue;
                  if (!validateMoveInOneDirection(i,x,y)) bBreake = true;
                  if (bBreake) break;
              }
              if (bBreake) break;
          }
          bBreake = false;
          for (int x=positionX;x<8;++x)
          {
              for (int y=positionY; y>=0;--y)
              {
                  if (x == positionX && y == positionY)
                    continue;
                  if (!validateMoveInOneDirection(i,x,y)) bBreake = true;
                  if (bBreake) break;
              }
              if (bBreake) break;
          }
          bBreake = false;
          for (int x=positionX;x>=0;--x)
          {
              for (int y=positionY; y<8;++y)
              {
                  if (x == positionX && y == positionY)
                    continue;
                  if (!validateMoveInOneDirection(i,x,y)) bBreake = true;
                  if (bBreake) break;
              }
              if (bBreake) break;
          }
          bBreake = false;
          for (int x=positionX;x>=0;--x)
          {
              for (int y=positionY; y>=0;--y)
              {
                  if (x == positionX && y == positionY)
                    continue;
                  if (!validateMoveInOneDirection(i,x,y)) bBreake = true;
                  if (bBreake) break;
              }
              if (bBreake) break;
          }
          break;
        }
    }
}


bool ChessBoard::validateMoveInOneDirection(int idxFigure,int xPos, int yPos)
{
  for (int j=0; j< m_boxes.count(); ++j)
    {
        if (m_boxes.at(j)->PositionX == xPos && m_boxes.at(j)->PositionY == yPos)
        {
            if (m_figures.at(idxFigure)->ValidatePosition(m_boxes.at(j)->PositionX, m_boxes.at(j)->PositionY)
                && !m_boxes.at(j)->m_bHasFigure)
              {
                m_boxes.at(j)->setBrush(Qt::green);
                return true;
              }
            else if (m_figures.at(idxFigure)->ValidatePosition(m_boxes.at(j)->PositionX, m_boxes.at(j)->PositionY) && m_boxes.at(j)->m_bHasFigure && m_figures.at(idxFigure)->m_stopOnOtherFigure)
              return false;
            break;
        }
    }
  return true;
}


void ChessBoard::clearMoves()
{
          for (int j=0;j<m_boxes.count();++j)
            {
              m_boxes.at(j)->ResetBrush();
            }
}
