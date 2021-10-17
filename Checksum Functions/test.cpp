#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum(unsigned int n);
void add_checksum(unsigned int array[], std::size_t capacity);
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned int array[], std::size_t capacity);

#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{20224012};
	unsigned int protected_value = add_checksum(value_to_protect);
    
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20209913, 20224012, 20209913};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0}; series_index < QTY_VALUES; series_index++){
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif

unsigned int add_checksum(unsigned int n){
    if (n<99999999){
        int ans=n;
        int arr[7]{};
        for (int i{7};i>=0;--i){
            arr[i] = n%10;
            n/=10;
        }
        for (int i{7};i>=0;i-=2){
            arr[i]*=2;
            if (arr[i]>9){
                int temp{};
                for (int j{};j<2;++j){
                    temp+=arr[i]%10;
                    arr[i]/=10;
                }
                arr[i]=temp;
            }
        }

        int d;
        for (int i{};i<8;++i){
            d+=arr[i];
        }
        d*=9;
        d%=10; 

        ans*=10;
        ans+=d;
        return ans;
    } else {
        return 99999999;
    }
}

void add_checksum(unsigned int array[], std::size_t capacity){
    for(int i{};i<capacity;++i){
        array[i]=add_checksum(array[i]);
    }
    return;
}

bool verify_checksum(unsigned int n){

}

unsigned int remove_checksum(unsigned int n){

}

void remove_checksum(unsigned int array[], std::size_t capacity){

}