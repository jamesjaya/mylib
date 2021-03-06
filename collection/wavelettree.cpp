#include <bits/stdc++.h>
 
using namespace std;

const int DEBUG = 0;

template<class T>
class wavelet_tree {
	private:
	T low, high;
	wavelet_tree *left, *right;
	vector<T> freq;
 
	int less_than_equal_aux(int l, int r, T k) {
		// pass 1-based index
		if (l > r || k < low) return 0;
		if (high <= k) return r - l + 1;
		int lb = freq[l-1];
		int rb = freq[r];
		return this->left->less_than_equal_aux(lb + 1, rb, k) + this->right->less_than_equal_aux(l-lb, r-rb, k);
	}
 
	int kth_ascending_aux(int l, int r, T k) {
		if (l > r) return 0;
		if (low == high) return low;
		int lb = freq[l-1];
		int rb = freq[r];
		int on_left_side = rb - lb;
		if (k <= on_left_side) return this->left->kth_ascending_aux(lb+1, rb, k);
		return this->right->kth_ascending_aux(l-lb, r-rb, k - on_left_side);
	}
 
	public:
	wavelet_tree(auto from, auto to, T low, T high): low(low), high(high) {
		// cout << low << ' ' << high << endl;
		if (DEBUG) {
			for (auto it = from; it != to; it++) {
				cout << *it << ' ';
			}
			cout << endl;
		}
 
		if (from >= to) {
			return;
		}
 
		freq.reserve(to - from + 1);
		freq.push_back(0);
 
		if (high == low) {
			for (auto it = from; it != to; it++) {
				freq.push_back(freq.back() + 1);
			}
			return;
		}
 
		T mid = low + (high - low) / 2;
		auto lessThanMid = [mid](T x) {
			return x <= mid;
		};
 
		for (auto it = from; it != to; it++) {
			freq.push_back(freq.back() + lessThanMid(*it));
		}
 
		auto pivot = stable_partition(from, to, lessThanMid);
 
		left = new wavelet_tree(from, pivot, low, mid);
		right = new wavelet_tree(pivot, to, mid + 1, high);
	}
 
	int less_than_equal(int l, int r, T k) {
		return this->less_than_equal_aux(l+1, r+1, k);
	}
 
	int kth_ascending(int l, int r, int k) {
		return this->kth_ascending_aux(l+1, r+1, k);
	}
};
 
template<class T>
class wavelet_tree_builder {
	public:
	static wavelet_tree<T> build_wavelet_tree(vector<T>& arr) {
		T low = arr[0];
		T high = arr[0];
		for (auto element: arr) {
			low = min(low, element);
			high = max(high, element);
		}
 
		return wavelet_tree<T>(arr.begin(), arr.end(), low, high);
	}
};
 
int main() {
	vector<int> arr = {0, 0, 9, 1, 2, 1, 7, 6, 4, 8, 9, 4, 3, 7, 5, 9, 2, 7, 0, 5, 1, 0};
	vector<int> cpy = arr;
	wavelet_tree<int> wt = wavelet_tree_builder<int>::build_wavelet_tree(arr);
	for (const int& element: arr) {
		cout << element << ' ';
	}
	cout << "\n";
	cout << "Subarray 0-12\n";
	for (int i = 0; i <= 12; i++) {
		cout << cpy[i] << ' ';
	}
	cout << "\n";
	cout << "Subarray 0-12 less than equal to 5: " << wt.less_than_equal(0, 12, 5) << "\n";
	cout << "Subarray 0-12 less than equal to 6: " << wt.less_than_equal(0, 12, 6) << "\n";
	cout << "Subarray 13-20\n";
	for (int i = 13; i <= 20; i++) {
		cout << cpy[i] << ' ';
	}
	cout << "\n";
	cout << "Subarray 13-20 less than equal to 6: " << wt.less_than_equal(13, 20, 6) << "\n";
	cout << "Subarray 13-20 less than equal to 7: " << wt.less_than_equal(13, 20, 7) << "\n";
}
