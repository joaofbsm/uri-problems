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

    Space(int area, int length, int width) {
        this->area = area;
        this->length = length;
		this->width = width;
    }

	Space(int length, int width)	{
		this->area = length * width;
		this->length = length;
		this->width = width;
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

    Space large_space = Space(max_area, max_length, max_width);

    return large_space;
}


// Get the largest empty spaces in the house
vector<Space> get_largest_spaces(vector< vector<char> > house_plant, int smallest_table_area, int smallest_table_dim) {
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

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         if (memo[i][j] > 9) {
    //             cout << memo[i][j] << ' ';
    //         }
    //         else {
    //             cout << ' ' << memo[i][j] << ' ';
    //         }
            
    //     }
    //     cout << endl;
    // }

    // Find the largest empty spaces in the house
    vector<Space> largest_spaces;
    for (int i = n; i >= 0; i--) {
        Space large_space = find_large_space(memo[i]);
        if ((smallest_table_area <= large_space.area) and
            (smallest_table_dim <= large_space.length) and
            (smallest_table_dim <= large_space.width)) {
            largest_spaces.push_back(large_space);
        }
    }

   for (auto const& t: largest_spaces) {
       cout << t.area << ' ' << t.length << ' ' << t.width << '\n';
    }

    // Sort spaces using the same comparison used for tables
    sort(largest_spaces.begin(), largest_spaces.end(), comp);

    return largest_spaces;
}


vector<Space> alternative_get_largest_spaces(vector< vector<char> > house_plant, int smallest_table_area, int smallest_table_dim) {
    int left[m];
    int right[m];
    int length[m];

    memset(left, 0, sizeof(left));
    memset(right, m, sizeof(right));
    memset(length, 0, sizeof(length));

    vector<Space> largest_spaces;

    for (int i = 0; i < n; i++) {
        int row_max_area = 0;
        int cur_left = 0;
        int cur_right = m;

        int cur_area, cur_length, cur_width;

        // Update length
        for (int j = 0; j < m; j++) {
            if (house_plant[i][j] == '.') {
                length[j] += 1;
            }
            else {
                length[j] = 0;
            }
        }

        // Update left
        for (int j = 0; j < m; j++) {
            if (house_plant[i][j] == '.') {
                left[j] = left[j] >= cur_left ? left[j] : cur_left;
            }
            else {
                left[j] = 0;
                cur_left = j + 1;
            }
        }

        // Update right
        for (int j = m - 1; j > -1; j--) {
            if (house_plant[i][j] == '.') {
                right[j] = right[j] <= cur_right ? right[j] : cur_right;
            }
            else {
                right[j] = m;
                cur_right = j;
            }
        }

        // Update area
        for (int j = 0; j < m; j++) {
            cur_length = length[j];
            cur_width = right[j] - left[j];
            cur_area = cur_length * cur_width;

            if ((row_max_area < cur_area) and
                (smallest_table_area <= cur_area) and
                (smallest_table_dim <= cur_length) and
                (smallest_table_dim <= cur_width)) {
                row_max_area = cur_area;
                largest_spaces.push_back(Space(cur_area, cur_length, cur_width));
            }
        }
    }

    // Sort spaces using the same comparison used for tables
    sort(largest_spaces.begin(), largest_spaces.end(), comp);

    return largest_spaces;
}


Space find_largest_table_fit(vector<Space> tables, vector<Space> largest_spaces) {
    bool is_table_fit[tables.size()];
    memset(is_table_fit, false, sizeof(is_table_fit));

    int tables_to_fit = tables.size();

    for (auto const& space: largest_spaces) {
        for (int i = 0; i < tables.size(); i++) {
            // Only execute if table has not been fit yet
            if (!is_table_fit[i]) {
                Space table = tables[i];
                if (table.area <= space.area) {
                    if (((table.length <= space.length) and (table.width <= space.width)) or
                        ((table.width <= space.length) and (table.length <= space.width))) {
                        is_table_fit[i] = true;
                        tables_to_fit--;
                        if (tables_to_fit == 0) {
                            break;
                        }
                    }
                }
            }
        }

        // If largest table was already fit, prevent more computations
        if (is_table_fit[0]) {
            return tables[0];
        }

        if (tables_to_fit == 0) {
            break;
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
    int qty_tables, area, length, width;
    cin >> qty_tables;
    vector<Space> tables;
    int smallest_table_dim = 1000;
    int smallest_table_area = 1000;
    for (int i = 0; i < qty_tables; i++) {
        cin >> length >> width;
        area = length * width;
        Space table = Space(area, length, width);
        tables.push_back(table);

        if (area < smallest_table_area) {
            smallest_table_area = area;
        }
        if (length < smallest_table_dim) {
            smallest_table_dim = length;
        }
        if (width < smallest_table_dim) {
            smallest_table_dim = width;
        }
    }

    // Sort tables by area in non-increasing order and use width as tiebreaker
    sort(tables.begin(), tables.end(), comp);

    // Get the largest spaces using the max histogram heuristic
    vector<Space> largest_spaces = get_largest_spaces(house_plant, smallest_table_area, smallest_table_dim);
    // vector<Space> largest_spaces = alternative_get_largest_spaces(house_plant, smallest_table_area, smallest_table_dim);

    // for (auto const& t: largest_spaces) {
    //    cout << t.area << ' ' << t.length << ' ' << t.width << '\n';
    // }

    // Find the largest table that fits any of these spaces
    Space largest_table = find_largest_table_fit(tables, largest_spaces);

    cout << largest_table.length << ' ' << largest_table.width << endl;
}