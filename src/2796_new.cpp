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

    Space(int length, int width)    {
        this->area = length * width;
        this->length = length;
        this->width = width;
    }

    Space(int area, int length, int width) {
        this->area = area;
        this->length = length;
        this->width = width;
    }

};

// House plant dimensions
int n, m;
int memo[1000][1000];
int max_extension_per_dim[1001];
vector<Space> large_spaces;


// Sort array of Space objects first by area and then by width
bool comp_tiebreaker(Space const& A, Space const& B) {
    return (A.area > B.area) || ((A.area == B.area) && (A.width >= B.width));
}


// Sort array of Space objects first by area
bool comp(Space const& A, Space const& B) {
    return (A.area > B.area);
}

// Find all the useful empty spaces
int find_large_spaces(int smallest_table_area, int smallest_table_dim) {
    for (int i = n - 1; i >= 0; i--) {
    	int max_area, max_length, max_width, max_dim, min_dim, cur_area, cur_length, cur_width, starting_pos;
        max_area = 0;
        max_length = 0;
        max_width = 0;
        starting_pos = 0;

        stack<int> s;

        cout << i << endl;

        for (int j = 0; j < m; j++) {
        	if ((s.empty()) or (memo[i][j] > memo[i][s.top()])) {
        		if (memo[i][j] > 0) {
        			s.push(j);
        		}
        	}
        	else if (memo[i][j] < memo[i][s.top()]) {
        		while ((!s.empty()) and (memo[i][j] < memo[i][s.top()])) {
        			starting_pos = s.top();
        			cur_length = j - starting_pos;
        			cur_width = memo[i][starting_pos];
        			cur_area = cur_length * cur_width;
        			s.pop();

        			if (cur_length > cur_width) {
		                min_dim = cur_width;
		                max_dim = cur_length;
		            }
		            else {
		                min_dim = cur_length;
		                max_dim = cur_width;
		            }
		            cout << j << ' ' << starting_pos << endl;
		            if (s.empty()) {
		            	cout << cur_area << ' ' << cur_length << ' ' << cur_width << endl << endl;
		            }
		            else {
		            	cout << cur_area << ' ' << cur_length << ' ' << cur_width << ' ' << s.top() << endl << endl;
		            }

		            if ((cur_area >= smallest_table_area) and
		                (min_dim >= smallest_table_dim) and
		                (max_dim > max_extension_per_dim[min_dim]) and
		                (min_dim > max_extension_per_dim[max_dim])) {

                		large_spaces.push_back(Space(cur_area, cur_length, cur_width));

		                for (int k = min_dim; k > 0; k--) {
		                    if (max_extension_per_dim[k] < max_dim) {
		                        max_extension_per_dim[k] = max_dim;
		                    }
		                    else {
		                        break;
		                    }
		                }

		                for (int k = max_dim; k > min_dim; k--) {
		                    if (max_extension_per_dim[k] < min_dim) {
		                        max_extension_per_dim[k] = min_dim;
		                    }
		                    else {
		                        break;
		                    }
		                }

        				//cout << cur_area << ' ' << cur_length << ' ' << cur_width << endl;
        			}
        		}
        		if (s.empty()) {
        			s.push(starting_pos);
        		}
        	}
        }

        while (!s.empty()) {
			starting_pos = s.top();
			cur_length = m - starting_pos;
			cur_width = memo[i][starting_pos];
			cur_area = cur_length * cur_width;
			s.pop();

			if (cur_length > cur_width) {
                min_dim = cur_width;
                max_dim = cur_length;
            }
            else {
                min_dim = cur_length;
                max_dim = cur_width;
            }

            cout << cur_area << ' ' << cur_length << ' ' << cur_width << endl << endl;

            if ((cur_area >= smallest_table_area) and
                (min_dim >= smallest_table_dim) and
                (max_dim > max_extension_per_dim[min_dim]) and
                (min_dim > max_extension_per_dim[max_dim])) {

        		large_spaces.push_back(Space(cur_area, cur_length, cur_width));

                for (int k = min_dim; k > 0; k--) {
                    if (max_extension_per_dim[k] < max_dim) {
                        max_extension_per_dim[k] = max_dim;
                    }
                    else {
                        break;
                    }
                }

                for (int k = max_dim; k > min_dim; k--) {
                    if (max_extension_per_dim[k] < min_dim) {
                        max_extension_per_dim[k] = min_dim;
                    }
                    else {
                        break;
                    }
                }

				//cout << cur_area << ' ' << cur_length << ' ' << cur_width << endl;
			}
        }
    }
}


Space find_largest_table_fit(vector<Space> tables, vector<Space> large_spaces, Space largest_table) {
    bool is_table_fit[tables.size()];
    memset(is_table_fit, 0, sizeof(is_table_fit));
    int tables_to_fit = tables.size();

    Space table;
    Space largest_fitted_table = Space(0, 0, 0);

    // Get largest dimension found in spaces to prevent processing of larger tables
    int largest_space_dim = 0;
    for (auto space: large_spaces) {
        if (space.length > largest_space_dim) {
            largest_space_dim = space.length;
        }
        if (space.width > largest_space_dim) {
            largest_space_dim = space.width;
        }
    }

    for (auto space: large_spaces) {
        for (int i = 0; i < tables.size(); i++) {
            // Only execute if table has not been fit yet
            if (is_table_fit[i] == 0) {
                table = tables[i];

                // Table cannot fit in any space. Mark as fit to prevent future processing.
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

                // Initial fit check to reduce overhead
                if (table.area <= space.area) {
                    // Simulates 90 degree rotation
                    if (((table.length <= space.length) and (table.width <= space.width)) or
                        ((table.width <= space.length) and (table.length <= space.width))) {
                        if (table.area >= largest_fitted_table.area) {
                            // Table is the largest possible
                            if ((table.area == largest_table.area) and (table.width == largest_table.area) and (table.length == largest_table.length)) {
                                    return largest_table;
                            }

                            // Tiebreaker if area is the same as previous largest
                            if (table.area == largest_fitted_table.area) {
                                if (table.width > largest_fitted_table.width) {
                                    largest_fitted_table = table;
                                }
                            }
                            // Table has a bigger area
                            else {
                                largest_fitted_table = table;
                            }
                        }

                        // Table has been fit
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
	// Makes the IO operations insanely faster
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    // Read house dimensions
    cin >> n >> m;

    // memset(max_extension_per_dim, 0, sizeof(max_extension_per_dim));
    memset(memo, 0, sizeof(memo));

    // Read the house already creating the memoization structure to compute the max histogram area
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

           cout << memo[i][j];
        }
        cout << endl;
    }

    // Variables used to read and store the tables
    int num_tables, cur_area, cur_length, cur_width;
    vector<Space> tables;

    // Values used to reduce the search space and make the solution more efficient
    int smallest_table_dim = 1000;
    int smallest_table_area = 1000000;
    Space largest_table = Space(0, 0, 0);

    // Read all tables as Space objects
    cin >> num_tables;
    for (int i = 0; i < num_tables; i++) {
        cin >> cur_length >> cur_width;
        cur_area = cur_length * cur_width;
        Space cur_table = Space(cur_area, cur_length, cur_width);
        tables.push_back(cur_table);

        // Update largest table if necessary
        if (cur_area >= largest_table.area) {
            if (cur_area == largest_table.area) {
                if (cur_width > largest_table.width) {
                    largest_table = cur_table;
                }
            }
            else {
                largest_table = cur_table;
            }
        }

        // Save smallest area and dimensions found
        if (cur_area < smallest_table_area) {
            smallest_table_area = cur_area;
        }

        if (cur_length < smallest_table_dim) {
            smallest_table_dim = cur_length;
        }
        if (cur_width < smallest_table_dim) {
            smallest_table_dim = cur_width;
        }
    }


    //cout << largest_table.area << ' ' << largest_table.length << ' ' << largest_table.width << endl << smallest_table_area << ' ' << smallest_table_dim << endl;

    // Get the largest spaces using the max histogram heuristic
    find_large_spaces(smallest_table_area, smallest_table_dim);

    // Sort spaces using the same comparison used for tables
    sort(large_spaces.begin(), large_spaces.end(), comp_tiebreaker);

    // for (auto const& t: large_spaces) {
    //    cout << t.area << ' ' << t.length << ' ' << t.width << '\n';
    // }

    // Find the largest table that fits any of these spaces
    Space largest_fitted_table = find_largest_table_fit(tables, large_spaces, largest_table);

    cout << largest_fitted_table.length << ' ' << largest_fitted_table.width << endl;

}