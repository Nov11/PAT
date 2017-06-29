#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <assert.h>
#include <functional>
using namespace std;

class Solution {
	static size_t hashPair(const pair<int, int> &x)
	{
		return ((x.first) << 16) | (x.second);
	}
	static bool equalPair(const pair<int, int> &x, const pair<int, int> &y) {
		return x.first == y.first && x.second == y.second;
	}
	vector<int> nodesMin{ 0 };
	vector<int> nodesMax{ 0 };
	const static int REMAINDER = 1000000007;
	unordered_map<pair<int, int>, int, decltype(&Solution::hashPair), decltype(&Solution::equalPair)> br{ 20, &Solution::hashPair, &Solution::equalPair };
	unordered_map<pair<int, int>, int, decltype(&Solution::hashPair), decltype(&Solution::equalPair)> rr{ 20, &Solution::hashPair, &Solution::equalPair };

	//���������Ǻ�ɫ�ķ�ͬ�����������Ŀ
	//nodes�ǽڵ�������height�Ǻڸ߶�
	long long redRoot(int nodes, int height) {
		if (height < 0) { return 0; }
		auto p = make_pair(nodes, height);
		auto iter = rr.find(p);
		if (iter != rr.end()) { return iter->second; }
		long long sum = 0;
		for (int i = 0; i < nodes; i++) {
			sum += blackRoot(i, height) * blackRoot(nodes - 1 - i, height) ;
			sum %= REMAINDER;
		}
		rr[p] = sum;
		return sum;
	}

	//���������Ǻ�ɫ�ķ�ͬ�����������Ŀ
	//nodes�ǽڵ�������height�Ǻڸ߶�
	long long blackRoot(int nodes, int height) {
		if (height <= 0) { return 0; }
		if (nodes < nodesMin[height] || nodes > nodesMax[height]) {
			return 0;
		}
		auto p = make_pair(nodes, height);
		auto r = br.find(p);
		if (r != br.end()) { return r->second; }
		long long sum = 0;
		for (int i = 0; i < nodes; i++) {
			sum += blackRoot(i, height - 1) * blackRoot(nodes - 1 - i, height - 1);
			sum %= REMAINDER;
			sum += blackRoot(i, height - 1) * redRoot(nodes - 1 - i, height - 1);
			sum %= REMAINDER;
			sum += redRoot(i, height - 1) * blackRoot(nodes - 1 - i, height - 1);
			sum %= REMAINDER;
			sum += redRoot(i, height - 1) * redRoot(nodes - 1 - i, height - 1);
			sum %= REMAINDER;
		}
		br[p] = sum;
		return sum;
	}

public:
	//����������ĺڸ߶�h���ڵ���Ŀ������2^h - 1, �ڵ���������4^h - 1 = 2^h * 2^h - 1
	Solution() {
		int base = 2;
		for (int i = 1; i < 10; i++) {
			nodesMin.push_back(base - 1);
			nodesMax.push_back(base * base - 1);
			base *= 2;
		}

		br[make_pair(1, 1)] = 1;
		rr[make_pair(1, 0)] = 1;
		rr[make_pair(0, 0)] = 1;
	}

	int distinctRBTrees(int internalNodes) {
		assert(internalNodes <= 500);
		int sum = 0;
		for (int height = 1; height <= 9; height++) {
			sum += blackRoot(internalNodes, height);
			sum %= REMAINDER;
		}
		return sum;
	}
};

int main() {
	Solution s;
	int nodes;
	while (cin >> nodes) {
		cout << s.distinctRBTrees(nodes) << endl;
	}
}