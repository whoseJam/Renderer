#pragma once

#include <type_traits>

namespace Type {
    template<typename T>
    auto getEnumBase(T value) {
        auto ret = static_cast<std::underlying_type<T>::type>(value);
        return ret;
    }
}