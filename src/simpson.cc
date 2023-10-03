#include <iostream>
#include <iomanip>
#include <functional>
#include <chrono>

#include <cinttypes>
#include <cmath>

/* decimal type to use for functions */
#define FT double 

constexpr std::int32_t bench_count = 10000;
constexpr std::int32_t steps = 10000;


std::uint64_t get_current_time() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

FT f(const FT &x) {
    FT t = x;
    return std::sin(t);
}

FT simpson_integration(const FT &a, const FT &b) {
    const FT h = (b - a) / steps;
    FT s = f(a) + f(b);

    for (std::int32_t i = 1; i < steps; i++) {
        s += f(a + h * i) * (1 + (i & 1)) * 2;
    }

    return s * h / 3;
}

[[clang::optnone]] void runner() {
    FT out = 0;
    for (std::int32_t i = 0; i < bench_count; i++) {
        out = static_cast<std::int32_t>(simpson_integration(i, i + 1));
    }
}

int main() {
    std::uint64_t begin_time = get_current_time();
    runner();
    std::uint64_t end_time = get_current_time();

    std::cout << std::setprecision(15) << (end_time - begin_time) / static_cast<FT>(bench_count) << std::endl;

    return 0;
}
