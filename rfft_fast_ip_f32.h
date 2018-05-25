/*
 *  Created on: 17 May 2018
 *      Author: Vincent van Beveren
 *              vvanbeveren [at] gmail.com
 */

#include "arm_math.h"

#ifndef RFFT_FAST_IP_H_
#define RFFT_FAST_IP_H_

void arm_rfft_fast_ip_f32(
	arm_rfft_fast_instance_f32 * S,
	float32_t * p,
	uint8_t ifftFlag);


#endif /* RFFT_FAST_IP_H_ */
