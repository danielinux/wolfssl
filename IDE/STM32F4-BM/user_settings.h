/* 
 * Copyright (C) 2006-2021 wolfSSL Inc.
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



#define NO_64BIT
#define WOLFSSL_GENERAL_ALIGNMENT 4
//#define DEBUG_WOLFSSL
//#define WOLFSSL_LOG_PRINTF
#define SINGLE_THREADED
#define WOLFSSL_USER_IO
#define NO_ASN_TIME
#define WOLFSSL_USER_CURRTIME
#define NO_OLD_RNGNAME
#define SMALL_SESSION_CACHE
#define WOLFSSL_SMALL_STACK
#define TFM_ARM
#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define NO_SIG_WRAPPER
#define WOLFCRYPT_ONLY

/* ECC definitions */
#   define HAVE_ECC
#   define FP_ECC
#   define ECC_ALT_SIZE
#   define USE_FAST_MATH
#   undef FP_LUT
#   define FP_LUT 4
#   define WOLFSSL_HAVE_SP_ECC

/* SP math */
#define WOLFSSL_SP_MATH
#define WOLFSSL_SP_SMALL
#define SP_WORD_SIZE 32
#define WOLFSSL_HAVE_SP_RSA

/* Edwards */
#if 0
#   define HAVE_ED25519
#   define ED25519_SMALL
#   define USE_FAST_MATH
#   define WOLFSSL_SHA512
#   define HAVE_CURVE25519
#   define WOLFSSL_SHA512

/* Chacha20-poly1305 */
#   define HAVE_CHACHA
#   define HAVE_POLY1305
#endif

/* RSA */
#define RSA_LOW_MEM
#define WC_RSA_BLINDING

/* SHA */
#define USE_SLOW_SHA
#define USE_SLOW_SHA2
//#define USE_SLOW_SHA512

/* Disabled ciphers */
#define NO_DES3
#define NO_MD4
#define NO_RABBIT
#define NO_RC4
#define NO_HC128
#define NO_HASH_DBRG


#define NO_WRITEV
#define NO_DEV_RANDOM
#define NO_FILESYSTEM
#define NO_MAIN_DRIVER
#define NO_DSA
#define NO_DH

#define WOLFSSL_GENSEED_FORTEST


#include <stdlib.h>
