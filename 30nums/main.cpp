#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


string a;
int count = 0;
void com(int i, int j){
	cout << i << " " << j << endl;
    while(a[i]==a[j]&&i<j) {
        i++;
        j--;
    }
    if(i>=j)return;
    if(a[i]>a[j]){
        count++;
    }
    return;
}

int partision(vector<int>& nums, int left, int right){
	int pivot = nums[right];
	int i=left;
	for(int j=left; j<right; j++){
		if(nums[j] < pivot){
			swap(nums[i], nums[j]);
			i++;
		}
	}
	swap(nums[i], nums[right]);//?

	cout << "pivot: " << pivot << endl;
	for(auto i: nums){
		cout << i << " ";
	}
	cout << endl;
	return i;
}

int quickSelect(vector<int>& nums, int left, int right, int target){
	
	if(left==right) return nums[left];
	// 一次partision 可以拿到一个确定位置的元素
	int pivotIndex = partision(nums, left, right);

	if (pivotIndex == target){
		return nums[pivotIndex];
	}else if(pivotIndex < target){
		return quickSelect(nums, pivotIndex+1, right, target);
	}else{
		return quickSelect(nums, left, pivotIndex-1, target);
	}
	
}

int main(int argc, char** argv) {

	// //输入num 
	// getline(cin, a);
	// int n = a.size();
	
	// //双指针 二维遍历
	// for(int i=0; i < n-1; i++){
	// 	for(int j=i+1; j < n; j++){
	// 		com(i,j);
	// 	}
	// } 
	// cout << count;

	vector<int> nums = {3,2,1,5,2};
	int target = 3;
	int res = quickSelect(nums, 0, nums.size()-1, target-1);
	cout << res << endl;
	for(auto i: nums){
		cout << i << " ";
	}
	cout << endl;

	return 0;

}