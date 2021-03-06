//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Jump2DConstraintJacobian.h
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 26-Aug-2019 18:20:14
//
#ifndef JUMP2DCONSTRAINTJACOBIAN_H
#define JUMP2DCONSTRAINTJACOBIAN_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Jump2DBounds_types.h"

// Function Declarations
extern void Jump2DConstraintJacobian(const double in1[2], double dt, const
  double in3[4], double m, double Iyy, double mu_g, double
  constraint_jacobian_nz[35]);

#endif

//
// File trailer for Jump2DConstraintJacobian.h
//
// [EOF]
//
