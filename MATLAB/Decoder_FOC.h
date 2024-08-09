/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Decoder_FOC.h
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

#ifndef Decoder_FOC_h_
#define Decoder_FOC_h_
#ifndef Decoder_FOC_COMMON_INCLUDES_
#define Decoder_FOC_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Decoder_FOC_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<S1>/currloop' */
typedef struct {
  real32_T Merge1;                     /* '<S3>/Merge1' */
  real32_T Merge;                      /* '<S3>/Merge' */
  real32_T Motor_state;                /* '<S3>/Chart1' */
  real32_T ZReset;                     /* '<S3>/Chart1' */
  real32_T UnitDelay1_DSTATE;          /* '<S3>/Unit Delay1' */
  real32_T Integrator_DSTATE;          /* '<S57>/Integrator' */
  real32_T Integrator_DSTATE_e;        /* '<S114>/Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S13>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S13>/Discrete-Time Integrator1' */
  real32_T cnt;                        /* '<S3>/Chart1' */
  uint16_T temporalCounter_i1;         /* '<S3>/Chart1' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S13>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S13>/Discrete-Time Integrator1' */
  uint8_T is_active_c7_Decoder_FOC;    /* '<S3>/Chart1' */
  uint8_T is_c7_Decoder_FOC;           /* '<S3>/Chart1' */
} DW_currloop;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_currloop currloop_d;              /* '<S1>/currloop' */
  real_T RestsSingal;                  /* '<S3>/Chart1' */
  real32_T RateTransition3;            /* '<S1>/Rate Transition3' */
  real32_T Saturation;                 /* '<S180>/Saturation' */
  real32_T UnitDelay_DSTATE;           /* '<S7>/Unit Delay' */
  real32_T Integrator_DSTATE;          /* '<S173>/Integrator' */
  real32_T RateTransition3_Buffer0;    /* '<S1>/Rate Transition3' */
  real32_T Integrator_PREV_U;          /* '<S173>/Integrator' */
  uint32_T speedloop_PREV_T;           /* '<S1>/speedloop' */
  int8_T Integrator_PrevResetState;    /* '<S173>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S173>/Integrator' */
  boolean_T speedloop_RESET_ELAPS_T;   /* '<S1>/speedloop' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: sine_table_values_Value
   * Referenced by: '<S20>/sine_table_values'
   */
  real32_T sine_table_values_Value[1002];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T v_bus;                      /* '<Root>/v_bus' */
  real32_T Motor_OnOff;                /* '<Root>/Motor_OnOff' */
  real_T SpeedRef;                     /* '<Root>/SpeedRef' */
  real32_T Ia;                         /* '<Root>/Ia' */
  real32_T Ib;                         /* '<Root>/Ib' */
  real32_T Ic;                         /* '<Root>/Ic' */
  real32_T theta_fbk;                  /* '<Root>/theta_fbk' */
  real32_T wn_fbk;                     /* '<Root>/wn_fbk' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T tABC[3];                      /* '<Root>/tABC' */
} ExtY;

/* Type definition for custom storage class: Struct */
typedef struct PMSM_Para_tag {
  real32_T Pn;                         /* Referenced by: '<S13>/Gain' */
} PMSM_Para_type;

typedef struct cur_PI_tag {
  real32_T Ki_cur;                     /* Referenced by:
                                        * '<S3>/Constant'
                                        * '<S3>/Constant2'
                                        */
  real32_T Kp_cur;                     /* Referenced by:
                                        * '<S3>/Constant1'
                                        * '<S3>/Constant3'
                                        */
} cur_PI_type;

typedef struct spd_PI_tag {
  real32_T Ki_spd;                   /* Referenced by: '<S170>/Integral Gain' */
  real32_T Kp_spd;               /* Referenced by: '<S178>/Proportional Gain' */
} spd_PI_type;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T id_fb;                 /*  */
extern real32_T iq_fb;                 /*  */

/* Model entry point functions */
extern void Decoder_FOC_initialize(void);
extern void Decoder_FOC_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern PMSM_Para_type PMSM_Para;
extern cur_PI_type cur_PI;
extern spd_PI_type spd_PI;

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Scope' : Unused code path elimination
 * Block '<S13>/Scope1' : Unused code path elimination
 * Block '<S74>/Data Type Duplicate' : Unused code path elimination
 * Block '<S75>/Data Type Duplicate' : Unused code path elimination
 * Block '<S75>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S77>/Data Type Duplicate' : Unused code path elimination
 * Block '<S77>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S19>/Scope' : Unused code path elimination
 * Block '<S19>/Scope4' : Unused code path elimination
 * Block '<S131>/Scope' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S3>/Scope1' : Unused code path elimination
 * Block '<S3>/Scope10' : Unused code path elimination
 * Block '<S3>/Scope2' : Unused code path elimination
 * Block '<S3>/Scope3' : Unused code path elimination
 * Block '<S3>/Scope4' : Unused code path elimination
 * Block '<S3>/Scope5' : Unused code path elimination
 * Block '<S3>/Scope8' : Unused code path elimination
 * Block '<S3>/Scope9' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Propagation' : Unused code path elimination
 * Block '<S135>/Data Type Duplicate' : Unused code path elimination
 * Block '<S136>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S1>/Rate Transition' : Eliminated since input and output rates are identical
 * Block '<S1>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S21>/Kalphabeta0' : Eliminated nontunable gain of 1
 * Block '<S3>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S3>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S3>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S3>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S74>/Ka' : Eliminated nontunable gain of 1
 * Block '<S74>/Kb' : Eliminated nontunable gain of 1
 * Block '<S74>/Kc' : Eliminated nontunable gain of 1
 * Block '<S20>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<S2>/One' : Unused code path elimination
 * Block '<S2>/Sum' : Unused code path elimination
 * Block '<S2>/UseInputPort' : Unused code path elimination
 * Block '<S2>/a' : Unused code path elimination
 * Block '<S76>/Offset' : Unused code path elimination
 * Block '<S76>/Unary_Minus' : Unused code path elimination
 * Block '<S78>/Offset' : Unused code path elimination
 * Block '<S78>/Unary_Minus' : Unused code path elimination
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
 * hilite_system('decoder/Decoder_FOC')    - opens subsystem decoder/Decoder_FOC
 * hilite_system('decoder/Decoder_FOC/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'decoder'
 * '<S1>'   : 'decoder/Decoder_FOC'
 * '<S2>'   : 'decoder/Decoder_FOC/IIR Filter'
 * '<S3>'   : 'decoder/Decoder_FOC/currloop'
 * '<S4>'   : 'decoder/Decoder_FOC/speedloop'
 * '<S5>'   : 'decoder/Decoder_FOC/IIR Filter/IIR Filter'
 * '<S6>'   : 'decoder/Decoder_FOC/IIR Filter/IIR Filter/Low-pass'
 * '<S7>'   : 'decoder/Decoder_FOC/IIR Filter/IIR Filter/Low-pass/IIR Low Pass Filter'
 * '<S8>'   : 'decoder/Decoder_FOC/currloop/Chart1'
 * '<S9>'   : 'decoder/Decoder_FOC/currloop/Clarke Transform'
 * '<S10>'  : 'decoder/Decoder_FOC/currloop/D_Loop'
 * '<S11>'  : 'decoder/Decoder_FOC/currloop/If Action Subsystem'
 * '<S12>'  : 'decoder/Decoder_FOC/currloop/If Action Subsystem1'
 * '<S13>'  : 'decoder/Decoder_FOC/currloop/If Action Subsystem2'
 * '<S14>'  : 'decoder/Decoder_FOC/currloop/If Action Subsystem3'
 * '<S15>'  : 'decoder/Decoder_FOC/currloop/Inverse Clarke Transform'
 * '<S16>'  : 'decoder/Decoder_FOC/currloop/Inverse Park Transform'
 * '<S17>'  : 'decoder/Decoder_FOC/currloop/Park Transform'
 * '<S18>'  : 'decoder/Decoder_FOC/currloop/Q_Loop'
 * '<S19>'  : 'decoder/Decoder_FOC/currloop/SVPWM'
 * '<S20>'  : 'decoder/Decoder_FOC/currloop/Sine-Cosine Lookup'
 * '<S21>'  : 'decoder/Decoder_FOC/currloop/Clarke Transform/Three phase input'
 * '<S22>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Anti-windup'
 * '<S23>'  : 'decoder/Decoder_FOC/currloop/D_Loop/D Gain'
 * '<S24>'  : 'decoder/Decoder_FOC/currloop/D_Loop/External Derivative'
 * '<S25>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Filter'
 * '<S26>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Filter ICs'
 * '<S27>'  : 'decoder/Decoder_FOC/currloop/D_Loop/I Gain'
 * '<S28>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Ideal P Gain'
 * '<S29>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Ideal P Gain Fdbk'
 * '<S30>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Integrator'
 * '<S31>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Integrator ICs'
 * '<S32>'  : 'decoder/Decoder_FOC/currloop/D_Loop/N Copy'
 * '<S33>'  : 'decoder/Decoder_FOC/currloop/D_Loop/N Gain'
 * '<S34>'  : 'decoder/Decoder_FOC/currloop/D_Loop/P Copy'
 * '<S35>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Parallel P Gain'
 * '<S36>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Reset Signal'
 * '<S37>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Saturation'
 * '<S38>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Saturation Fdbk'
 * '<S39>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Sum'
 * '<S40>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Sum Fdbk'
 * '<S41>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tracking Mode'
 * '<S42>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tracking Mode Sum'
 * '<S43>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tsamp - Integral'
 * '<S44>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tsamp - Ngain'
 * '<S45>'  : 'decoder/Decoder_FOC/currloop/D_Loop/postSat Signal'
 * '<S46>'  : 'decoder/Decoder_FOC/currloop/D_Loop/preSat Signal'
 * '<S47>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Anti-windup/Disc. Clamping Parallel'
 * '<S48>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S49>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S50>'  : 'decoder/Decoder_FOC/currloop/D_Loop/D Gain/Disabled'
 * '<S51>'  : 'decoder/Decoder_FOC/currloop/D_Loop/External Derivative/Disabled'
 * '<S52>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Filter/Disabled'
 * '<S53>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Filter ICs/Disabled'
 * '<S54>'  : 'decoder/Decoder_FOC/currloop/D_Loop/I Gain/External Parameters'
 * '<S55>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Ideal P Gain/Passthrough'
 * '<S56>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Ideal P Gain Fdbk/Disabled'
 * '<S57>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Integrator/Discrete'
 * '<S58>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Integrator ICs/Internal IC'
 * '<S59>'  : 'decoder/Decoder_FOC/currloop/D_Loop/N Copy/Disabled wSignal Specification'
 * '<S60>'  : 'decoder/Decoder_FOC/currloop/D_Loop/N Gain/Disabled'
 * '<S61>'  : 'decoder/Decoder_FOC/currloop/D_Loop/P Copy/Disabled'
 * '<S62>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Parallel P Gain/External Parameters'
 * '<S63>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Reset Signal/Disabled'
 * '<S64>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Saturation/Enabled'
 * '<S65>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Saturation Fdbk/Disabled'
 * '<S66>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Sum/Sum_PI'
 * '<S67>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Sum Fdbk/Disabled'
 * '<S68>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tracking Mode/Disabled'
 * '<S69>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tracking Mode Sum/Passthrough'
 * '<S70>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tsamp - Integral/TsSignalSpecification'
 * '<S71>'  : 'decoder/Decoder_FOC/currloop/D_Loop/Tsamp - Ngain/Passthrough'
 * '<S72>'  : 'decoder/Decoder_FOC/currloop/D_Loop/postSat Signal/Forward_Path'
 * '<S73>'  : 'decoder/Decoder_FOC/currloop/D_Loop/preSat Signal/Forward_Path'
 * '<S74>'  : 'decoder/Decoder_FOC/currloop/Inverse Clarke Transform/Two phase input'
 * '<S75>'  : 'decoder/Decoder_FOC/currloop/Inverse Park Transform/Two inputs CRL'
 * '<S76>'  : 'decoder/Decoder_FOC/currloop/Inverse Park Transform/Two inputs CRL/Switch_Axis'
 * '<S77>'  : 'decoder/Decoder_FOC/currloop/Park Transform/Two inputs CRL'
 * '<S78>'  : 'decoder/Decoder_FOC/currloop/Park Transform/Two inputs CRL/Switch_Axis'
 * '<S79>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Anti-windup'
 * '<S80>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/D Gain'
 * '<S81>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/External Derivative'
 * '<S82>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Filter'
 * '<S83>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Filter ICs'
 * '<S84>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/I Gain'
 * '<S85>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Ideal P Gain'
 * '<S86>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Ideal P Gain Fdbk'
 * '<S87>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Integrator'
 * '<S88>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Integrator ICs'
 * '<S89>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/N Copy'
 * '<S90>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/N Gain'
 * '<S91>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/P Copy'
 * '<S92>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Parallel P Gain'
 * '<S93>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Reset Signal'
 * '<S94>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Saturation'
 * '<S95>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Saturation Fdbk'
 * '<S96>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Sum'
 * '<S97>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Sum Fdbk'
 * '<S98>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Tracking Mode'
 * '<S99>'  : 'decoder/Decoder_FOC/currloop/Q_Loop/Tracking Mode Sum'
 * '<S100>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Tsamp - Integral'
 * '<S101>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Tsamp - Ngain'
 * '<S102>' : 'decoder/Decoder_FOC/currloop/Q_Loop/postSat Signal'
 * '<S103>' : 'decoder/Decoder_FOC/currloop/Q_Loop/preSat Signal'
 * '<S104>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Anti-windup/Disc. Clamping Parallel'
 * '<S105>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S106>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S107>' : 'decoder/Decoder_FOC/currloop/Q_Loop/D Gain/Disabled'
 * '<S108>' : 'decoder/Decoder_FOC/currloop/Q_Loop/External Derivative/Disabled'
 * '<S109>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Filter/Disabled'
 * '<S110>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Filter ICs/Disabled'
 * '<S111>' : 'decoder/Decoder_FOC/currloop/Q_Loop/I Gain/External Parameters'
 * '<S112>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Ideal P Gain/Passthrough'
 * '<S113>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Ideal P Gain Fdbk/Disabled'
 * '<S114>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Integrator/Discrete'
 * '<S115>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Integrator ICs/Internal IC'
 * '<S116>' : 'decoder/Decoder_FOC/currloop/Q_Loop/N Copy/Disabled wSignal Specification'
 * '<S117>' : 'decoder/Decoder_FOC/currloop/Q_Loop/N Gain/Disabled'
 * '<S118>' : 'decoder/Decoder_FOC/currloop/Q_Loop/P Copy/Disabled'
 * '<S119>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Parallel P Gain/External Parameters'
 * '<S120>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Reset Signal/Disabled'
 * '<S121>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Saturation/Enabled'
 * '<S122>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Saturation Fdbk/Disabled'
 * '<S123>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Sum/Sum_PI'
 * '<S124>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Sum Fdbk/Disabled'
 * '<S125>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Tracking Mode/Disabled'
 * '<S126>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Tracking Mode Sum/Passthrough'
 * '<S127>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Tsamp - Integral/TsSignalSpecification'
 * '<S128>' : 'decoder/Decoder_FOC/currloop/Q_Loop/Tsamp - Ngain/Passthrough'
 * '<S129>' : 'decoder/Decoder_FOC/currloop/Q_Loop/postSat Signal/Forward_Path'
 * '<S130>' : 'decoder/Decoder_FOC/currloop/Q_Loop/preSat Signal/Forward_Path'
 * '<S131>' : 'decoder/Decoder_FOC/currloop/SVPWM/ie_t'
 * '<S132>' : 'decoder/Decoder_FOC/currloop/Sine-Cosine Lookup/Interpolation'
 * '<S133>' : 'decoder/Decoder_FOC/currloop/Sine-Cosine Lookup/WrapUp'
 * '<S134>' : 'decoder/Decoder_FOC/currloop/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S135>' : 'decoder/Decoder_FOC/currloop/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S136>' : 'decoder/Decoder_FOC/currloop/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S137>' : 'decoder/Decoder_FOC/speedloop/PID Controller3'
 * '<S138>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Anti-windup'
 * '<S139>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/D Gain'
 * '<S140>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/External Derivative'
 * '<S141>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Filter'
 * '<S142>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Filter ICs'
 * '<S143>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/I Gain'
 * '<S144>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Ideal P Gain'
 * '<S145>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Ideal P Gain Fdbk'
 * '<S146>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Integrator'
 * '<S147>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Integrator ICs'
 * '<S148>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/N Copy'
 * '<S149>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/N Gain'
 * '<S150>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/P Copy'
 * '<S151>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Parallel P Gain'
 * '<S152>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Reset Signal'
 * '<S153>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Saturation'
 * '<S154>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Saturation Fdbk'
 * '<S155>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Sum'
 * '<S156>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Sum Fdbk'
 * '<S157>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tracking Mode'
 * '<S158>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tracking Mode Sum'
 * '<S159>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tsamp - Integral'
 * '<S160>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tsamp - Ngain'
 * '<S161>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/postSat Signal'
 * '<S162>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/preSat Signal'
 * '<S163>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S164>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S165>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S166>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/D Gain/Disabled'
 * '<S167>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/External Derivative/Disabled'
 * '<S168>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Filter/Disabled'
 * '<S169>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Filter ICs/Disabled'
 * '<S170>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/I Gain/Internal Parameters'
 * '<S171>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Ideal P Gain/Passthrough'
 * '<S172>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S173>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Integrator/Discrete'
 * '<S174>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Integrator ICs/Internal IC'
 * '<S175>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S176>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/N Gain/Disabled'
 * '<S177>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/P Copy/Disabled'
 * '<S178>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S179>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Reset Signal/External Reset'
 * '<S180>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Saturation/Enabled'
 * '<S181>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Saturation Fdbk/Disabled'
 * '<S182>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Sum/Sum_PI'
 * '<S183>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Sum Fdbk/Disabled'
 * '<S184>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tracking Mode/Disabled'
 * '<S185>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S186>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S187>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S188>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/postSat Signal/Forward_Path'
 * '<S189>' : 'decoder/Decoder_FOC/speedloop/PID Controller3/preSat Signal/Forward_Path'
 */
#endif                                 /* Decoder_FOC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
