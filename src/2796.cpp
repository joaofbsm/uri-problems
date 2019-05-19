/* https://www.urionlinejudge.com.br/judge/pt/problems/view/2796 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string.h>

using namespace std;


// House plant dimensions
int n, m;


// Space data structure used for both tables and spaces in the house
class Space {
public:
	int area, length, width;

	Space(int length, int width)	{
		this->length = length;
		this->width = width;
		this->area = length * width;
	}
};


// Sort array of Space objects first by area and then by width
bool comp(Space const& A, Space const& B) {
    return (A.area > B.area) || ((A.area == B.area) && (A.width > B.width));
}


// Find the largest space considering this row using the max histogram area heuristic
Space find_large_space(int *row) {
    int max_area, max_length, max_width, current_area, current_length, current_width;
    max_area = 0;
    max_length = 0;
    max_width = 0;

    stack<int> s;

    for (int j = 0; j < m; j++) {
        while ((!s.empty()) and (row[s.top()] > row[j])) {
            current_length = row[s.top()];
            s.pop();
            if (s.empty()) {
                current_width = j;
            }
            else {
                current_width = j - s.top() - 1;
            }

            current_area = current_length * current_width;
            if (current_area > max_area) {
                max_area = current_area;
                max_length = current_length;
                max_width = current_width;
            }
        }
        s.push(j);
    }

    Space large_space = Space(max_length, max_width);

    return large_space;
}


// Get the largest empty spaces in the house
vector<Space> get_largest_spaces(vector< vector<char> > house_plant) {
    // Memoization matrix
    int memo[n][m];
    memset(memo, 0, sizeof(memo));

    // Initialize first row
    for (int j = 0; j < m; j++) {
        if (house_plant[0][j] == '.') {
            memo[0][j] = 1;
        }
    }

    // Complete the other rows using memoization
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (house_plant[i][j] == '.') {
                memo[i][j] = memo[i - 1][j] + 1;
            }
        }
    }

    // Find the largest empty spaces in the house
    vector<Space> largest_spaces;
    for (int i = 0; i < n; i++) {
        Space large_space = find_large_space(memo[i]);
        largest_spaces.push_back(large_space);
    }

    // Sort spaces using the same comparison used for tables
    sort(largest_spaces.begin(), largest_spaces.end(), comp);

    return largest_spaces;
}


Space find_largest_table_fit(vector<Space> tables, vector<Space> largest_spaces) {
    bool is_table_fit[tables.size()] = {false};

    for (auto const& space: largest_spaces) {
        for (int i = 0; i < tables.size(); i++) {
            // Only execute is table has not been fit yet
            if (!is_table_fit[i]) {
                Space table = tables[i];
                if (table.area <= space.area) {
                    if (((table.length <= space.length) and (table.width <= space.width)) or
                        ((table.width <= space.length) and (table.length <= space.width))) {
                        is_table_fit[i] = true;
                    }
                }
            }
        }
    }

    // Find largest table that fits any space
    int i = 0;
    while (!is_table_fit[i]) {
        i++;
    }

    return tables[i];
}


int main() {
    cin >> n >> m;

    // Stores the house plant
    vector< vector<char> > house_plant;
    char pos;
    for (int i = 0; i < n; i++) {
        vector<char> row;
        for (int j = 0; j < m; j++) {
            cin >> pos;
            row.push_back(pos);
        }
        house_plant.push_back(row);
    }

    // Read all tables as Space objects
    int qty_tables, length, width;
    cin >> qty_tables;
    vector<Space> tables;
    for (int i = 0; i < qty_tables; i++) {
        cin >> length >> width;
        Space table = Space(length, width);
        tables.push_back(table);
    }

    // Sort tables by area in non-increasing order and use width as tiebreaker
    sort(tables.begin(), tables.end(), comp);

    // Get the largest spaces using the max histogram heuristic
    vector<Space> largest_spaces = get_largest_spaces(house_plant);

    // Find the largest table that fits any of these spaces
    Space largest_table = find_largest_table_fit(tables, largest_spaces);

    cout << largest_table.length << ' ' << largest_table.width << endl;
}