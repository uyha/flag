# A C++20 library for using bitwise operators on flag enums

This library provides a set of free function templates which perform bitwise opertions on scoped enums that satisfy the `Flag` concept. When these function templates are used, instead of return `int` like normal bitwise operators, they return the underlying type of the input enum.

## Examples

```cpp
#include <cassert>
#include <cstdint>
#include <river/flag.hpp>

enum class FilePermission : std::uint16_t {
  all_execute = 0b0'000'000'001,
  all_write   = 0b0'000'000'010,
  all_read    = 0b0'000'000'100,

  group_execute = 0b0'000'001'000,
  group_write   = 0b0'000'010'000,
  group_read    = 0b0'000'100'000,

  user_execute = 0b0'001'000'000,
  user_write   = 0b0'010'000'000,
  user_read    = 0b0'100'000'000,

  directory = 0b1'000'000'000
};
IS_FLAG_ENUM(FilePermission); // Opting in making FilePermission enum as a flag enum

int main() {
  using namespace river::flags; // All operators are define in the river namespace

  // type of file_permission is std::uint16_t
  auto const file_permission = FilePermission::all_execute | FilePermission::all_write |
                               FilePermission::all_read | FilePermission::group_execute |
                               FilePermission::group_write | FilePermission::group_read |
                               FilePermission::user_execute | FilePermission::user_write |
                               FilePermission::user_read | FilePermission::directory;

  auto const all_execute = has<FilePermission::all_execute>(file_permission);
  auto const user_write  = has<FilePermission::user_write>(file_permission);

  assert(all_execute);
  assert(user_write);
}
```

## Usage
This is a header only library, copy the file `flag.hpp` to your source code and start using it.

Users can mark their scoped enums as flag enums by using the macro `IS_FLAG_ENUM` or specialize the variable template `is_flag_enum` to true.
