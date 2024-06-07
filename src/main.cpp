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

/// @brief 打印matrix
/// @tparam T 
/// @param matrix 
template <typename T>
void my_printf_matrix(const vector<vector<T>>& matrix){
    for(vector<T> v : matrix){
        for(T i : v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void my_printf_args(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
}

//参数解析


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

    int int_max = INT32_MAX;
    //以HEX显示 int_max
    printf("int_max = %x\n", int_max);
    printf("int_max = %d\n", int_max);
    unsigned int uint_max = UINT32_MAX;
    printf("uint_max = %x\n", uint_max);
    printf("uint_max = %d\n", uint_max);

    //
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    //初始化一个大小为n*n的matrix，初值为0
    int n = 3;
    vector<vector<int>> matrix2(n, vector<int>(n, 0));
    //打印该matrix
    my_printf_matrix<int>(matrix);
    my_printf_matrix<int>(matrix2);



    return 0;


}
