#ifndef PONG_UTILS_SRC
#define PONG_UTILS_SRC

#include <filesystem>
#include <source_location>

namespace pong::utils {

namespace fs = std::filesystem;

[[nodiscard]] auto src_absolute_path(const std::source_location src_loc = std::source_location::current()) noexcept
    -> fs::path;

} // namespace pong::utils

#endif // PONG_UTILS_SRC
