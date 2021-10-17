#include <iostream>

int main();

int main(){
    double x{0.0};

    std::cout << "Enter value of x: ";
    std::cin >> x;

    //This local variable should hold the result of stair(x)
    int stair_result{};

    //TASK: Write code that calculates an integer value corresponding to the value of the function stair(x) here

    for (int i=0; i>-1; i++){
        if (x>=0){
            if ((x>=i)&&(x<(i+1))){
                stair_result = i;
                break;
            }
        } else {
            if ((x>=(-i))&&(x<((-i)+1))){
                stair_result = -i;
                break;
            }
        }
    }

    std::cout << "The value of stair(x) is: " << stair_result << std::endl;

    return 0;
}