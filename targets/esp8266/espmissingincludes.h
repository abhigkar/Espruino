/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2015 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * This file is designed to be parsed during the build process
 *
 * Contains ESP8266 board specific functions.
 * ----------------------------------------------------------------------------
 */
#ifndef ESPMISSINGINCLUDES_H
#define ESPMISSINGINCLUDES_H

#include <user_interface.h>
#include <eagle_soc.h>

// The linking is arranged to put all functions into IROM, so we need a special define to put
// a function into IRAM
#define CALLED_FROM_INTERRUPT __attribute__((section(".iram1.text." __FILE__)))

//Missing function prototypes in include folders. Gcc will warn on these if we don't define 'em anywhere.
//MOST OF THESE ARE GUESSED! but they seem to work and shut up the compiler.
typedef struct espconn espconn;

bool wifi_station_set_hostname(char *);
char *wifi_station_get_hostname(void);

int atoi(const char *nptr);

void ets_install_putc1(void *routine); // necessary for #define os_xxx -> ets_xxx
void ets_isr_attach(int intr, void *handler, void *arg);
void ets_isr_mask(unsigned intr);
void ets_isr_unmask(unsigned intr);
void ets_intr_lock(void);
void ets_intr_unlock(void);
void NmiTimSetFunc(void (*func)(void));

int ets_memcmp(const void *s1, const void *s2, size_t n);
void *ets_memcpy(void *dest, const void *src, size_t n);
void *ets_memmove(void *dest, const void *src, size_t n);
void *ets_memset(void *s, int c, size_t n);
int ets_sprintf(char *str, const char *format, ...)  __attribute__ ((format (printf, 2, 3)));
int ets_str2macaddr(void *, void *);
int ets_strcmp(const char *s1, const char *s2);
char *ets_strcpy(char *dest, const char *src);
size_t ets_strlen(const char *s);
int ets_strncmp(const char *s1, const char *s2, int len);
char *ets_strncpy(char *dest, const char *src, size_t n);
char *ets_strstr(const char *haystack, const char *needle);

void ets_timer_arm_new(ETSTimer *a, int b, int c, int isMstimer);
void ets_timer_disarm(ETSTimer *a);
void ets_timer_setfn(ETSTimer *t, ETSTimerFunc *fn, void *parg);

void ets_update_cpu_frequency(int freqmhz);

int os_snprintf(char *str, size_t size, const char *format, ...) __attribute__((format(printf, 3, 4)));
int os_printf_plus(const char *format, ...)  __attribute__((format(printf, 1, 2)));

// memory allocation functions are "different" due to memory debugging functionality
// added in SDK 1.4.0
#ifndef ESPSDK_1_3_0
void  vPortFree(void *ptr, char * file, int line);
void *pvPortMalloc(size_t xWantedSize, char * file, int line);
void *pvPortZalloc(size_t, char * file, int line);
void *vPortMalloc(size_t xWantedSize);
void  pvPortFree(void *ptr);
void *pvPortRealloc(void *pv, size_t size, char * file, int line);
#else
void  vPortFree(void *ptr);
void *pvPortMalloc(size_t xWantedSize);
void *pvPortZalloc(size_t);
void *vPortMalloc(size_t xWantedSize);
void  pvPortFree(void *ptr);
void *pvPortRealloc(void *pv, size_t size);
#define os_realloc pvPortRealloc
void *pvPortRealloc(void* ptr, size_t size);
#endif

void uart_div_modify(int no, unsigned int freq);
uint32 system_get_time();
int rand(void);
void ets_bzero(void *s, size_t n);
void ets_delay_us(int ms);

// disappeared in SDK 1.1.0:
#define os_timer_done ets_timer_done
#define os_timer_handler_isr ets_timer_handler_isr
#define os_timer_init ets_timer_init

// This is not missing in SDK 1.1.0 but causes a parens error
#undef PIN_FUNC_SELECT
#define PIN_FUNC_SELECT(PIN_NAME, FUNC)  do { \
    WRITE_PERI_REG(PIN_NAME,   \
        (READ_PERI_REG(PIN_NAME) & ~(PERIPHS_IO_MUX_FUNC<<PERIPHS_IO_MUX_FUNC_S))  \
            |( (((FUNC&BIT2)<<2)|(FUNC&0x3))<<PERIPHS_IO_MUX_FUNC_S) );  \
    } while (0)


// Shortcuts for memory functions
//#define os_malloc   pvPortMalloc // defined in SDK 1.4.0 onwards
//#define os_free     vPortFree    // defined in SDK 1.4.0 onwards
//#define os_zalloc   pvPortZalloc // defined in SDK 1.4.0 onwards
//uint8 wifi_get_opmode(void); // defined in SDK 1.0.0 onwards
//int os_random();             // defined in SDK 1.1.0 onwards

#endif
