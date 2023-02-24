//
// Created by pc on 2023/2/7.
//

#ifndef TEST_ALLOCATOR_H
#define TEST_ALLOCATOR_H
#include <unistd.h>
#include <cstdlib>
#if !defined(__APPLE__) && !defined(__FreeBSD__)
#include <malloc.h>
#endif
#include <algorithm>
namespace IO
{

static constexpr size_t MALLOC_MIN_ALIGNMENT = 8;
namespace IO
{
    class Allocator
    {
    public:
        void * alloc(size_t size,size_t alignment = 0)
        {
            return allocNoTrack(size,alignment);
        }

        void free(void *buf,size_t size)
        {
            try {
                freeNoTrack(buf,size);
            }
            catch(...)
            {
                throw;
            }
        }
    private:
        void* allocNoTrack(size_t size,size_t alignment)
        {
            void* buffer;
            size_t mmap_min_alignment = 8;
            //this is no mmap
            {
                if(alignment < MALLOC_MIN_ALIGNMENT)
                {
                    buffer = ::malloc(size);
                    if(nullptr == buffer)
                        throw ; //TO DO exception
                }
                else
                {
                    buffer = nullptr;
                    int res = posix_memalign(&buffer, alignment, size);
                    if (0 != res)
                        throw ;
                }
            }
            return buffer;
        }

        void freeNoTrack(void *buf,size_t size)
        {
            ::free(buf);
        }

    };
}
}
#endif //TEST_ALLOCATOR_H
