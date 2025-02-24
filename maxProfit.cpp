#include <iostream>
#include <vector>
#include <unordered_map>
#include "maxProfit.h"

using namespace std;

// global variable to store computed results using memoization
vector<vector<vector<int>>> memo;

// recursive function to find the maximum profit
int findMaxProfit(int day, int transactions_left, bool holding, vector<int>& prices) {
    // base case: if we have no more days left or no more transactions allowed
    if (day >= prices.size() || transactions_left == 0) 
        return 0;

    // if we have already computed this case, return the stored value
    if (memo[day][transactions_left][holding] != -1) 
        return memo[day][transactions_left][holding];

    int doNothing = findMaxProfit(day + 1, transactions_left, holding, prices);

    if (holding) { 
        // case 1: we are holding a stock -> we can sell it or do nothing
        int sell = prices[day] + findMaxProfit(day + 1, transactions_left - 1, false, prices);
        memo[day][transactions_left][holding] = max(sell, doNothing);
    } else { 
        // case 2: we do not have a stock -> we can buy it or do nothing
        int buy = -prices[day] + findMaxProfit(day + 1, transactions_left, true, prices);
        memo[day][transactions_left][holding] = max(buy, doNothing);
    }

    return memo[day][transactions_left][holding];
}

// main function
int maxProfit(vector<int>& prices, int max_trans) {
    int n = prices.size();
    
    // initialize the memoization table with -1, not yet computed
    memo.assign(n, vector<vector<int>>(max_trans + 1, vector<int>(2, -1)));
    
    // start from day 0, with all transactions available, and not holding any stock
    return findMaxProfit(0, max_trans, false, prices);
}
return 0;
}
