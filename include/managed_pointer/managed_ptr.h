#pragma once

#include <memory>

#include "untyped_managed_ptr.h"

namespace ManagedPointer {

    template <typename T>
    class managed_ptr : public untyped_managed_ptr {
        class managed_ptr_deleter {
            bool _deletes_pointer = true;

        public:
            void set_deletes_pointer(bool deletes_pointer = true) {
                _deletes_pointer = deletes_pointer;
            }
            bool deletes_pointer() const { return _deletes_pointer; }

            void operator()(T* ptr) const {
                if (_deletes_pointer) delete ptr;
            }
        };

        std::unique_ptr<T, managed_ptr_deleter> _ptr;

    public:
        managed_ptr() : _ptr(new T()) {}
        managed_ptr(T&& value) : _ptr(new T(std::forward<T>(value))) {}
        managed_ptr(T* ptr, bool deletes_pointer = true) : _ptr(ptr) {
            _ptr.get_deleter().set_deletes_pointer(deletes_pointer);
        }

        ~managed_ptr() = default;

        // Extra lovely functionality for untyped base class with type erasure :)
        void*                void_ptr() const override { return _ptr.get(); }
        untyped_managed_ptr* untyped() const { return this; }

        void disable_delete() { _ptr.get_deleter().set_deletes_pointer(false); }
        void enable_delete() { _ptr.get_deleter().set_deletes_pointer(true); }
        bool deletes_pointer() const { return _ptr.get_deleter().deletes_pointer(); }
        void set_deletes_pointer(bool deletes_pointer = true) {
            _ptr.get_deleter().set_deletes_pointer(deletes_pointer);
        }

        managed_ptr(const managed_ptr&)            = delete;
        managed_ptr& operator=(const managed_ptr&) = delete;

        managed_ptr(managed_ptr&& other) noexcept : _ptr(std::move(other._ptr)) {}
        managed_ptr& operator=(managed_ptr&& other) noexcept {
            if (this != &other) _ptr = std::move(other._ptr);
            return *this;
        }

        T* get() const { return _ptr.get(); }
        T* operator->() const { return _ptr.get(); }
        T& operator*() const { return *_ptr; }

        explicit operator bool() const { return _ptr.get() != nullptr; }

        void reset(T* ptr = nullptr) { _ptr.reset(ptr); }
        void release() { _ptr.release(); }
    };
}
