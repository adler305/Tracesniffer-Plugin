#include "stdint.h"

#ifndef SELFFIFO_H_
#define SELFFIFO_H_

#define BUFFER_FAIL     0
#define BUFFER_SUCCESS  1

#define BUFFER_SIZE 4096 // has to be 2^n (8, 16, 32, 64 ...)
#define BUFFER_MASK (BUFFER_SIZE-1)

struct Buffer {
  uint8_t data[BUFFER_SIZE];
  uint8_t read;
  uint8_t write;
} buffer;

uint8_t BufferIn(uint8_t byte);
uint8_t BufferOut(uint8_t *pByte);
#endif
