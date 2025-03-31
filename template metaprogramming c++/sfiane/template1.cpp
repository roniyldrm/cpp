#include <type_traits>
#include <cmath>

//basic sfiane without enable_if  

template<typename T, int I> 
bool areEqualImpl(T a, T b, char (*f) [I % 2 == 0] = nullptr) { 
    return a == b; 
} 

template<typename T, int I> 
bool areEqualImpl(T a, T b, char (*f) [I % 2 == 1] = nullptr) { 
    return std::abs(a - b) < 0.1; 
} 
//if I is 1 meaning its a float then results char (*f) [0](c style array with size 0 not allowed) and because of this
//compiler will try to find another impl and not throw an error effectively choosing the right implementation

//we take advantage of compilation error to make compiler choose right function 
template<typename T> 
bool areEqual(T a, T b) { 
    constexpr int isFloating = std::is_floating_point_v<T> ? 1: 0; 
    return areEqualImpl<T, isFloating>(a, b); 
}