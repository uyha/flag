# A C++20 library for using bitwise operators on flag enums

This library provides a set of free function templates which perform bitwise operations on scoped enums that satisfy the `Flag` concept. When these function templates are used, instead of return `int` like normal bitwise operators, they return the underlying type of the input enum.

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
  auto file_permission = FilePermission::all_execute | FilePermission::user_execute;

  assert(has<FilePermission::all_execute>(file_permission));
  assert(has<FilePermission::user_execute>(file_permission));

  // Add group_execute to file_permission
  file_permission |= FilePermission::group_execute;
  assert(has<FilePermission::group_execute>(file_permission));

  // Toggle user_execute bit of file_permission
  file_permission ^= FilePermission::user_execute;
  assert(!has<FilePermission::user_execute>(file_permission));
  file_permission ^= FilePermission::user_execute;
  assert(has<FilePermission::user_execute>(file_permission));
}
```

## Usage
This is a header only library, copy the file `flag.hpp` to your source code and start using it.

Users can mark their scoped enums as flag enums by using the macro `IS_FLAG_ENUM` or specialize the variable template `is_flag_enum` to true.
