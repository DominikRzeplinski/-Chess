#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Figures/FigureBase.h"

/*!
 * \brief The ChessBoard class represent model for chess game
 * This class acts like engine and container for chess game
 */
class ChessBoard
{
public:
  /*!
   * \brief ChessBoard constructor
   */
  ChessBoard();
  /*!
   * \brief Reset game
   * remove existing game elements and prepare game for starting new one.
   */
  void Reset();
  /*!
   * \brief validMoves validate valid moves for given figure and all enamy figures
   * \param positionX coorinates of figure for which validations are computed
   * \param positionY coorinates of figure for which validations are computed
   */
  void validMoves(int positionX, int positionY);
  /*!
   * \brief setNewPosition Set new position for figure
   * \param positionX current coordinates of figure
   * \param positionY current coordinates of figure
   * \param newPositionX new coordinates for figure
   * \param newPositionY new coordinates for figure
   * \return true if new position can be accesed, other false
   */
  bool setNewPosition(int positionX, int positionY,int newPositionX, int newPositionY);
  /*!
   * \brief promotionSelected Select figure for promoted pawn
   * \param positionX coordinates of selected figure for promotion
   * \param positionY coordinates of selected figure for promotion
   * \return
   */
  bool promotionSelected(int positionX, int positionY);
  /*!
   * \brief endOfGame true if game has ended, other false
   */
  bool endOfGame;
  /*!
   * \brief checkMate true if checkMate was done
   */
  bool checkMate;
  /*!
   * \brief figures figures that are in game or where killed
   */
  QList<FigureBase*> figures;
  /*!
   * \brief promotionFigures figures that are available to be chosen during promotion
   */
  QList<FigureBase*> promotionFigures;
  /*!
   * \brief leftSideWinner true if player on left side win, other false
   */
  bool leftSideWinner;
  /*!
   * \brief promotionActive true if pawn is in promotion, other false
   */
  bool promotionActive;
  /*!
   * \brief availableMoves list of valid moves for selected figure
   */
  QVector<QPair<int,int>> availableMoves;
  /*!
   * \brief availableStrikeMoves list of valid strike moves for selected figure
   */
  QVector<QPair<int,int>> availableStrikeMoves;
private:
  /*!
   * \brief figureEnPassant temporarily figure created after pawn dash 2 position.
   * used to determinate if enamy pawn can be killed EnPassant
   */
  FigureBase* figureEnPassant;
  /*!
   * \brief validateMoveInOneDirection determinate if move for figure is valid in specyfic direction.
   * (if enamy or ally figure stands in direction, or if direction for type of figure is valid)
   *  depends of validation coordinates are added as enemyAvailableStrikeMoves, enemyAllValidStrikeMoves, enemyAvailableMoves,
   *                                                 availableStrikeMoves,,availableMoves
   * \param figure for which validation is made
   * \param xPos coordinate of direction
   * \param yPos coordinate of direction
   * \param enemy if computaction is made for enamy figure
   * \return true if direction is not clocked, other false
   */
  bool validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy = false);
  /*!
   * \brief cleanScene removes all object from game
   */
  void cleanScene();
  /*!
   * \brief enemyAvailableMoves list of valid enamy next move positions
   */
  QVector<QPair<int,int>> enemyAvailableMoves;
  /*!
   * \brief enemyAvailableStrikeMoves list of valid enamy strikes in next move
   */
  QVector<QPair<int,int>> enemyAvailableStrikeMoves;
  /*!
   * \brief enemyAllValidStrikeMoves list of all valid positions on wich enamy can strike
   */
  QVector<QPair<int,int>> enemyAllValidStrikeMoves;
  /*!
   * \brief getFigureAtPosition
   * \param positionX coordinates of figure
   * \param positionY coordinates of figure
   * \return pointer for figure at given coordinates if exist, other null
   */
  FigureBase* getFigureAtPosition(int positionX, int positionY);
  /*!
   * \brief setAllValidMoves determinete valid moves for figure
   * \param positionX coordinates of figure
   * \param positionY coordinates of figure
   * \param enemy determinates if valid moves are for enamy figure
   */
  void setAllValidMoves(int positionX, int positionY, bool enemy = false);
  /*!
   * \brief isCheckMate determinate if mate was done
   * \param leftSide side of player turn
   * \return true if mate was done, other false
   */
  bool isCheckMate(bool leftSide);
  /*!
   * \brief getEnemyAvailableMoves determinate valid moves for enamy
   * \param leftSide side of active player
   */
  void getEnemyAvailableMoves(bool leftSide);
  /*!
   * \brief setWinner set which side has won game
   * \param leftSide side of finer
   */
  void setWinner(bool leftSide);
  /*!
   * \brief isEnPassantPosition determinate if given position can be strike enPassant
   * \param xPos coordinates for validation
   * \param yPos coordinates for validation
   * \return true, if there can be strike enPassant, other false
   */
  bool isEnPassantPosition(int xPos, int yPos);
  /*!
   * \brief checkCheckMate determinate if check was done
   * \param positionX coordinates of last moved figure
   * \param positionY coordinates of last moved figure
   * \return true if check was done, other false
   */
  bool checkCheckMate(int positionX, int positionY);
};

#endif // CHESSBOARD_H
