/*
 * max6675.h
 *
 *  Created on: Mar 7, 2021
 *      Author: PEPE
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

#include <stdint.h>

void initSPI2(void);
uint16_t ReadTemp(void);

#endif /* INC_MAX6675_H_ */
