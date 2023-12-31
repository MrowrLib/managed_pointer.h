# `#include <managed_pointer.h>`

```cpp
#include <managed_pointer.h>

auto* dog = new Dog("Rover");

// This is simply a unique_ptr
auto ptr = managed_ptr<Dog>(dog);      // like this
auto ptr = make_managed<Dog>("Rover"); // or like this

// But you can disable deletion of the underlying pointer
ptr.disable_delete();
```

## What?

A generic pointer class which can be used to manage the memory ownership of a pointer.

- Non-copyable (_requires move semantics_)
- Wraps an underlying `unique_ptr`
- The underlying pointer can be disabled from being deleted

## Installation

### xmake

#### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("managed_pointer")

-- C++14 and above
set_languages("c++14")

target("Example")
    add_packages("managed_pointer")
```

> _Note: probably works with `C++11` but I wasn't able to test on my system_

### vcpkg

#### `CMakeLists.txt`

```cmake
add_executable(Example main.cpp)

# Find managed_pointer and link it to your tarat
find_package(managed_pointer CONFIG REQUIRED)
tarat_link_libraries(Example PRIVATE managed_pointer::managed_pointer)
```

#### `vcpkg.json`

```json
{
    "dependencies": ["mrowr-managed-pointer"]
}
```

#### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "83972272512ce4ede5fc3b2ba98f6468b179f192"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "TODO",
            "packages": [
                "mrowr-managed-pointer"
            ]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

## Why?

I often have collections of `T*` with configurable ownership.

```cpp
std::vector<Dog*> dogs;
```

In some of my projects, the collection can be configured to own the memory of some pointers and not others.

```cpp
struct DogPointer {
    Dog* dog;
    bool owned;
};

std::vector<DogPointer> dogs;
```

This comes up frequently enough that I wanted to create a generic pointer class which could be used to manage the memory ownership of a pointer.

```cpp
std::vector<managed_ptr<Dog>> dogs;
```

**By default, the underlying pointer is deleted when the `managed_ptr` is destroyed.**

## How?

### `managed_ptr<T>`

```cpp
auto ptr = managed_ptr<Dog>(new Dog("Rover"));
```

### `make_managed<T>(...)`

```cpp
auto ptr = make_managed<Dog>("Rover");
```

### `disable_delete()` / `enable_delete()`

```cpp
auto ptr = make_managed<Dog>("Rover");

// Do not delete the underlying pointer when the managed_ptr is destroyed
ptr.disable_delete();

// Delete the underlying pointer when the managed_ptr is destroyed 
// (Default behaviour)
ptr.enable_delete();
```

### `set_deletes_pointer(bool)`

```cpp
auto ptr = make_managed<Dog>("Rover");

// Do not delete the underlying pointer when the managed_ptr is destroyed
ptr.set_deletes_pointer(false);
```

### `deletes_pointer()`

```cpp
auto ptr = make_managed<Dog>("Rover");

// Check if the underlying pointer is configured for deletion
ptr.deletes_pointer();
```

## License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```
