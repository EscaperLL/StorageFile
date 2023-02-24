//
// Created by pc on 2023/2/21.
//

#ifndef TEST_READBUFFERFROMFILEBASE_H
#define TEST_READBUFFERFROMFILEBASE_H
#include <string>
#include <functional>
#include "BufferWithOwnMemory.h"
#include "SeekableReadBuffer.h"
namespace IO
{
class ReadBufferFromFIleBase :public BufferWithOwnMemory<SeekableReadBuffer>{
public:
    ReadBufferFromFIleBase();
    ReadBufferFromFIleBase(char * existing_memory,size_t buf_size,size_t alignment);
    ReadBufferFromFIleBase(ReadBufferFromFIleBase &&) = default;
    ~ReadBufferFromFIleBase() override;
    virtual std::string getFileName() const  = 0;

    /// It is possible to get information about the time of each reading.
    struct ProfileInfo
    {
        size_t bytes_requested;
        size_t bytes_read;
        size_t nanoseconds;
    };

    using ProfileCallback = std::function<void(ProfileInfo)>;

protected:
    ProfileCallback  m_profile_cb;
};

}
#endif //TEST_READBUFFERFROMFILEBASE_H
