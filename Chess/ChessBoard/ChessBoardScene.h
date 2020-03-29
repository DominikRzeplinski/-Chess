#ifndef CHESSBOARDSCENE_H
#define CHESSBOARDSCENE_H
#include <QGraphicsScene>
#include "ChessBoardBox.h"
#include "ChessBoardSidePanel.h"
#include "Figures/FigureView.h"
#include "ChessBoardPlayerText.h"
#include "ChessBoardPromotion.h"
#include "ChessBoard.h"
#include "ChessBoardHistory.h"

/*!
 * \brief The ChessBoardScene class represents view and controller for game
 */
class ChessBoardScene:public QGraphicsScene
{
public:
  /*!
   * \brief ChessBoardScene constructor
   * \param parent QObject
   */
  ChessBoardScene(QObject *parent = 0);
  /*!
   * \brief Reset game
   */
  void Reset();
  /*!
   * \brief saveGame save game in file
   * \param fileName name of file
   */
  void saveGame(QString fileName);
  /*!
   * \brief loadGame from file
   * \param fileName file name
   */
  void loadGame(QString fileName);
private:
  /*!
   * \brief boxes list of boxes of chess board
   */
  QList<ChessBoardBox*> boxes;
  /*!
   * \brief panelLeft left panel for player
   */
  ChessBoardSidePanel* panelLeft;
  /*!
   * \brief panelRight right panel for player
   */
  ChessBoardSidePanel* panelRight;
  /*!
   * \brief figureViews views of alive and killed figures in game
   */
  QList<FigureView*> figureViews;
  /*!
   * \brief promotionFigureViews views of promotion figures for pawn pwomotion
   */
  QList<FigureView*> promotionFigureViews;
  /*!
   * \brief promotion promotion box for pawn promotion select
   */
  ChessBoardPromotion *promotion;
  /*!
   * \brief playerTextLeft text container for left player
   */
  ChessBoardPlayerText *playerTextLeft;
  /*!
   * \brief playerTextRight text container for right player
   */
  ChessBoardPlayerText *playerTextRight;
  /*!
   * \brief getBoxAtPosition return box at given coordinates
   * \param positionX coordinate of box
   * \param positionY coordinate of box
   * \return pointer for box if exist, other null
   */
  ChessBoardBox* getBoxAtPosition(int positionX, int positionY);
  /*!
   * \brief getBoxUnderMouse retrive box under mouse position
   * \return pointer for box under mouse cursor if exist, other null
   */
  ChessBoardBox* getBoxUnderMouse();
  /*!
   * \brief setColorForBoxes Update colors of boxes
   */
  void setColorForBoxes();
  /*!
   * \brief cleanScene remove all iteams from scene
   */
  void cleanScene();
  /*!
   * \brief chessBoard pointer for chess board model
   */
  ChessBoard* chessBoard;
  /*!
   * \brief history pointer for history of game
   */
  ChessBoardHistory* history;
  /*!
   * \brief refresh views
   */
  void refresh();
  /*!
   * \brief refreshAfterPromotion refresh views of promotion
   */
  void refreshAfterPromotion();
public slots:
  /*!
   * \brief promotionSelected Slot for selecting figure for pawn promotion
   * \param positionX coordinates of selected figure
   * \param positionY coordinates of selected figure
   */
  void promotionSelected(int positionX, int positionY);
  /*!
   * \brief validMoves for selected figure
   * \param positionX coordinates of selected figure
   * \param positionY coordinates of selected figure
   */
  void validMoves(int positionX, int positionY);
  /*!
   * \brief clearMoves remove moves from view
   */
  void clearMoves();
  /*!
   * \brief setNewPosition set new position for figure
   * \param positionX coordinates of figure
   * \param positionY coordinates of figure
   */
  void setNewPosition(int positionX, int positionY);
};

#endif // CHESSBOARDSCENE_H
