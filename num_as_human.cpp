#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

void convertNumberToWords(const std::string& input, std::vector<std::string>& subs){
    int l = 0;
    for(int sub = input.length() / 3 ; sub > 0 ; sub --){
        subs.push_back(input.substr(l,3));
        l += 3;
    }
}

int main(){

    std::string input;
    std::getline(std::cin, input);
    int i = input.length();

    std::unordered_map<int,std::string> nums_as_str = {
        {0,""},{1,"one"},{2,"two"},{3,"three"},{4,"four"},
        {5,"five"},{6,"six"},{7,"seven"},{8,"eight"},{9,"nine"},
        {10,"ten"},{11,"eleven"},{12,"twelve"},{13,"thirteen"},
        {14,"fourteen"},{15,"fifteen"},{16,"sixteen"},{17,"seventeen"},
        {18,"eighteen"},{19,"nineteen"},{20,"twenty"},{30,"thirty"},{40,"forty"},
        {50,"fifty"},{60,"sixty"},{70,"seventy"},{80,"eighty"},{90,"ninety"}
    };

    std::unordered_map<int,std::string> scales = {
        {2,"thousand"},{3,"million"},{4,"billion"},{5,"trillion"}
    };

    std::vector<std::string> triplets;

    if(i % 3 != 0){
        triplets.push_back(input.substr(0,i % 3));
        convertNumberToWords(input.substr(i % 3, input.length()), triplets);
    }else {
        convertNumberToWords(input,triplets);
    }

    auto parseNum  = [&triplets,&nums_as_str,&scales]() -> std::string{
        std::string output;
        std::string subPart;
        int scaleIndex = triplets.size();
        
        if(std::string first3 = triplets[0]; first3.length() == 3){
            subPart += nums_as_str[first3.at(0) - '0'] + " ";
            subPart += "hundred ";

            if(first3.at(1) != '0'){
                subPart += nums_as_str[(first3.at(1) - '0') * 10] + " ";
            }
            subPart += nums_as_str[first3.at(2) - '0'] + " ";

        }else if(first3.length() == 2){
            subPart += nums_as_str[(first3.at(0) - '0') * 10] + " ";
            subPart += nums_as_str[first3.at(1) - '0'] + " ";
        }else if(first3.length() == 1) {
            subPart += nums_as_str[first3.at(0) - '0'] + " ";
        }

        output += subPart + scales[scaleIndex] + " ";
        triplets.erase(triplets.begin());
        subPart = "";
        scaleIndex --;

        for(auto& subStr : triplets){

            if(subStr.at(0) != '0'){
                subPart += nums_as_str[subStr.at(0) - '0'] + " ";
                subPart += "hundred ";
            }
            if(subStr.at(1) != '0'){
                subPart += nums_as_str[(subStr.at(1) - '0') * 10] + " ";
            }
            subPart += nums_as_str[subStr.at(2) - '0'] + " ";
            
            output += subPart + scales[scaleIndex] + " ";
            subPart = "";
            scaleIndex--;
            
        }

        return output;
    };

    std::cout << parseNum();

}