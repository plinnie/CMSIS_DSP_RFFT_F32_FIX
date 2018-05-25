/*
 *
 *  Created on: 17 May 2018
 *      Author: Vincent van Beveren
 *              vvanbeveren [at] gmail.com
 */

#include <rfft_fast_ip_f32.h>
#include <stdio.h>
#include <stdbool.h>

#define PTR_TO_INDEX(SRC, CUR)		((int)( CUR-SRC ))
#define P_TO_INDEX(CUR)		PTR_TO_INDEX(p, CUR)

typedef float32_t cplx32_t[2];

static inline void stage_merge_single(cplx32_t pA, cplx32_t pB,
		cplx32_t pCoeff, cplx32_t pOut, bool merge)
{
    float32_t xAR, xAI, xBR, xBI;				/* temporary variables              */
    float32_t t1a, t1b;				         /* temporary variables              */
    float32_t r, s, t, u;				   /* temporary variables              */
    float32_t twR, twI;						   /* RFFT Twiddle coefficients        */

    xAR = pA[0];
    xAI = pA[1];
    xBR = pB[0];
    xBI = pB[1];

    twR = pCoeff[0];
    twI = pCoeff[1];

    if (merge) {
        t1a = xAR - xBR ;
        t1b = xAI + xBI ;
    }
    else
    {
		t1a = xBR - xAR ;
		t1b = xBI + xAI ;
    }
    // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
    // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
    r = twR * t1a;
    t = twI * t1a;
    u = twR * t1b;
    s = twI * t1b;

    if (merge) {
        *pOut++ = 0.5f * (xAR + xBR - r - s ); //xAR
        *pOut++ = 0.5f * (xAI - xBI + t - u ); //xAI
    }
    else
    {
        pOut[0] = 0.5f * (xAR + xBR + r + s ); //xAR
        pOut[1] = 0.5f * (xAI - xBI + t - u ); //xAI
    }

}


/**
 * In-place version of the stage function for the RFFT
 */
void stage_rfft_ip_f32(arm_rfft_fast_instance_f32 * S, float32_t * p)
{
	uint32_t  k, l;								   /* Loop Counter                     */
	float32_t * pCoeff = S->pTwiddleRFFT;  /* Points to RFFT Twiddle factors   */

	float32_t *pA = p;						   /* increasing pointer               */
	float32_t *pB = p;						   /* decreasing pointer               */

	float32_t * pOut = p;
	cplx32_t tmp;

	k = ( (S->Sint).fftLen ) - 1;
	l = ( (S->Sint).fftLen /2 ) - 1;

	// reverse direction
	float32_t * pCoeffR = S->pTwiddleRFFT + 2 * k;  /* Points to RFFT Twiddle factors   */
	float32_t * pOutR = pOut + 2*k;


    tmp[0] = 0.5f * ( pA[0] + pA[0] + ( pA[1] + pA[1] ) );
    tmp[1] = 0.5f * ( ( pA[0] + pA[0] ) - ( pA[1] + pA[1] ) );

    *pOut++ = tmp[0];
    *pOut++ = tmp[1];


	pCoeff+=2;

	pB  = p + 2*k;
	pA += 2;

	do
	{
		stage_merge_single(pA, pB, pCoeff, tmp, false);
		stage_merge_single(pB, pA, pCoeffR, pOutR, false);
		pCoeff+=2;
		pCoeffR-=2;

		pOut[0] = tmp[0];
		pOut[1] = tmp[1];
		pOut +=2;
		pOutR-=2;
		pA += 2;
		pB -= 2;
		l--;
	} while(l > 0u);

	stage_merge_single(pA, pB, pCoeff, pOut, false);
}


/* Prepares data for inverse cfft */
void merge_rfft_ip_f32(
		arm_rfft_fast_instance_f32 * S,
		float32_t * p)
{
   uint32_t  k, l;							/* Loop Counter                     */
   float32_t *pCoeff = S->pTwiddleRFFT;		/* Points to RFFT Twiddle factors   */
   float32_t *pA = p;						/* increasing pointer               */
   float32_t *pB = p;						/* decreasing pointer               */
   float32_t * pOut = p;

   cplx32_t tmp;
   k = (S->Sint).fftLen - 1;
   l = ( (S->Sint).fftLen /2 ) - 1;
	float32_t * pCoeffR = S->pTwiddleRFFT + 2 * k;  /* Points to RFFT Twiddle factors   */
	float32_t * pOutR = pOut + 2*k;

   pCoeff += 2 ;

   tmp[0] = 0.5f * ( pA[0] + pA[1] );
   tmp[1] = 0.5f * ( pA[0] - pA[1] );

   *pOut++=tmp[0];
   *pOut++=tmp[1];

   pB  =  p + 2*k ;
   pA +=  2	   ;

   do
   {
	   stage_merge_single(pA, pB, pCoeff, tmp, true);
	   stage_merge_single(pB, pA, pCoeffR, pOutR, true);
		pCoeff+=2;
		pCoeffR-=2;

		pOut[0] = tmp[0];
		pOut[1] = tmp[1];
		pOut +=2;
		pOutR-=2;
		pA += 2;
		pB -= 2;
		l--;
   } while (l > 0u);
   stage_merge_single(pA, pB, pCoeff, pOut, true);

}


void arm_rfft_fast_ip_f32(
	arm_rfft_fast_instance_f32 * S,
	float32_t * p,
	uint8_t ifftFlag)
{
   arm_cfft_instance_f32 * Sint = &(S->Sint);
   Sint->fftLen = S->fftLenRFFT / 2;

   /* Calculation of Real FFT */
   if(ifftFlag)
   {
      /*  Real FFT compression */
      merge_rfft_ip_f32(S, p);

      /* Complex radix-4 IFFT process */
      arm_cfft_f32( Sint, p, ifftFlag, 1);
   }
   else
   {
      /* Calculation of RFFT of input */
      arm_cfft_f32( Sint, p, ifftFlag, 1);

      /*  Real FFT extraction */
      stage_rfft_ip_f32(S, p);
   }
}
