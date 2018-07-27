/*
 *
 *  Created on: 17 May 2018
 *      Author: Vincent van Beveren
 *              vvanbeveren [at] gmail.com
 */

#include "arm_math.h"
#include "arm_common_tables.h"

#define _RFFT_FAST_INSTANCE_F32_INIT(CFFT_SIZE, APAD, REAL_SIZE) \
		.Sint = { \
				.fftLen = CFFT_SIZE, \
				.pTwiddle = (float32_t *) twiddleCoef_ ## CFFT_SIZE, \
				.pBitRevTable = (uint16_t *)armBitRevIndexTable ## CFFT_SIZE, \
				.bitRevLength = ARMBITREVINDEXTABLE ## APAD ## CFFT_SIZE ## _TABLE_LENGTH }, \
		.fftLenRFFT = REAL_SIZE, \
		.pTwiddleRFFT = (float32_t *) twiddleCoef_rfft_ ## REAL_SIZE


const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len4096 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(2048,, 4096)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len2048 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(1024,, 2048)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len1024 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(512, _, 1024)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len512 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(256, _, 512)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len256 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(128, _, 256)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len128 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(64, __, 128)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len64 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(32, __, 64)
};

const arm_rfft_fast_instance_f32 arm_rfft_fast_f32_len32 =
{
		_RFFT_FAST_INSTANCE_F32_INIT(16, __, 32)
};
