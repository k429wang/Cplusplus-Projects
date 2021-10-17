#include <iostream>

#ifndef MARMOSET_TESTING
int main();
#endif

int mode (int data_elements[], std::size_t qty_elements, int lowest_value, int highest_value);

#ifndef MARMOSET_TESTING
int main(){
    const std::size_t size {6};
    int arr[size]{-1,-2,-3,-3,-6,-6};
    int low{};
    int high{};
    for (int i{};i<size;++i){
        if (i==0){
            low = arr[i];
            high = arr[i];
        } else {
            if (arr[i]>high){
                high=arr[i];
            } else if (arr[i]<low) {
                low=arr[i];
            }
        }
    }
    int ans = mode(arr,size,low,high);
}
#endif

int mode(int data_elements[], std::size_t qty_elements, int lowest_value, int highest_value){
    int ans{};
    int max{};
    int counter{};
    for (int i{};i<qty_elements;++i){
        int temp{data_elements[i]};
        for (int j{}; j<qty_elements;++j){
            if (data_elements[j]==temp){
                counter++;
            }
        }
        if (counter>max){
            max=counter;
            ans=data_elements[i];
        } else if (counter==max){
            if (data_elements[i]<ans){
                ans = data_elements[i];
            }
        }
        counter=0;
    }
    return ans;
}