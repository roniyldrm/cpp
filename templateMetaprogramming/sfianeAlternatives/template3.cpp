#include<cmath>
#include <type_traits>
#include <iostream>

struct intTag{};
struct floatTag{};


template<typename T>
T square_impl(T value,intTag ){
    return value * value;
}

template<typename T>
T square_impl(T value,floatTag ){
    return sqrtf(value);
}

template<typename T>
T square(T value){

    if (std::is_integral<T>::value){
        return square_impl(value,intTag{});
    }
    //using the function with type but no variable name just to make compiler choose right function for us

    if (std::is_integral<T>::value){
        return square_impl(value,floatTag{});
    }
    
    return T{};
}

