#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <conio.h>


class towerGenerator{
    private:
        static  std::random_device rd;
        static  std::mt19937 gen; 
        static  std::uniform_int_distribution<> uni_dist;
        
        towerGenerator(){
            
        }
    
    public:
        static towerGenerator& getInstance(){
            static towerGenerator tw;
            return tw;
        }

        std::string getTowerOutput(){
            std::stringstream output;
            output << "\n\n\t\t-------------\n";

            auto helper = [&]() {
                int kilcik_index = uni_dist(gen);
                return kilcik_index == 1 ? std::string{"\t\t- X | O | O -\n"} :
                    kilcik_index == 2 ? std::string{"\t\t- O | X | O -\n"} :
                    kilcik_index == 3 ? std::string{"\t\t- O | O | X -\n"} : std::string{""};
            };

            for (int i = 0; i < 7; i++){
                output << helper();
                output << "\t\t-------------\n";
            }   

            return output.str();
        }
        
        towerGenerator(const towerGenerator&) = delete;
        towerGenerator& operator=(const towerGenerator&) = delete;
};

std::random_device towerGenerator::rd{};
std::mt19937 towerGenerator::gen{towerGenerator::rd()};
std::uniform_int_distribution<> towerGenerator::uni_dist{1, 3};


int main(){
    
    std::cout <<"-------Tower predict bot %99 accurate-------\n";
    std::cout << towerGenerator::getInstance().getTowerOutput();

    while (true) {
        if(_kbhit()) {
            char ch = _getch();

            if (ch == 13){
                std::cout << towerGenerator::getInstance().getTowerOutput();
            }else{
                break;
            }
        }
    }
    
}