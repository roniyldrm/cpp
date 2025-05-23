#include <type_traits>
#include <iostream>


template<typename T>
auto get_value_impl(T t, std::true_type){
    return t;
}

template<typename T>
auto get_value_impl(T t, std::false_type){
    std::cout << "not arithmetic ";
}

//sfiane alternative tag dispacthing 
template<typename T>
auto get_value(T t) {
    return get_value_impl(t, std::is_arithmetic<T>());
}


auto a = get_value(1);
auto b = get_value(5.5);

int main(){
    get_value("lalala");    
}