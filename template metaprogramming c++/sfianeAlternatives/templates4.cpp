#include <string>
#include <type_traits>
#include <iostream>


template<typename T, int S>
struct ToStringImpl{
    static std::string toString(const T& x){
        return std::to_string{x};
    }
};
//partially specialized struct
//why not just use functions ? because functions cannot  be partially specialized

template<typename T>
struct ToStringImpl<T, 0>{
    static std::string toString(const T& x){
        return std::string{x};
    }
};

template<typename T>
auto toString(T x){
    constexpr int hasStdToString = std::is_arithmetic_v<T> ? 1 : 0;
    //must be constexpr bcz it will be used compile time replacement for int s 
    return ToStringImpl<T , hasStdToString>::toString(x);
    //if hasStdToString is 0 2. struct will be used because its is the most specialized one
    //if hasStdToString is other than 0  1.struct will be used
}