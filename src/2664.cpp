#include <iostream>
#include <stdio.h>

using namespace std;


long long int create_exercise_program(int time_remaining, int current_difficulty, int min_difficulty, int max_difficulty, long long int* memo[max_difficulty + 1]) {
    if (time_remaining == 0) {
        return 1;
    }

    long long int qty_programs = memo[time_remaining][current_difficulty];

    if (qty_programs == 0) {
        if (current_difficulty == min_difficulty) {
            qty_programs = create_exercise_program(time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty, memo);
        }
        else if (current_difficulty == max_difficulty) {
            qty_programs = create_exercise_program(time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty, memo);
        }
        else {
            qty_programs += create_exercise_program(time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty, memo);
            qty_programs += create_exercise_program(time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty, memo);
        }

        memo[time_remaining][current_difficulty] = qty_programs;
    }

    return qty_programs;
}


int main() {

    int total_time, min_difficulty, max_difficulty;

    cin >> total_time >> min_difficulty >> max_difficulty;

    max_difficulty = max_difficulty - min_difficulty;
    min_difficulty = 0;

    long long int memo[total_time][max_difficulty + 1] = {};

    long long int qty_programs = 0;

    // Adjusts total time for 0 indexing
    total_time = total_time - 1;

    for (int i = 0; i < (max_difficulty + 1); i++) {
        qty_programs += create_exercise_program(total_time, i, min_difficulty, max_difficulty, memo);
    }

    long long int mod = 1000000007;

    cout << qty_programs % (mod);

    free(memo);

    return 0;
}
