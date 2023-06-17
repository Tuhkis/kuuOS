#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long int i64;

#define NULL 0

void* memset(void* b, i32 val, u16 count);

#endif
