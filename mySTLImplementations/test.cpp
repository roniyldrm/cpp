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
    //////////////////////////
    my_optional<std::pair<int,std::string>> opt;
    my_optional<std::pair<int,std::string>> opt2 = {1990,"feyyaz yigit"};

    std::cout << opt.value().first;
    std::cout << opt.value().second;

    opt = std::pair<int,std::string>{1000,"abcde"};
    opt = {2000,"aaa"};

    opt2.emplace(1500,"asdasda");
    
    std::cout << opt2.value().first;
    std::cout << opt2.value().second;

    opt2.swap(opt);

    std::cout << opt2.value().first;
    std::cout << opt2.value().second;

    auto fun = [](bool e) -> my_optional<std::string> {
        if(e){
            return my_optional<std::string>{"str"};
        }
        return my_nullopt;
    };

    std::string str = *fun(false);
    std::string str2 = *fun(true);
    
    std::cout << str << str2;
}