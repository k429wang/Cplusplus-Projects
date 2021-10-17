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
	unsigned int value_to_protect{21352411};
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
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0}; series_index < QTY_VALUES; series_index++){
		std::cout << value_series[series_index] << " ";
	}
    std::cout << std::endl;

	unsigned int removed_value = remove_checksum(protected_value);
    std::cout << "The value " << protected_value
		<< " with the checksum removed is " << removed_value
		<< "." << std::endl;
	
    remove_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums removed: ";
	for (std::size_t series_index {0}; series_index < QTY_VALUES; series_index++){
		std::cout << value_series[series_index] << " ";
	}
    std::cout << std::endl;
    return 0;
}
#endif

unsigned int add_checksum(unsigned int n){
    if (n<=99999999){
        unsigned int ans = n;

        int size{};
        if (n==0){
            size=1;
        } else {
            while (n>0){
                size++;
                n/=10;
            }
        }

        n = ans;
        unsigned int arr[size]{};

        for (int i{size-1};i>=0;--i){
            arr[i] = n%10;
            n/=10;
        }

        for (int i{size-1};i>=0;i-=2){
            arr[i]*=2;
            if (arr[i]>9){
                int temp{};
                while (arr[i]>0){
                    temp+=arr[i]%10;
                    arr[i]/=10;
                }
                arr[i]=temp;
            }
        }
        int d{};
        for (int i{};i<size;++i){
            d+=arr[i];
        }

        d*=9;
        d%=10; 

        ans*=10;
        ans+=d;
        return ans;
    } else {
        return UINT_MAX;
    }
}

void add_checksum(unsigned int array[], std::size_t capacity){
    for(int i{};i<capacity;++i){
        array[i]=add_checksum(array[i]);
    }
    return;
}

bool verify_checksum(unsigned int n){
    unsigned int temp = n/10;
    if ((n<=999999999)&&(n==(add_checksum(temp)))){
        return true;
    } else {
        return false;
    }
}

unsigned int remove_checksum(unsigned int n){
    unsigned int temp = n/10;
    if ((n>999999999)||(n!=(add_checksum(temp)))){
        return UINT_MAX;
    } else {
        return n/10;
    }
}

void remove_checksum(unsigned int array[], std::size_t capacity){
    for (int i{};i<capacity;++i){
        array[i]=remove_checksum(array[i]);
    }
}