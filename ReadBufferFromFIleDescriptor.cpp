//
// Created by pc on 2023/2/21.
//

#include <errno.h>
#include <time.h>
#include "ReadBufferFromFIleDescriptor.h"

namespace IO
{
std::string ReadBufferFromFIleDescriptor::getFileName() const
{
    return "(fd = " + std::to_string(m_fd)+")";
}

bool ReadBufferFromFIleDescriptor::nextImpl()
{
    size_t bytes_readed = 0;

    while (!bytes_readed)
    {
        int ret = 0;
        {
            ret = ::read(m_fd,m_internal_buf.begin(),m_internal_buf.size());
            if (!ret)
                break;
            if (-1 == ret && errno != EINTR)
            {
                throw ;
            }

            if (ret)
                bytes_readed += ret;
        }
        m_file_offset_of_buffer_end += bytes_readed;
    }
    if (bytes_readed)
    {
        m_working_buf = m_internal_buf;
        m_working_buf.resize(bytes_readed);
    } else
    {
        return false;
    }
    return true;;
}

off_t ReadBufferFromFIleDescriptor::seek(off_t off, int whence)
{
    size_t new_pos;
    if (whence == SEEK_SET)
    {
        new_pos = off;
    } else if(whence == SEEK_CUR)
    {
        new_pos = m_file_offset_of_buffer_end - (m_working_buf.end() - m_pos) + off;
    } else
    {
        throw ;
    }

    if (new_pos +(m_working_buf.end() - m_pos) == m_file_offset_of_buffer_end)
        return new_pos;

    if (m_file_offset_of_buffer_end - m_working_buf.size() <= static_cast<size_t>(new_pos)
        &&new_pos < m_file_offset_of_buffer_end)
    {
        //position still inside buffer
        m_pos = m_working_buf.end() - m_file_offset_of_buffer_end + new_pos;

        return new_pos;
    } else
    {
        m_pos = m_working_buf.end();
        off_t res = ::lseek(m_fd,new_pos,SEEK_SET);
        if (-1 == res)
            throw ;
        m_file_offset_of_buffer_end = new_pos;
        return res;
    }
}

bool ReadBufferFromFIleDescriptor::pool(size_t timeout) {
return true;
}
}
