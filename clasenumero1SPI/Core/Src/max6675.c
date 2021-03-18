/*
 * max6675.c
 *
 *  Created on: Mar 7, 2021
 *      Author: PEPE
 */


#include "main.h"
#include "max6675.h"
//#include "stm32l476xx.h"
//#include "stm32l4xx_hal.h"



void initSPI2(void)
{

	//Define SPI2 PIN PB13,PB14 & PB15
	GPIOB->MODER &= 0xABFFFFFF;

	// enable SPI2
	RCC->APB1ENR1 |= (1 <<14);

	// SET pin speed in very high
	GPIOB->OSPEEDR |= 0xFC000000;


	GPIOB->AFR[1] |= (0x5 << 20); //for pin 13 clk
	GPIOB->AFR[1] |= (0X5 << 24); // for pin 14 mosi
	GPIOB->AFR[1] |= (0x5 << 28); // for pin 15 miso

	// Define SPI2 CLOCK
	SPI2->CR1 |= (1 <<5);

	// DEFINE MODE SPI IN 0
	SPI2->CR1 |= (0 <<1); // CPOL IN 0
	SPI2->CR1 |= (0 <<0); // CPHA IN 0

	// set data size to 16 (sz)
	SPI2->CR2 |= (0xF << 8);

	// set master mode
	SPI2->CR1 |= (1 << 2);

	// SOFTWARE slave managment
	SPI2->CR1 |= (1 << 9);

	// Internal slave selector
	SPI2->CR1 |= (1 << 8);

	// enable SPI2
	SPI2->CR1 |= (1 <<6);

	// Wait while initialize
	HAL_Delay(100);

}

uint16_t ReadTemp(void)
{
	uint16_t sTemp;

	// set CD low
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);


	// send data
	*(uint16_t*)&SPI2->DR = 0X0000;

	// while until transmist is empty
	while(!(SPI2->SR & (1 << 1)));

	// WAIT BUSY
	while(!(SPI2->SR & (1 << 7)));


	// read data
	sTemp = *(uint16_t*)&SPI2->DR;

	// set CS high
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

	return sTemp;

}
