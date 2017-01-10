/*
N point Complex fft and inverse fft functions
*/

#include "simpleDSP_fft.h"


void FFT(COMPLEX *Y, int N) /*input sample array, # of points      */
  {
  COMPLEX temp1,temp2;      /*temporary storage variables          */
  int i,j,k;                /*loop counter variables               */
  int upper_leg, lower_leg; /*index of upper/lower butterfly leg   */
  int leg_diff;             /*difference between upper/lower leg   */
  int num_stages=0;         /*number of FFT stages, or iterations  */
  int index, step;          /*index and step between twiddle factor*/
  /* log(base 2) of # of points = # of stages  */
  i=1;
  do
    {
    num_stages+=1;
    i=i*2;
    } while (i!=N);
  /* starting difference between upper and lower butterfly legs*/
  leg_diff=N/2;
  /* step between values in twiddle factor array twiddle.h     */
  step=512/N;
  /* For N-point FFT                                           */
  for (i=0;i<num_stages;i++)
    {
    index=0;
    for (j=0;j<leg_diff;j++)
      {
      for (upper_leg=j;upper_leg<N;upper_leg+=(2*leg_diff))
        {
        lower_leg=upper_leg+leg_diff;
        temp1.real=(Y[upper_leg]).real + (Y[lower_leg]).real;
        temp1.imag=(Y[upper_leg]).imag + (Y[lower_leg]).imag;
        temp2.real=(Y[upper_leg]).real - (Y[lower_leg]).real;
        temp2.imag=(Y[upper_leg]).imag - (Y[lower_leg]).imag;
        (Y[lower_leg]).real=temp2.real*(w[index]).real-temp2.imag*(w[index]).imag;
        (Y[lower_leg]).imag=temp2.real*(w[index]).imag+temp2.imag*(w[index]).real;
        (Y[upper_leg]).real=temp1.real;
        (Y[upper_leg]).imag=temp1.imag;
        }
      index+=step;
      }
    leg_diff=leg_diff/2;
    step*=2;
    }
/* bit reversal for resequencing data */
  j=0;
  for (i=1;i<(N-1);i++)
    {
    k=N/2;
    while (k<=j)
      {
      j=j-k;
      k=k/2;
      }
    j=j+k;
    if (i<j)
      {
      temp1.real=(Y[j]).real;
      temp1.imag=(Y[j]).imag;
      (Y[j]).real=(Y[i]).real;
      (Y[j]).imag=(Y[i]).imag;
      (Y[i]).real=temp1.real;
      (Y[i]).imag=temp1.imag;
      }
    }
  return;
  }

void IFFT(COMPLEX *Y, int N) /*input sample array, # of points      */
  {
  COMPLEX temp1,temp2;      /*temporary storage variables          */
  int i,j,k;                /*loop counter variables               */
  int upper_leg, lower_leg; /*index of upper/lower butterfly leg   */
  int leg_diff;             /*difference between upper/lower leg   */
  int num_stages=0;         /*number of FFT stages, or iterations  */
  int index, step;          /*index and step between twiddle factor*/

  for (i=0;i<=N;i++)
      {
      //w[i].real=w[i].real;
      w[i].imag=-w[i].imag;
      }
  /* log(base 2) of # of points = # of stages  */
  i=1;
  do
    {
    num_stages+=1;
    i=i*2;
    } while (i!=N);

  /* starting difference between upper and lower butterfly legs*/
  leg_diff=N/2;
  /* step between values in twiddle factor array twiddle.h     */
  step=512/N;
  /* For N-point IFFT                                           */
  for (i=0;i<num_stages;i++)
    {
    index=0;
    for (j=0;j<leg_diff;j++)
      {
      for (upper_leg=j;upper_leg<N;upper_leg+=(2*leg_diff))
        {
        lower_leg=upper_leg+leg_diff;
        temp1.real=(Y[upper_leg]).real + (Y[lower_leg]).real;
        temp1.imag=(Y[upper_leg]).imag + (Y[lower_leg]).imag;
        temp2.real=(Y[upper_leg]).real - (Y[lower_leg]).real;
        temp2.imag=(Y[upper_leg]).imag - (Y[lower_leg]).imag;
        (Y[lower_leg]).real=temp2.real*(w[index]).real-temp2.imag*(w[index]).imag;
        (Y[lower_leg]).imag=temp2.real*(w[index]).imag+temp2.imag*(w[index]).real;
        (Y[upper_leg]).real=temp1.real;
        (Y[upper_leg]).imag=temp1.imag;
        }
      index+=step;
      }
    leg_diff=leg_diff/2;
    step*=2;
    }
  /* bit reversal for resequencing data */
  j=0;
  for (i=1;i<(N-1);i++)
    {
    k=N/2;
    while (k<=j)
      {
      j=j-k;
      k=k/2;
      }
    j=j+k;
    if (i<j)
      {
      temp1.real=(Y[j]).real;
      temp1.imag=(Y[j]).imag;
      (Y[j]).real=(Y[i]).real;
      (Y[j]).imag=(Y[i]).imag;
      (Y[i]).real=temp1.real;
      (Y[i]).imag=temp1.imag;
      }
    }
  return;
  }

COMPLEX w[] = {
       1.00000,-0.00000,
       0.99992,-0.01227,
       0.99970,-0.02454,
       0.99932,-0.03681,
       0.99880,-0.04907,
       0.99812,-0.06132,
       0.99729,-0.07356,
       0.99631,-0.08580,
       0.99518,-0.09802,
       0.99391,-0.11022,
       0.99248,-0.12241,
       0.99090,-0.13458,
       0.98918,-0.14673,
       0.98730,-0.15886,
       0.98528,-0.17096,
       0.98311,-0.18304,
       0.98079,-0.19509,
       0.97832,-0.20711,
       0.97570,-0.21910,
       0.97294,-0.23106,
       0.97003,-0.24298,
       0.96698,-0.25487,
       0.96378,-0.26671,
       0.96043,-0.27852,
       0.95694,-0.29028,
       0.95331,-0.30201,
       0.94953,-0.31368,
       0.94561,-0.32531,
       0.94154,-0.33689,
       0.93734,-0.34842,
       0.93299,-0.35990,
       0.92851,-0.37132,
       0.92388,-0.38268,
       0.91911,-0.39399,
       0.91421,-0.40524,
       0.90917,-0.41643,
       0.90399,-0.42756,
       0.89867,-0.43862,
       0.89322,-0.44961,
       0.88764,-0.46054,
       0.88192,-0.47140,
       0.87607,-0.48218,
       0.87009,-0.49290,
       0.86397,-0.50354,
       0.85773,-0.51410,
       0.85136,-0.52459,
       0.84485,-0.53500,
       0.83822,-0.54532,
       0.83147,-0.55557,
       0.82459,-0.56573,
       0.81758,-0.57581,
       0.81046,-0.58580,
       0.80321,-0.59570,
       0.79584,-0.60551,
       0.78835,-0.61523,
       0.78074,-0.62486,
       0.77301,-0.63439,
       0.76517,-0.64383,
       0.75721,-0.65317,
       0.74914,-0.66242,
       0.74095,-0.67156,
       0.73265,-0.68060,
       0.72425,-0.68954,
       0.71573,-0.69838,
       0.70711,-0.70711,
       0.69838,-0.71573,
       0.68954,-0.72425,
       0.68060,-0.73265,
       0.67156,-0.74095,
       0.66242,-0.74914,
       0.65317,-0.75721,
       0.64383,-0.76517,
       0.63439,-0.77301,
       0.62486,-0.78074,
       0.61523,-0.78835,
       0.60551,-0.79584,
       0.59570,-0.80321,
       0.58580,-0.81046,
       0.57581,-0.81758,
       0.56573,-0.82459,
       0.55557,-0.83147,
       0.54532,-0.83822,
       0.53500,-0.84485,
       0.52459,-0.85136,
       0.51410,-0.85773,
       0.50354,-0.86397,
       0.49290,-0.87009,
       0.48218,-0.87607,
       0.47140,-0.88192,
       0.46054,-0.88764,
       0.44961,-0.89322,
       0.43862,-0.89867,
       0.42756,-0.90399,
       0.41643,-0.90917,
       0.40524,-0.91421,
       0.39399,-0.91911,
       0.38268,-0.92388,
       0.37132,-0.92851,
       0.35990,-0.93299,
       0.34842,-0.93734,
       0.33689,-0.94154,
       0.32531,-0.94561,
       0.31368,-0.94953,
       0.30201,-0.95331,
       0.29028,-0.95694,
       0.27852,-0.96043,
       0.26671,-0.96378,
       0.25487,-0.96698,
       0.24298,-0.97003,
       0.23106,-0.97294,
       0.21910,-0.97570,
       0.20711,-0.97832,
       0.19509,-0.98079,
       0.18304,-0.98311,
       0.17096,-0.98528,
       0.15886,-0.98730,
       0.14673,-0.98918,
       0.13458,-0.99090,
       0.12241,-0.99248,
       0.11022,-0.99391,
       0.09802,-0.99518,
       0.08580,-0.99631,
       0.07356,-0.99729,
       0.06132,-0.99812,
       0.04907,-0.99880,
       0.03681,-0.99932,
       0.02454,-0.99970,
       0.01227,-0.99992,
      };


