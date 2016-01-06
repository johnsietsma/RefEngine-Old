#pragma once

#if defined __APPLE__
namespace std {
template <typename T, typename... Args>
auto make_unique(Args&&... args) -> std::unique_ptr<T>
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#endif

