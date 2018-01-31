/*!
   \file
   \brief This is a collection of helper functions that are used throughout the project.

*/
#ifndef HELPER
#define HELPER

#include <cmath>
#include <algorithm>

//#include "constants.h"
namespace mathself {
/*!
    \brief The namespace that wraps helper.h
    \namespace Helper
*/
namespace SelfHelper {

/*!
   \fn static inline float normalizeHeading(float t)
   \brief Normalizes a heading given in degrees to (0,360]
   \param t heading in degrees
*/
static inline float normalizeHeading(float t) {
  if ((int)t <= 0 || (int)t >= 360) {
    if (t < -0.1) {
      t += 360.f;
    } else if ((int)t >= 360) {
      t -= 360.f;
    } else {
      t =  0;
    }
  }

  return t;
}

/*!
   \fn float normalizeHeadingRad(float t)
   \brief Normalizes a heading given in rad to (0,2PI]
   \param t heading in rad
*/
static inline float normalizeHeadingRad(float t) {
  if (t < 0) {
    t = t - 2.f * M_PI * (int)(t / (2.f * M_PI));
    return 2.f * M_PI + t;
  }

  return t - 2.f * M_PI * (int)(t / (2.f * M_PI));
}

/**
 * @brief NormalizeAngle
 * @param angle normalize the angle to [-pi , pi];
 * @return
 */
static inline double NormalizeAngleMPI2PI(const double angle) {
  const double new_angle = std::fmod(angle + M_PI, M_PI * 2.0);
  return (new_angle < 0 ? new_angle + M_PI * 2.0 : new_angle) - M_PI;
}

/*!
   \fn float toDeg(float t)
   \brief Converts and normalizes a heading given in rad to deg
   \param t heading in deg
*/
static inline float toDeg(float t) {
  return normalizeHeadingRad(t) * 180.f / M_PI ;
}

/*!
   \fn float toRad(float t)
   \brief Converts and normalizes a heading given in deg to rad
   \param t heading in rad
*/
static inline float toRad(float t) {
  return normalizeHeadingRad(t / 180.f * M_PI);
}

/*!
   \fn float clamp(float n, float lower, float upper)
   \brief Clamps a number between a lower and an upper bound
   \param
*/
static inline float clamp(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

static inline bool equalZero(float n, float precision = 0.001)
{
  if(fabs(n) < precision)
    return true;
  else
    return false;
}

}
}

#endif // HELPER

