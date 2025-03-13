/*
 * helicopter_2017b.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_2017b".
 *
 * Model version              : 5.0
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar 13 09:26:27 2025
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_2017b.h"
#include "helicopter_2017b_private.h"
#include "helicopter_2017b_dt.h"

/* Block signals (default storage) */
B_helicopter_2017b_T helicopter_2017b_B;

/* Continuous states */
X_helicopter_2017b_T helicopter_2017b_X;

/* Block states (default storage) */
DW_helicopter_2017b_T helicopter_2017b_DW;

/* Real-time model */
static RT_MODEL_helicopter_2017b_T helicopter_2017b_M_;
RT_MODEL_helicopter_2017b_T *const helicopter_2017b_M = &helicopter_2017b_M_;

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
  helicopter_2017b_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_2017b_output(void)
{
  /* local block i/o variables */
  real_T rtb_u[2];
  real_T rtb_xx[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_Gain1[6];
  real_T rtb_uKxx[2];
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int32_T i;
  int32_T i_0;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    /* set solver stop time */
    if (!(helicopter_2017b_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_2017b_M->solverInfo,
                            ((helicopter_2017b_M->Timing.clockTickH0 + 1) *
        helicopter_2017b_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_2017b_M->solverInfo,
                            ((helicopter_2017b_M->Timing.clockTick0 + 1) *
        helicopter_2017b_M->Timing.stepSize0 +
        helicopter_2017b_M->Timing.clockTickH0 *
        helicopter_2017b_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_2017b_M)) {
    helicopter_2017b_M->Timing.t[0] = rtsiGetT(&helicopter_2017b_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_2017b_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_2017b/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_2017b_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_2017b_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_2017b_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_2017b_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_2017b_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_2017b_B.TravelCounttorad = helicopter_2017b_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_2017b_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopter_2017b_B.Gain = helicopter_2017b_P.Gain_Gain *
      helicopter_2017b_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Travel offset'
     */
    helicopter_2017b_B.Sum3 = helicopter_2017b_P.Traveloffset_Value +
      helicopter_2017b_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_2017b_B.PitchCounttorad = helicopter_2017b_P.PitchCounttorad_Gain
      * rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopter_2017b_B.Gain_i = helicopter_2017b_P.Gain_Gain_a *
      helicopter_2017b_B.PitchCounttorad;
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_2017b_B.Gain_d = (helicopter_2017b_P.TravelTransferFcn_C *
    helicopter_2017b_X.TravelTransferFcn_CSTATE +
    helicopter_2017b_P.TravelTransferFcn_D * helicopter_2017b_B.TravelCounttorad)
    * helicopter_2017b_P.Gain_Gain_l;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_2017b_B.Gain_b = (helicopter_2017b_P.PitchTransferFcn_C *
    helicopter_2017b_X.PitchTransferFcn_CSTATE +
    helicopter_2017b_P.PitchTransferFcn_D * helicopter_2017b_B.PitchCounttorad) *
    helicopter_2017b_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_2017b_B.ElevationCounttorad = helicopter_2017b_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 *
      helicopter_2017b_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopter_2017b_B.Gain_e = helicopter_2017b_P.Gain_Gain_lv *
      helicopter_2017b_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_2017b_B.Sum = helicopter_2017b_B.Gain_e +
      helicopter_2017b_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_2017b_B.Gain_dg = (helicopter_2017b_P.ElevationTransferFcn_C *
    helicopter_2017b_X.ElevationTransferFcn_CSTATE +
    helicopter_2017b_P.ElevationTransferFcn_D *
    helicopter_2017b_B.ElevationCounttorad) * helicopter_2017b_P.Gain_Gain_n;
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    rtb_TmpSignalConversionAtToFile[0] = helicopter_2017b_B.Sum3;
    rtb_TmpSignalConversionAtToFile[1] = helicopter_2017b_B.Gain_d;
    rtb_TmpSignalConversionAtToFile[2] = helicopter_2017b_B.Gain_i;
    rtb_TmpSignalConversionAtToFile[3] = helicopter_2017b_B.Gain_b;
    rtb_TmpSignalConversionAtToFile[4] = helicopter_2017b_B.Sum;
    rtb_TmpSignalConversionAtToFile[5] = helicopter_2017b_B.Gain_dg;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_2017b_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_2017b_DW.ToFile_IWORK.Count * (6 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_2017b_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          helicopter_2017b_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_2017b_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFile[0];
          u[2] = rtb_TmpSignalConversionAtToFile[1];
          u[3] = rtb_TmpSignalConversionAtToFile[2];
          u[4] = rtb_TmpSignalConversionAtToFile[3];
          u[5] = rtb_TmpSignalConversionAtToFile[4];
          u[6] = rtb_TmpSignalConversionAtToFile[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(helicopter_2017b_M,
                              "Error writing to MAT-file data.mat");
            return;
          }

          if (((++helicopter_2017b_DW.ToFile_IWORK.Count) * (6 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file data.mat.\n");
          }
        }
      }
    }
  }

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1[0] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Sum3;
  rtb_Gain1[1] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_d;
  rtb_Gain1[2] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_i;
  rtb_Gain1[3] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_b;
  rtb_Gain1[4] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Sum;
  rtb_Gain1[5] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_dg;

  /* FromWorkspace: '<S5>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_2017b_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter_2017b_M->Timing.t[0];
    if (t >= pTimeValues[80]) {
      {
        int_T elIdx;
        for (elIdx = 0; elIdx < 6; ++elIdx) {
          (&rtb_xx[0])[elIdx] = pDataValues[80];
          pDataValues += 81;
        }
      }
    } else {
      /* Get index */
      if (t <= pTimeValues[0]) {
        currTimeIndex = 0;
      } else if (t >= pTimeValues[80]) {
        currTimeIndex = 79;
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

      helicopter_2017b_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

      /* Post output */
      {
        real_T t1 = pTimeValues[currTimeIndex];
        real_T t2 = pTimeValues[currTimeIndex + 1];
        if (t1 == t2) {
          if (t < t1) {
            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 6; ++elIdx) {
                (&rtb_xx[0])[elIdx] = pDataValues[currTimeIndex];
                pDataValues += 81;
              }
            }
          } else {
            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 6; ++elIdx) {
                (&rtb_xx[0])[elIdx] = pDataValues[currTimeIndex + 1];
                pDataValues += 81;
              }
            }
          }
        } else {
          real_T f1 = (t2 - t) / (t2 - t1);
          real_T f2 = 1.0 - f1;
          real_T d1;
          real_T d2;
          int_T TimeIndex= currTimeIndex;

          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              d1 = pDataValues[TimeIndex];
              d2 = pDataValues[TimeIndex + 1];
              (&rtb_xx[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
              pDataValues += 81;
            }
          }
        }
      }
    }
  }

  for (i = 0; i < 6; i++) {
    /* Sum: '<S5>/Sum' */
    rtb_xx[i] = rtb_Gain1[i] - rtb_xx[i];
  }

  /* FromWorkspace: '<S5>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_2017b_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_2017b_M->Timing.t[0];
    if (t >= pTimeValues[80]) {
      {
        int_T elIdx;
        for (elIdx = 0; elIdx < 2; ++elIdx) {
          (&rtb_u[0])[elIdx] = pDataValues[80];
          pDataValues += 81;
        }
      }
    } else {
      /* Get index */
      if (t <= pTimeValues[0]) {
        currTimeIndex = 0;
      } else if (t >= pTimeValues[80]) {
        currTimeIndex = 79;
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

      helicopter_2017b_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

      /* Post output */
      {
        real_T t1 = pTimeValues[currTimeIndex];
        real_T t2 = pTimeValues[currTimeIndex + 1];
        if (t1 == t2) {
          if (t < t1) {
            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 2; ++elIdx) {
                (&rtb_u[0])[elIdx] = pDataValues[currTimeIndex];
                pDataValues += 81;
              }
            }
          } else {
            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 2; ++elIdx) {
                (&rtb_u[0])[elIdx] = pDataValues[currTimeIndex + 1];
                pDataValues += 81;
              }
            }
          }
        } else {
          real_T f1 = (t2 - t) / (t2 - t1);
          real_T f2 = 1.0 - f1;
          real_T d1;
          real_T d2;
          int_T TimeIndex= currTimeIndex;

          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              d1 = pDataValues[TimeIndex];
              d2 = pDataValues[TimeIndex + 1];
              (&rtb_u[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
              pDataValues += 81;
            }
          }
        }
      }
    }
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S5>/Gain'
   */
  for (i = 0; i < 2; i++) {
    rtb_Clock = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Clock += helicopter_2017b_P.K[(i_0 << 1) + i] * rtb_xx[i_0];
    }

    rtb_uKxx[i] = rtb_u[i] - rtb_Clock;
  }

  /* End of Sum: '<S5>/Sum1' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  rtb_Clock = ((rtb_uKxx[0] - rtb_Gain1[2]) * helicopter_2017b_P.K_pp -
               helicopter_2017b_P.K_pd * rtb_Gain1[3]) +
    helicopter_2017b_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_2017b_X.Integrator_CSTATE >=
      helicopter_2017b_P.Integrator_UpperSat) {
    helicopter_2017b_X.Integrator_CSTATE =
      helicopter_2017b_P.Integrator_UpperSat;
  } else {
    if (helicopter_2017b_X.Integrator_CSTATE <=
        helicopter_2017b_P.Integrator_LowerSat) {
      helicopter_2017b_X.Integrator_CSTATE =
        helicopter_2017b_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Derivative = rtb_uKxx[1] - rtb_Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopter_2017b_P.K_ep * rtb_Derivative +
                   helicopter_2017b_X.Integrator_CSTATE) -
                  helicopter_2017b_P.K_ed * rtb_Gain1[5]) +
    helicopter_2017b_P.Vs_ff;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    rtAction = (int8_T)!(helicopter_2017b_M->Timing.t[0] >= 2.0);
    helicopter_2017b_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_2017b_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopter_2017b_B.In1 = helicopter_2017b_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
      srUpdateBC(helicopter_2017b_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Derivative = helicopter_2017b_M->Timing.t[0];
  if ((helicopter_2017b_DW.TimeStampA >= rtb_Derivative) &&
      (helicopter_2017b_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopter_2017b_DW.TimeStampA;
    lastU = &helicopter_2017b_DW.LastUAtTimeA;
    if (helicopter_2017b_DW.TimeStampA < helicopter_2017b_DW.TimeStampB) {
      if (helicopter_2017b_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopter_2017b_DW.TimeStampB;
        lastU = &helicopter_2017b_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_2017b_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopter_2017b_DW.TimeStampB;
        lastU = &helicopter_2017b_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_2017b_B.PitchCounttorad - *lastU) /
      (rtb_Derivative - lastTime);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopter_2017b_B.Gain_l = helicopter_2017b_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) * helicopter_2017b_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter_2017b_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_2017b_B.BackmotorSaturation =
      helicopter_2017b_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_2017b_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_2017b_B.BackmotorSaturation =
      helicopter_2017b_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_2017b_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) *
    helicopter_2017b_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_2017b_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_2017b_B.FrontmotorSaturation =
      helicopter_2017b_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_2017b_P.FrontmotorSaturation_LowerSat)
  {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_2017b_B.FrontmotorSaturation =
      helicopter_2017b_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_2017b_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_2017b/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_2017b_DW.HILWriteAnalog_Buffer[0] =
        helicopter_2017b_B.FrontmotorSaturation;
      helicopter_2017b_DW.HILWriteAnalog_Buffer[1] =
        helicopter_2017b_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILWriteAnalog_channels, 2,
        &helicopter_2017b_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_2017b_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_2017b_DW.TimeStampA == (rtInf)) {
    helicopter_2017b_DW.TimeStampA = helicopter_2017b_M->Timing.t[0];
    lastU = &helicopter_2017b_DW.LastUAtTimeA;
  } else if (helicopter_2017b_DW.TimeStampB == (rtInf)) {
    helicopter_2017b_DW.TimeStampB = helicopter_2017b_M->Timing.t[0];
    lastU = &helicopter_2017b_DW.LastUAtTimeB;
  } else if (helicopter_2017b_DW.TimeStampA < helicopter_2017b_DW.TimeStampB) {
    helicopter_2017b_DW.TimeStampA = helicopter_2017b_M->Timing.t[0];
    lastU = &helicopter_2017b_DW.LastUAtTimeA;
  } else {
    helicopter_2017b_DW.TimeStampB = helicopter_2017b_M->Timing.t[0];
    lastU = &helicopter_2017b_DW.LastUAtTimeB;
  }

  *lastU = helicopter_2017b_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_2017b_M->solverInfo);
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
  if (!(++helicopter_2017b_M->Timing.clockTick0)) {
    ++helicopter_2017b_M->Timing.clockTickH0;
  }

  helicopter_2017b_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_2017b_M->solverInfo);

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
    if (!(++helicopter_2017b_M->Timing.clockTick1)) {
      ++helicopter_2017b_M->Timing.clockTickH1;
    }

    helicopter_2017b_M->Timing.t[1] = helicopter_2017b_M->Timing.clockTick1 *
      helicopter_2017b_M->Timing.stepSize1 +
      helicopter_2017b_M->Timing.clockTickH1 *
      helicopter_2017b_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_2017b_derivatives(void)
{
  XDot_helicopter_2017b_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_2017b_T *) helicopter_2017b_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_2017b_P.TravelTransferFcn_A *
    helicopter_2017b_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_2017b_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_2017b_P.PitchTransferFcn_A *
    helicopter_2017b_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_2017b_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_2017b_P.ElevationTransferFcn_A *
    helicopter_2017b_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_2017b_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_2017b_X.Integrator_CSTATE <=
          helicopter_2017b_P.Integrator_LowerSat);
  usat = (helicopter_2017b_X.Integrator_CSTATE >=
          helicopter_2017b_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_2017b_B.In1 > 0.0)) || (usat &&
       (helicopter_2017b_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_2017b_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_2017b_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_2017b/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_2017b_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (helicopter_2017b_DW.HILInitialize_Card, "update_rate=normal;decimation=1",
       32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_2017b_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
      return;
    }

    if ((helicopter_2017b_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_2017b_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_2017b_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_2017b_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_2017b_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (helicopter_2017b_DW.HILInitialize_Card,
         helicopter_2017b_P.HILInitialize_AIChannels, 8U,
         &helicopter_2017b_DW.HILInitialize_AIMinimums[0],
         &helicopter_2017b_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_2017b_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_2017b_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_2017b_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_2017b_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_2017b_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_2017b_DW.HILInitialize_Card,
         helicopter_2017b_P.HILInitialize_AOChannels, 8U,
         &helicopter_2017b_DW.HILInitialize_AOMinimums[0],
         &helicopter_2017b_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_2017b_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_2017b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_2017b_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILInitialize_AOChannels, 8U,
        &helicopter_2017b_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_2017b_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_2017b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_2017b_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_2017b_DW.HILInitialize_Card,
         helicopter_2017b_P.HILInitialize_AOChannels, 8U,
         &helicopter_2017b_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_2017b_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_2017b_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_2017b_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_2017b_DW.HILInitialize_Card,
         helicopter_2017b_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_2017b_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_2017b_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_2017b_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter_2017b_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILInitialize_EIChannels, 8U,
        &helicopter_2017b_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_2017b_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_2017b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_2017b_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_2017b_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_2017b_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_2017b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_2017b_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter_2017b_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_2017b_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_2017b_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_2017b_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_2017b_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_2017b_DW.HILInitialize_Card,
          &helicopter_2017b_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes,
          &helicopter_2017b_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_2017b_DW.HILInitialize_Card,
          &helicopter_2017b_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_2017b_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_2017b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_2017b_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_2017b_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_2017b_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_2017b_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_2017b_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter_2017b_DW.HILInitialize_POModeValues
        [0],
        (t_pwm_alignment *) &helicopter_2017b_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_2017b_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_2017b_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_2017b_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_2017b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_2017b_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILInitialize_POChannels, 8U,
        &helicopter_2017b_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_2017b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_2017b_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_2017b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_2017b_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_2017b_DW.HILInitialize_Card,
        helicopter_2017b_P.HILInitialize_POChannels, 8U,
        &helicopter_2017b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_2017b_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_2017b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_2017b_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_2017b_DW.HILInitialize_Card,
         helicopter_2017b_P.HILInitialize_POChannels, 8U,
         &helicopter_2017b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_2017b/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_2017b_DW.HILInitialize_Card,
       helicopter_2017b_P.HILReadEncoderTimebase_SamplesI,
       helicopter_2017b_P.HILReadEncoderTimebase_Channels, 3,
       &helicopter_2017b_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_2017b_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (helicopter_2017b_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "data.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_2017b_M, "Error creating .mat file data.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopter_2017b_M,
                        "Error writing mat file header to file data.mat");
      return;
    }

    helicopter_2017b_DW.ToFile_IWORK.Count = 0;
    helicopter_2017b_DW.ToFile_IWORK.Decimation = -1;
    helicopter_2017b_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<S5>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413625261, 3.1262155534579983,
      3.1033093000299643, 3.0666274151911783, 3.0144539223941584,
      2.9456562771175667, 2.8595077632935446, 2.7555515879651526,
      2.633505110490284, 2.4931956060320961, 2.334518576064299,
      2.1584793409164913, 1.968119317212401, 1.7680403010990278,
      1.563566979749011, 1.3600182793687574, 1.1622065091332505,
      0.974151874696412, 0.79884518049659015, 0.63836019920565645,
      0.49403940173055538, 0.36650583442087076, 0.25574888013546432,
      0.16123797235008014, 0.082041104924956282, 0.016936769254855946,
      -0.035485847487685754, -0.0767403030461282, -0.10837016611942106,
      -0.13188942284505364, -0.14873497757379742, -0.16023000618521732,
      -0.16755707312608589, -0.171740102209701, -0.17363466849090295,
      -0.17392652731661742, -0.17313877719836449, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909068423,
      -0.046506351618112111, -0.091625013712135384, -0.14672753935514368,
      -0.2086939711880792, -0.27519058110636668, -0.34459405529608833,
      -0.41582470131356863, -0.48818590989947458, -0.56123801783275173,
      -0.63470811987118847, -0.70415694059122957, -0.7614400948163621,
      -0.80031606445349268, -0.81789328540006656, -0.81419480152101431,
      -0.79124708094202811, -0.752218537747354, -0.70122677679928735,
      -0.64193992516373455, -0.57728318990040428, -0.5101342692387385,
      -0.44302781714162587, -0.37804363114153672, -0.31678746970049537,
      -0.26041734268040134, -0.2096904669701668, -0.16501782223376973,
      -0.12651945229317146, -0.094077026902530281, -0.067382218914975214,
      -0.045980114445679593, -0.02930826776347429, -0.016732116334460562,
      -0.0075782651248076979, -0.0011674353028578552, 0.0031510004730117753,
      0.00596200704698269, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.10602875205865551, 0.22266037932317656, 0.31888147181640641,
      0.38944360631144165, 0.43795507377677839, 0.46997264230390068,
      0.49051724877547082, 0.50343100141474351, 0.5114213858602934,
      0.51630439857701838, 0.51925862127063693, 0.49083774073287656,
      0.4048554562972328, 0.27476050576021588, 0.12422908450177979,
      -0.026139471520315507, -0.16218572478522295, -0.2758388373935512,
      -0.3603902914440319, -0.41901682433554133, -0.45696911093349307,
      -0.47458292550548736, -0.47428277391095525, -0.45928340767986892,
      -0.43293515391561666, -0.39840252871829984, -0.3585181837488543,
      -0.31572919147708428, -0.27209177531921308, -0.22929067214588392,
      -0.188668707489346, -0.15126190042859289, -0.11783024498466541,
      -0.088883435176175862, -0.064695924281610445, -0.045309296736852432,
      -0.030521054753003162, -0.019867120876179076, -0.012621270591268292, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462206,
      0.46652650905808424, 0.38488436997291947, 0.282248537980141,
      0.19404586986134689, 0.12807027410848898, 0.082178425886280451,
      0.051655010557090549, 0.031961537782199768, 0.019532050866899815,
      0.011816890774474434, -0.11368352215104154, -0.34392913774257511,
      -0.52037980214806778, -0.60212568503374431, -0.60147422408838114,
      -0.54418501305962985, -0.454612450433313, -0.33820581620192275,
      -0.23450613156603786, -0.1518091463918069, -0.07045525828797719,
      0.0012006063781284872, 0.059997464924345434, 0.10539301505700921,
      0.13813050078926725, 0.15953737987778219, 0.17115596908708014,
      0.17454966463148469, 0.17120441269331657, 0.1624878586261517,
      0.14962722824301239, 0.13372662177571, 0.11578723923395816,
      0.0967500435782617, 0.077546510179032052, 0.059152967935397073,
      0.042615735507296339, 0.028983401139643147, 0.018989555441112308, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.004218516497356219,
      0.011646146609262963, 0.021583840865301202, 0.033554337154620813,
      0.047229891618006066, 0.0623692364039152, 0.078759368172963543,
      0.096156508896620529, 0.11422066211150161, 0.13243810474263318,
      0.15002497311671512, 0.16580326480498803, 0.17803902952601353,
      0.18422937306571502, 0.180822056459574, 0.17140849635233993,
      0.15852750054502243, 0.14394257287305054, 0.12885051949939652,
      0.11403755481678408, 0.09999571606341881, 0.087009050253273226,
      0.07521721412316916, 0.064661753190254315, 0.055319801023812273,
      0.047128226661220518, 0.040000493091632769, 0.033838744069731669,
      0.028541644473450145, 0.024009830064438582, 0.020149101686797559,
      0.016872267578191918, 0.014100191945603087, 0.011762036384487211,
      0.0097951326966789088, 0.0081445140681649514, 0.0067622931505792565,
      0.0056071637194386251, 0.0046435934852054545, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.016874065989424876, 0.029710520447626974,
      0.039750777024152972, 0.047881985157278428, 0.054702217853540992,
      0.060557379143636555, 0.065560527076193365, 0.06958856289462792,
      0.0722566128595244, 0.072869770524526242, 0.07034747349632775,
      0.063113166753091587, 0.048943058884101956, 0.024761374158806013,
      -0.01362926642456415, -0.037654240428936246, -0.051523983229270057,
      -0.058339710687887583, -0.060368213494616012, -0.059251858730449747,
      -0.056167355013461116, -0.051946663240582343, -0.0471673445204163,
      -0.042221843731659339, -0.037367808665768179, -0.032766297450367,
      -0.028510934278351011, -0.024646996087604397, -0.021188398385126081,
      -0.018127257636046237, -0.015442913510564111, -0.013107336434422556,
      -0.011088302530355332, -0.0093526222444635012, -0.0078676147512332061,
      -0.0066024745140558323, -0.0055288836703427779, -0.0046205177245625256,
      -0.0038542809369326819, -0.0032096569194189446, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopter_2017b_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_2017b_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_2017b_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<S5>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.37449549582579739, 0.10868975024906782,
      -0.10914607207429655, -0.27426516693602337, -0.3934637603941134,
      -0.473348187906605, -0.52020607538124142, -0.52359877559829882,
      -0.52359877559829882, -0.51885761642576411, -0.48725675476615427,
      -0.44678870080148547, -0.40066020416408915, -0.35157503494234454,
      -0.30176340856435496, -0.25302857391702971, -0.20679483600311221,
      -0.16415513717752503, -0.12591506032872854, -0.092625827965114274,
      -0.064625928466381169, -0.042046610018471008, -0.024824150976263063,
      -0.012680467632979139, -0.0050914526808599663, -0.0012412120377908549,
      -1.131396220219233E-7, -2.7995187537411443E-7, -1.4229414284673516E-6,
      3.6148656778045312E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.10546291243390546, 0.12241300533732527, 0.14124642121971112,
      0.16184314000167949, 0.18391525811013829, 0.20690463985157054,
      0.22989301405557744, 0.25144577795961454, 0.2694060876901363,
      0.28063027645169308, 0.28063073199657668, 0.26309237133822655,
      0.21924471581825886, 0.1370253824821433, 9.6127696507692435E-7,
      1.1947697904965721E-7, 5.6288514706833624E-7, 2.4166280527124919E-7,
      8.1283250797041467E-8, -7.4358745031285794E-7, -9.79095548848638E-7,
      -1.5091363763520027E-6, -2.0003699928115295E-7, 6.8881963485333354E-8,
      3.2395584055558595E-7, 1.6766220912734544E-6, 7.7222994713572379E-8,
      5.046575093182048E-7, -7.6148688874662239E-7, -1.2221133450083968E-7,
      6.5116759784645092E-7, -9.6986086981432314E-8, -2.7749883867267281E-7,
      -4.86960872462132E-7, -6.6832866315936874E-8, 1.259887627778575E-7,
      -1.1108152540853467E-6, -4.0794656541646273E-7, -2.1238140533671328E-8,
      3.6148656778045312E-7, 3.6148656778045312E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_2017b_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_2017b_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_2017b_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopter_2017b_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_2017b_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_2017b_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_2017b_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_2017b_X.Integrator_CSTATE = helicopter_2017b_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_2017b_DW.TimeStampA = (rtInf);
  helicopter_2017b_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_2017b_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_2017b/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_2017b_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_2017b_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_2017b_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_2017b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_2017b_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_2017b_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_2017b_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_2017b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_2017b_P.HILInitialize_POFinal;
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
      result = hil_write(helicopter_2017b_DW.HILInitialize_Card
                         , helicopter_2017b_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_2017b_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_2017b_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_2017b_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_2017b_DW.HILInitialize_Card,
            helicopter_2017b_P.HILInitialize_AOChannels,
            num_final_analog_outputs,
            &helicopter_2017b_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_2017b_DW.HILInitialize_Card,
            helicopter_2017b_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter_2017b_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_2017b_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_2017b_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_2017b_DW.HILInitialize_Card);
    hil_close(helicopter_2017b_DW.HILInitialize_Card);
    helicopter_2017b_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_2017b_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "data.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_2017b_M, "Error closing MAT-file data.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_2017b_M,
                          "Error reopening MAT-file data.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1,
           helicopter_2017b_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopter_2017b_M,
                          "Error writing header for ans to MAT-file data.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_2017b_M, "Error closing MAT-file data.mat");
        return;
      }

      helicopter_2017b_DW.ToFile_PWORK.FilePtr = (NULL);
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
  helicopter_2017b_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_2017b_update();
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
  helicopter_2017b_initialize();
}

void MdlTerminate(void)
{
  helicopter_2017b_terminate();
}

/* Registration function */
RT_MODEL_helicopter_2017b_T *helicopter_2017b(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_2017b_P.Integrator_UpperSat = rtInf;
  helicopter_2017b_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_2017b_M, 0,
                sizeof(RT_MODEL_helicopter_2017b_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_2017b_M->solverInfo,
                          &helicopter_2017b_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_2017b_M->solverInfo, &rtmGetTPtr(helicopter_2017b_M));
    rtsiSetStepSizePtr(&helicopter_2017b_M->solverInfo,
                       &helicopter_2017b_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_2017b_M->solverInfo, &helicopter_2017b_M->derivs);
    rtsiSetContStatesPtr(&helicopter_2017b_M->solverInfo, (real_T **)
                         &helicopter_2017b_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_2017b_M->solverInfo,
      &helicopter_2017b_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_2017b_M->solverInfo,
      &helicopter_2017b_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_2017b_M->solverInfo,
      &helicopter_2017b_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_2017b_M->solverInfo,
      &helicopter_2017b_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_2017b_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_2017b_M)));
    rtsiSetRTModelPtr(&helicopter_2017b_M->solverInfo, helicopter_2017b_M);
  }

  rtsiSetSimTimeStep(&helicopter_2017b_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_2017b_M->intgData.f[0] = helicopter_2017b_M->odeF[0];
  helicopter_2017b_M->contStates = ((real_T *) &helicopter_2017b_X);
  rtsiSetSolverData(&helicopter_2017b_M->solverInfo, (void *)
                    &helicopter_2017b_M->intgData);
  rtsiSetSolverName(&helicopter_2017b_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_2017b_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_2017b_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_2017b_M->Timing.sampleTimes =
      (&helicopter_2017b_M->Timing.sampleTimesArray[0]);
    helicopter_2017b_M->Timing.offsetTimes =
      (&helicopter_2017b_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_2017b_M->Timing.sampleTimes[0] = (0.0);
    helicopter_2017b_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_2017b_M->Timing.offsetTimes[0] = (0.0);
    helicopter_2017b_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_2017b_M, &helicopter_2017b_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_2017b_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_2017b_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_2017b_M, -1);
  helicopter_2017b_M->Timing.stepSize0 = 0.002;
  helicopter_2017b_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_2017b_M->Sizes.checksums[0] = (2046918193U);
  helicopter_2017b_M->Sizes.checksums[1] = (4220322023U);
  helicopter_2017b_M->Sizes.checksums[2] = (2515522201U);
  helicopter_2017b_M->Sizes.checksums[3] = (3617213643U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_2017b_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_2017b_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_2017b_M->extModeInfo,
      &helicopter_2017b_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_2017b_M->extModeInfo,
                        helicopter_2017b_M->Sizes.checksums);
    rteiSetTPtr(helicopter_2017b_M->extModeInfo, rtmGetTPtr(helicopter_2017b_M));
  }

  helicopter_2017b_M->solverInfoPtr = (&helicopter_2017b_M->solverInfo);
  helicopter_2017b_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_2017b_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_2017b_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_2017b_M->blockIO = ((void *) &helicopter_2017b_B);

  {
    helicopter_2017b_B.TravelCounttorad = 0.0;
    helicopter_2017b_B.Gain = 0.0;
    helicopter_2017b_B.Sum3 = 0.0;
    helicopter_2017b_B.Gain_d = 0.0;
    helicopter_2017b_B.PitchCounttorad = 0.0;
    helicopter_2017b_B.Gain_i = 0.0;
    helicopter_2017b_B.Gain_b = 0.0;
    helicopter_2017b_B.ElevationCounttorad = 0.0;
    helicopter_2017b_B.Gain_e = 0.0;
    helicopter_2017b_B.Sum = 0.0;
    helicopter_2017b_B.Gain_dg = 0.0;
    helicopter_2017b_B.Gain_l = 0.0;
    helicopter_2017b_B.BackmotorSaturation = 0.0;
    helicopter_2017b_B.FrontmotorSaturation = 0.0;
    helicopter_2017b_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_2017b_M->defaultParam = ((real_T *)&helicopter_2017b_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_2017b_X;
    helicopter_2017b_M->contStates = (x);
    (void) memset((void *)&helicopter_2017b_X, 0,
                  sizeof(X_helicopter_2017b_T));
  }

  /* states (dwork) */
  helicopter_2017b_M->dwork = ((void *) &helicopter_2017b_DW);
  (void) memset((void *)&helicopter_2017b_DW, 0,
                sizeof(DW_helicopter_2017b_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_2017b_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_2017b_DW.TimeStampA = 0.0;
  helicopter_2017b_DW.LastUAtTimeA = 0.0;
  helicopter_2017b_DW.TimeStampB = 0.0;
  helicopter_2017b_DW.LastUAtTimeB = 0.0;
  helicopter_2017b_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_2017b_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_2017b_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_2017b_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_2017b_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_2017b_M->Sizes.numY = (0);/* Number of model outputs */
  helicopter_2017b_M->Sizes.numU = (0);/* Number of model inputs */
  helicopter_2017b_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_2017b_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_2017b_M->Sizes.numBlocks = (64);/* Number of blocks */
  helicopter_2017b_M->Sizes.numBlockIO = (15);/* Number of block outputs */
  helicopter_2017b_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return helicopter_2017b_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
