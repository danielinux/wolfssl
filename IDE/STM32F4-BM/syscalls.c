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


extern unsigned int _start_heap;
#define NULL (((void *)0))

void * _sbrk(unsigned int incr)
{
    static unsigned char *heap = (unsigned char *)&_start_heap;
    void *old_heap = heap;
    if (((incr >> 2) << 2) != incr)
        incr = ((incr >> 2) + 1) << 2;

    if (heap == NULL)
		heap = (unsigned char *)&_start_heap;
	else
        heap += incr;
    return old_heap;
}

void * _sbrk_r(unsigned int incr)
{
    static unsigned char *heap = NULL;
    void *old_heap = heap;
    if (((incr >> 2) << 2) != incr)
        incr = ((incr >> 2) + 1) << 2;

    if (old_heap == NULL)
		old_heap = heap = (unsigned char *)&_start_heap;
    heap += incr;
    return old_heap;
}

int _write(void *r, uint8_t *text, int len)
{
    return -1;
}

int _close(int fd)
{
    return -1;
}

int _fstat(int fd)
{
    return -1;
}

int _lseek(int fd, int whence, int off)
{
    return -1;
}

int _read(uint8_t *buf, int len)
{
    return -1;
}

int _isatty(int fd)
{
    return 1;
}


