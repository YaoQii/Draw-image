#ifndef CURVE_3_H
#define CURVE_3_H
#include "helper.h"
#include "vector2d.h"
#include "small_linalg.h"
//#include "constants.h"
#include <QPointF>
namespace mathself {
typedef enum {Calcurvature, Calheading, Calsteer} CalType;
  /**
   * @brief curvatureCal
   * @param xim1
   * @param xi
   * @param xip1
   * @return
   */
  ///over load
  inline float curvatureCal(Vector2D xim1, Vector2D xi, Vector2D xip1)
  {
    // the vectors between the nodes
    mathself::Vector2D Dxi = xi - xim1;
    mathself::Vector2D Dxip1 = xip1 - xi;

    float kappa = 0;
    // the distance of the vectors
    float absDxi = Dxi.length();
    float absDxip1 = Dxip1.length();
    // ensure that the absolute values are not null
    if (absDxi > 0 && absDxip1 > 0) {
      // the angular change at the node
      float Dphi = std::acos(mathself::SelfHelper::clamp(Dxi.dot(Dxip1) / (absDxi * absDxip1), -1, 1));
      kappa = Dphi / absDxi;
    }
    if(Dxi.getX() * Dxip1.getY() - Dxi.getY() * Dxip1.getX() < 0)  kappa = -kappa;
    return kappa;
  }

  inline float curvatureCal(QPointF xim1, QPointF xi, QPointF xip1)
  {
    // the vectors between the nodes
    mathself::Vector2D Dxi(xi.x() - xim1.x(), xi.y() - xim1.y());
    mathself::Vector2D Dxip1(xip1.x() - xi.x(), xip1.y() - xi.y());

    float kappa = 0;
    // the distance of the vectors
    float absDxi = Dxi.length();
    float absDxip1 = Dxip1.length();
    // ensure that the absolute values are not null
    if (absDxi > 0 && absDxip1 > 0) {
      // the angular change at the node
      float Dphi = std::acos(mathself::SelfHelper::clamp(Dxi.dot(Dxip1) / (absDxi * absDxip1), -1, 1));
      kappa = Dphi / absDxi;
    }
    if(Dxi.getX() * Dxip1.getY() - Dxi.getY() * Dxip1.getX() < 0)  kappa = -kappa;
    return kappa;
  }

} //namespace mathself
#endif // CURVE_3_H
