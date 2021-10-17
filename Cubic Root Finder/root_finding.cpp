#include <iostream>

int main();

double find_root(double a,double b,double c,double d,double low,double up);

double find_root(double a,double b,double c,double d,double low,double up){
    double ans{};
    for(double i{low};i<up;i+=0.0000001){
        double temp{(a*i*i*i)+(b*i*i)+(c*i)+d};
        if (temp<0.0000001){
            if (temp>(-0.0000001)){
                ans=i;
            }
        }
    }
    return ans;
}

char terminate();

char terminate(){
    char ans;
    std::cout << "Do you wish to find another root (Y/N)?";
    std::cin >> ans;
    return ans;
}

int main(){
    char s{'Y'};
    while (s=='Y'){
        double a{}, b{}, c{}, d{}, low{}, up{}, x{};

        std::cout << "Enter coefficients (A, B, C, and D): " << std::endl;
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        std::cin >> d;

        std::cout << "Enter the lower and upper bound of the search interval: " << std::endl;
        std::cin >> low;
        std::cin >> up;

        x = find_root(a,b,c,d,low,up);

        std::cout << "The root found was x = ";
        std::cout << x << std::endl;
        s = terminate();
    }
    std::cout << "Program terminated." << std::endl;
}