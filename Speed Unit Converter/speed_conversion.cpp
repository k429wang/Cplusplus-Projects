#include <iostream>

int main();

int main(){
    double miles = 120;
    double feet{};
    double meters{};
    double km{};
    double furlongs{};

    feet = (miles*5280)/3600;
    meters = (feet/3.28084);
    km = (meters/1000)*3600;
    furlongs = ((meters/201.168)*(60*60*24*14));

    std::cout << "The speed is " << miles << " miles per hour" << std::endl;
    std::cout << "The speed is " << feet << " feet per second" << std::endl;
    std::cout << "The speed is " << meters << " meters per second" << std::endl;
    std::cout << "The speed is " << km << " kilometers per hour" << std::endl;
    std::cout << "The speed is " << furlongs << " furlongs per fortnight" << std::endl;

}