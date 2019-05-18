"""https://www.urionlinejudge.com.br/judge/pt/problems/view/2241"""


def main():
    table_dim, qty_plays = [int(i) for i in input().split()]

    # Initialize table with all 0's
    table = [[[0 for _ in range(table_dim)] for _ in range(table_dim)] for _ in range(table_dim)]

    # Black stones
    for _ in range(qty_plays):
        i, j = [int(a) - 1 for a in input().split()]
        table[i][j][0] = 1

    # White stones
    for _ in range(qty_plays):
        i, j = [int(a) - 1 for a in input().split()]
        table[i][j][0] = 2

    black_points = 0
    white_points = 0

    for n in range(1, table_dim):
        for i in range(table_dim - n):
            for j in range(table_dim - n):
                previous_n = n - 1
                winner = 0

                current_value = table[i][j][previous_n]

                if current_value != 0:
                    if current_value == -1:
                        table[i][j][n] = -1
                        continue

                    if winner == 0 or winner == current_value:
                        winner = current_value
                    else:
                        table[i][j][n] = -1
                        continue

                current_value = table[i + 1][j][previous_n]

                if current_value != 0:
                    if current_value == -1:
                        table[i][j][n] = -1
                        continue

                    if winner == 0 or winner == current_value:
                        winner = current_value
                    else:
                        table[i][j][n] = -1
                        continue

                current_value = table[i][j + 1][previous_n]

                if current_value != 0:
                    if current_value == -1:
                        table[i][j][n] = -1
                        continue

                    if winner == 0 or winner == current_value:
                        winner = current_value
                    else:
                        table[i][j][n] = -1
                        continue

                current_value = table[i + 1][j + 1][previous_n]

                if current_value != 0:
                    if current_value == -1:
                        table[i][j][n] = -1
                        continue

                    if winner == 0 or winner == current_value:
                        winner = current_value
                    else:
                        table[i][j][n] = -1
                        continue

                table[i][j][n] = winner

                if winner == 1:
                    black_points += 1
                elif winner == 2:
                    white_points += 1

    print(black_points + qty_plays, white_points + qty_plays)

if __name__ == '__main__':
    main()