/* https://www.urionlinejudge.com.br/judge/pt/problems/view/2241 */
#include <iostream>
#include <string.h>

using namespace std;


int main() {
    int table_dim, qty_plays;
    cin >> table_dim >> qty_plays;

    // Initialize table with all 0's
    int table[table_dim][table_dim];
    memset(table, 0, sizeof(table));

    // for (int i = 0; i < table_dim; i++) {
    //    for (int j = 0; j < table_dim; j++) {
    //        cout << table[i][j] << ' ';
    //    }
    //    cout << endl;
    //}

    int l, c;

    // Black stones
    for (int i = 0; i < qty_plays; i++) {
        cin >> l >> c;
        table[l - 1][c - 1] = 1;
    }


    // Black stones
    for (int i = 0; i < qty_plays; i++) {
        cin >> l >> c;
        table[l - 1][c - 1] = 2;
    }

    int black_points = qty_plays;
    int white_points = qty_plays;

    int current_value, winner;

    for (int n = 1; n < table_dim; n++) {
        for (int i = 0; i < (table_dim - n); i++) {
            for (int j = 0; j < (table_dim - n); j++) {
                winner = 0;

                current_value = table[i][j];

                if (current_value != 0) {
                    if (current_value == -1) {
                        table[i][j] = -1;
                        continue;
                    }

                    if ((winner == 0) or (winner == current_value)) {
                        winner = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                current_value = table[i + 1][j];

                if (current_value != 0) {
                    if (current_value == -1) {
                        table[i][j] = -1;
                        continue;
                    }

                    if ((winner == 0) or (winner == current_value)) {
                        winner = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                current_value = table[i][j + 1];

                if (current_value != 0) {
                    if (current_value == -1) {
                        table[i][j] = -1;
                        continue;
                    }

                    if ((winner == 0) or (winner == current_value)) {
                        winner = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                current_value = table[i + 1][j + 1];

                if (current_value != 0) {
                    if (current_value == -1) {
                        table[i][j] = -1;
                        continue;
                    }

                    if ((winner == 0) or (winner == current_value)) {
                        winner = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                table[i][j] = winner;

                if (table[i][j] == 1) {
                    black_points += 1;
                }
                else if (table[i][j] == 2) {
                    white_points += 1;
                }
            }
        }
    }

    cout << black_points << ' ' << white_points << endl;
}
