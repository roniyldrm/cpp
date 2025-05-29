#include "./headers/my_std_array.hpp"
#include <iostream>

int main(){

    my_array<int,10> arr{{1,2,3,4,5}};

    for (auto& i : arr){
        std::cout<<i;
    }

    auto it = arr.begin();

    std::cout<<*it;
}