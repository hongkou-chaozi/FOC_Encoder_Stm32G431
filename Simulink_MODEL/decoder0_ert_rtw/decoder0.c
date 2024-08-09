/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: decoder0.c
 *
 * Code generated for Simulink model 'decoder0'.
 *
 * Model version                  : 2.9
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Jul  2 20:50:11 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "decoder0.h"
#include "rtwtypes.h"
#include <math.h>

/* Exported data definition */

/* Definition for custom storage class: Struct */
PMSM_Para_type PMSM_Para = {
  /* Pn */
  5.0F
};

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void Decoder_Step(const real32_T *rtd_Cnt_per_Rev, const uint32_T
  *rtd_EncoderCnt, const uint32_T *rtd_EncoderIdx, real32_T *rtd_EncoderRPM,
  real32_T *rtd_Encoder_eleAngle, const real32_T *rtd_Encoder_offset,
  DW_Decoder_Step *localDW);
static void decoder(DW_decoder *localDW);

/* Output and update for atomic system: '<S1>/Decoder_Step' */
static void Decoder_Step(const real32_T *rtd_Cnt_per_Rev, const uint32_T
  *rtd_EncoderCnt, const uint32_T *rtd_EncoderIdx, real32_T *rtd_EncoderRPM,
  real32_T *rtd_Encoder_eleAngle, const real32_T *rtd_Encoder_offset,
  DW_Decoder_Step *localDW)
{
  real32_T rtb_Product;
  real32_T rtb_Product_m;
  uint32_T rtb_Delay;
  uint32_T u1;

  /* Outputs for IfAction SubSystem: '<S5>/PositionNoReset' incorporates:
   *  ActionPort: '<S19>/Action Port'
   */
  /* If: '<S5>/If1' incorporates:
   *  DataStoreRead: '<S2>/Data Store Read1'
   *  DataStoreRead: '<S2>/Data Store Read2'
   *  DataStoreRead: '<S2>/Data Store Read3'
   *  DataTypeConversion: '<S22>/DTC'
   *  DataTypeConversion: '<S24>/Data Type Conversion'
   *  Fcn: '<S2>/Fcn'
   *  Gain: '<S25>/Gain'
   *  MinMax: '<S19>/MinMax'
   *  Product: '<S5>/Product'
   *  Sum: '<S19>/Sum3'
   *  Sum: '<S19>/Sum7'
   */
  rtb_Delay = *rtd_EncoderCnt - *rtd_EncoderIdx;
  u1 = rtb_Delay + (uint32_T)*rtd_Cnt_per_Rev;
  if (rtb_Delay <= u1) {
    u1 = rtb_Delay;
  }

  rtb_Product = 1.0F / *rtd_Cnt_per_Rev * 6.28318548F * (real32_T)u1;

  /* End of If: '<S5>/If1' */
  /* End of Outputs for SubSystem: '<S5>/PositionNoReset' */

  /* If: '<S12>/If' incorporates:
   *  Constant: '<S14>/Constant'
   *  DataStoreRead: '<S2>/Data Store Read'
   *  Gain: '<S17>/Number of pole pairs'
   *  Sum: '<S14>/Add'
   *  Sum: '<S15>/Add'
   *  Switch: '<S11>/Switch'
   */
  if (rtb_Product <= *rtd_Encoder_offset) {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    rtb_Product_m = (rtb_Product + 6.28318548F) - *rtd_Encoder_offset;

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    rtb_Product_m = rtb_Product - *rtd_Encoder_offset;

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem1' */
  }

  rtb_Product_m *= PMSM_Para.Pn;

  /* End of If: '<S12>/If' */

  /* Sum: '<S13>/Add' incorporates:
   *  DataStoreWrite: '<S2>/Data Store Write'
   *  Gain: '<S13>/Multiply'
   *  Gain: '<S13>/Multiply1'
   *  Rounding: '<S13>/Floor'
   */
  *rtd_Encoder_eleAngle = rtb_Product_m - floorf(0.159154937F * rtb_Product_m) *
    6.28318548F;

  /* DataTypeConversion: '<S6>/AlgoDataType' incorporates:
   *  Constant: '<S6>/PositionToCount'
   *  Product: '<S6>/Product'
   */
  rtb_Delay = (uint32_T)(6.83563648E+8F * rtb_Product);

  /* Sum: '<S9>/Add1' incorporates:
   *  DataStoreWrite: '<S2>/Data Store Write1'
   *  DataTypeConversion: '<S27>/DTC'
   *  Delay: '<S6>/Delay'
   *  Gain: '<S6>/SpeedGain'
   *  Product: '<S9>/Product'
   *  Product: '<S9>/Product1'
   *  Sum: '<S6>/SpeedCount'
   *  UnitDelay: '<S9>/Unit Delay'
   */
  *rtd_EncoderRPM = (real32_T)((int32_T)rtb_Delay - (int32_T)
    localDW->Delay_DSTATE[localDW->CircBufIdx]) * 4.65661287E-6F * 0.01F + 0.99F
    * localDW->UnitDelay_DSTATE;

  /* Update for Delay: '<S6>/Delay' */
  localDW->Delay_DSTATE[localDW->CircBufIdx] = rtb_Delay;
  if (localDW->CircBufIdx < 29U) {
    localDW->CircBufIdx++;
  } else {
    localDW->CircBufIdx = 0U;
  }

  /* End of Update for Delay: '<S6>/Delay' */

  /* Update for UnitDelay: '<S9>/Unit Delay' incorporates:
   *  DataStoreWrite: '<S2>/Data Store Write1'
   */
  localDW->UnitDelay_DSTATE = *rtd_EncoderRPM;
}

/* Output and update for atomic system: '<Root>/decoder' */
static void decoder(DW_decoder *localDW)
{
  real32_T EncoderRPM;
  real32_T Encoder_eleAngle;

  /* Outputs for Atomic SubSystem: '<S1>/Decoder_Step' */
  Decoder_Step(&localDW->Cnt_per_Rev, &localDW->EncoderCnt, &localDW->EncoderIdx,
               &EncoderRPM, &Encoder_eleAngle, &localDW->Encoder_offset,
               &localDW->Decoder_Step_h);

  /* End of Outputs for SubSystem: '<S1>/Decoder_Step' */
}

/* Model step function */
void decoder0_step(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/decoder' */
  decoder(&rtDW.decoder_o);

  /* End of Outputs for SubSystem: '<Root>/decoder' */
}

/* Model initialize function */
void decoder0_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
