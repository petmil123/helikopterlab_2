/*
 * helicopter_R2016b.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_R2016b".
 *
 * Model version              : 3.0
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Feb 13 10:05:10 2025
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_R2016b.h"
#include "helicopter_R2016b_private.h"
#include "helicopter_R2016b_dt.h"

/* Block signals (default storage) */
B_helicopter_R2016b_T helicopter_R2016b_B;

/* Continuous states */
X_helicopter_R2016b_T helicopter_R2016b_X;

/* Block states (default storage) */
DW_helicopter_R2016b_T helicopter_R2016b_DW;

/* Real-time model */
static RT_MODEL_helicopter_R2016b_T helicopter_R2016b_M_;
RT_MODEL_helicopter_R2016b_T *const helicopter_R2016b_M = &helicopter_R2016b_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_R2016b_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_R2016b_output(void)
{
  /* local block i/o variables */
  real_T rtb_Clock;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_Backgain;
  real_T rtb_Clock_tmp;
  real_T rtb_Derivative;
  real_T rtb_K_pp;
  real_T *lastU;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    /* set solver stop time */
    if (!(helicopter_R2016b_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_R2016b_M->solverInfo,
                            ((helicopter_R2016b_M->Timing.clockTickH0 + 1) *
        helicopter_R2016b_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_R2016b_M->solverInfo,
                            ((helicopter_R2016b_M->Timing.clockTick0 + 1) *
        helicopter_R2016b_M->Timing.stepSize0 +
        helicopter_R2016b_M->Timing.clockTickH0 *
        helicopter_R2016b_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_R2016b_M)) {
    helicopter_R2016b_M->Timing.t[0] = rtsiGetT(&helicopter_R2016b_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_R2016b_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_R2016b/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_R2016b_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_R2016b_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_R2016b_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_R2016b_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_R2016b_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_R2016b_B.TravelCounttorad = helicopter_R2016b_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_R2016b_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter_R2016b_B.Gain = helicopter_R2016b_P.Gain_Gain *
      helicopter_R2016b_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_R2016b_B.PitchCounttorad =
      helicopter_R2016b_P.PitchCounttorad_Gain * rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter_R2016b_B.Gain_i = helicopter_R2016b_P.Gain_Gain_a *
      helicopter_R2016b_B.PitchCounttorad;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_R2016b_P.TravelTransferFcn_C *
    helicopter_R2016b_X.TravelTransferFcn_CSTATE;
  rtb_Clock += helicopter_R2016b_P.TravelTransferFcn_D *
    helicopter_R2016b_B.TravelCounttorad;

  /* Gain: '<S13>/Gain' */
  helicopter_R2016b_B.Gain_d = helicopter_R2016b_P.Gain_Gain_l * rtb_Clock;

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_R2016b_P.PitchTransferFcn_C *
    helicopter_R2016b_X.PitchTransferFcn_CSTATE;
  rtb_Clock += helicopter_R2016b_P.PitchTransferFcn_D *
    helicopter_R2016b_B.PitchCounttorad;

  /* Gain: '<S10>/Gain' */
  helicopter_R2016b_B.Gain_b = helicopter_R2016b_P.Gain_Gain_ae * rtb_Clock;
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_R2016b_B.ElevationCounttorad = helicopter_R2016b_P.elevation_gain
      * rtb_HILReadEncoderTimebase_o3 *
      helicopter_R2016b_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter_R2016b_B.Gain_e = helicopter_R2016b_P.Gain_Gain_lv *
      helicopter_R2016b_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_R2016b_B.Sum = helicopter_R2016b_B.Gain_e +
      helicopter_R2016b_P.elavation_offsetdeg_Value;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_R2016b_P.ElevationTransferFcn_C *
    helicopter_R2016b_X.ElevationTransferFcn_CSTATE;
  rtb_Clock += helicopter_R2016b_P.ElevationTransferFcn_D *
    helicopter_R2016b_B.ElevationCounttorad;

  /* Gain: '<S8>/Gain' */
  helicopter_R2016b_B.Gain_dg = helicopter_R2016b_P.Gain_Gain_n * rtb_Clock;
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    rtb_TmpSignalConversionAtToFile[0] = helicopter_R2016b_B.Gain;
    rtb_TmpSignalConversionAtToFile[1] = helicopter_R2016b_B.Gain_d;
    rtb_TmpSignalConversionAtToFile[2] = helicopter_R2016b_B.Gain_i;
    rtb_TmpSignalConversionAtToFile[3] = helicopter_R2016b_B.Gain_b;
    rtb_TmpSignalConversionAtToFile[4] = helicopter_R2016b_B.Sum;
    rtb_TmpSignalConversionAtToFile[5] = helicopter_R2016b_B.Gain_dg;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_R2016b_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_R2016b_DW.ToFile_IWORK.Count * (6 + 1)) + 1 < 100000000 )
      {
        FILE *fp = (FILE *) helicopter_R2016b_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          helicopter_R2016b_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_R2016b_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFile[0];
          u[2] = rtb_TmpSignalConversionAtToFile[1];
          u[3] = rtb_TmpSignalConversionAtToFile[2];
          u[4] = rtb_TmpSignalConversionAtToFile[3];
          u[5] = rtb_TmpSignalConversionAtToFile[4];
          u[6] = rtb_TmpSignalConversionAtToFile[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(helicopter_R2016b_M,
                              "Error writing to MAT-file simdata.mat");
            return;
          }

          if (((++helicopter_R2016b_DW.ToFile_IWORK.Count) * (6 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file simdata.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_R2016b_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_R2016b_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_R2016b_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter_R2016b_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_R2016b_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Clock = pDataValues[currTimeIndex];
        } else {
          rtb_Clock = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Clock = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Sum: '<S5>/Sum2'
   */
  rtb_Clock -= helicopter_R2016b_P.Gain1_Gain * helicopter_R2016b_B.Gain_i;

  /* Gain: '<S5>/K_pp' */
  rtb_K_pp = helicopter_R2016b_P.K_pp * rtb_Clock;

  /* Clock: '<S3>/Clock' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S5>/K_pd'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Clock = helicopter_R2016b_P.Gain1_Gain * helicopter_R2016b_B.Gain_b *
    helicopter_R2016b_P.K_pd;
  rtb_Clock = (rtb_K_pp - rtb_Clock) + helicopter_R2016b_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_R2016b_X.Integrator_CSTATE >=
      helicopter_R2016b_P.Integrator_UpperSat) {
    helicopter_R2016b_X.Integrator_CSTATE =
      helicopter_R2016b_P.Integrator_UpperSat;
  } else {
    if (helicopter_R2016b_X.Integrator_CSTATE <=
        helicopter_R2016b_P.Integrator_LowerSat) {
      helicopter_R2016b_X.Integrator_CSTATE =
        helicopter_R2016b_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Derivative = helicopter_R2016b_P.elevation_ref_Value -
    helicopter_R2016b_P.Gain1_Gain * helicopter_R2016b_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopter_R2016b_P.K_ep * rtb_Derivative +
                   helicopter_R2016b_X.Integrator_CSTATE) -
                  helicopter_R2016b_P.Gain1_Gain * helicopter_R2016b_B.Gain_dg *
                  helicopter_R2016b_P.K_ed) + helicopter_R2016b_P.Vs_ff;

  /* Sum: '<S1>/Add' */
  rtb_K_pp = rtb_Clock + rtb_Backgain;

  /* Sum: '<S1>/Subtract' */
  rtb_Backgain -= rtb_Clock;

  /* Clock: '<S3>/Clock' incorporates:
   *  Derivative: '<S4>/Derivative'
   */
  rtb_Clock_tmp = helicopter_R2016b_M->Timing.t[0];

  /* Clock: '<S3>/Clock' */
  rtb_Clock = rtb_Clock_tmp;

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopter_R2016b_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_R2016b_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopter_R2016b_B.In1 = helicopter_R2016b_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
      srUpdateBC(helicopter_R2016b_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_R2016b_DW.TimeStampA >= rtb_Clock_tmp) &&
      (helicopter_R2016b_DW.TimeStampB >= rtb_Clock_tmp)) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = helicopter_R2016b_DW.TimeStampA;
    lastU = &helicopter_R2016b_DW.LastUAtTimeA;
    if (helicopter_R2016b_DW.TimeStampA < helicopter_R2016b_DW.TimeStampB) {
      if (helicopter_R2016b_DW.TimeStampB < rtb_Clock_tmp) {
        rtb_Derivative = helicopter_R2016b_DW.TimeStampB;
        lastU = &helicopter_R2016b_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_R2016b_DW.TimeStampA >= rtb_Clock_tmp) {
        rtb_Derivative = helicopter_R2016b_DW.TimeStampB;
        lastU = &helicopter_R2016b_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_R2016b_B.PitchCounttorad - *lastU) /
      (rtb_Clock_tmp - rtb_Derivative);
  }

  /* Gain: '<S11>/Gain' */
  helicopter_R2016b_B.Gain_l = helicopter_R2016b_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
  }

  /* Gain: '<S1>/Back gain' */
  rtb_Derivative = helicopter_R2016b_P.Backgain_Gain * rtb_Backgain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter_R2016b_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_R2016b_B.BackmotorSaturation =
      helicopter_R2016b_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_R2016b_P.BackmotorSaturation_LowerSat)
  {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_R2016b_B.BackmotorSaturation =
      helicopter_R2016b_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_R2016b_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
  }

  /* Gain: '<S1>/Front gain' */
  rtb_Derivative = helicopter_R2016b_P.Frontgain_Gain * rtb_K_pp;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_R2016b_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_R2016b_B.FrontmotorSaturation =
      helicopter_R2016b_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_R2016b_P.FrontmotorSaturation_LowerSat)
  {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_R2016b_B.FrontmotorSaturation =
      helicopter_R2016b_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_R2016b_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_R2016b/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_R2016b_DW.HILWriteAnalog_Buffer[0] =
        helicopter_R2016b_B.FrontmotorSaturation;
      helicopter_R2016b_DW.HILWriteAnalog_Buffer[1] =
        helicopter_R2016b_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILWriteAnalog_channels, 2,
        &helicopter_R2016b_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_R2016b_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_R2016b_DW.TimeStampA == (rtInf)) {
    helicopter_R2016b_DW.TimeStampA = helicopter_R2016b_M->Timing.t[0];
    lastU = &helicopter_R2016b_DW.LastUAtTimeA;
  } else if (helicopter_R2016b_DW.TimeStampB == (rtInf)) {
    helicopter_R2016b_DW.TimeStampB = helicopter_R2016b_M->Timing.t[0];
    lastU = &helicopter_R2016b_DW.LastUAtTimeB;
  } else if (helicopter_R2016b_DW.TimeStampA < helicopter_R2016b_DW.TimeStampB)
  {
    helicopter_R2016b_DW.TimeStampA = helicopter_R2016b_M->Timing.t[0];
    lastU = &helicopter_R2016b_DW.LastUAtTimeA;
  } else {
    helicopter_R2016b_DW.TimeStampB = helicopter_R2016b_M->Timing.t[0];
    lastU = &helicopter_R2016b_DW.LastUAtTimeB;
  }

  *lastU = helicopter_R2016b_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_R2016b_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_R2016b_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter_R2016b_M->Timing.clockTick0)) {
    ++helicopter_R2016b_M->Timing.clockTickH0;
  }

  helicopter_R2016b_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_R2016b_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter_R2016b_M->Timing.clockTick1)) {
      ++helicopter_R2016b_M->Timing.clockTickH1;
    }

    helicopter_R2016b_M->Timing.t[1] = helicopter_R2016b_M->Timing.clockTick1 *
      helicopter_R2016b_M->Timing.stepSize1 +
      helicopter_R2016b_M->Timing.clockTickH1 *
      helicopter_R2016b_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_R2016b_derivatives(void)
{
  XDot_helicopter_R2016b_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_R2016b_T *) helicopter_R2016b_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_R2016b_P.TravelTransferFcn_A *
    helicopter_R2016b_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_R2016b_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_R2016b_P.PitchTransferFcn_A *
    helicopter_R2016b_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_R2016b_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_R2016b_P.ElevationTransferFcn_A *
    helicopter_R2016b_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_R2016b_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_R2016b_X.Integrator_CSTATE <=
          helicopter_R2016b_P.Integrator_LowerSat);
  usat = (helicopter_R2016b_X.Integrator_CSTATE >=
          helicopter_R2016b_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_R2016b_B.In1 > 0.0)) || (usat
       && (helicopter_R2016b_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_R2016b_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_R2016b_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_R2016b/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_R2016b_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (helicopter_R2016b_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_R2016b_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
      return;
    }

    if ((helicopter_R2016b_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_R2016b_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_R2016b_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_R2016b_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_R2016b_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (helicopter_R2016b_DW.HILInitialize_Card,
         helicopter_R2016b_P.HILInitialize_AIChannels, 8U,
         &helicopter_R2016b_DW.HILInitialize_AIMinimums[0],
         &helicopter_R2016b_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_R2016b_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_R2016b_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_R2016b_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_R2016b_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_R2016b_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_R2016b_DW.HILInitialize_Card,
         helicopter_R2016b_P.HILInitialize_AOChannels, 8U,
         &helicopter_R2016b_DW.HILInitialize_AOMinimums[0],
         &helicopter_R2016b_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_R2016b_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_R2016b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_R2016b_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILInitialize_AOChannels, 8U,
        &helicopter_R2016b_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_R2016b_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_R2016b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_R2016b_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_R2016b_DW.HILInitialize_Card,
         helicopter_R2016b_P.HILInitialize_AOChannels, 8U,
         &helicopter_R2016b_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_R2016b_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_R2016b_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            helicopter_R2016b_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_R2016b_DW.HILInitialize_Card,
         helicopter_R2016b_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_R2016b_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_R2016b_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_R2016b_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter_R2016b_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILInitialize_EIChannels, 8U,
        &helicopter_R2016b_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_R2016b_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_R2016b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_R2016b_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_R2016b_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_R2016b_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_R2016b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_R2016b_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter_R2016b_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_R2016b_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_R2016b_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_R2016b_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_R2016b_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_R2016b_DW.HILInitialize_Card,
          &helicopter_R2016b_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes,
          &helicopter_R2016b_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_R2016b_DW.HILInitialize_Card,
          &helicopter_R2016b_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_R2016b_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_R2016b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_R2016b_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_R2016b_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_R2016b_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_R2016b_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_R2016b_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *)
        &helicopter_R2016b_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_R2016b_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_R2016b_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_R2016b_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_R2016b_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_R2016b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_R2016b_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILInitialize_POChannels, 8U,
        &helicopter_R2016b_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_R2016b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_R2016b_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_R2016b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_R2016b_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_R2016b_DW.HILInitialize_Card,
        helicopter_R2016b_P.HILInitialize_POChannels, 8U,
        &helicopter_R2016b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_R2016b_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_R2016b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_R2016b_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_R2016b_DW.HILInitialize_Card,
         helicopter_R2016b_P.HILInitialize_POChannels, 8U,
         &helicopter_R2016b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_R2016b/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_R2016b_DW.HILInitialize_Card,
       helicopter_R2016b_P.HILReadEncoderTimebase_SamplesI,
       helicopter_R2016b_P.HILReadEncoderTimebase_Channels, 3,
       &helicopter_R2016b_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_R2016b_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (helicopter_R2016b_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "simdata.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_R2016b_M,
                        "Error creating .mat file simdata.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopter_R2016b_M,
                        "Error writing mat file header to file simdata.mat");
      return;
    }

    helicopter_R2016b_DW.ToFile_IWORK.Count = 0;
    helicopter_R2016b_DW.ToFile_IWORK.Decimation = -1;
    helicopter_R2016b_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829859, 0.52359877559829859,
      0.52359877559829859, 0.52359877559829859, 0.52359877559829859,
      0.52359877559829837, 0.52359877559829815, 0.52359877559829771,
      0.52359877559829548, 0.38860612175084963, 0.10951766411519659,
      -0.11003765190229997, -0.27691054207702592, -0.3979061298598523,
      -0.47963605934628578, -0.52359877303293778, -0.523598775598013,
      -0.523598775598036, -0.5235987755625281, -0.5034343603774375,
      -0.46496995819400527, -0.4207730301407801, -0.37347825146308289,
      -0.32522954483788541, -0.27772317732172674, -0.23225508120327132,
      -0.18977001060991705, -0.15091060293692415, -0.11606484364205627,
      -0.085410818112476861, -0.058957969261630161, -0.03658436369748802,
      -0.018069704892336613, -0.003124022354960343, 0.0085878843575980524,
      0.017426054255803014, 0.02375875141320638, 0.027949299298708707,
      0.03034600017717981, 0.031274762598678563, 0.031034060588966295,
      0.029891860219849131, 0.028084169840834172, 0.025814896852281777,
      0.023256724337087809, 0.020552753349086461, 0.017818689725695891,
      0.015145386800299088, 0.012601586460726732, 0.010236729997641025,
      0.0080837366800790011, 0.0061616717273568211, 0.0044782462017948221,
      0.0030321093244014552, 0.001814908903614687, 0.00081310811961887719,
      9.5570245552956123E-6, -0.00061517496674801109, -0.0010816933626409675,
      -0.0014108831694982227, -0.0016232044680177804, -0.0017381581202886576,
      -0.0017739001480583383, -0.001746983524506196, -0.0016722069319636823,
      -0.0015625512958579169, -0.0014291864721555081, -0.0012815322245767202,
      -0.0011273594818902444, -0.00097291973648327978, -0.00082309227185339839,
      -0.00068154064254299929, -0.00055087144231746876, -0.00043278986336825476,
      -0.00032824785871288231, -0.00023758186729783137, -0.00016063804831123463,
      -9.688380452921308E-5, -4.5505064502959769E-5, -5.4893532089872465E-6,
      2.4304874298053392E-5, 4.5091814682152176E-5, 5.811372429320727E-5,
      6.4606854940252312E-5, 6.5776445270504524E-5, 6.2779129588852456E-5,
      5.6710935135595442E-5, 4.8598784526343586E-5, 3.9393060373593691E-5,
      2.995829079210921E-5, 2.1058387476569074E-5, 1.3332252032149938E-5,
      7.2554315446726747E-6, 3.0850963401718445E-6, 7.9190416268914987E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_R2016b_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_R2016b_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_R2016b_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopter_R2016b_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_R2016b_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_R2016b_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_R2016b_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_R2016b_X.Integrator_CSTATE = helicopter_R2016b_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_R2016b_DW.TimeStampA = (rtInf);
  helicopter_R2016b_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_R2016b_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_R2016b/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_R2016b_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_R2016b_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_R2016b_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_R2016b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_R2016b_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_R2016b_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_R2016b_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_R2016b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_R2016b_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_R2016b_DW.HILInitialize_Card
                         , helicopter_R2016b_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_R2016b_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_R2016b_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_R2016b_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (helicopter_R2016b_DW.HILInitialize_Card,
             helicopter_R2016b_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &helicopter_R2016b_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_R2016b_DW.HILInitialize_Card,
            helicopter_R2016b_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter_R2016b_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_R2016b_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_R2016b_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_R2016b_DW.HILInitialize_Card);
    hil_close(helicopter_R2016b_DW.HILInitialize_Card);
    helicopter_R2016b_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_R2016b_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "simdata.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_R2016b_M,
                          "Error closing MAT-file simdata.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_R2016b_M,
                          "Error reopening MAT-file simdata.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1,
           helicopter_R2016b_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopter_R2016b_M,
                          "Error writing header for ans to MAT-file simdata.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_R2016b_M,
                          "Error closing MAT-file simdata.mat");
        return;
      }

      helicopter_R2016b_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter_R2016b_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_R2016b_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_R2016b_initialize();
}

void MdlTerminate(void)
{
  helicopter_R2016b_terminate();
}

/* Registration function */
RT_MODEL_helicopter_R2016b_T *helicopter_R2016b(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_R2016b_P.Integrator_UpperSat = rtInf;
  helicopter_R2016b_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_R2016b_M, 0,
                sizeof(RT_MODEL_helicopter_R2016b_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_R2016b_M->solverInfo,
                          &helicopter_R2016b_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_R2016b_M->solverInfo, &rtmGetTPtr
                (helicopter_R2016b_M));
    rtsiSetStepSizePtr(&helicopter_R2016b_M->solverInfo,
                       &helicopter_R2016b_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_R2016b_M->solverInfo, &helicopter_R2016b_M->derivs);
    rtsiSetContStatesPtr(&helicopter_R2016b_M->solverInfo, (real_T **)
                         &helicopter_R2016b_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_R2016b_M->solverInfo,
      &helicopter_R2016b_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_R2016b_M->solverInfo,
      &helicopter_R2016b_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_R2016b_M->solverInfo,
      &helicopter_R2016b_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_R2016b_M->solverInfo,
      &helicopter_R2016b_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_R2016b_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_R2016b_M)));
    rtsiSetRTModelPtr(&helicopter_R2016b_M->solverInfo, helicopter_R2016b_M);
  }

  rtsiSetSimTimeStep(&helicopter_R2016b_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_R2016b_M->intgData.f[0] = helicopter_R2016b_M->odeF[0];
  helicopter_R2016b_M->contStates = ((real_T *) &helicopter_R2016b_X);
  rtsiSetSolverData(&helicopter_R2016b_M->solverInfo, (void *)
                    &helicopter_R2016b_M->intgData);
  rtsiSetSolverName(&helicopter_R2016b_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_R2016b_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_R2016b_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_R2016b_M->Timing.sampleTimes =
      (&helicopter_R2016b_M->Timing.sampleTimesArray[0]);
    helicopter_R2016b_M->Timing.offsetTimes =
      (&helicopter_R2016b_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_R2016b_M->Timing.sampleTimes[0] = (0.0);
    helicopter_R2016b_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_R2016b_M->Timing.offsetTimes[0] = (0.0);
    helicopter_R2016b_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_R2016b_M, &helicopter_R2016b_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_R2016b_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_R2016b_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_R2016b_M, -1);
  helicopter_R2016b_M->Timing.stepSize0 = 0.002;
  helicopter_R2016b_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_R2016b_M->Sizes.checksums[0] = (1341221828U);
  helicopter_R2016b_M->Sizes.checksums[1] = (3373039391U);
  helicopter_R2016b_M->Sizes.checksums[2] = (4110259065U);
  helicopter_R2016b_M->Sizes.checksums[3] = (3210618354U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_R2016b_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_R2016b_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_R2016b_M->extModeInfo,
      &helicopter_R2016b_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_R2016b_M->extModeInfo,
                        helicopter_R2016b_M->Sizes.checksums);
    rteiSetTPtr(helicopter_R2016b_M->extModeInfo, rtmGetTPtr(helicopter_R2016b_M));
  }

  helicopter_R2016b_M->solverInfoPtr = (&helicopter_R2016b_M->solverInfo);
  helicopter_R2016b_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_R2016b_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_R2016b_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_R2016b_M->blockIO = ((void *) &helicopter_R2016b_B);

  {
    helicopter_R2016b_B.TravelCounttorad = 0.0;
    helicopter_R2016b_B.Gain = 0.0;
    helicopter_R2016b_B.Gain_d = 0.0;
    helicopter_R2016b_B.PitchCounttorad = 0.0;
    helicopter_R2016b_B.Gain_i = 0.0;
    helicopter_R2016b_B.Gain_b = 0.0;
    helicopter_R2016b_B.ElevationCounttorad = 0.0;
    helicopter_R2016b_B.Gain_e = 0.0;
    helicopter_R2016b_B.Sum = 0.0;
    helicopter_R2016b_B.Gain_dg = 0.0;
    helicopter_R2016b_B.Gain_l = 0.0;
    helicopter_R2016b_B.BackmotorSaturation = 0.0;
    helicopter_R2016b_B.FrontmotorSaturation = 0.0;
    helicopter_R2016b_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_R2016b_M->defaultParam = ((real_T *)&helicopter_R2016b_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_R2016b_X;
    helicopter_R2016b_M->contStates = (x);
    (void) memset((void *)&helicopter_R2016b_X, 0,
                  sizeof(X_helicopter_R2016b_T));
  }

  /* states (dwork) */
  helicopter_R2016b_M->dwork = ((void *) &helicopter_R2016b_DW);
  (void) memset((void *)&helicopter_R2016b_DW, 0,
                sizeof(DW_helicopter_R2016b_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_R2016b_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_R2016b_DW.TimeStampA = 0.0;
  helicopter_R2016b_DW.LastUAtTimeA = 0.0;
  helicopter_R2016b_DW.TimeStampB = 0.0;
  helicopter_R2016b_DW.LastUAtTimeB = 0.0;
  helicopter_R2016b_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_R2016b_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_R2016b_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_R2016b_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_R2016b_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_R2016b_M->Sizes.numY = (0);/* Number of model outputs */
  helicopter_R2016b_M->Sizes.numU = (0);/* Number of model inputs */
  helicopter_R2016b_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_R2016b_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_R2016b_M->Sizes.numBlocks = (59);/* Number of blocks */
  helicopter_R2016b_M->Sizes.numBlockIO = (14);/* Number of block outputs */
  helicopter_R2016b_M->Sizes.numBlockPrms = (144);/* Sum of parameter "widths" */
  return helicopter_R2016b_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
