
#include "selfFIFO.h"

uint8_t BufferIn(uint8_t byte)
{
  uint8_t next = ((buffer.write + 1) & BUFFER_MASK);

  if (buffer.read == next)
    return BUFFER_FAIL; 

  buffer.data[buffer.write] = byte;
  buffer.write = next;

  return BUFFER_SUCCESS;
}


uint8_t BufferOut(uint8_t *pByte)
{
  if (buffer.read == buffer.write)
    return BUFFER_FAIL;

  *pByte = buffer.data[buffer.read];

  buffer.read = (buffer.read+1) & BUFFER_MASK;

  return BUFFER_SUCCESS;
}
