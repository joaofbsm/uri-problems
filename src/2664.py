"""https://www.urionlinejudge.com.br/judge/pt/problems/view/2664"""


def create_exercise_program(memo, time_remaining, current_difficulty, min_difficulty, max_difficulty):
    # Base case
    if time_remaining == 0:
        return 1

    qty_programs = memo[time_remaining].get(current_difficulty, 0)

    if qty_programs == 0:
        if current_difficulty == min_difficulty:
            qty_programs = create_exercise_program(memo, time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty)
        elif current_difficulty == max_difficulty:
            qty_programs = create_exercise_program(memo, time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty)
        else:
            qty_programs += create_exercise_program(memo, time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty)
            qty_programs += create_exercise_program(memo, time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty)

        memo[time_remaining][current_difficulty] = qty_programs

    return qty_programs


def main():
    total_time, min_difficulty, max_difficulty = [int(i) for i in input().split()]

    memo = [{} for _ in range(total_time)]
    qty_programs = 0

    # Adjusts total time for 0 indexing
    total_time -= 1
    for i in range(min_difficulty, max_difficulty + 1):
        qty_programs += create_exercise_program(memo, total_time, i, min_difficulty, max_difficulty)

    print((qty_programs % (10 ** 9 + 7)))


if __name__ == '__main__':
    main()
