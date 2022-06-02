/* 
 * Copyright (C) 2006-2022 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

extern unsigned int _stored_data;
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_bss;
extern unsigned int _end_bss;
extern unsigned int _end_stack;
extern unsigned int _start_heap;

#define STACK_PAINTING

static volatile unsigned int avail_mem = 0;
static unsigned int sp;

extern void main(void);
void isr_reset(void) {
    register unsigned int *src, *dst;
    src = (unsigned int *) &_stored_data;
    dst = (unsigned int *) &_start_data;
    /* Copy the .data section from flash to RAM. */
    while (dst < (unsigned int *)&_end_data) {
        *dst = *src;
        dst++;
        src++;
    }

    /* Initialize the BSS section to 0 */
    dst = &_start_bss;
    while (dst < (unsigned int *)&_end_bss) {
        *dst = 0U;
        dst++;
    }

    /* Paint the stack. */
    avail_mem = &_end_stack - &_start_heap;
    {
        asm volatile("mrs %0, msp" : "=r"(sp));
        dst = ((unsigned int *)(&_end_stack)) - (8192 / sizeof(unsigned int)); ;
        while ((unsigned int)dst < sp) {
            *dst = 0xDEADC0DE;
            dst++;
        }
    }
    /* Run the program! */
    main();
}

void isr_fault(void)
{
    /* Panic. */
    while(1) ;;
}


void isr_memfault(void)
{
    /* Panic. */
    while(1) ;;
}

void isr_busfault(void)
{
    /* Panic. */
    while(1) ;;
}

void isr_usagefault(void)
{
    /* Panic. */
    while(1) ;;
}
        

void isr_empty(void)
{
    /* Ignore the event and continue */
}



__attribute__ ((section(".isr_vector")))
void (* const IV[])(void) =
{
	(void (*)(void))(&_end_stack),
	isr_reset,                   // Reset
	isr_fault,                   // NMI
	isr_fault,                   // HardFault
	isr_memfault,                // MemFault
	isr_busfault,                // BusFault
	isr_usagefault,              // UsageFault
	0, 0, 0, 0,                  // 4x reserved
	isr_empty,                   // SVC
	isr_empty,                   // DebugMonitor
	0,                           // reserved
	isr_empty,                   // PendSV
	isr_empty,                   // SysTick

    isr_empty,                     // GPIO Port A
    isr_empty,                     // GPIO Port B
    isr_empty,                     // GPIO Port C
    isr_empty,                     // GPIO Port D
    isr_empty,                     // GPIO Port E
    isr_empty,                     // UART0 Rx and Tx
    isr_empty,                     // UART1 Rx and Tx
    isr_empty,                     // SSI0 Rx and Tx
    isr_empty,                     // I2C0 Master and Slave
    isr_empty,                     // PWM Fault
    isr_empty,                     // PWM Generator 0
    isr_empty,                     // PWM Generator 1
    isr_empty,                     // PWM Generator 2
    isr_empty,                     // Quadrature Encoder 0
    isr_empty,                     // ADC Sequence 0
    isr_empty,                     // ADC Sequence 1
    isr_empty,                     // ADC Sequence 2
    isr_empty,                     // ADC Sequence 3
    isr_empty,                     // Watchdog timer
    isr_empty,                     // Timer 0 subtimer A
    isr_empty,                     // Timer 0 subtimer B
    isr_empty,                     // Timer 1 subtimer A
    isr_empty,                     // Timer 1 subtimer B
    isr_empty,                     // Timer 2 subtimer A
    isr_empty,                     // Timer 3 subtimer B
    isr_empty,                     // Analog Comparator 0
    isr_empty,                     // Analog Comparator 1
    isr_empty,                     // Analog Comparator 2
    isr_empty,                     // System Control (PLL, OSC, BO)
    isr_empty,                     // FLASH Control
    isr_empty,                     // GPIO Port F
    isr_empty,                     // GPIO Port G
    isr_empty,                     // GPIO Port H
    isr_empty,                     // UART2 Rx and Tx
    isr_empty,                     // SSI1 Rx and Tx
    isr_empty,                     // Timer 3 subtimer A
    isr_empty,                     // Timer 3 subtimer B
    isr_empty,                     // I2C1 Master and Slave
    isr_empty,                     // Quadrature Encoder 1
    isr_empty,                     // CAN0
    isr_empty,                     // CAN1
    isr_empty,                     // CAN2
    isr_empty,                     // Ethernet
    isr_empty,                     // Hibernate


};
