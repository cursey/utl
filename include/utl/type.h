#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "utl/whoami.h"

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

#if ARCH_X86_64 || ARCH_ARM64
typedef i64 isize;
typedef u64 usize;
#endif

#define MAX_U64 0xffffffffffffffffull
#define MAX_U32 0xffffffffu
#define MAX_U16 0xffffu
#define MAX_U8 0xffu

#if ARCH_X86_64
#define MAX_USIZE 0xffffffffffffffffull
#endif

#define MAX_I64 0x7fffffffffffffffull
#define MAX_I32 0x7fffffffu
#define MAX_I16 0x7fffu
#define MAX_I8 0x7fu

#if ARCH_X86_64
#define MAX_ISIZE 0x7fffffffffffffffull
#endif

#define MIN_I64 0xffffffffffffffffull
#define MIN_I32 0xffffffffu
#define MIN_I16 0xffffu
#define MIN_I8 0xffu

#if ARCH_X86_64
#define MIN_ISIZE 0xffffffffffffffffull
#endif