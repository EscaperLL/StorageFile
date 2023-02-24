//
// Created by pc on 2023/2/21.
//

#include "ReadBufferFromFIleBase.h"
namespace IO
{
ReadBufferFromFIleBase::ReadBufferFromFIleBase():BufferWithOwnMemory<SeekableReadBuffer>(0){}

ReadBufferFromFIleBase::ReadBufferFromFIleBase(char *existing_memory, size_t buf_size, size_t alignment)
    :BufferWithOwnMemory<SeekableReadBuffer>(buf_size,existing_memory,alignment)
{}

ReadBufferFromFIleBase::~ReadBufferFromFIleBase() =default;
}
