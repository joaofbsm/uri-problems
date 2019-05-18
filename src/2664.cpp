#include <iostream>
#include <string.h>

using namespace std;


long long mod = 1000000007;
long long memo[50][100000];


long long create_exercise_program(int time_remaining, int current_difficulty, int min_difficulty, int max_difficulty) {
    // Border cases
    if (current_difficulty < min_difficulty || current_difficulty > max_difficulty) {
        return 0;
    }

    // Base case
    if (time_remaining == 0) {
        return 1;
    }

    // Compute memoization matrix position
    if (memo[time_remaining][current_difficulty] == 0) {
        memo[time_remaining][current_difficulty] += create_exercise_program(time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty);
        memo[time_remaining][current_difficulty] += create_exercise_program(time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty);
        memo[time_remaining][current_difficulty] %= mod;
    }

    return memo[time_remaining][current_difficulty];
}


int main() {

    // Read input
    int total_time, min_difficulty, max_difficulty;
    cin >> total_time >> min_difficulty >> max_difficulty;

    // Adjust difficulties for sequential indexing from 0
    max_difficulty = max_difficulty - min_difficulty;
    min_difficulty = 0;

    // Initialize very position with 0
    memset(memo, 0, sizeof(memo));

    // Adjusts total time for 0 indexing
    total_time = total_time - 1;

    // Calculate the total quantity of programs by summing the quantity for each starting difficulty
    long long qty_programs = 0;
    for (int i = 0; i <= max_difficulty; i++) {
        qty_programs += create_exercise_program(total_time, i, min_difficulty, max_difficulty);
    }

    cout << qty_programs % mod << endl;

    return 0;
}
