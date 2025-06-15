#include <chrono>
#include <iostream>

using time_p = std::chrono::time_point<std::chrono::steady_clock>;
using duration = std::chrono::duration<float>;
struct timer{
    time_p t1,t2;
    duration dur;
    
    timer(){
        t1 = std::chrono::high_resolution_clock::now();
    }
    ~timer(){
        t2 = std::chrono::high_resolution_clock::now();
        dur = t1 - t2;
        std::cout << dur.count() << "s ";
    }
};

void func(){
    timer t;
    for(int i = 0; i < 1000000; i++){}
}

int main(){
    func();
}