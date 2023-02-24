//
// Created by pc on 2023/2/22.
//
#include <fcntl.h>
#include <errno.h>
#include "ReadBufferFromFile.h"

namespace IO
{
ReadBufferFromFile::ReadBufferFromFile(const std::string &file_name, size_t buf_size, int flags, char *existing_memory,
                                       size_t alignment):ReadBufferFromFIleDescriptor(-1,buf_size,existing_memory,alignment), m_file_name(file_name)
{
    m_fd = ::open(file_name.c_str(),flags == -1? O_RDONLY | O_CLOEXEC : flags | O_CLOEXEC);

    if (-1 == m_fd)
    {
        throw ;
    }

}

ReadBufferFromFile::ReadBufferFromFile(int &fd, const std::string & original_file_name, size_t buf_size,
                                       char *existing_memory, size_t alignment)
                                       :ReadBufferFromFIleDescriptor(fd,buf_size,existing_memory,alignment),
                                        m_file_name(original_file_name.empty() ? "(fd = " + std::to_string(fd) + ")" : original_file_name)
{
    fd = -1;
}

void ReadBufferFromFile::close()
{
    if(m_fd < 0)
        return;
    if (0 != ::close(m_fd))
        throw ;

    m_fd = -1;
}

ReadBufferFromFile::~ReadBufferFromFile()
{
    if (m_fd < 0)
        return;
    close();

}
}
