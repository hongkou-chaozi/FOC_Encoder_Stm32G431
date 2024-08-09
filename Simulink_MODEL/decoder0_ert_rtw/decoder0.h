/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: decoder0.h
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

#ifndef decoder0_h_
#define decoder0_h_
#ifndef decoder0_COMMON_INCLUDES_
#define decoder0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* decoder0_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S1>/Decoder_Step' */
typedef struct {
  real32_T UnitDelay_DSTATE;           /* '<S9>/Unit Delay' */
  uint32_T Delay_DSTATE[30];           /* '<S6>/Delay' */
  uint32_T CircBufIdx;                 /* '<S6>/Delay' */
} DW_Decoder_Step;

/* Block signals and states (default storage) for system '<Root>/decoder' */
typedef struct {
  DW_Decoder_Step Decoder_Step_h;      /* '<S1>/Decoder_Step' */
  real32_T Encoder_offset;             /* '<S1>/Data Store Memory' */
  real32_T Cnt_per_Rev;                /* '<S1>/Data Store Memory3' */
  uint32_T EncoderCnt;                 /* '<S1>/Data Store Memory1' */
  uint32_T EncoderIdx;                 /* '<S1>/Data Store Memory2' */
} DW_decoder;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_decoder decoder_o;                /* '<Root>/decoder' */
} DW;

/* Type definition for custom storage class: Struct */
typedef struct PMSM_Para_tag {
  real32_T Pn;                 /* Referenced by: '<S17>/Number of pole pairs' */
} PMSM_Para_type;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* Model entry point functions */
extern void decoder0_initialize(void);
extern void decoder0_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern PMSM_Para_type PMSM_Para;

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/ReplaceInport_Npp' : Unused code path elimination
 * Block '<S6>/DataTypeSet' : Unused code path elimination
 * Block '<S6>/fixdtDatatype' : Unused code path elimination
 * Block '<S3>/One' : Unused code path elimination
 * Block '<S3>/Sum' : Unused code path elimination
 * Block '<S3>/UseInputPort' : Unused code path elimination
 * Block '<S3>/a' : Unused code path elimination
 * Block '<S11>/Constant' : Unused code path elimination
 * Block '<S11>/Constant1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('decoder/decoder')    - opens subsystem decoder/decoder
 * hilite_system('decoder/decoder/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'decoder'
 * '<S1>'   : 'decoder/decoder'
 * '<S2>'   : 'decoder/decoder/Decoder_Step'
 * '<S3>'   : 'decoder/decoder/Decoder_Step/IIR Filter'
 * '<S4>'   : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position'
 * '<S5>'   : 'decoder/decoder/Decoder_Step/Quadrature Decoder'
 * '<S6>'   : 'decoder/decoder/Decoder_Step/Speed Measurement'
 * '<S7>'   : 'decoder/decoder/Decoder_Step/IIR Filter/IIR Filter'
 * '<S8>'   : 'decoder/decoder/Decoder_Step/IIR Filter/IIR Filter/Low-pass'
 * '<S9>'   : 'decoder/decoder/Decoder_Step/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S10>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec'
 * '<S11>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point'
 * '<S12>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point/Compensate Offset'
 * '<S13>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point/Mech To Elec'
 * '<S14>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point/Compensate Offset/If Action Subsystem'
 * '<S15>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point/Compensate Offset/If Action Subsystem1'
 * '<S16>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point/Mech To Elec/Variant Subsystem'
 * '<S17>'  : 'decoder/decoder/Decoder_Step/Mechanical to Electrical Position/MechToElec/floating-point/Mech To Elec/Variant Subsystem/Dialog'
 * '<S18>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/DT_Handle'
 * '<S19>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/PositionNoReset'
 * '<S20>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/PositionResetAtIndex'
 * '<S21>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/Variant Subsystem'
 * '<S22>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/DT_Handle/floating-point'
 * '<S23>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/PositionNoReset/Variant Subsystem'
 * '<S24>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/PositionNoReset/Variant Subsystem/Input Port'
 * '<S25>'  : 'decoder/decoder/Decoder_Step/Quadrature Decoder/Variant Subsystem/Input Port'
 * '<S26>'  : 'decoder/decoder/Decoder_Step/Speed Measurement/DT_Handle'
 * '<S27>'  : 'decoder/decoder/Decoder_Step/Speed Measurement/DT_Handle/floating-point'
 */
#endif                                 /* decoder0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
