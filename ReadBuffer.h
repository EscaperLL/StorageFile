//
// Created by pc on 2023/2/9.
//

#ifndef TEST_READBUFFER_H
#define TEST_READBUFFER_H
#include "BufferBase.h"
#include <string.h>

namespace IO
{
class ReadBuffer : public BufferBase
{
public:
    ReadBuffer(Position ptr,size_t size): BufferBase(ptr,0,size){}

    ReadBuffer(Position ptr ,size_t offset,size_t size): BufferBase(ptr,offset,size){}

    //sometime can hold lot of memory ,so disable copy constructor
    ReadBuffer(const ReadBuffer &) = delete;
    //set m_working_buf end ptr
    void set(Position ptr,size_t size) {BufferBase::set(ptr,0,size); m_working_buf.resize(0);}

    void setWithBytesToIgnore(Position ptr,size_t size,size_t bytes_to_ignore)
    {
        m_internal_buf=Buffer(ptr,ptr+size);
        m_working_buf = Buffer(ptr+bytes_to_ignore,ptr+size);
        m_pos = ptr + bytes_to_ignore;
    }

    bool  next()
    {
        m_bytes += offset();
        bool res = nextImpl();
        if (!res)
            m_working_buf.resize(0);
        m_pos = m_working_buf.begin() +m_working_buffer_offset;
        m_working_buffer_offset = 0;
        return res;
    }

    inline void nextIfAtEnd()
    {
        if (!hasPendingData())
            next();
    }

    virtual ~ReadBuffer(){
    }

    inline bool eof()
    {
        return !hasPendingData() && !next();
    }

    void ignore()
    {
        if (!eof())
            ++m_pos;
        else
            throwReadAfterEof();
    }

    void  ignore(size_t n)
    {
        while (0 != n && !eof())
        {
            size_t bytes_to_ignore = std::min(static_cast<unsigned long>(n),static_cast<unsigned long>(m_working_buf.end()-m_pos));
            m_pos += bytes_to_ignore;
            n -=bytes_to_ignore;
        }
        if (n)
            throwReadAfterEof();
    }

    size_t tryIgnore(size_t n)
    {
        size_t bytes_to_ignored = 0;
        while (0 != n && !eof())
        {
            size_t bytes_to_ignore = std::min(static_cast<unsigned long>(n),static_cast<unsigned long>(m_working_buf.end()-m_pos));
            m_pos += bytes_to_ignore;
            bytes_to_ignored +=bytes_to_ignore;
        }
        return bytes_to_ignored;
    }

    inline bool read(char & c)
    {
        if(eof())
           return false;
        c = *m_pos++;
        return true;
    }

    inline void readStrict(char & c)
    {
        if(read(c))
            return ;
        throw ;
    }

    size_t read(char * to,size_t n)
    {
        size_t byte_readed = 0;
        while (0 == n && !eof())
        {
            size_t bytes_to_read = std::min(static_cast<unsigned long>(n),static_cast<unsigned long>(m_working_buf.end()-m_pos));
            ::memcpy(m_pos,to,bytes_to_read);
            n -=bytes_to_read;
            m_pos += bytes_to_read;
        }
        return byte_readed;
    }

    void readStrict(char * to,size_t n)
    {
        size_t bytes_to_readed = read(to,n);
        if (bytes_to_readed != n)
            throw ;
    }

    /** A method that can be more efficiently implemented in derived classes, in the case of reading large enough blocks.
  * The implementation can read data directly into `to`, without superfluous copying, if in `to` there is enough space for work.
  * For example, a CompressedReadBuffer can decompress the data directly into `to`, if the entire decompressed block fits there.
  * By default - the same as read.
  * Don't use for small reads.
  */
    virtual size_t readBig(char * to, size_t n)
    {
        return read(to, n);
    }


protected:
    size_t m_working_buffer_offset = 0;

private:
    virtual bool nextImpl(){return false;}

    void throwReadAfterEof()
    {
        throw ;
    }

};
}
#endif //TEST_READBUFFER_H
