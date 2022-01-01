#include <iostream>
#include <string>

int main();
bool get_trans_type(std::string t);

int main(){
    std::string trans_type = "Sell";
    if(get_trans_type(trans_type)){
        std::cout << "true";
    } else {
                std::cout << "false";
    }
}

bool get_trans_type(std::string t)  { return (t == "Buy") ? true: false ; }