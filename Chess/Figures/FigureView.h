#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H
#include "QGraphicsPixmapItem"
#include "QEvent"
#include "QObject"
#include "FigureBase.h"

/*!
 * \brief The FigureView class for displaing figures
 */
class FigureView: public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  /*!
   * \brief FigureView constructor
   * \param figure figure for wich the view is created
   * \param parent QGraphicsItem
   */
  FigureView(FigureBase* figure = 0,QGraphicsItem *parent = 0);
  /*!
   * \brief figureBase pointer for model of figure
   */
  FigureBase* figureBase;
protected:
  /*!
   * \brief mousePressEvent triggerd when figure view is clicked by left button of mouse
   * \param event QGraphicsSceneMouseEvent
   */
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  /*!
   * \brief mouseMoveEvent mousePressEvent triggerd when figure view is dragged
   * \param event QGraphicsSceneMouseEvent
   */
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  /*!
   * \brief mouseReleaseEvent triggerd when left button of mouse is relesed
   * \param event QGraphicsSceneMouseEvent
   */
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  /*!
   * \brief m_translatePoint Initial point of mouse cursor when figure View was clicked
   */
  QPointF m_translatePoint;
signals:
  /*!
   * \brief figurePromotionSelected Signal that promotion figure was chosen
   * \param positionX coordinates of selected figure
   * \param positionY coordinates of selected figure
   */
  void figurePromotionSelected(int positionX, int positionY);
  /*!
   * \brief figureSelected Signal that figure was selected
   * \param positionX coordinates of selected figure
   * \param positionY coordinates of selected figure
   */
  void figureSelected(int positionX, int positionY);
  /*!
   * \brief figureDeselected Signal that figure is no longer selected
   */
  void figureDeselected();
  /*!
   * \brief figureMoved Signal that figure has been moved
   * \param positionX coordinates of selected figure
   * \param positionY coordinates of selected figure
   */
  void figureMoved(int positionX, int positionY);
};

#endif // FIGUREVIEW_H
