/* https://www.urionlinejudge.com.br/judge/pt/problems/view/2241 */
#include <iostream>
#include <string.h>

using namespace std;


int main() {
    int table_dim, qty_plays, l, c;
    cin >> table_dim >> qty_plays;

    // Initialize table with all 0's
    int table[table_dim][table_dim];
    memset(table, 0, sizeof(table));

    // Black stones
    for (int i = 0; i < qty_plays; i++) {
        cin >> l >> c;
        table[l - 1][c - 1] = 1;
    }


    // White stones
    for (int i = 0; i < qty_plays; i++) {
        cin >> l >> c;
        table[l - 1][c - 1] = 2;
    }

    int black_points = qty_plays;
    int white_points = qty_plays;

    // Auxiliary variable to prevent repetitive indexing
    int current_value;

    // Solve for all squares of side 2 to table_dim
    // We don't need to have a third dimension to store the solutions, as we do it in place
    for (int n = 1; n < table_dim; n++) {
        for (int i = 0; i < (table_dim - n); i++) {
            for (int j = 0; j < (table_dim - n); j++) {
                // Checks all composing sub-squares, which have sides equals n - 1 at this point

                // Starts from [i][j]
                if (table[i][j] == -1) {
                    continue;
                }

                current_value = table[i + 1][j];
                if (current_value != 0) {
                    if ((table[i][j] == 0) or (table[i][j] == current_value)) {
                        table[i][j] = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                current_value = table[i][j + 1];
                if (current_value != 0) {
                    if ((table[i][j] == 0) or (table[i][j] == current_value)) {
                        table[i][j] = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                current_value = table[i + 1][j + 1];
                if (current_value != 0) {
                    if ((table[i][j] == 0) or (table[i][j] == current_value)) {
                        table[i][j] = current_value;
                    }
                    else {
                        table[i][j] = -1;
                        continue;
                    }
                }

                // Count points
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
