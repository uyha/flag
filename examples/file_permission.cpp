#include <cassert>
#include <cstdint>
#include <river/flag.hpp>

namespace filesystem {
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
} // namespace filesystem

int main() {
  using namespace river::flags; // All operators are define in the river namespace
  using filesystem::FilePermission;

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