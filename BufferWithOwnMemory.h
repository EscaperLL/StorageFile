//
// Created by pc on 2023/2/20.
//

#ifndef TEST_BUFFERWITHOWNMEMORY_H
#define TEST_BUFFERWITHOWNMEMORY_H
#include "nonCopyable.h"
#include "Allocator.h"


namespace IO
{
    struct Memory : noncopyable,IO::Allocator
    {
        static constexpr size_t pad_right = 15;
        size_t m_capacity = 0;  /// With padding.
        size_t m_size = 0;
        char * m_data = nullptr;
        size_t m_alignment = 0;

        Memory() {}

        Memory(size_t size,size_t alignment = 0) :m_capacity(size),m_size(size),m_alignment(alignment)
        {
		alloc();
	}

        size_t size() const { return m_size; }
        const char & operator[](size_t i) const { return m_data[i]; }
        char & operator[](size_t i) { return m_data[i]; }
        const char * data() const { return m_data; }
        char * data() { return m_data; }

        void resize(size_t new_size)
        {
            if (0 == m_size)
            {
                m_size = new_size;
                m_capacity = new_size;
                alloc();
            }
            else if (new_size < m_capacity - pad_right)
            {
                m_size = new_size;
            }
            else
            {
                size_t new_cap = align(new_size + pad_right,m_alignment);
                m_data = static_cast<char *> (Allocator::alloc(new_cap,m_alignment));
                m_capacity = new_cap;
                m_size = new_cap - pad_right;
            }
        }

    private:
        static size_t align(const size_t value,const size_t alignment)
        {
            if (!alignment)
                return value;
            return (value + alignment -1) /alignment * alignment;
        }

        void alloc()
        {
            if (nullptr != m_data)
            {
                m_data = nullptr;
                return;
            }
            size_t padded_cap = m_capacity + pad_right;
            size_t new_cap = align(padded_cap,m_alignment);
            m_data = static_cast<char *>(Allocator::alloc(new_cap,m_alignment));
            m_capacity = new_cap;
            m_size = m_capacity - pad_right;
        }

        void dealloc()
        {
            if (!m_data)
                return;
            Allocator::free(m_data,m_capacity);
            m_data = nullptr;
        }
    };

    template<typename base>
    class BufferWithOwnMemory :public base
    {
    protected:
    Memory memory; 

    public:
        BufferWithOwnMemory(size_t size = 10000,char * existing_buff= nullptr,size_t alinment = 0)
        : base(nullptr,0), memory(existing_buff ? 0:size,alinment)
        {
            base::set(existing_buff ? existing_buff:memory.data(),size);
            base::m_padded = !existing_buff;
        }
    };
}
#endif //TEST_BUFFERWITHOWNMEMORY_H
