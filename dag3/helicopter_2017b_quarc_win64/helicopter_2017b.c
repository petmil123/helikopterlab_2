/*
 * helicopter_2017b.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_2017b".
 *
 * Model version              : 11.0
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar  6 15:16:57 2025
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
  real_T rtb_xx[4];
  real_T rtb_Frontgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_Backgain;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain1_idx_3;
  real_T *lastU;
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
     *  Constant: '<Root>/Constant'
     */
    helicopter_2017b_B.Sum3 = helicopter_2017b_P.Constant_Value +
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
  rtb_Gain1_idx_2 = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_i;
  rtb_Gain1_idx_3 = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_b;

  /* FromWorkspace: '<S5>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_2017b_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter_2017b_M->Timing.t[0];
    if (t >= pTimeValues[140]) {
      {
        int_T elIdx;
        for (elIdx = 0; elIdx < 4; ++elIdx) {
          (&rtb_xx[0])[elIdx] = pDataValues[140];
          pDataValues += 141;
        }
      }
    } else {
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

      helicopter_2017b_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

      /* Post output */
      {
        real_T t1 = pTimeValues[currTimeIndex];
        real_T t2 = pTimeValues[currTimeIndex + 1];
        if (t1 == t2) {
          if (t < t1) {
            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 4; ++elIdx) {
                (&rtb_xx[0])[elIdx] = pDataValues[currTimeIndex];
                pDataValues += 141;
              }
            }
          } else {
            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 4; ++elIdx) {
                (&rtb_xx[0])[elIdx] = pDataValues[currTimeIndex + 1];
                pDataValues += 141;
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
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              d1 = pDataValues[TimeIndex];
              d2 = pDataValues[TimeIndex + 1];
              (&rtb_xx[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
              pDataValues += 141;
            }
          }
        }
      }
    }
  }

  /* Sum: '<S5>/Sum' incorporates:
   *  Gain: '<S2>/Gain1'
   */
  rtb_xx[0] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Sum3 - rtb_xx[0];
  rtb_xx[1] = helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_d -
    rtb_xx[1];
  rtb_xx[2] = rtb_Gain1_idx_2 - rtb_xx[2];
  rtb_xx[3] = rtb_Gain1_idx_3 - rtb_xx[3];

  /* FromWorkspace: '<S5>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_2017b_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_2017b_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_2017b_M->Timing.t[0];
    if (t >= pTimeValues[140]) {
      rtb_Frontgain = pDataValues[140];
    } else {
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

      helicopter_2017b_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

      /* Post output */
      {
        real_T t1 = pTimeValues[currTimeIndex];
        real_T t2 = pTimeValues[currTimeIndex + 1];
        if (t1 == t2) {
          if (t < t1) {
            rtb_Frontgain = pDataValues[currTimeIndex];
          } else {
            rtb_Frontgain = pDataValues[currTimeIndex + 1];
          }
        } else {
          real_T f1 = (t2 - t) / (t2 - t1);
          real_T f2 = 1.0 - f1;
          real_T d1;
          real_T d2;
          int_T TimeIndex= currTimeIndex;
          d1 = pDataValues[TimeIndex];
          d2 = pDataValues[TimeIndex + 1];
          rtb_Frontgain = (real_T) rtInterpolate(d1, d2, f1, f2);
          pDataValues += 141;
        }
      }
    }
  }

  /* Sum: '<S6>/Sum2' incorporates:
   *  Gain: '<S5>/Gain'
   *  Sum: '<S5>/Sum1'
   */
  rtb_Gain1_idx_2 = (rtb_Frontgain - (((helicopter_2017b_P.K[0] * rtb_xx[0] +
    helicopter_2017b_P.K[1] * rtb_xx[1]) + helicopter_2017b_P.K[2] * rtb_xx[2])
    + helicopter_2017b_P.K[3] * rtb_xx[3])) - rtb_Gain1_idx_2;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S6>/Sum3'
   */
  rtb_Frontgain = helicopter_2017b_P.K_pd * rtb_Gain1_idx_3;
  rtb_Frontgain = (helicopter_2017b_P.K_pp * rtb_Gain1_idx_2 - rtb_Frontgain) +
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

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Gain1_idx_3 = helicopter_2017b_P.elevation_ref_Value -
    helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopter_2017b_P.K_ep * rtb_Gain1_idx_3 +
                   helicopter_2017b_X.Integrator_CSTATE) -
                  helicopter_2017b_P.Gain1_Gain * helicopter_2017b_B.Gain_dg *
                  helicopter_2017b_P.K_ed) + helicopter_2017b_P.Vs_ff;

  /* Sum: '<S1>/Subtract' */
  rtb_Gain1_idx_2 = rtb_Backgain - rtb_Frontgain;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Frontgain = (rtb_Frontgain + rtb_Backgain) *
    helicopter_2017b_P.Frontgain_Gain;

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
    helicopter_2017b_B.In1 = helicopter_2017b_P.K_ei * rtb_Gain1_idx_3;
    if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
      srUpdateBC(helicopter_2017b_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Gain1_idx_3 = helicopter_2017b_M->Timing.t[0];
  if ((helicopter_2017b_DW.TimeStampA >= rtb_Gain1_idx_3) &&
      (helicopter_2017b_DW.TimeStampB >= rtb_Gain1_idx_3)) {
    rtb_Gain1_idx_3 = 0.0;
  } else {
    rtb_Backgain = helicopter_2017b_DW.TimeStampA;
    lastU = &helicopter_2017b_DW.LastUAtTimeA;
    if (helicopter_2017b_DW.TimeStampA < helicopter_2017b_DW.TimeStampB) {
      if (helicopter_2017b_DW.TimeStampB < rtb_Gain1_idx_3) {
        rtb_Backgain = helicopter_2017b_DW.TimeStampB;
        lastU = &helicopter_2017b_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_2017b_DW.TimeStampA >= rtb_Gain1_idx_3) {
        rtb_Backgain = helicopter_2017b_DW.TimeStampB;
        lastU = &helicopter_2017b_DW.LastUAtTimeB;
      }
    }

    rtb_Gain1_idx_3 = (helicopter_2017b_B.PitchCounttorad - *lastU) /
      (rtb_Gain1_idx_3 - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopter_2017b_B.Gain_l = helicopter_2017b_P.Gain_Gain_a1 * rtb_Gain1_idx_3;
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
  }

  /* Gain: '<S1>/Back gain' */
  rtb_Gain1_idx_2 *= helicopter_2017b_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Gain1_idx_2 > helicopter_2017b_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_2017b_B.BackmotorSaturation =
      helicopter_2017b_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Gain1_idx_2 < helicopter_2017b_P.BackmotorSaturation_LowerSat)
  {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_2017b_B.BackmotorSaturation =
      helicopter_2017b_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_2017b_B.BackmotorSaturation = rtb_Gain1_idx_2;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_2017b_M)) {
  }

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Frontgain > helicopter_2017b_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_2017b_B.FrontmotorSaturation =
      helicopter_2017b_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Frontgain < helicopter_2017b_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_2017b_B.FrontmotorSaturation =
      helicopter_2017b_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_2017b_B.FrontmotorSaturation = rtb_Frontgain;
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
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413582149, 3.1262155534451876,
      3.1033093000086569, 3.0666274151712036, 3.0144539223755227,
      2.9456562770894306, 2.8595077632555621, 2.7555515879060017,
      2.6335051104155554, 2.4931956059418106, 2.3345185759585552,
      2.1583782670744793, 1.9678000582515516, 1.7674109956246029,
      1.5625809551106749, 1.3586838042117442, 1.160591837149455,
      0.97235388541366807, 0.79694979461985793, 0.63643262347983853,
      0.49215933324437616, 0.36485709433426744, 0.25463979479113147,
      0.16109616198091428, 0.0834005747557621, 0.020423656701467584,
      -0.029167441634014041, -0.0668229040038159, -0.094039064045908782,
      -0.11230155619180422, -0.12304153585051807, -0.12760344282663016,
      -0.12722271685527081, -0.12301190963314952, -0.11595372709583784,
      -0.10689965407139555, -0.096572947136789308, -0.085574921741480167,
      -0.074393600563130949, -0.0634139273105431, -0.052928880655307133,
      -0.0431509443432898, -0.034223500308595875, -0.026231810823570321,
      -0.019213342952669438, -0.013167263940239541, -0.0080629999030516417,
      -0.003847803070130456, -0.00045331552823972581, 0.0021988489643171485,
      0.0041924581202335883, 0.00561288393568181, 0.0065441176580294065,
      0.0070664922880743688, 0.0072550250673766078, 0.0071782928369717534,
      0.0068977561525435886, 0.0064674529807464409, 0.0059339890637071287,
      0.005336759157297092, 0.0047083409042859093, 0.004075010768385825,
      0.0034573389697872951, 0.0028708275277732087, 0.0023265621902544961,
      0.0018318551167922441, 0.0013908606229879653, 0.0010051510698949417,
      0.000674244088509103, 0.00039607579358547237, 0.00016741749631803696,
      -1.5764280173353518E-5, -0.00015800288862485154, -0.00026407881776125905,
      -0.00033881524299180372, -0.00038691737194857987, -0.00041285075168763388,
      -0.00042075359471869405, -0.00041437825157052425, -0.00039705716707539766,
      -0.00037168896787536797, -0.00034074070929140037, -0.00030626273220211531,
      -0.00026991302316673263, -0.00023298841458157724, -0.00019646039112445756,
      -0.00016101367185843268, -0.00012708610401340157, -9.4908725844947074E-5,
      -6.4545123717650192E-5, -3.592941340810369E-5, -8.9023066044331287E-6,
      1.67552334246215E-5, 4.1291304298416117E-5, 6.4956082751181863E-5,
      8.7979585567719455E-5, 0.00011055557877131724, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048923398721,
      -0.046506351662157289, -0.091625013736012784, -0.14672753940708549,
      -0.20869397121864477, -0.27519058114010431, -0.34459405537252386,
      -0.41582470135528887, -0.48818590995171285, -0.561238017907483,
      -0.6347081199260326, -0.70456123549066352, -0.7623128352917653,
      -0.80155625052037771, -0.8193201620233741, -0.81558860358056107,
      -0.79236786825385808, -0.75295180693473029, -0.70161636313035314,
      -0.64206868453368082, -0.57709316092407781, -0.50920895564774549,
      -0.44086919821273646, -0.37417453124482747, -0.31078234891724055,
      -0.25190767220695082, -0.19836439333609265, -0.15062184952529542,
      -0.10886464018016356, -0.07304996857806309, -0.042959918628759981,
      -0.018247627906739717, 0.0015229038873976648, 0.01684322888524967,
      0.028232730151315905, 0.03621629209775086, 0.0413068277394143,
      0.043992101580596736, 0.044725284715710238, 0.043918693010878487,
      0.041940186619511988, 0.039111745249671807, 0.035709776139896919,
      0.031966757940831904, 0.028073871482771681, 0.02418431604818146,
      0.020417056146099066, 0.016860787330772131, 0.013577950167695991,
      0.010608657970925807, 0.00797443662371479, 0.0056817032618060835,
      0.0037249348892810677, 0.00208949852019731, 0.00075413111717369035,
      -0.00030692892176399362, -0.0011221467378358095, -0.0017212126872867938,
      -0.002133855668163705, -0.0023889196256491785, -0.0025136730121218032,
      -0.0025333205435167688, -0.002470687194509419, -0.0023460457681799335,
      -0.0021770613499695005, -0.0019788282937381069, -0.0017639779752998287,
      -0.0015428382123137971, -0.0013236279254513681, -0.0011126731797602906,
      -0.00091463318910013419, -0.00073272710592316419, -0.00056895443377438662,
      -0.00042430371650861211, -0.00029894570099385254, -0.00019240851577919036,
      -0.00010373351896749664, -3.1611372109650092E-5, 2.5501372608845534E-5,
      6.9284337970899255E-5, 0.00010147279680020074, 0.00012379303434022928,
      0.00013791190835482731, 0.0001453988361432044, 0.00014769843433975455,
      0.00014611209382889268, 0.00014178687706407854, 0.00013571027138385935,
      0.00012870951267127332, 0.00012145440851360878, 0.00011446284124166739,
      0.00010810842721246931, 0.00010263016011615059, 9.814428349528332E-5,
      9.4659113811636483E-5, 9.2094011265841629E-5, 9.030397281419112E-5,
      8.9110874036922542E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205271733, 0.22266037931724236, 0.31888147181806148,
      0.38944360630172736, 0.43795507376893028, 0.469972642297003,
      0.49051724877245173, 0.50343100141613528, 0.511421385864229,
      0.51630439858397115, 0.51925862127874811, 0.49369514248843205,
      0.40816625077914015, 0.27735747076053063, 0.12554854218715172,
      -0.026373229727520486, -0.164115288753387, -0.27857766715340654,
      -0.36281931108439069, -0.4208602499345514, -0.4592221853769799,
      -0.47977963628668946, -0.48299930537324831, -0.47137243453595939,
      -0.44803173403682817, -0.41610372882431246, -0.3784234455677159,
      -0.33742606610112374, -0.29512400757550161, -0.25312442043433514,
      -0.21266498101944237, -0.17465703260766607, -0.13973056788676946,
      -0.10827820595832821, -0.0804966450091294, -0.056424766734068543,
      -0.035977961708859529, -0.018978489955039257, -0.0051818583726613854,
      0.0057006821092561166, 0.013983327514848432, 0.019990343358361584,
      0.024043818388026383, 0.02645422305472489, 0.027513434693403949,
      0.027489892301860053, 0.026625554219235958, 0.025134349771202436,
      0.023201839266379642, 0.020985823213777732, 0.018617670416006593,
      0.016204163759810819, 0.013829691513070119, 0.011558639652003877,
      0.0094378667907011327, 0.0074991671131323656, 0.0057616481733788749,
      0.004233969333186649, 0.0029164029915336176, 0.0018026946366057617,
      0.00088170928936859294, 0.000138861248639488, -0.00044266859119290736,
      -0.00088091799737366472, -0.0011943173280699604, -0.0014010355304926447,
      -0.0015184799956344808, -0.0015629313846180493, -0.0015492945849823192,
      -0.0014909475751988532, -0.0013996710157261338, -0.0012856427225392819,
      -0.0011574826975170316, -0.0010223360238825752, -0.00088598257729399776,
      -0.000752964135150469, -0.00062672101042093864, -0.00050973178870228342,
      -0.00040365106669892903, -0.00030944127771603824, -0.00022749573336744433,
      -0.00015775091422065568, -9.9786809252599973E-5, -5.2914746154653081E-5,
      -1.6252681796502522E-5, 1.121164885808934E-5, 3.0568980152079206E-5,
      4.2947128133796753E-5, 4.9478688816551042E-5, 5.12763053039933E-5,
      4.94137271926931E-5, 4.4910571443512737E-5, 3.8718299576467885E-5,
      3.1704462708836978E-5, 2.4631848245970644E-5, 1.8129165110125633E-5,
      1.2651308119449034E-5, 8.4323664856222891E-6, 5.4485824280137152E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823901749,
      0.46652650906565823, 0.38488436998130687, 0.28224853798850719,
      0.19404586987415359, 0.12807027412177555, 0.082178425901790933,
      0.051655010571723288, 0.031961537788015172, 0.019532050866728629,
      0.011816890785683402, -0.10225391516443232, -0.34211556681781941,
      -0.52323512013886564, -0.60723571423600387, -0.6076870879145424,
      -0.55096823602552736, -0.45784951366768789, -0.33696657572239386,
      -0.23216375540673251, -0.15344774176262255, -0.082229803638574475,
      -0.012878676345992591, 0.04650748334066946, 0.093362802005396567,
      0.12771202085591069, 0.15072113302893114, 0.16398951787526592,
      0.16920823410343, 0.16799834857169477, 0.1618377576439376,
      0.1520317936439845, 0.13970585888932918, 0.12580944770610064,
      0.11112624379569233, 0.096287513099123312, 0.081787220097741226,
      0.067997887011750621, 0.055186526330156124, 0.043530161930048182,
      0.033130581618621424, 0.024028063358229098, 0.016213900126937561,
      0.0096416186714836424, 0.0042368465446831673, -9.4169569525813716E-5,
      -0.0034573523454725806, -0.0059648177867319685, -0.0077300420168559137,
      -0.0088640642080029166, -0.0094726111929120463, -0.0096540266244159074,
      -0.0094978889882161091, -0.00908420744514386, -0.008483091446542957,
      -0.0077547987100980908, -0.0069500757595734146, -0.0061107153607488467,
      -0.0052702653666019993, -0.0044548334196176965, -0.0036839413888630555,
      -0.0029713921618689664, -0.0023261193597050411, -0.0017529976249371878,
      -0.0012535973236524201, -0.00082687280939718055, -0.00046977786004715448,
      -0.0001778055558752001, 5.4547198370003656E-5, 0.0002333880394876374,
      0.00036510623743847613, 0.00045611317304471139, 0.0005126400998364867,
      0.00054058669474881253, 0.00054541378618761383, 0.00053207376862337641,
      0.000504972498913732, 0.00046795688686614975, 0.00042432288798838181,
      0.00037683915597394656, 0.00032778217738046929, 0.00027897927658426233,
      0.00023185641986875168, 0.00018748825240018474, 0.00014664825741329273,
      0.0001098573226275894, 7.7429325189325263E-5, 4.9512591913512545E-5,
      2.6126242727142571E-5, 7.190465950770913E-6, -7.4503124411433E-6,
      -1.8012622997093177E-5, -2.4769087469308143E-5, -2.8055347469382831E-5,
      -2.8290457852568025E-5, -2.6010732544506974E-5, -2.1911427962136809E-5,
      -1.687576653522889E-5, -1.1935136230282875E-5, -8.0237304763823422E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

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
  helicopter_2017b_M->Sizes.checksums[0] = (1782252296U);
  helicopter_2017b_M->Sizes.checksums[1] = (108766134U);
  helicopter_2017b_M->Sizes.checksums[2] = (2384524848U);
  helicopter_2017b_M->Sizes.checksums[3] = (4100503825U);

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
  helicopter_2017b_M->Sizes.numBlocks = (65);/* Number of blocks */
  helicopter_2017b_M->Sizes.numBlockIO = (15);/* Number of block outputs */
  helicopter_2017b_M->Sizes.numBlockPrms = (149);/* Sum of parameter "widths" */
  return helicopter_2017b_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
