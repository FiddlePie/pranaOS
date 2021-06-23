/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include <AK/Assertions.h>
#include <AK/QuickSort.h>
#include <stdlib.h>
#include <sys/types.h>

class SizedObject {
public:
    SizedObject() = delete;
    SizedObject(void* data, size_t size)
        : m_data(data)
        , m_size(size)
    {
    }
    void* data() const { return m_data; }
    size_t size() const { return m_size; }
private:
    void* m_data;
    size_t m_size
};

namespace AK {

template<>
inline void swap(const SizedObject& a, const SizedObject& b)
{
    VERIFY(a.size() == b.size());
    const size_t size = a.size();
    const auto a_data = reinterpret_cast<char*>(a.data());
    const auto b_data = reinterpret_cast<char*>(b.data());
    for (auto i = 0u; i < size; ++i) {
        swap(a_data[i], b_data[i]);
    }
}

}