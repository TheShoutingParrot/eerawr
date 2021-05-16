#ifndef _EERAWR_H
#define _EERAWR_H

#include <bcm2835.h>
#include <shiftr.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* EEPROM control pins */

/* EEPROM IO */
#define IO_PIN_0                RPI_V2_GPIO_P1_03
#define IO_PIN_1                RPI_V2_GPIO_P1_05
#define IO_PIN_2                RPI_GPIO_P1_07
#define IO_PIN_3                RPI_GPIO_P1_08
#define IO_PIN_4                RPI_GPIO_P1_10
#define IO_PIN_5                RPI_GPIO_P1_12
#define IO_PIN_6                RPI_GPIO_P1_16
#define IO_PIN_7                RPI_GPIO_P1_22

/* Output enable pin */
#define ROM_OUTPUT_ENABLE       RPI_V2_GPIO_P1_29       
#define ROM_WRITE_ENABLE        RPI_V2_GPIO_P1_31
#define ROM_CHIP_ENABLE         RPI_V2_GPIO_P1_33

/* Shift register control pins */
#define DATA_PIN                RPI_GPIO_P1_11
#define CLOCK_PIN               RPI_GPIO_P1_15
#define LATCH_PIN               RPI_GPIO_P1_23
#define RESET_PIN               RPI_GPIO_P1_21
#define ENABLE_PIN              RPI_GPIO_P1_19

/* Misc */

#define MAX_ADDRESS             32768

enum _Operation {
        NOP, READBYTE, WRITEBYTE, READALL, WRITEFILE,
};

bool inputMode(uint8_t *io, uint8_t enable);
bool outputMode(uint8_t *io, uint8_t *control);
uint8_t readIO(uint8_t *io);
void writeIO(uint8_t *io, uint8_t we, uint8_t ce, uint8_t byte);

void help(void);
void usage(void);
void die(const char *fmt, ...);

#endif /*#ifndef _EERAWR_H*/
