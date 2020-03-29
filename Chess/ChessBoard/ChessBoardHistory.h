#ifndef CHESSBOARDHISTORY_H
#define CHESSBOARDHISTORY_H
#include "ChessBoardMove.h"
#include "QList"

/*!
 * \brief The ChessBoardHistory class store information about game history
 */
class ChessBoardHistory
{
public:
  /*!
   * \brief ChessBoardHistory constructor
   */
  ChessBoardHistory();
  /*!
   * \brief addMove add move to history
   * \param move which was done
   */
  void addMove(ChessBoardMove move);
  /*!
   * \brief getChessBoardHistory
   * \return pointer for list of moves that was done in game
   */
  QList<ChessBoardMove>* getChessBoardHistory();
  /*!
   * \brief saveGame save moves of game in file
   * \param fileName path for savin game history
   */
  void saveGame(QString fileName);
  /*!
   * \brief loadGame load game history from file
   * \param fileName path for game history
   */
  void loadGame(QString fileName);
private:
  /*!
   * \brief chessBoardMoves list of moves in game
   */
  QList<ChessBoardMove> chessBoardMoves;
};

#endif // CHESSBOARDHISTORY_H
