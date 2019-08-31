#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <type_traits>

// ------------------------------------------------------------------
template<typename T>
decltype
(
    std::enable_if_t<std::is_integral<T>::value>(),
    std::string()
)
ip_to_string(const T& addr) {
    constexpr auto sz = sizeof(T);
    const uint8_t* const tokens = reinterpret_cast<const uint8_t*>(&addr);

    std::string result;
    
    for(std::size_t i = sz-1; i != 0; --i) {
        result += std::to_string(*(tokens+i));
        result += '.';
    }
    result += std::to_string(*tokens);
    return result;
}

// ------------------------------------------------------------------
template<typename T>
decltype
( 
    std::enable_if_t<std::is_same<std::string, T>::value>(),
    std::string()
)
ip_to_string(const T& addr) {
    return addr;
}

// ------------------------------------------------------------------
template<class T>
decltype
(
    std::enable_if_t<!std::is_same<std::string, T>::value>(), 
    std::declval<T>().cbegin(), 
    std::declval<T>().cend(), 
    std::string()
)
ip_to_string(const T& addr) {
   
    std::string result;
    for(auto i = addr.cbegin(), end = addr.cend(); i != end; ++i) {
        result += std::to_string(*i);

        if (std::next(i, 1) != end) {
            result += '.';
        }
    }
    return result;
}

// ------------------------------------------------------------------
template<typename... T>
constexpr typename std::enable_if_t<sizeof...(T) < 2, bool>
are_same() {
    return true;
}

// ------------------------------------------------------------------
template<typename A, typename B, typename... T>
constexpr bool
are_same() {
    return std::is_same<A, B>::value && are_same<T...>();
}

// ------------------------------------------------------------------
template<std::size_t I = 0, typename... T>
decltype
(
    std::enable_if_t<are_same<T...>()>(),
    std::enable_if_t<I == sizeof...(T)>(),
    std::string()
)
ip_to_string(const std::tuple<T...>&) {
    return "";
}

// ------------------------------------------------------------------
template<std::size_t I = 0, typename... T>
decltype
(
    std::enable_if_t<are_same<T...>()>(),
    std::enable_if_t<I < sizeof...(T)>(),
    std::string()
)
ip_to_string(const std::tuple<T...>& addr) {
    std::string result;

    result += std::to_string(std::get<I>(addr));

    if (I < sizeof...(T)-1) {
        result += '.';
    }

    result += ip_to_string<I+1, T...>(addr);
    return result;
}
