"""https://www.urionlinejudge.com.br/judge/pt/problems/view/2664"""


def create_exercise_program(time_remaining, current_difficulty):

    # Border cases
    if current_difficulty < min_difficulty or current_difficulty > max_difficulty:
        return 0

    if memo[time_remaining][current_difficulty] != 0:
        return memo[time_remaining][current_difficulty]

    # Base case
    if time_remaining == 0:
        memo[time_remaining][current_difficulty] = 1
        return memo[time_remaining][current_difficulty]

    memo[time_remaining][current_difficulty] = (create_exercise_program(time_remaining - 1, current_difficulty + 1)
                                                + create_exercise_program(time_remaining - 1, current_difficulty - 1))

    return memo[time_remaining][current_difficulty]


mod = 1000000007

total_time, min_difficulty, max_difficulty = [int(i) for i in input().split()]

max_difficulty = max_difficulty - min_difficulty
min_difficulty = 0

memo = [[0 for _ in range(max_difficulty + 1)] for _ in range(total_time)]
total_programs = 0

# Adjusts total time for 0 indexing
total_time -= 1
for i in range(max_difficulty + 1):
    total_programs += create_exercise_program(total_time, i)

print(total_programs % mod)
