/* https://www.urionlinejudge.com.br/judge/pt/problems/view/2796 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string.h>
#include <bits/stdc++.h> 

using namespace std;


// Space data structure used for both tables and spaces in the house
class Space {
public:
    int area, length, width;

    Space() {
    }

    Space(int area, int length, int width) {
        this->area = area;
        this->length = length;
        this->width = width;
    }

    Space(int length, int width)    {
        this->area = length * width;
        this->length = length;
        this->width = width;
    }

};


// House plant dimensions
int n, m;
int memo[1000][1000];
int max_width_per_length[1000];
int max_length_per_width[1000];
vector<Space> largest_spaces;


// Sort array of Space objects first by area and then by width
bool comp_tiebreaker(Space const& A, Space const& B) {
    return (A.area > B.area) || ((A.area == B.area) && (A.width > B.width));
}

// Sort array of Space objects first by area
bool comp(Space const& A, Space const& B) {
    return (A.area > B.area);
}


// Find the largest space considering this row using the max histogram area procedure
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
void get_largest_spaces(int smallest_table_area, int smallest_table_dim) {
    // Find the largest empty spaces in the house starting from the bottom
    for (int i = n - 1; i >= 0; i--) {
        Space large_space = find_large_space(memo[i]);
        if ((large_space.area >= smallest_table_area) and
            (large_space.length >= smallest_table_dim) and
            (large_space.width >= smallest_table_dim) and
            (large_space.length > max_length_per_width[large_space.width]) and
            (large_space.width > max_width_per_length[large_space.length])) {
            
            largest_spaces.push_back(large_space);
            max_width_per_length[large_space.length] = large_space.width;
            max_length_per_width[large_space.width] = large_space.length;
        }
    }
}


// Find the largest space considering this row using the max histogram area procedure
void find_largest_spaces(int smallest_table_area, int smallest_table_dim) {
    for (int i = n - 1; i >= 0; i--) {
        int *row = memo[i];
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

                    Space large_space = Space(max_area, max_length, max_width);
                    if ((large_space.area >= smallest_table_area) and
                        (large_space.length >= smallest_table_dim) and
                        (large_space.width >= smallest_table_dim) and
                        (large_space.length > max_length_per_width[large_space.width]) and
                        (large_space.width > max_width_per_length[large_space.length])) {
                        
                        largest_spaces.push_back(large_space);
                        max_width_per_length[large_space.length] = large_space.width;
                        max_length_per_width[large_space.width] = large_space.length;
                    }
                }
            }
            s.push(j);
        }
    }
}


Space find_largest_table_fit(vector<Space> tables, vector<Space> largest_spaces, Space largest_table) {
    bool is_table_fit[tables.size()];
    memset(is_table_fit, 0, sizeof(is_table_fit));
    int tables_to_fit = tables.size();

    Space table;
    Space largest_fitted_table = Space(0, 0, 0);

    int largest_space_dim = 0;
    for (auto const& space: largest_spaces) {
        if (space.length > largest_space_dim) {
            largest_space_dim = space.length;
        }
        if (space.width > largest_space_dim) {
            largest_space_dim = space.width;
        }
    }

    for (auto space: largest_spaces) {
        for (int i = 0; i < tables.size(); i++) {
            // Only execute if table has not been fit yet
            if (is_table_fit[i] == 0) {
                table = tables[i];
                if ((table.width > largest_space_dim) or (table.length > largest_space_dim)) {
                    is_table_fit[i] = 1;
                    tables_to_fit--;
                    if (tables_to_fit == 0) {
                        return largest_fitted_table;
                    }
                    else {
                        continue;
                    }
                }

                if (table.area <= space.area) {
                    if (((table.length <= space.length) and (table.width <= space.width)) or
                        ((table.width <= space.length) and (table.length <= space.width))) {
                        if (table.area >= largest_fitted_table.area) {
                            if ((table.area == largest_table.area) and (table.width == largest_table.area) and (table.length == largest_table.length)) {
                                    return largest_table;
                            }

                            if (table.area == largest_fitted_table.area) {
                                if (table.width > largest_fitted_table.width) {
                                    largest_fitted_table = table;
                                }
                            }
                            else {
                                largest_fitted_table = table;
                            }
                        } 

                        is_table_fit[i] = 1;
                        tables_to_fit--;
                        if (tables_to_fit == 0) {
                            return largest_fitted_table;
                        }
                    }
                }
            }
        }
    }

    return largest_fitted_table;
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

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
    Space largest_table = Space(0, 0, 0);
    int smallest_table_dim = 1000;
    int smallest_table_area = 1000;
    for (int i = 0; i < qty_tables; i++) {
        cin >> length >> width;
        area = length * width;
        Space table = Space(area, length, width);
        tables.push_back(table);

        if (area >= largest_table.area) {
            if (area == largest_table.area) {
                if (largest_table.length > length) {
                    largest_table = table;
                }
            }
            else {
                largest_table = table;
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
    
    // Get the largest spaces using the max histogram heuristic
    get_largest_spaces(smallest_table_area, smallest_table_dim);
    // find_largest_spaces(smallest_table_area, smallest_table_dim);

    // Sort spaces using the same comparison used for tables
    // sort(largest_spaces.begin(), largest_spaces.end(), comp);

    // for (auto const& t: largest_spaces) {
    //    cout << t.area << ' ' << t.length << ' ' << t.width << '\n';
    // }

    // Find the largest table that fits any of these spaces
    Space largest_fitted_table = find_largest_table_fit(tables, largest_spaces, largest_table);

    cout << largest_fitted_table.length << ' ' << largest_fitted_table.width << endl;
}