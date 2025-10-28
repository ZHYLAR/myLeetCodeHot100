#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution
{
public:
	// int gcd(int a,int b) {
	// 	return b>0 ? gcd(b,a%b):a;
	// }


	void rotate(vector<int> &nums, int k)
	{
		int num_nums = nums.size();
		int temp0;
		int attr = 0;
		int attr_tmp = 0;

		k = k%num_nums;
		// int loop = gcd(num_nums,k);
        int count = 0;

		for(int round=0; 1 ; round++){
            if(count==num_nums) break;
			temp0 = nums[round];
			attr = round;
			do
			{
				attr_tmp = (attr + k) % num_nums; // 本次被替换的位置

				nums[attr_tmp] = nums[attr_tmp] ^ temp0;
				temp0 =  nums[attr_tmp] ^ temp0;
				nums[attr_tmp] =  nums[attr_tmp] ^ temp0;
                count++;
				// temp1 = nums[attr_tmp];
				// nums[attr_tmp] = temp0; // 替换
				// temp0 = temp1;
				// temp = nums[(attr_tmp+k)%num_nums];
				attr = attr_tmp;
			} while (attr!=round);
		}
		
	}
};


// class Solution
// {
// public:
// 	int gcd(int a,int b) {
// 		return b>0 ? gcd(b,a%b):a;
// 	}


// 	void rotate(vector<int> &nums, int k)
// 	{
// 		int num_nums = nums.size();
// 		int temp0,temp1;
// 		int attr = 0;
// 		int attr_tmp = 0;

// 		k = k%num_nums;
// 		int loop = gcd(num_nums,k);

// 		for(int round=0; round < loop; round++){
// 			temp0 = nums[round];
// 			attr = round;
// 			do
// 			{
// 				attr_tmp = (attr + k) % num_nums; // 本次被替换的位置

// 				nums[attr_tmp] = nums[attr_tmp] ^ temp0;
// 				temp0 =  nums[attr_tmp] ^ temp0;
// 				nums[attr_tmp] =  nums[attr_tmp] ^ temp0;

// 				// temp1 = nums[attr_tmp];
// 				// nums[attr_tmp] = temp0; // 替换
// 				// temp0 = temp1;
// 				// temp = nums[(attr_tmp+k)%num_nums];
// 				attr = attr_tmp;
// 			} while (attr!=round);
// 		}
		
// 	}
// };

int main()
{
	Solution solution;
	vector<int> nums = {-1,-100,3,99};
	int k = 2;

	solution.rotate(nums, k);
	for(auto & num : nums)
	{
		cout << num << " " ;
	}

	cout << endl;
	return 0;
}
