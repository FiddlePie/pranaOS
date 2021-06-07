
#pragma once

#include <AKF/Noncopyable.h>
#include <AKF/NonnullRefPtr.h>
#include <AKF/OSError.h>
#include <AKF/RefCounted.h>
#include <AKF/Result.h>

namespace AKF {

class MappedFile : public RefCounted<MappedFile> {
    AKF_MAKFE_NONCOPYABLE(MappedFile);
    AKF_MAKFE_NONMOVABLE(MappedFile);

public:
    static Result<NonnullRefPtr<MappedFile>, OSError> map(const String& path);
    ~MappedFile();

    void* data() { return m_data; }
    const void* data() const { return m_data; }

    size_t size() const { return m_size; }

    ReadonlyBytes bytes() const { return { m_data, m_size }; }

private:
    explicit MappedFile(void*, size_t);

    void* m_data { nullptr };
    size_t m_size { 0 };
};

}

using AKF::MappedFile;
