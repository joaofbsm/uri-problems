"""https://www.urionlinejudge.com.br/judge/pt/problems/view/2664"""


def create_exercise_program(time_remaining, current_difficulty, min_difficulty, max_difficulty):
    # Base case
    if time_remaining == 1:
        return 1

    qty_programs = 0

    if current_difficulty == min_difficulty:
        qty_programs += create_exercise_program(time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty)
    elif current_difficulty == max_difficulty:
        qty_programs += create_exercise_program(time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty)
    else:
        qty_programs += create_exercise_program(time_remaining - 1, current_difficulty + 1, min_difficulty, max_difficulty)
        qty_programs += create_exercise_program(time_remaining - 1, current_difficulty - 1, min_difficulty, max_difficulty)

    return qty_programs


def main():
    total_time, min_difficulty, max_difficulty = [int(i) for i in input().split()]

    qty_programs = 0
    for i in range(min_difficulty, max_difficulty + 1):
        qty_programs += create_exercise_program(total_time, i, min_difficulty, max_difficulty)

    print((qty_programs % (10 ** 9 + 7)))


if __name__ == '__main__':
    main()
