//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Jump2DCost.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 26-Aug-2019 18:20:14
//

// Include Files
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

// Function Definitions

//
// JUMP2DCOST
//     J = JUMP2DCOST(IN1,IN2,IN3,IN4,IN5,IN6)
// Arguments    : const double in1[6]
//                const double in2[4]
//                const double in3[6]
//                const double in4[4]
//                const double in5[6]
//                const double in6[4]
// Return Type  : double
//
double Jump2DCost(const double in1[6], const double in2[4], const double in3[6],
                  const double in4[4], const double in5[6], const double in6[4])
{
  double t2;
  double t3;
  double t4;
  double t5;
  double t6;
  double t7;
  double t8;
  double t9;
  double t10;
  double t11;

  //     This function was generated by the Symbolic Math Toolbox version 7.1.
  //     26-Aug-2019 18:15:39
  t2 = in2[2] - in4[2];
  t3 = in2[0] - in4[0];
  t4 = in2[3] - in4[3];
  t5 = in2[1] - in4[1];
  t6 = in1[5] - in3[5];
  t7 = in1[3] - in3[3];
  t8 = in1[4] - in3[4];
  t9 = in1[2] - in3[2];
  t10 = in1[0] - in3[0];
  t11 = in1[1] - in3[1];
  return ((((((((in5[0] * (t10 * t10) + in5[3] * (t7 * t7)) + in5[2] * (t9 * t9))
               + in5[5] * (t6 * t6)) + in5[1] * (t11 * t11)) + in5[4] * (t8 * t8))
            + in6[0] * (t3 * t3)) + in6[2] * (t2 * t2)) + in6[1] * (t5 * t5)) +
    in6[3] * (t4 * t4);
}

//
// File trailer for Jump2DCost.cpp
//
// [EOF]
//
