#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

namespace MintLib {
	 long long GetFibonachi(const int& n) {
		long long prev_prev_number = 0, prev_number = 1;
		long long fibonachi_number = 0;
		for (int i = 2; i <= n; ++i) {
			fibonachi_number = prev_prev_number + prev_number;
			prev_prev_number = prev_number;
			prev_number = fibonachi_number;
		}
		return fibonachi_number;
	}

	// find the number of paths to the last cell if the grasshopper can jump 1, 2, . k cells	
	long long GetNumberOfPaths(const int& n, const int& k) {
		std::vector<int> dp(n, 1);	
		long long sub_sum = 1;
		for (int i = 1; i < n; ++i) {
			dp[i] = sub_sum;
			sub_sum += dp[i];
			if (i - k >= 0) {
				sub_sum -= dp[i - k];
			}
		}
		return dp.back();
	}

	// fin minimum sum you can obtain to get to the last cell, you can jumnp 1...k cells
	long long GetMinimumSum(const std::vector<long long>& costs, const int& n, const int& k = 2) {
		std::vector<long long> dp(n);
		std::vector<long long> path(n);

		for (int i = 1; i < n; ++i) {
			dp[i] = LONG_LONG_MAX;
			for (int j = 1; j <= k; ++j) {
				if (j <= i) {
					long long dp_tmp = dp[i - j] + costs[i];
					if (dp_tmp < dp[i]) {
						dp[i] = dp_tmp;
						path[i] = i - j;
					}	
				}
			}
		}

		return dp.back();
	}
};



