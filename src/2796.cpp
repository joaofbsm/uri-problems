/* https://www.urionlinejudge.com.br/judge/pt/problems/view/2796 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string.h>

using namespace std;


// House plant dimensions
int n, m;
int memo[1000][1000];
int max_width_per_length[1000];
int max_length_per_width[1000];


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
                (smallest_table_dim <= cur_width) and
                (cur_width > max_width_per_length[cur_length]) and
                (cur_length > max_length_per_width[cur_width])) {
                row_max_area = cur_area;
                largest_spaces.push_back(Space(cur_area, cur_length, cur_width));
                max_width_per_length[cur_length] = cur_width;
                max_length_per_width[cur_width] = cur_length;
            }
        }
    }

    // Sort spaces using the same comparison used for tables
    sort(largest_spaces.begin(), largest_spaces.end(), comp);

    return largest_spaces;
}


// Find the largest space considering this row using the max histogram area procedure
Space find_large_space(int* row) {
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
vector<Space> get_largest_spaces(int smallest_table_area, int smallest_table_dim) {
    // Find the largest empty spaces in the house starting from the bottom
    vector<Space> largest_spaces;
    for (int i = n - 1; i >= 0; i--) {
        Space large_space = find_large_space(memo[i]);
        if ((smallest_table_area <= large_space.area) and
            (smallest_table_dim <= large_space.length) and
            (smallest_table_dim <= large_space.width) and
            (large_space.width > max_width_per_length[large_space.length]) and
            (large_space.length > max_length_per_width[large_space.width])) {
            largest_spaces.push_back(large_space);
            max_width_per_length[large_space.length] = large_space.width;
            max_length_per_width[large_space.width] = large_space.length;
        }
    }

   // for (auto const& t: largest_spaces) {
   //     cout << t.area << ' ' << t.length << ' ' << t.width << '\n';
   //  }

    // Sort spaces using the same comparison used for tables
    //sort(largest_spaces.begin(), largest_spaces.end(), comp);

    return largest_spaces;
}


Space find_largest_table_fit(vector<Space> tables, vector<Space> largest_spaces, Space big_table) {
    bool is_table_fit[tables.size()];
    memset(is_table_fit, false, sizeof(is_table_fit));

    int tables_to_fit = tables.size();

    Space largest_table = Space(0, 0, 0);

    int largest_space_dim = 0;

    for (auto const& space: largest_spaces) {
        if (space.length > largest_space_dim) {
            largest_space_dim = space.length;
        }
        if (space.width > largest_space_dim) {
            largest_space_dim = space.width;
        }
    }

    for (auto const& space: largest_spaces) {
        for (int i = 0; i < tables.size(); i++) {
            // Only execute if table has not been fit yet
            if (!is_table_fit[i]) {
                Space table = tables[i];
                if ((table.width > largest_space_dim) or (table.length > largest_space_dim)) {
                    is_table_fit[i] = true;
                    tables_to_fit--;
                    continue;
                }

                if (table.area <= space.area) {
                    if (((table.length <= space.length) and (table.width <= space.width)) or
                        ((table.width <= space.length) and (table.length <= space.width))) {
                        is_table_fit[i] = true;
                        tables_to_fit--;
                        if (table.area >= largest_table.area) {
                            if ((table.area == big_table.area) and (table.width == big_table.area) and (table.length == big_table.length)) {
                                    return big_table;
                            }

                            if (table.area == largest_table.area) {
                                if (table.width > largest_table.width) {
                                    largest_table = table;
                                }
                            }
                            else {
                                largest_table = table;
                            }
                        } 
                        if (tables_to_fit == 0) {
                            break;
                        }
                    }
                }
            }
        }

        if (tables_to_fit == 0) {
            break;
        }
    }

    return largest_table;
}


int main() {
    cin >> n >> m;

    memset(max_width_per_length, 0, sizeof(max_width_per_length));
    memset(max_length_per_width, 0, sizeof(max_length_per_width));

    memset(memo, 0, sizeof(memo));

    char pos;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> pos;
            if (i == 0) {
                if (pos == '.') {
                    memo[i][j] = 1;
                }
                else {
                    memo[i][j] = 0;
                }
            }
            else {
                if (pos == '.') {
                    memo[i][j] = memo[i - 1][j] + 1;
                }
                else {
                    memo[i][j] = 0;
                }
            }
        }
    }

    // Read all tables as Space objects
    int qty_tables, area, length, width;
    cin >> qty_tables;
    vector<Space> tables;
    Space big_table = Space(0, 0, 0);
    int smallest_table_dim = 1000;
    int smallest_table_area = 1000;
    for (int i = 0; i < qty_tables; i++) {
        cin >> length >> width;
        area = length * width;
        Space table = Space(area, length, width);
        tables.push_back(table);

        if (area >= big_table.area) {
            if (area == big_table.area) {
                if (big_table.length > length) {
                    big_table = table;
                }
            }
            else {
                big_table = table;
            }
        }

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

    // // Sort tables by area in non-increasing order and use width as tiebreaker
    // sort(tables.begin(), tables.end(), comp);

    // // Get the largest spaces using the max histogram heuristic
    vector<Space> largest_spaces = get_largest_spaces(smallest_table_area, smallest_table_dim);
    // // vector<Space> largest_spaces = alternative_get_largest_spaces(house_plant, smallest_table_area, smallest_table_dim);

    // for (auto const& t: largest_spaces) {
    //    cout << t.area << ' ' << t.length << ' ' << t.width << '\n';
    // }

    // Find the largest table that fits any of these spaces
    Space largest_table = find_largest_table_fit(tables, largest_spaces, big_table);

    cout << largest_table.length << ' ' << largest_table.width << endl;
}