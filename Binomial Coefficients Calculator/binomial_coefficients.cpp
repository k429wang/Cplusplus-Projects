#include <iostream>
#include <limits>

int main();

int main(){
    int n, k{};

    std::cout << "Binomial Coefficients Calculator" << std::endl;
    std::cout << "Enter the value for n: ";
    std::cin >> n;
    std::cout << "Enter the value for k: ";
    std::cin >> k;

    if ((n>=k)&&(k>=0)){
        int num{1};
        int den{1};
        int temp{n-k};
        int nCk{};

        if (k<(n-k)){
            k = n-k;
        }

        for (int j{}; j<(n-k);++j){
            den*= temp;
            temp -=1;
        }

        for (int i{}; i<(n-k);++i){
            num*=n;
            n-=1;
        }

    

        nCk = num/den;
        std::cout << num << std::endl;
        std::cout << den << std::endl;

        std::cout << nCk << std::endl;

    } else {
        std::cout << "Cannot calculate nCk because condition n >= k >= 0 was not met." << std::endl;
    }

}