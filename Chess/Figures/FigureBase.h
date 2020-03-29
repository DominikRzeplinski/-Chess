#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QImage"

/*!
 * \brief The FigureType enum determines type of figure
 * Alive - figure is alive and is in game
 * Killed - figure was killed and is no longer in game
 * Promotion - figure is not in game but can be if pawn promote to it
 */
enum class FigureType { Alive,
                        Killed,
                        Promotion
                      };

/*!
 * \brief The FigureBase class
 *
 * Abstract class for figures in chess game
 * Each figure need to inherit from this class
 */
class FigureBase
{
public:
  /*!
   * \brief FigureBase constructor
   * \param side determinate for wich player figure is created
   * \param type enum for figure
   * \param x coordinate of figure on board
   * \param y coordinate of figure on board
   */
  FigureBase(bool side = true, FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for figure
   * \param PositionX new coordinates for figure
   * \param PositionY new coordinates for figure
   * \return true if new coordinates are in reach for figure, other false
   */
  bool virtual validatePosition(int PositionX, int PositionY) =0;
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for figure to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if figure can strike on new coordinates, other false
   */
  bool virtual validateStrikePosition(int PositionX, int PositionY) =0;
  /*!
   * \brief setPosition Set new coordinates for figure
   * \param Posx new x coordinates
   * \param Posy new y coordinates
   */
  void setPosition(int Posx, int Posy);
  /*!
   * \brief canSelect Check if figure can be selected
   * \return true if figure can be selected, other false
   */
  bool canSelect();
  /*!
   * \brief canMove Check if figure can be moved
   * \return true if figure can be moved, other false
   */
  bool canMove();
  /*!
   * \brief positionX current coordinate of figure
   */
  int positionX;
  /*!
   * \brief positionY current coordinate of figure
   */
  int positionY;
  /*!
   * \brief leftSide side determinate for wich player figure is created
   */
  bool leftSide;
  /*!
   * \brief leftSideTurn static member for class, determinate which player turn is now
   */
  static bool leftSideTurn;
  /*!
   * \brief type type od figure
   */
  FigureType type;
  /*!
   * \brief firstMove determinate if first move was done. if yes, firstMove is false
   */
  bool firstMove;
  /*!
   * \brief stopOnOtherFigure determinate if figure stop on other figures in case of move or strike.
   */
  bool stopOnOtherFigure;
  /*!
   * \brief image Image of figure
   */
  QImage image;
};

#endif // FIGUREBASE_H
