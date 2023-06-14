#ifndef PONG_UTILS_MATCH
#define PONG_UTILS_MATCH

namespace pong::utils {

template <typename... Ts>
struct match : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
match(Ts...) -> match<Ts...>;

} // namespace pong::utils

#endif // PONG_UTILS_MATCH
