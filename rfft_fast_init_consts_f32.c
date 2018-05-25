/*
 *
 *  Created on: 17 May 2018
 *      Author: Vincent van Beveren
 *              vvanbeveren [at] gmail.com
 */

#include "arm_math.h"
#include "arm_common_tables.h"

#define _LAZY_BUM(FFT_SIZE, APAD, REAL_SIZE, TWID_SIZE) \
		.Sint = { \
				.fftLen = FFT_SIZE, \
				.pTwiddle = (float32_t *) twiddleCoef_ ## REAL_SIZE, \
				.pBitRevTable = (uint16_t *)armBitRevIndexTable ## REAL_SIZE, \
				.bitRevLength = ARMBITREVINDEXTABLE ## APAD ## REAL_SIZE ## _TABLE_LENGTH }, \
		.fftLenRFFT = REAL_SIZE, \
		.pTwiddleRFFT = (float32_t *) twiddleCoef_rfft_ ## TWID_SIZE


const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len4096 =
{
		_LAZY_BUM(1024,, 2048, 4096)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len2048 =
{
		_LAZY_BUM(512,, 1024, 2048)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len1024 =
{
		_LAZY_BUM(256, _, 512, 1024)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len512 =
{
		_LAZY_BUM(128, _, 256, 512)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len256 =
{
		_LAZY_BUM(64, _, 128, 256)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len128 =
{
		_LAZY_BUM(32, __, 64, 128)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len64 =
{
		_LAZY_BUM(16, __, 32, 64)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len32 =
{
		_LAZY_BUM(8, __, 16, 32)
};
