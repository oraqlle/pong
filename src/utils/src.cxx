#include <utils/src.hxx>

#include <iostream>

namespace pong::utils {

namespace fs = std::filesystem;

[[nodiscard]] auto src_absolute_path(const std::source_location src_loc) noexcept
    -> fs::path
{
    return fs::weakly_canonical(fs::path { src_loc.file_name() });
}

} // namespace pong::utils
