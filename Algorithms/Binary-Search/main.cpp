#include<iostream>
#include<vector>
using namespace std;

bool judge(int guess, int target) {
    return guess <= target;
}

int binary_search_ml(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;

    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (judge(nums[mid], target)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    return l;
}

int binary_search_nb(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;

    while (l < r) {
        int mid = (l + r) / 2;
        if (judge(nums[mid], target)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

int binary_search(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;

    while (l < r) {
        int mid = (l + r) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > target) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (nums[l] == target) return l;

    return -1;
};

int main() {
    int tmp[] = {1, 2, 3, 3, 3, 4, 5, 6};
    vector<int> nums(tmp, tmp + 8);
    cout << binary_search(nums, 3) << endl;
    // cout << binary_search_ml(nums, 3) << endl;
    // cout << binary_search_nb(nums, 3) << endl;
    return 0;
}


