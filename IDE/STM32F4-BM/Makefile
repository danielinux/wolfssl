## 
## Copyright (C) 2006-2022 wolfSSL Inc.
## 
## This file is part of wolfSSL.
## 
## wolfSSL is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
## 
## wolfSSL is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA


CROSS_COMPILE:=arm-none-eabi-
CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)gcc
WOLFSSL_ROOT:=$(PWD)/../..
WOLFSSL_BUILD:=$(PWD)/build

LSCRIPT:=target.ld


OBJCOPY:=$(CROSS_COMPILE)objcopy
CFLAGS:=-mcpu=cortex-m3 -mthumb -g -ggdb -Wall -Wno-main -Wstack-usage=8192 -ffreestanding -Wno-unused -nostdlib -I.
LDFLAGS:=-T $(LSCRIPT) -Wl,-gc-sections -Wl,-Map=image.map -mcpu=cortex-m3 -mthumb -nostartfiles -lm

CFLAGS+=-DWOLFSSL_USER_SETTINGS
CFLAGS+=-I$(WOLFSSL_ROOT)/wolfssl
CFLAGS+=-I$(WOLFSSL_ROOT)


# Application objects
#

OBJS= main.o startup.o syscalls.o mpu.o


# Wolfcrypt objects
#

WOLFSSL_OBJS += 	\
	$(WOLFSSL_BUILD)/wolfcrypt/aes.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/asn.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/chacha.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/chacha20_poly1305.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/coding.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/curve25519.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/dh.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/dsa.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/error.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/ecc.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/ed25519.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/rsa.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/fe_low_mem.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/fe_operations.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/ge_low_mem.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/ge_operations.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/hash.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/hmac.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/integer.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/logging.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/md5.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/memory.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/poly1305.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/pwdbased.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/random.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/sha.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/sha256.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/sha512.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/wc_encrypt.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/wc_port.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/wolfmath.o \
	$(WOLFSSL_BUILD)/wolfcrypt/tfm.o  \
	$(WOLFSSL_BUILD)/wolfcrypt/test/test.o 
	
OBJS_SPMATH:= $(WOLFSSL_BUILD)/wolfcrypt/sp_c32.o  \
 		 		$(WOLFSSL_BUILD)/wolfcrypt/sp_int.o

OBJS+=$(WOLFSSL_OBJS) $(OBJS_SPMATH)

vpath %.c $(dir $(WOLFSSL_ROOT)/src)
vpath %.c $(dir $(WOLFSSL_ROOT)/wolfcrypt/src)
vpath %.c $(dir $(WOLFSSL_ROOT)/wolfcrypt/test)

all: image.bin

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(WOLFSSL_BUILD)/%.o: $(WOLFSSL_ROOT)/src/%.c
	$(CC) -c -o $(@) $(CFLAGS) $^

$(WOLFSSL_BUILD)/wolfcrypt/%.o: $(WOLFSSL_ROOT)/wolfcrypt/src/%.c
	$(CC) -c -o $(@) $(CFLAGS) $^

$(WOLFSSL_BUILD)/wolfcrypt/test/%.o: $(WOLFSSL_ROOT)/wolfcrypt/test/%.c
	$(CC) -c -o $(@) $(CFLAGS) $^

image.bin: image.elf
	$(OBJCOPY) -O binary $^ $@

$(WOLFSSL_BUILD):
	mkdir -p build/wolfcrypt/test

image.elf: $(WOLFSSL_BUILD) $(OBJS) $(LSCRIPT)
	mkdir -p $(WOLFSSL_BUILD)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
	
clean:
	@rm -f image.bin image.elf *.o
	@rm -f image.map
	@rm -rf build

