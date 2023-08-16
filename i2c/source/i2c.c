#include <stdio.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "fsl_power.h"
#include "oled.h"
#include "neopixels.h"

#define I2C_OLED ((I2C_Type *)I2C1_BASE)
#define LEDS 10
#define BUFFER_SIZE 32
#define BARMODE PB_CENTER

char sbuff[32];
lpadc_conv_result_t g_LpadcResultConfigStruct;
uint16_t adcCh1, adcCh2;
float Xval, Yval;
int Xint, Yint;
/* ADC0_IRQn interrupt handler */
void ADC0_IRQHANDLER(void) {
	LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
	adcCh1=g_LpadcResultConfigStruct.convValue;
	LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
	adcCh2=g_LpadcResultConfigStruct.convValue;
}

uint32_t increase_color(uint32_t color, int pair)
{
	uint32_t mask = 0xFF;
	uint32_t shift = pair * 8;
	uint32_t color_pair = (color >> shift) & mask;

	if (color_pair < 0xFF) {
		color_pair++;
	}

	color &= ~(mask << shift);
	color |= color_pair << shift;

	return color;
}
uint32_t decrease_color(uint32_t color, int pair)
{
	uint32_t mask = 0xFF;
	uint32_t shift = pair * 8;
	uint32_t color_pair = (color >> shift) & mask;

	if (color_pair > 0) {
		color_pair--;
	}

	color &= ~(mask << shift);
	color |= color_pair << shift;

	return color;
}


typedef struct{
	char name[16];
	uint8_t min;
	uint8_t max;
}Menu_t;


Menu_t mm [4]={
		{"Diode", 0,   (LEDS-1)},
		{"Blue", 0, 254},
		{"Red",   0, 254},
		{"Green",  0, 254}
};

int diode_select [LEDS][5]={
		{1, 0, 0, 0},
		{2, 0, 0, 0},
		{3, 0, 0, 0},
		{4, 0, 0, 0},
		{5, 0, 0, 0},
		{6, 0, 0, 0},
		{7, 0, 0, 0},
		{8, 0, 0, 0},
		{9, 0, 0, 0},
		{10, 0, 0, 0},
};

uint32_t colors[LEDS] = {0};
/*
 * @brief Application entry point.
 */
int main(void) {
	/* Disable LDOGPADC power down */
	POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	/* Initialize OLED */
	OLED_Init(I2C_OLED);
	OLED_Puts(52, 0, "MENU");
	OLED_Draw_Line(0,10, 127,10);

	OLED_Refresh_Gram();
	int max=4;
	int i;
	int sel=0;
	int ds=0;

	/* Initialize neopixels */
	Neopixels_Init(FLEXCOMM3_PERIPHERAL, LEDS);
	uint32_t color=0x666666;

	while(1) {

		Xint=(adcCh1/100)-327;
		Yint=(adcCh2/100)-327;
		sprintf(sbuff, "CH1:%04d CH2:%04d",Xint , Yint);
		OLED_Puts(0, 2, sbuff);
		//display option
		for(i=0;i<max;i++){
			if(i==sel){
				sprintf(sbuff, "[*] %s = %03d", mm[i].name, diode_select[ds][i]);
			}
			else{
				sprintf(sbuff, "[ ] %s = %03d", mm[i].name, diode_select[ds][i]);
			}
			OLED_Puts(0, 3+i, sbuff);
		}
		OLED_Refresh_Gram();
		//Y Sektor
		if(Yint>300 && sel<(max-1)){
			sel++;
		}else if(Yint<(-300) && sel>0){
			sel--;
		}
		//X sektor
		switch (sel){
		case 0:
			if(Xint>300 && ds<mm[0].max){
				ds++;
			}else if(Xint<(-300) && ds>0){
				ds--;
			}
			break;
		case 1:
		case 2:
		case 3:
			if(Xint>300 && diode_select[ds][sel]<mm[sel].max){

				color=colors[ds];
				colors[ds]=increase_color(color,sel-1);
				diode_select[ds][sel]++;
			}else if(Xint<(-300) && diode_select[ds][sel]>mm[sel].min){
				color=colors[ds];
				colors[ds]=decrease_color(color,sel-1);
				diode_select[ds][sel]--;
			}
			break;
		}
		Neopixels_Send(colors);


	}
	return 0 ;
}
