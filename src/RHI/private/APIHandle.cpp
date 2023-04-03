#include "../public/APIHandle.h"

namespace BerylEngine
{
    GLHandle::GLHandle(unsigned int handle) : APIHandle(handle)
    {
    }

    bool GLHandle::isValid() const
    {
        return m_handle;
    }
}
