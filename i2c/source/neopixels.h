/*
 * neopixels.h
 *
 *  Created on: 28 lis 2021
 *      Author: daniel
 */

#ifndef NEOPIXELS_H_
#define NEOPIXELS_H_

#include "fsl_spi.h"

#define GET_BIT(k, n)	(k &   (1 << (n)))
#define SET_BIT(k, n)	(k |=  (1 << (n)))
#define CLR_BIT(k, n)	(k &= ~(1 << (n)))

#define CODE_0			0b10000
#define CODE_1			0b11100

void Neopixels_Init(SPI_Type *base, uint32_t n);
void Neopixels_Send(uint32_t *value);

void Neopixels_Animate(uint32_t *value, uint32_t color);
void Neopixels_ShiftL(uint32_t *dst, uint32_t *src);
void Neopixels_ShiftR(uint32_t *dst, uint32_t *src);

#endif /* NEOPIXELS_H_ */
