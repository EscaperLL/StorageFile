//
// Created by pc on 2023/2/21.
//

#ifndef TEST_READBUFFERFROMFILEDESCRIPTOR_H
#define TEST_READBUFFERFROMFILEDESCRIPTOR_H
#include "ReadBufferFromFIleBase.h"

namespace IO
{
class ReadBufferFromFIleDescriptor :public ReadBufferFromFIleBase{
protected:
    int m_fd;

    off_t m_file_offset_of_buffer_end; /// What offset in file corresponds to working_buffer.end().

    bool nextImpl() override;

    std::string getFileName() const override;
public:

    ReadBufferFromFIleDescriptor(int fd,size_t buf_size=10000,char * exist_memory= nullptr,size_t alignment=0)
        : ReadBufferFromFIleBase(exist_memory,buf_size,alignment),m_fd(fd),m_file_offset_of_buffer_end(0)
    {}

    ReadBufferFromFIleDescriptor(ReadBufferFromFIleDescriptor&&) = default;

    int getFD()const
    {
        return m_fd;
    }

    off_t getPosition() override
    {
        return m_file_offset_of_buffer_end -(m_working_buf.end() - m_pos);
    }

    off_t seek(off_t off,int whence) override;

private:
    bool pool(size_t timeout);
};

}
#endif //TEST_READBUFFERFROMFILEDESCRIPTOR_H
