#pragma once

#include <type_traits>

namespace ManagedPointer {

    struct untyped_managed_ptr_impl {
        virtual ~untyped_managed_ptr_impl()                               = default;
        virtual void*    void_ptr() const                                 = 0;
        virtual void     disable_delete()                                 = 0;
        virtual void     enable_delete()                                  = 0;
        virtual bool     deletes_pointer() const                          = 0;
        virtual void     set_deletes_pointer(bool deletes_pointer = true) = 0;
        virtual void     reset()                                          = 0;
        virtual void     release()                                        = 0;
        virtual explicit operator bool() const                            = 0;

        template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
        T as() const {
            auto* ptr = void_ptr();
            if (!ptr) return nullptr;
            return static_cast<T>(ptr);
        }

        template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
        T as() const {
            auto* ptr = void_ptr();
            if (!ptr) return {};
            return *static_cast<T*>(ptr);
        }
    };
}
