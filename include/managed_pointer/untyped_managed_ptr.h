#pragma once

namespace ManagedPointer {

    struct untyped_managed_ptr {
        virtual ~untyped_managed_ptr() = default;
        virtual void* void_ptr() const = 0;
    };
}
