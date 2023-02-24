//
// Created by pc on 2023/2/21.
//

#ifndef TEST_SEEKABLEREADBUFFER_H
#define TEST_SEEKABLEREADBUFFER_H
#include <unistd.h>
#include "ReadBuffer.h"
namespace IO
{
class SeekableReadBuffer : public ReadBuffer
{
public:
    SeekableReadBuffer(Position ptr,size_t n): ReadBuffer(ptr,n){}

    SeekableReadBuffer(Position ptr,size_t offset,size_t n): ReadBuffer(ptr,offset,n){}

    virtual off_t seek(off_t off,int whence) = 0;

    virtual off_t getPosition() = 0;
};
}
#endif //TEST_SEEKABLEREADBUFFER_H
