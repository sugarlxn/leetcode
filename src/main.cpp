#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> test1(vector<int>& nums){
    vector<int> res = nums;
    res[res.size()-1] = 8;
    return res;
}

/// @brief  打印vector
/// @tparam T 
/// @param nums 
/// @param flag 
template <typename T>
void my_printf_vector(const vector<T>& nums, bool flag = 0){
    //横向打印
    if(flag == 0){
        for(T i : nums){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    //纵向打印
    else{
        for(T i : nums){
            std::cout << i << std::endl;
        }
    }
}


void my_printf_args(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    printf("Hello World\n");
    vector<int> v = {3, 7, 1, 4, 5};
    vector<int> res = test1(v);
    std::sort(v.begin(), v.end());
    my_printf_vector<int>(v);
    my_printf_vector<int>(res);

    vector<float> c = {0.0,1.5,2.4,8,9};
    std::sort(c.begin(), c.end());
    my_printf_vector<float>(c,1);

    return 0;


}
