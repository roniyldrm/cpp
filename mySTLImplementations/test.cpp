#include "./headers/my_std_array.hpp"
#include "./headers/my_std_optional.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
int main(){

    my_array<int,10> arr{{1,2,3,4,5}};

    for (auto& i : arr){
        std::cout<<i;
    }

    auto it = arr.begin();

    std::cout<<*it;

    my_optional<std::pair<int,std::string>> opt;
    
    my_optional<std::pair<int,std::string>> opt2 = {1990,"feyyaz yigit"};

    std::cout << opt.value().first;
    std::cout << opt.value().second;

    opt = {1000,"abcde"};

    opt2.emplace(opt);
    
    std::cout << opt2.value().first;
    std::cout << opt2.value().second;
}