#include "mathlib.h"

#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * Compute the absolute value of x.
 */
double Abs(double x) { return (x < 0) ? -x : x; }

/*
 * Compute the square root of x >= 0.
 */
double Sqrt(double x) {
  if (x < 0) {
    return nan("nan");
  }

  double old = 0.0;
  double new = 1.0;

  while (Abs(old - new) > EPSILON) {
    old = new;
    new = 0.5 * (old + (x / old));
  }

  return new;
}

/*
 * Compute the sine of x.
 */
double Sin(double x) {
  double normalized = fmod(x, 2 * M_PI);
  double term = normalized;
  double sum = normalized;
  int n = 1;

  while (Abs(term) > EPSILON) {
    term *= -normalized * normalized / ((n + 1) * (n + 2));
    sum += term;
    n += 2;
  }

  return sum;
}

/*
 * Compute the cosine of x.
 */
double Cos(double x) {
  double normalized = fmod(x, 2 * M_PI);
  double term = 1;
  double sum = 1;
  int n = 0;

  while (Abs(term) > EPSILON) {
    term *= -normalized * normalized / ((n + 1) * (n + 2));
    sum += term;
    n += 2;
  }

  return sum;
}

/*
 * Compute the tangent of x.
 *
 * NOTE:
 * Tan(M_PI / 2) will not be undefined for two reasons:
 * (1) the IEEE 754 double precision standard cannot perfectly represent
 *     pi in binary; and
 * (2) the Taylor-Maclaurin series used to approximate Cos(pi/2) will not
 *     converge to 0.
 *  Therefore, it will instead to converge to a very, very small
 *  number resulting in a very, very large value of Tan(pi/2).
 */
double Tan(double x) { return Sin(x) / Cos(x); }
