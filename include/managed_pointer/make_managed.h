#pragma once

#include "managed_ptr.h"

namespace ManagedPointer {

    template <typename T, typename... Args>
    inline managed_ptr<T> make_managed(Args&&... args) {
        return managed_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    inline managed_ptr<T> make_managed(T* ptr, bool deletes_pointer = true) {
        return managed_ptr<T>(ptr, deletes_pointer);
    }
}
