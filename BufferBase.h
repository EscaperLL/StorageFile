//
// Created by pc on 2023/2/7.
//

#ifndef TEST_BUFFERBASE_H
#define TEST_BUFFERBASE_H
#include <algorithm>

namespace IO
{
class BufferBase
{
public:
    /** Cursor in the buffer. The position of write or read. */
    using Position = char *;
/*
    struct Buffer
    {
        Buffer(Position begin_pos_, Position end_pos_) : begin_pos(begin_pos_), end_pos(end_pos_) {}

        inline Position begin() const { return begin_pos; }
        inline Position end() const { return end_pos; }
        inline size_t size() const { return size_t(end_pos - begin_pos); }
        inline void resize(size_t size) { end_pos = begin_pos + size; }
        inline bool empty() const { return size() == 0; }

        inline void swap(Buffer & other)
        {
            std::swap(begin_pos, other.begin_pos);
            std::swap(end_pos, other.end_pos);
        }

    private:
        Position begin_pos;
        Position end_pos;        /// 1 byte after the end of the buffer
    };
*/
    struct Buffer{
        Buffer(Position begin_,Position end_) : m_begin(begin_), m_end(end_) {}

        inline Position begin() const { return m_begin;}
        inline Position end() const { return m_end;}
        inline size_t size() const { return size_t(m_end - m_begin); }
        inline void resize(size_t size) { m_end = m_begin + size; }
        inline bool empty() const { return size() == 0; }

        inline void swap(Buffer & other)
        {
            std::swap(m_begin, other.m_begin);
            std::swap(m_end, other.m_end);
        }
    private:
        Position m_begin;
        Position m_end;
    };

    BufferBase(Position pos,size_t offset,size_t size):m_pos(pos+offset),m_bytes(size),m_working_buf(pos,pos+offset),m_internal_buf(pos,pos+offset){}

    void set(Position pos,size_t offset ,size_t size)
    {
        m_working_buf = Buffer(pos,pos+size);
        m_internal_buf = Buffer(pos,pos+size);
        m_pos = pos + offset;
        m_bytes = size;
    }
    //get the buffer
    inline Buffer& internalBuffer(){return m_internal_buf;}
    //get the part of buffer that you can read/write
    inline Buffer& buffer(){return  m_working_buf;}
    //
    inline Position position(){return m_pos;}
    //get the bytes of cursor from beginning of buffer
    inline size_t offset() const {return size_t(m_pos - m_working_buf.begin());}
    //
    inline size_t available() const {return size_t(m_working_buf.end() - m_pos);}
    //
    inline void swap(BufferBase & oth)
    {
        std::swap(m_pos,oth.m_pos);
        m_working_buf.swap(oth.m_working_buf);
        m_internal_buf.swap(oth.m_internal_buf);
    }
    size_t count() const{return m_bytes + offset();}

    inline bool hasPendingData(){return available()>0;}

    bool isPadded() const{return m_padded;}
protected:
    void resetWorkingBuffer()
    {
        /// Move position to the end of buffer to trigger call of 'next' on next reading.
        /// Discard all data in current working buffer to prevent wrong assumptions on content
        /// of buffer, e.g. for optimizations of seeks in seekable buffers.
        m_working_buf.resize(0);
        m_pos = m_working_buf.end();
    }
    Buffer m_working_buf;
    Buffer m_internal_buf;

    Position m_pos;

    size_t m_bytes=0;

    bool m_padded{false};
};
}
#endif //TEST_BUFFERBASE_H
