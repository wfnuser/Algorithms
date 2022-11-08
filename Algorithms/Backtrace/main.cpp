#include<iostream>
#include<vector>
using namespace std;


// 回溯法是递归思想的经典应用。本模板以力扣经典问题全排列为例讨论。
// https://leetcode.cn/problems/permutations/description/

// 回溯中需要设置状态 表达当前局面在搜索空间中的位置，比如下棋时当前的棋盘状态（历史以来的每一步棋所累积的状态）
// 本例中为搜索到第n个数时，前n个数的排列；为了加快搜索速度，用used数组标记每个数字是否已经被使用过
bool backtrace(vector<vector<int> >& res, vector<int>& path, vector<int>& used, vector<int>& selections) {
	// 判断是否满足退出条件
	if (path.size() == selections.size()) {
		// 退出后处理逻辑
		// 此例中具体行为为积累可行方案至结果数组；注意，path本身
		res.push_back(vector<int>(path));
	}

	// 尝试所有可能的方案
	for (int i = 0; i < selections.size(); i++) {
		// 如果数字没有被选中过，可以尝试加入排列
		if (!used[selections[i]]) {
			// 尝试当前方案，设置状态
			path.push_back(selections[i]);
			used[selections[i]] = 1;
			// 递归
			backtrace(res, path, used, selections);
			// 恢复现场
			// 不采用当前方案，则需要把对应的状态清理；好比下棋的时候不能连下两步
			used[selections[i]] = 0;
			path.pop_back();
		}
	}
}

int main() {
	vector<vector<int> > res;
	vector<int> path;
	
	vector<int> selections = {1,2,3};
	vector<int> used(selections.size(), 0);

	backtrace(res, path, used, selections);

	for (auto sol: res) {
		cout << "{";
		cout << sol[0];
		for (int i = 1; i < sol.size(); i++) {
			cout << ", " << sol[i];
		}
		cout << "}" << endl;
	}
}


