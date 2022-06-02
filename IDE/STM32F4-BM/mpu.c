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

#include <stdint.h>

#define MPU_BASE (0xE000ED90)
extern uint32_t _end_stack;

/* FAULT enable register SHCSR */
#define SHCSR (*(volatile uint32_t *)(0xE000ED24))

/* Bit to enable memory fault handler */
#define MEMFAULT_ENABLE (1 << 16)

/* MPU Registers */
#define MPU_TYPE (*(volatile uint32_t *)(MPU_BASE + 0x00))
#define MPU_CTRL (*(volatile uint32_t *)(MPU_BASE + 0x04))
#define MPU_RNR  (*(volatile uint32_t *)(MPU_BASE + 0x08))
#define MPU_RBAR (*(volatile uint32_t *)(MPU_BASE + 0x0c))
#define MPU_RASR (*(volatile uint32_t *)(MPU_BASE + 0x10))

/* Some use-case specific values for RASR */
#define RASR_ENABLED  (1)
#define RASR_RW       (1 << 24)
#define RASR_RDONLY   (5 << 24)
#define RASR_NOACCESS (0 << 24)
#define RASR_SCB      (7 << 16)
#define RASR_SB       (5 << 16)
#define RASR_NOEXEC   (1 << 28)


/* Size */
#define MPUSIZE_1K      (0x09 << 1)
#define MPUSIZE_2K      (0x0a << 1)
#define MPUSIZE_4K      (0x0b << 1)
#define MPUSIZE_8K      (0x0c << 1)
#define MPUSIZE_16K     (0x0d << 1)
#define MPUSIZE_32K     (0x0e << 1)
#define MPUSIZE_64K     (0x0f << 1)
#define MPUSIZE_128K    (0x10 << 1)
#define MPUSIZE_256K    (0x11 << 1)
#define MPUSIZE_512K    (0x12 << 1)
#define MPUSIZE_1M      (0x13 << 1)
#define MPUSIZE_2M      (0x14 << 1)
#define MPUSIZE_4M      (0x15 << 1)
#define MPUSIZE_8M      (0x16 << 1)
#define MPUSIZE_16M     (0x17 << 1)
#define MPUSIZE_32M     (0x18 << 1)
#define MPUSIZE_64M     (0x19 << 1)
#define MPUSIZE_128M    (0x1a << 1)
#define MPUSIZE_256M    (0x1b << 1)
#define MPUSIZE_512M    (0x1c << 1)
#define MPUSIZE_1G      (0x1d << 1)
#define MPUSIZE_2G      (0x1e << 1)
#define MPUSIZE_4G      (0x1f << 1)


#define STACK_SIZE (4 * 1024)

static void mpu_set_region(int region, uint32_t start, uint32_t attr)
{
    MPU_RNR = region;
    MPU_RBAR = start;
    MPU_RNR = region;
    MPU_RASR = attr;
}


int mpu_enable(void)
{
    volatile uint32_t type;
    volatile uint32_t start;
    volatile uint32_t attr;

    type = MPU_TYPE;
    if (type == 0) {
        /* MPU not present! */
        return -1;
    }


    /* Disable MPU to reconfigure regions */
    MPU_CTRL = 0;

    /* Set flash area as read-only, executable */
    start = 0;
    attr = RASR_ENABLED | MPUSIZE_256K | RASR_SCB | RASR_RDONLY;
    mpu_set_region(0, start, attr);

    /* Set RAM as read-write, not executable */
    start = 0x20000000;
    attr = RASR_ENABLED | MPUSIZE_64K | RASR_SCB | RASR_RW | RASR_NOEXEC;
    mpu_set_region(1, start, attr);

    /* Set 1KB guard area below the allowed stack region */
    start = (uint32_t)(&_end_stack) - (STACK_SIZE + 1024);
    attr = RASR_ENABLED | MPUSIZE_1K | RASR_SCB | RASR_NOACCESS | RASR_NOEXEC;
    mpu_set_region(2, start, attr);

    /* Set System register area */
    start = 0xE0000000;
    attr = RASR_ENABLED | MPUSIZE_256M | RASR_SB | RASR_RW | RASR_NOEXEC;
    mpu_set_region(3, start, attr);
    
    /* Enable MEMFAULT */
    SHCSR |= MEMFAULT_ENABLE;

    /* Enable the MPU, no background region */
    MPU_CTRL = 1;
    return 0;

}
