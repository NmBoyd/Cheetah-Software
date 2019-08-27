/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Jump2DCostGradient.cpp
 *
 * Code generation for function 'Jump2DCostGradient'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Jump2DBounds.h"
#include "Jump2DConstraintJacobian.h"
#include "Jump2DConstraintJacobianFinal.h"
#include "Jump2DConstraintJacobianFinalSP.h"
#include "Jump2DConstraintJacobianInitial.h"
#include "Jump2DConstraintJacobianInitialSP.h"
#include "Jump2DConstraintJacobianSP.h"
#include "Jump2DConstraints.h"
#include "Jump2DConstraintsFinal.h"
#include "Jump2DConstraintsInitial.h"
#include "Jump2DCost.h"
#include "Jump2DCostGradient.h"
#include "Jump2DInitialize.h"
#include "Jump2DLagrangianHessian.h"
#include "Jump2DLagrangianHessianFinal.h"
#include "Jump2DLagrangianHessianFinalSP.h"
#include "Jump2DLagrangianHessianInitial.h"
#include "Jump2DLagrangianHessianInitialSP.h"
#include "Jump2DLagrangianHessianSP.h"

/* Function Definitions */
void Jump2DCostGradient(const double in1[6], const double in2[4], const double
  in3[6], const double in4[4], const double in5[6], const double in6[4], double
  cost_gradient[10])
{
  /* JUMP2DCOSTGRADIENT */
  /*     COST_GRADIENT = JUMP2DCOSTGRADIENT(IN1,IN2,IN3,IN4,IN5,IN6) */
  /*     This function was generated by the Symbolic Math Toolbox version 7.1. */
  /*     26-Aug-2019 18:15:40 */
  cost_gradient[0] = in5[0] * (in1[0] * 2.0 - in3[0] * 2.0);
  cost_gradient[1] = in5[1] * (in1[1] * 2.0 - in3[1] * 2.0);
  cost_gradient[2] = in5[2] * (in1[2] * 2.0 - in3[2] * 2.0);
  cost_gradient[3] = in5[3] * (in1[3] * 2.0 - in3[3] * 2.0);
  cost_gradient[4] = in5[4] * (in1[4] * 2.0 - in3[4] * 2.0);
  cost_gradient[5] = in5[5] * (in1[5] * 2.0 - in3[5] * 2.0);
  cost_gradient[6] = in6[0] * (in2[0] * 2.0 - in4[0] * 2.0);
  cost_gradient[7] = in6[1] * (in2[1] * 2.0 - in4[1] * 2.0);
  cost_gradient[8] = in6[2] * (in2[2] * 2.0 - in4[2] * 2.0);
  cost_gradient[9] = in6[3] * (in2[3] * 2.0 - in4[3] * 2.0);
}

/* End of code generation (Jump2DCostGradient.cpp) */
