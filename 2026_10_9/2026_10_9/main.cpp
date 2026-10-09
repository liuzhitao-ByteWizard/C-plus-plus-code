#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//int singleNumber(vector<int>& numbers) {
//    sort(numbers.begin(), numbers.end());
//    int src = 0;
//    int dst = 0;
//    int find = 0; //保存只出现一次的数字
//    while (dst != numbers.size()) {
//        int count = 0; //每个元素出现的次数
//        while (numbers[src] == numbers[dst]) {
//            if (dst == numbers.size() - 1) {
//                find = numbers[dst];
//                break;
//            }
//            count++;
//            dst++;
//        }
//        if (count != 3) {
//            find = numbers[src];
//            break;
//        }
//        else {
//            src = dst;
//        }
//
//    }
//    return find;
//}

//int MoreThanHalfNum_Solution(vector<int>& numbers) {
//    // write code here
//    sort(numbers.begin(), numbers.end());
//    int src = 0;
//    int dst = 0;
//    int find = 0; //保存只出现一次的数字
//    while (dst != numbers.size()) {
//        int count = 0; //每个元素出现的次数
//        while (numbers[src] == numbers[dst]) {
//            if (dst == numbers.size() - 1) {
//                find = numbers[dst];
//                return find;
//            }
//            count++;
//            dst++;
//        }
//        if (count > numbers.size() / 2) {
//            find = numbers[src];
//            return find;
//        }
//        else {
//            src = dst;
//        }
//
//    }
//    return find;
//}


//vector<int> singleNumber(vector<int>& nums) {
//    sort(nums.begin(), nums.end());
//    vector<int> tmp;
//    int src = 0 , dst = 0;
//    int find1 = 0; //保存第一次只出现一次的数字
//    int find2 = 0; //保存第二次只出现一次的数字
//    int cnt = 1; //记录出现一次数字的元素个数
//    while (dst != nums.size()) {
//        int count = 0; //每个元素出现的次数
//        while (nums[src] == nums[dst]) {
//            if (dst == nums.size() - 1) {
//                find2 = nums[dst];
//                tmp.push_back(find1);
//                tmp.push_back(find2);
//                return tmp;
//            }
//            count++;
//            dst++;
//        }
//        if (count != 2) {
//            if (cnt == 2) {
//                find2 = nums[src];
//                src = dst;
//            }
//            else {
//                find1 = nums[src];
//                src = dst;
//            }
//            cnt++;
//        }
//        else {
//            src = dst;
//        }
//    }
//    tmp.push_back(find1);
//    tmp.push_back(find2);
//    return tmp;
//}


//int main() {
//	int ar[] = { 1,2,3,4,0,5,6,7,8,9 };
//	int n = sizeof(ar) / sizeof(int);
//	vector<int> v(ar, ar + n);
//	vector<int>::iterator it = v.begin();
//	while (it != v.end())
//	{
//		if (*it != 0)
//			cout << *it;
//		else
//			v.erase(it);
//		it++;
//	}
//	return 0;
//}

int main() {
	return 0;
}
