#include <iostream>
#include <optional>
#include <type_traits>
#include <pair>



void func(std::pair<int,char*> myp){

}

int main() {
    int a = 5;
    std::optional<int> o1{a};
    std::optional<int> o2{5};

    auto& r1 = *o1;
    auto& r2 = *o2;

    

    std::cout << std::boolalpha;
    std::cout << std::is_lvalue_reference_v<decltype(*o1)> << "\n";          // true
    std::cout << std::is_lvalue_reference_v<decltype(*o2)> << "\n";          // true

    std::cout << std::is_rvalue_reference_v<decltype(*std::move(o1))> << "\n"; // true
}