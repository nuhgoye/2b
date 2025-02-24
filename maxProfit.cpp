#include <iostream>
#include <vector>
#include <unordered_map>
#include "maxProfit.h"

using namespace std;

// global variable to store computed results using memoization
vector<vector<vector<int>>> memo;

// recursive function to find the maximum profit
int findMaxProfit(int day, int transactions_left, bool holding, vector<int>& prices) {
    // base cases: if no more days or no transactions left, return 0
    if (day >= prices.size() || transactions_left == 0) {
        return 0;
    }
    // return memoized result if already computed
    if (memo[day][transactions_left][holding] != -1) {
        return memo[day][transactions_left][holding];
    }
    // option 1: do nothing, move to the next day
    int doNothing = findMaxProfit(day + 1, transactions_left, holding, prices);
    // option 2: buy or sell based on whether we are holding stock or not
    if (holding) { 
        // if we are holding a stock, we can either sell it or do nothing
        int sell = prices[day] + findMaxProfit(day + 1, transactions_left - 1, false, prices);
        return memo[day][transactions_left][holding] = max(sell, doNothing);
    } else { 
        // if we are not holding, we can either buy or do nothing
        int buy = -prices[day] + findMaxProfit(day + 1, transactions_left, true, prices);
        return memo[day][transactions_left][holding] = max(buy, doNothing);
    }
}

// main function
int maxProfit(vector<int>& prices, int max_trans) {
    // edge case: if no prices or no transactions allowed, return 0
    if (prices.empty() || max_trans == 0) {
        return 0;
    }
    int n = prices.size();
    // initialize the memoization table with -1, not yet computed
    memo.assign(n, vector<vector<int>>(max_trans + 1, vector<int>(2, -1)));
    // start from day 0, with all transactions available, and NOT holding stock
    return findMaxProfit(0, max_trans, false, prices);
}
