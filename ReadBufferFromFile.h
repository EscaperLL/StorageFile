//
// Created by pc on 2023/2/22.
//

#ifndef TEST_READBUFFERFROMFILE_H
#define TEST_READBUFFERFROMFILE_H
#include "ReadBufferFromFIleDescriptor.h"

namespace IO
{
class ReadBufferFromFile : public ReadBufferFromFIleDescriptor
{

protected:
    std::string m_file_name;

public:
    explicit ReadBufferFromFile(const std::string & file_name,size_t buf_size = 1000, int flags = -1,char * existing_memory = nullptr,size_t alignment=0);

    explicit ReadBufferFromFile(int & fd,const std::string& ori_file_name = {},
                                size_t buf_size=1000,
                                char* existing_memory= nullptr,
                                size_t alignment =0);

    ~ReadBufferFromFile() override;

    void close();

    std::string getFileName()const override
    {
        return m_file_name;
    }
};

}
#endif //TEST_READBUFFERFROMFILE_H

