/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Decoder_FOC.c
 *
 * Code generated for Simulink model 'Decoder_FOC'.
 *
 * Model version                  : 2.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Sun Aug  4 23:04:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Decoder_FOC.h"
#include "rtwtypes.h"
#include <math.h>
#include "arm_math.h"
#include <float.h>
#include "math.h"

/* Named constants for Chart: '<S3>/Chart1' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_OpenStage                   ((uint8_T)3U)
#define IN_RunStage                    ((uint8_T)4U)
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Exported block signals */
real32_T id_fb;                        /*  */
real32_T iq_fb;                        /*  */

/* Exported data definition */

/* Definition for custom storage class: Struct */
PMSM_Para_type PMSM_Para = {
  /* Pn */
  5.0F
};

cur_PI_type cur_PI = {
  /* Ki_cur */
  1.5F,

  /* Kp_cur */
  0.09F
};

spd_PI_type spd_PI = {
  /* Ki_spd */
  0.007F,

  /* Kp_spd */
  0.01F
};

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real32_T rt_modf_snf(real32_T u0, real32_T u1);
static void currloop_Init(real_T *rty_RestsSingal, DW_currloop *localDW);
static void currloop(real32_T rtu_MotorOnOff1, real32_T rtu_iq_ref, real32_T
                     rtu_theta_fbk, real32_T rtu_Vdc, real32_T rtu_ia, real32_T
                     rtu_ib, real32_T rtu_Ic, real_T *rty_RestsSingal, real_T
                     rty_tABC[3], DW_currloop *localDW);
static void rate_scheduler(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

/* Return rtNaN needed by the generated code. */
static real_T rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rtM->Timing.TaskCounters.TID[1])++;
  if ((rtM->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.001s, 0.0s] */
    rtM->Timing.TaskCounters.TID[1] = 0;
  }
}

real32_T rt_modf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  y = u0;
  if (u1 == 0.0F) {
    if (u0 == 0.0F) {
      y = u1;
    }
  } else if (rtIsNaNF(u0) || rtIsNaNF(u1) || rtIsInfF(u0)) {
    y = (rtNaNF);
  } else if (u0 == 0.0F) {
    y = 0.0F / u1;
  } else if (rtIsInfF(u1)) {
    if ((u1 < 0.0F) != (u0 < 0.0F)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmodf(u0, u1);
    yEq = (y == 0.0F);
    if ((!yEq) && (u1 > floorf(u1))) {
      real32_T q;
      q = fabsf(u0 / u1);
      yEq = !(fabsf(q - floorf(q + 0.5F)) > FLT_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0F;
    } else if ((u0 < 0.0F) != (u1 < 0.0F)) {
      y += u1;
    }
  }

  return y;
}

/* System initialize for atomic system: '<S1>/currloop' */
static void currloop_Init(real_T *rty_RestsSingal, DW_currloop *localDW)
{
  /* SystemInitialize for Chart: '<S3>/Chart1' */
  *rty_RestsSingal = 0.0;

  /* SystemInitialize for IfAction SubSystem: '<S3>/If Action Subsystem2' */
  /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_PrevRese = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_PrevRes = 2;

  /* End of SystemInitialize for SubSystem: '<S3>/If Action Subsystem2' */
}

/* Output and update for atomic system: '<S1>/currloop' */
static void currloop(real32_T rtu_MotorOnOff1, real32_T rtu_iq_ref, real32_T
                     rtu_theta_fbk, real32_T rtu_Vdc, real32_T rtu_ia, real32_T
                     rtu_ib, real32_T rtu_Ic, real_T *rty_RestsSingal, real_T
                     rty_tABC[3], DW_currloop *localDW)
{
  int32_T k;
  real32_T tmpForInput_tmp[9];
  real32_T cos_g;
  real32_T rtb_DiscreteTimeIntegrator;
  real32_T rtb_IProdOut;
  real32_T rtb_Integrator_b;
  real32_T rtb_Saturation;
  real32_T rtb_algDD_o1;
  real32_T rtb_algDD_o2;
  real32_T sin_g;
  real32_T tmpForInput_tmp_0;
  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_RelationalOperator_g;

  /* Chart: '<S3>/Chart1' */
  if (localDW->temporalCounter_i1 < 32767U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c7_Decoder_FOC == 0U) {
    localDW->is_active_c7_Decoder_FOC = 1U;
    localDW->is_c7_Decoder_FOC = IN_IDLE;
  } else {
    switch (localDW->is_c7_Decoder_FOC) {
     case IN_AlignStage:
      if (localDW->temporalCounter_i1 >= 1000) {
        localDW->temporalCounter_i1 = 0U;
        localDW->is_c7_Decoder_FOC = IN_OpenStage;
        localDW->ZReset = 0.0F;
        localDW->cnt = 0.0F;
      } else if (rtu_MotorOnOff1 == 0.0F) {
        localDW->is_c7_Decoder_FOC = IN_IDLE;
      } else {
        localDW->Motor_state = 2.0F;
        *rty_RestsSingal = 0.0;
      }
      break;

     case IN_IDLE:
      if (rtu_MotorOnOff1 == 1.0F) {
        localDW->temporalCounter_i1 = 0U;
        localDW->is_c7_Decoder_FOC = IN_AlignStage;
      } else {
        localDW->Motor_state = 1.0F;
        *rty_RestsSingal = 0.0;
      }
      break;

     case IN_OpenStage:
      if (rtu_MotorOnOff1 == 0.0F) {
        localDW->is_c7_Decoder_FOC = IN_IDLE;
      } else if (localDW->temporalCounter_i1 >= 30000) {
        localDW->is_c7_Decoder_FOC = IN_RunStage;
      } else {
        if (localDW->cnt == 1.0F) {
          localDW->ZReset = 1.0F;
        }

        localDW->cnt = 1.0F;
        localDW->Motor_state = 3.0F;
        *rty_RestsSingal = 0.0;
      }
      break;

     default:
      /* case IN_RunStage: */
      if (rtu_MotorOnOff1 == 0.0F) {
        localDW->is_c7_Decoder_FOC = IN_IDLE;
      } else {
        localDW->Motor_state = 5.0F;
        *rty_RestsSingal = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<S3>/Chart1' */

  /* SwitchCase: '<S3>/Switch Case1' */
  switch ((int32_T)localDW->Motor_state) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Merge: '<S3>/Merge' incorporates:
     *  Constant: '<S11>/Constant'
     *  SignalConversion generated from: '<S11>/theta_fd'
     */
    localDW->Merge = 0.0F;

    /* Merge: '<S3>/Merge1' incorporates:
     *  Constant: '<S11>/Constant1'
     *  SignalConversion generated from: '<S11>/iq_ref'
     */
    localDW->Merge1 = 0.0F;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    /* Merge: '<S3>/Merge' incorporates:
     *  Constant: '<S12>/Constant'
     *  SignalConversion generated from: '<S12>/theta_fd'
     */
    localDW->Merge = 0.0F;

    /* Merge: '<S3>/Merge1' incorporates:
     *  Constant: '<S12>/Constant1'
     *  SignalConversion generated from: '<S12>/iq_ref'
     */
    localDW->Merge1 = 1.0F;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem1' */
    break;

   case 3:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
    if ((localDW->ZReset > 0.0F) && (localDW->DiscreteTimeIntegrator_PrevRese <=
         0)) {
      localDW->DiscreteTimeIntegrator_DSTATE = 0.0F;
    }

    rtb_DiscreteTimeIntegrator = localDW->DiscreteTimeIntegrator_DSTATE;

    /* End of DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */

    /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' */
    if ((localDW->ZReset > 0.0F) && (localDW->DiscreteTimeIntegrator1_PrevRes <=
         0)) {
      localDW->DiscreteTimeIntegrator1_DSTATE = 0.0F;
    }

    /* Merge: '<S3>/Merge' incorporates:
     *  Constant: '<S13>/Constant'
     *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator1'
     *  Math: '<S13>/Mod'
     */
    localDW->Merge = rt_modf_snf(localDW->DiscreteTimeIntegrator1_DSTATE,
      6.28318548F);

    /* Merge: '<S3>/Merge1' incorporates:
     *  Constant: '<S13>/Constant2'
     *  SignalConversion generated from: '<S13>/iq_ref'
     */
    localDW->Merge1 = 1.0F;

    /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S13>/Gain'
     *  Product: '<S13>/Product'
     */
    localDW->DiscreteTimeIntegrator_DSTATE += PMSM_Para.Pn * 52.3598785F *
      0.333333343F * 0.0001F;
    if (localDW->ZReset > 0.0F) {
      localDW->DiscreteTimeIntegrator_PrevRese = 1;
    } else if (localDW->ZReset < 0.0F) {
      localDW->DiscreteTimeIntegrator_PrevRese = -1;
    } else if (localDW->ZReset == 0.0F) {
      localDW->DiscreteTimeIntegrator_PrevRese = 0;
    } else {
      localDW->DiscreteTimeIntegrator_PrevRese = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' */
    localDW->DiscreteTimeIntegrator1_DSTATE += 0.0001F *
      rtb_DiscreteTimeIntegrator;
    if (localDW->ZReset > 0.0F) {
      localDW->DiscreteTimeIntegrator1_PrevRes = 1;
    } else if (localDW->ZReset < 0.0F) {
      localDW->DiscreteTimeIntegrator1_PrevRes = -1;
    } else if (localDW->ZReset == 0.0F) {
      localDW->DiscreteTimeIntegrator1_PrevRes = 0;
    } else {
      localDW->DiscreteTimeIntegrator1_PrevRes = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator1' */
    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem2' */
    break;

   case 4:
    break;

   case 5:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* Merge: '<S3>/Merge' incorporates:
     *  SignalConversion generated from: '<S14>/theta_Close'
     *  UnitDelay: '<S3>/Unit Delay1'
     */
    localDW->Merge = localDW->UnitDelay1_DSTATE;

    /* Merge: '<S3>/Merge1' incorporates:
     *  SignalConversion generated from: '<S14>/iq_CloseRef'
     */
    localDW->Merge1 = rtu_iq_ref;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem3' */
    break;
  }

  /* End of SwitchCase: '<S3>/Switch Case1' */

  /* Gain: '<S133>/convert_pu' incorporates:
   *  DataStoreWrite: '<S3>/Data Store Write1'
   */
  rtb_DiscreteTimeIntegrator = 0.159154937F * localDW->Merge;

  /* If: '<S133>/If' incorporates:
   *  Constant: '<S134>/Constant'
   *  DataTypeConversion: '<S135>/Convert_back'
   *  DataTypeConversion: '<S135>/Convert_uint16'
   *  DataTypeConversion: '<S136>/Convert_back'
   *  DataTypeConversion: '<S136>/Convert_uint16'
   *  Gain: '<S20>/indexing'
   *  RelationalOperator: '<S134>/Compare'
   *  Sum: '<S135>/Sum'
   *  Sum: '<S136>/Sum'
   */
  if (rtb_DiscreteTimeIntegrator < 0.0F) {
    /* Outputs for IfAction SubSystem: '<S133>/If Action Subsystem' incorporates:
     *  ActionPort: '<S135>/Action Port'
     */
    tmpForInput_tmp_0 = rtb_DiscreteTimeIntegrator - (real32_T)(int16_T)floorf
      (rtb_DiscreteTimeIntegrator);

    /* End of Outputs for SubSystem: '<S133>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S133>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S136>/Action Port'
     */
    tmpForInput_tmp_0 = rtb_DiscreteTimeIntegrator - (real32_T)(int16_T)
      rtb_DiscreteTimeIntegrator;

    /* End of Outputs for SubSystem: '<S133>/If Action Subsystem1' */
  }

  rtb_DiscreteTimeIntegrator = 800.0F * tmpForInput_tmp_0;

  /* End of If: '<S133>/If' */

  /* Sum: '<S20>/Sum2' incorporates:
   *  DataTypeConversion: '<S20>/Data Type Conversion1'
   *  DataTypeConversion: '<S20>/Get_Integer'
   */
  rtb_Integrator_b = rtb_DiscreteTimeIntegrator - (real32_T)(uint16_T)
    rtb_DiscreteTimeIntegrator;

  /* Selector: '<S20>/Lookup' incorporates:
   *  Constant: '<S20>/sine_table_values'
   *  DataTypeConversion: '<S20>/Get_Integer'
   */
  sin_g = rtConstP.sine_table_values_Value[(uint16_T)rtb_DiscreteTimeIntegrator];

  /* Sum: '<S132>/Sum4' incorporates:
   *  Constant: '<S20>/offset'
   *  Constant: '<S20>/sine_table_values'
   *  DataStoreWrite: '<S3>/Data Store Write2'
   *  DataTypeConversion: '<S20>/Get_Integer'
   *  Product: '<S132>/Product'
   *  Selector: '<S20>/Lookup'
   *  Sum: '<S132>/Sum3'
   *  Sum: '<S20>/Sum'
   */
  sin_g += (rtConstP.sine_table_values_Value[(int32_T)((uint16_T)
             rtb_DiscreteTimeIntegrator + 1U)] - sin_g) * rtb_Integrator_b;

  /* Selector: '<S20>/Lookup' incorporates:
   *  Constant: '<S20>/offset'
   *  Constant: '<S20>/sine_table_values'
   *  DataTypeConversion: '<S20>/Get_Integer'
   *  Sum: '<S132>/Sum5'
   *  Sum: '<S20>/Sum'
   */
  cos_g = rtConstP.sine_table_values_Value[(int32_T)((uint16_T)
    rtb_DiscreteTimeIntegrator + 200U)];

  /* Sum: '<S132>/Sum6' incorporates:
   *  Constant: '<S20>/offset'
   *  Constant: '<S20>/sine_table_values'
   *  DataStoreWrite: '<S3>/Data Store Write3'
   *  DataTypeConversion: '<S20>/Get_Integer'
   *  Product: '<S132>/Product1'
   *  Selector: '<S20>/Lookup'
   *  Sum: '<S132>/Sum5'
   *  Sum: '<S20>/Sum'
   */
  cos_g += (rtConstP.sine_table_values_Value[(int32_T)((uint16_T)
             rtb_DiscreteTimeIntegrator + 201U)] - cos_g) * rtb_Integrator_b;

  /* Outputs for Atomic SubSystem: '<S17>/Two inputs CRL' */
  /* AlgorithmDescriptorDelegate generated from: '<S77>/a16' incorporates:
   *  DataStoreRead: '<S3>/Data Store Read4'
   *  DataStoreRead: '<S3>/Data Store Read5'
   *  Gain: '<S21>/one_by_3'
   *  Gain: '<S21>/one_by_sqrt3_'
   *  Sum: '<S21>/Sum'
   *  Sum: '<S21>/Sum1'
   *  Sum: '<S21>/Sum2'
   */
  arm_park_f32(rtu_ia - 0.333333343F * ((rtu_ia + rtu_ib) + rtu_Ic),
               0.577350259F * (rtu_ib - rtu_Ic), &id_fb, &iq_fb, sin_g, cos_g);

  /* End of Outputs for SubSystem: '<S17>/Two inputs CRL' */

  /* Sum: '<S66>/Sum' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Constant: '<S3>/Id_ref'
   *  DiscreteIntegrator: '<S57>/Integrator'
   *  Product: '<S62>/PProd Out'
   *  Sum: '<S3>/Sum'
   */
  rtb_DiscreteTimeIntegrator = (0.0F - id_fb) * cur_PI.Kp_cur +
    localDW->Integrator_DSTATE;

  /* DeadZone: '<S49>/DeadZone' */
  if (rtb_DiscreteTimeIntegrator > 15.0F) {
    rtb_IProdOut = rtb_DiscreteTimeIntegrator - 15.0F;
  } else if (rtb_DiscreteTimeIntegrator >= -15.0F) {
    rtb_IProdOut = 0.0F;
  } else {
    rtb_IProdOut = rtb_DiscreteTimeIntegrator - -15.0F;
  }

  /* End of DeadZone: '<S49>/DeadZone' */

  /* RelationalOperator: '<S47>/Relational Operator' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   */
  rtb_RelationalOperator_g = (rtb_IProdOut != 0.0F);

  /* Product: '<S54>/IProd Out' incorporates:
   *  Constant: '<S3>/Constant2'
   *  Constant: '<S3>/Id_ref'
   *  Sum: '<S3>/Sum'
   */
  rtb_Integrator_b = (0.0F - id_fb) * cur_PI.Ki_cur;

  /* Switch: '<S47>/Switch1' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   *  Constant: '<S47>/Constant'
   *  Constant: '<S47>/Constant2'
   *  RelationalOperator: '<S47>/fix for DT propagation issue'
   */
  if (rtb_IProdOut > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S47>/Switch2' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   *  Constant: '<S47>/Constant3'
   *  Constant: '<S47>/Constant4'
   *  RelationalOperator: '<S47>/fix for DT propagation issue1'
   */
  if (rtb_Integrator_b > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Saturate: '<S64>/Saturation' */
  if (rtb_DiscreteTimeIntegrator > 15.0F) {
    rtb_Saturation = 15.0F;
  } else if (rtb_DiscreteTimeIntegrator < -15.0F) {
    rtb_Saturation = -15.0F;
  } else {
    rtb_Saturation = rtb_DiscreteTimeIntegrator;
  }

  /* End of Saturate: '<S64>/Saturation' */

  /* Sum: '<S3>/Sum1' incorporates:
   *  DataStoreWrite: '<S3>/Data Store Write'
   */
  rtb_IProdOut = localDW->Merge1 - iq_fb;

  /* Sum: '<S123>/Sum' incorporates:
   *  Constant: '<S3>/Constant1'
   *  DiscreteIntegrator: '<S114>/Integrator'
   *  Product: '<S119>/PProd Out'
   */
  rtb_DiscreteTimeIntegrator = rtb_IProdOut * cur_PI.Kp_cur +
    localDW->Integrator_DSTATE_e;

  /* Saturate: '<S121>/Saturation' incorporates:
   *  DeadZone: '<S106>/DeadZone'
   */
  if (rtb_DiscreteTimeIntegrator > 15.0F) {
    tmpForInput_tmp_0 = 15.0F;
    rtb_DiscreteTimeIntegrator -= 15.0F;
  } else {
    if (rtb_DiscreteTimeIntegrator < -15.0F) {
      tmpForInput_tmp_0 = -15.0F;
    } else {
      tmpForInput_tmp_0 = rtb_DiscreteTimeIntegrator;
    }

    if (rtb_DiscreteTimeIntegrator >= -15.0F) {
      rtb_DiscreteTimeIntegrator = 0.0F;
    } else {
      rtb_DiscreteTimeIntegrator -= -15.0F;
    }
  }

  /* Outputs for Atomic SubSystem: '<S16>/Two inputs CRL' */
  /* AlgorithmDescriptorDelegate generated from: '<S75>/a16' incorporates:
   *  DataStoreRead: '<S3>/Data Store Read2'
   *  DataStoreRead: '<S3>/Data Store Read3'
   *  Saturate: '<S121>/Saturation'
   */
  arm_inv_park_f32(rtb_Saturation, tmpForInput_tmp_0, &rtb_algDD_o1,
                   &rtb_algDD_o2, sin_g, cos_g);

  /* End of Outputs for SubSystem: '<S16>/Two inputs CRL' */

  /* Gain: '<S74>/one_by_two' */
  sin_g = 0.5F * rtb_algDD_o1;

  /* Gain: '<S74>/sqrt3_by_two' */
  cos_g = 0.866025388F * rtb_algDD_o2;

  /* Sum: '<S74>/add_b' */
  rtb_algDD_o2 = cos_g - sin_g;

  /* Sum: '<S74>/add_c' */
  sin_g = (0.0F - sin_g) - cos_g;

  /* Product: '<S111>/IProd Out' incorporates:
   *  Constant: '<S3>/Constant'
   */
  rtb_IProdOut *= cur_PI.Ki_cur;

  /* Outputs for Atomic SubSystem: '<S3>/SVPWM' */
  /* MinMax: '<S131>/Max' incorporates:
   *  MinMax: '<S131>/Min'
   */
  tmpForInput_tmp[0] = rtb_algDD_o1;
  tmpForInput_tmp[1] = rtb_algDD_o2;
  tmpForInput_tmp[2] = sin_g;
  tmpForInput_tmp[3] = rtb_algDD_o1;
  tmpForInput_tmp[4] = rtb_algDD_o2;
  tmpForInput_tmp[5] = sin_g;
  tmpForInput_tmp[6] = rtb_algDD_o1;
  tmpForInput_tmp[7] = rtb_algDD_o2;
  tmpForInput_tmp[8] = sin_g;
  cos_g = rtb_algDD_o1;

  /* MinMax: '<S131>/Min' incorporates:
   *  MinMax: '<S131>/Max'
   */
  rtb_Saturation = rtb_algDD_o1;
  for (k = 0; k < 8; k++) {
    /* MinMax: '<S131>/Max' */
    tmpForInput_tmp_0 = tmpForInput_tmp[k + 1];
    cos_g = fmaxf(cos_g, tmpForInput_tmp_0);

    /* MinMax: '<S131>/Min' */
    rtb_Saturation = fminf(rtb_Saturation, tmpForInput_tmp_0);
  }

  /* Gain: '<S131>/Gain' incorporates:
   *  MinMax: '<S131>/Max'
   *  MinMax: '<S131>/Min'
   *  Sum: '<S131>/Sum'
   */
  cos_g = (cos_g + rtb_Saturation) * -0.5F;

  /* Product: '<S19>/Product1' incorporates:
   *  Constant: '<S19>/Constant'
   *  Constant: '<S3>/PWM_HalfPeriod'
   *  Gain: '<S19>/Gain'
   *  Product: '<S19>/Product'
   *  Sum: '<S19>/Sum'
   *  Sum: '<S19>/Sum1'
   */
  rty_tABC[0] = (-(cos_g + rtb_algDD_o1) / rtu_Vdc + 0.5) * 8000.0;
  rty_tABC[1] = (-(cos_g + rtb_algDD_o2) / rtu_Vdc + 0.5) * 8000.0;
  rty_tABC[2] = (-(cos_g + sin_g) / rtu_Vdc + 0.5) * 8000.0;

  /* End of Outputs for SubSystem: '<S3>/SVPWM' */

  /* Update for UnitDelay: '<S3>/Unit Delay1' */
  localDW->UnitDelay1_DSTATE = rtu_theta_fbk;

  /* Switch: '<S47>/Switch' incorporates:
   *  Constant: '<S47>/Constant1'
   *  Logic: '<S47>/AND3'
   *  RelationalOperator: '<S47>/Equal1'
   *  Switch: '<S47>/Switch1'
   *  Switch: '<S47>/Switch2'
   */
  if (rtb_RelationalOperator_g && (tmp == tmp_0)) {
    rtb_Integrator_b = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S57>/Integrator' incorporates:
   *  Switch: '<S47>/Switch'
   */
  localDW->Integrator_DSTATE += 0.0001F * rtb_Integrator_b;

  /* Switch: '<S104>/Switch1' incorporates:
   *  Constant: '<S104>/Clamping_zero'
   *  Constant: '<S104>/Constant'
   *  Constant: '<S104>/Constant2'
   *  RelationalOperator: '<S104>/fix for DT propagation issue'
   */
  if (rtb_DiscreteTimeIntegrator > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S104>/Switch2' incorporates:
   *  Constant: '<S104>/Clamping_zero'
   *  Constant: '<S104>/Constant3'
   *  Constant: '<S104>/Constant4'
   *  RelationalOperator: '<S104>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S104>/Switch' incorporates:
   *  Constant: '<S104>/Clamping_zero'
   *  Constant: '<S104>/Constant1'
   *  Logic: '<S104>/AND3'
   *  RelationalOperator: '<S104>/Equal1'
   *  RelationalOperator: '<S104>/Relational Operator'
   *  Switch: '<S104>/Switch1'
   *  Switch: '<S104>/Switch2'
   */
  if ((rtb_DiscreteTimeIntegrator != 0.0F) && (tmp == tmp_0)) {
    rtb_IProdOut = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S114>/Integrator' incorporates:
   *  Switch: '<S104>/Switch'
   */
  localDW->Integrator_DSTATE_e += 0.0001F * rtb_IProdOut;
}

/* Model step function */
void Decoder_FOC_step(void)
{
  real32_T Add1;
  real32_T Integrator;
  real32_T rtb_DeadZone;
  real32_T rtb_IntegralGain;
  real32_T rtb_Sum;
  uint32_T speedloop_ELAPS_T;
  int8_T tmp;
  int8_T tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/Decoder_FOC' */
  /* RateTransition: '<S1>/Rate Transition3' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* RateTransition: '<S1>/Rate Transition3' */
    rtDW.RateTransition3 = rtDW.RateTransition3_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition3' */

  /* Outputs for Atomic SubSystem: '<S1>/currloop' */
  /* Inport: '<Root>/Motor_OnOff' incorporates:
   *  Inport: '<Root>/Ia'
   *  Inport: '<Root>/Ib'
   *  Inport: '<Root>/Ic'
   *  Inport: '<Root>/theta_fbk'
   *  Inport: '<Root>/v_bus'
   *  Outport: '<Root>/tABC'
   */
  currloop(rtU.Motor_OnOff, rtDW.RateTransition3, rtU.theta_fbk, rtU.v_bus,
           rtU.Ia, rtU.Ib, rtU.Ic, &rtDW.RestsSingal, rtY.tABC, &rtDW.currloop_d);

  /* End of Outputs for SubSystem: '<S1>/currloop' */

  /* Update for Atomic SubSystem: '<Root>/Decoder_FOC' */
  /* Sum: '<S7>/Add1' incorporates:
   *  Inport: '<Root>/wn_fbk'
   *  Product: '<S7>/Product'
   *  Product: '<S7>/Product1'
   *  UnitDelay: '<S7>/Unit Delay'
   */
  Add1 = rtU.wn_fbk * 0.005F + 0.995F * rtDW.UnitDelay_DSTATE;

  /* End of Outputs for SubSystem: '<Root>/Decoder_FOC' */

  /* RateTransition: '<S1>/Rate Transition2' incorporates:
   *  RateTransition: '<S1>/Rate Transition1'
   */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/speedloop'
     */
    if (rtDW.speedloop_RESET_ELAPS_T) {
      speedloop_ELAPS_T = 0U;
    } else {
      speedloop_ELAPS_T = rtM->Timing.clockTick1 - rtDW.speedloop_PREV_T;
    }

    rtDW.speedloop_PREV_T = rtM->Timing.clockTick1;
    rtDW.speedloop_RESET_ELAPS_T = false;

    /* Sum: '<S4>/Sum2' incorporates:
     *  Inport: '<Root>/SpeedRef'
     */
    rtb_IntegralGain = (real32_T)rtU.SpeedRef - Add1;

    /* DiscreteIntegrator: '<S173>/Integrator' incorporates:
     *  RateTransition: '<S1>/Rate Transition7'
     */
    if (rtDW.Integrator_SYSTEM_ENABLE != 0) {
      /* DiscreteIntegrator: '<S173>/Integrator' */
      Integrator = rtDW.Integrator_DSTATE;
    } else if ((rtDW.RestsSingal > 0.0) && (rtDW.Integrator_PrevResetState <= 0))
    {
      /* DiscreteIntegrator: '<S173>/Integrator' */
      Integrator = 0.0F;
    } else {
      /* DiscreteIntegrator: '<S173>/Integrator' */
      Integrator = (real32_T)(0.001 * (real_T)speedloop_ELAPS_T
        * rtDW.Integrator_PREV_U) + rtDW.Integrator_DSTATE;
    }

    /* End of DiscreteIntegrator: '<S173>/Integrator' */

    /* Sum: '<S182>/Sum' incorporates:
     *  Gain: '<S178>/Proportional Gain'
     */
    rtb_Sum = spd_PI.Kp_spd * rtb_IntegralGain + Integrator;

    /* DeadZone: '<S165>/DeadZone' incorporates:
     *  Saturate: '<S180>/Saturation'
     */
    if (rtb_Sum > 3.0F) {
      rtb_DeadZone = rtb_Sum - 3.0F;

      /* Saturate: '<S180>/Saturation' */
      rtDW.Saturation = 3.0F;
    } else {
      if (rtb_Sum >= -3.0F) {
        rtb_DeadZone = 0.0F;
      } else {
        rtb_DeadZone = rtb_Sum - -3.0F;
      }

      if (rtb_Sum < -3.0F) {
        /* Saturate: '<S180>/Saturation' */
        rtDW.Saturation = -3.0F;
      } else {
        /* Saturate: '<S180>/Saturation' */
        rtDW.Saturation = rtb_Sum;
      }
    }

    /* End of DeadZone: '<S165>/DeadZone' */

    /* Gain: '<S170>/Integral Gain' */
    rtb_IntegralGain *= spd_PI.Ki_spd;

    /* Update for DiscreteIntegrator: '<S173>/Integrator' incorporates:
     *  RateTransition: '<S1>/Rate Transition7'
     */
    rtDW.Integrator_SYSTEM_ENABLE = 0U;
    rtDW.Integrator_DSTATE = Integrator;
    if (rtDW.RestsSingal > 0.0) {
      rtDW.Integrator_PrevResetState = 1;
    } else if (rtDW.RestsSingal < 0.0) {
      rtDW.Integrator_PrevResetState = -1;
    } else if (rtDW.RestsSingal == 0.0) {
      rtDW.Integrator_PrevResetState = 0;
    } else {
      rtDW.Integrator_PrevResetState = 2;
    }

    /* Switch: '<S163>/Switch1' incorporates:
     *  Constant: '<S163>/Clamping_zero'
     *  Constant: '<S163>/Constant'
     *  Constant: '<S163>/Constant2'
     *  RelationalOperator: '<S163>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S163>/Switch2' incorporates:
     *  Constant: '<S163>/Clamping_zero'
     *  Constant: '<S163>/Constant3'
     *  Constant: '<S163>/Constant4'
     *  RelationalOperator: '<S163>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S163>/Switch' incorporates:
     *  Constant: '<S163>/Clamping_zero'
     *  Logic: '<S163>/AND3'
     *  RelationalOperator: '<S163>/Equal1'
     *  RelationalOperator: '<S163>/Relational Operator'
     *  Switch: '<S163>/Switch1'
     *  Switch: '<S163>/Switch2'
     */
    if ((rtb_DeadZone != 0.0F) && (tmp == tmp_0)) {
      /* Update for DiscreteIntegrator: '<S173>/Integrator' incorporates:
       *  Constant: '<S163>/Constant1'
       */
      rtDW.Integrator_PREV_U = 0.0F;
    } else {
      /* Update for DiscreteIntegrator: '<S173>/Integrator' */
      rtDW.Integrator_PREV_U = rtb_IntegralGain;
    }

    /* End of Switch: '<S163>/Switch' */
    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */
  }

  /* End of RateTransition: '<S1>/Rate Transition2' */

  /* Update for UnitDelay: '<S7>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = Add1;

  /* Update for RateTransition: '<S1>/Rate Transition3' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    rtDW.RateTransition3_Buffer0 = rtDW.Saturation;
  }

  /* End of Update for RateTransition: '<S1>/Rate Transition3' */
  /* End of Update for SubSystem: '<Root>/Decoder_FOC' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }

  rate_scheduler();
}

/* Model initialize function */
void Decoder_FOC_initialize(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/Decoder_FOC' */
  /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S173>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' */

  /* SystemInitialize for Atomic SubSystem: '<S1>/currloop' */
  currloop_Init(&rtDW.RestsSingal, &rtDW.currloop_d);

  /* End of SystemInitialize for SubSystem: '<S1>/currloop' */
  /* End of SystemInitialize for SubSystem: '<Root>/Decoder_FOC' */

  /* Enable for Atomic SubSystem: '<Root>/Decoder_FOC' */
  /* Enable for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  rtDW.speedloop_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S173>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE = 1U;

  /* End of Enable for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of Enable for SubSystem: '<Root>/Decoder_FOC' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
