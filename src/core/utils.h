#pragma once

#include <string>
#include <vector>

#define FWD(var) std::forward<decltype(var)>(var)

namespace BerylEngine
{
    bool isDebuggerPresent();
    void debugBreak();

    class NonCopyable {
    public:
        constexpr NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;

        NonCopyable(NonCopyable&&) = default;
        NonCopyable& operator=(NonCopyable&&) = default;
    };

    class NonMovable : public NonCopyable {
    public:
        constexpr NonMovable() = default;
        NonMovable(const NonMovable&) = delete;
        NonMovable& operator=(const NonMovable&) = delete;

        NonMovable(NonMovable&&) = delete;
    };

	std::vector<std::string> splitstr(const std::string& str, char delim);
}