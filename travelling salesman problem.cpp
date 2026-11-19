#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1e9;

// Function to solve TSP using top-down DP with bitmasking
int tsp(int mask, int pos, int n, const vector<vector<int>>& dist, vector<vector<int>>& dp) {
    // Base case: All cities have been visited (all bits in mask are 1)
    if (mask == (1 << n) - 1) {
        return dist[pos][0]; // Return cost to go back to the starting city (0)
    }

    // Return already computed subproblem
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;

    // Try visiting every unvisited city
    for (int city = 0; city < n; city++) {
        // Check if 'city' is not visited yet
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, n, dist, dp);
            ans = min(ans, newAns);
        }
    }

    // Memoize and return the minimum cost
    return dp[mask][pos] = ans;
}

int main() {
    // Adjacency matrix representing distances between 4 cities
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int n = dist.size();

    // DP table initialized to -1: dimensions [2^n][n]
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    // Start from city 0 with only city 0 visited (mask = 1 -> binary 0001)
    int minCost = tsp(1, 0, n, dist, dp);

    cout << "Minimum traveling cost: " << minCost << endl;

    return 0;
}
