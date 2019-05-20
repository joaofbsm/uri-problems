"""https://www.urionlinejudge.com.br/judge/pt/problems/view/2796"""

from collections import deque


def find_max_area(row):
    s = deque()
    max_area = 0
    max_height = 0
    max_width = 0

    for i in range(len(row)):
        while s and row[s[-1]] > row[i]:
            height = row[s.pop()]
            if not s:
                width = i
            else:
                width = i - s[-1] - 1

            current_area = height * width
            if current_area > max_area:
                max_area = current_area
                max_height = height
                max_width = width

        s.append(i)

    return max_area, max_height, max_width


def get_max_areas(n, m, house_plant):
    # Memoization matrix
    memo = [[] for _ in range(n)]

    # Initialize first row
    for i in range(m):
        if house_plant[0][i] == '.':
            memo[0].append(1)
        else:
            memo[0].append(0)

    # Complete the other rows using memoization
    for i in range(1, n):
        for j in range(m):
            if house_plant[i][j] == '.':
                memo[i].append(memo[i - 1][j] + 1)
            else:
                memo[i].append(0)

    max_areas = []
    for i in range(n):
        current_area, current_height, current_width = find_max_area(memo[i])
        max_areas.append((current_area, current_height, current_width))

    max_areas.sort(key=lambda x: x[0], reverse=True)

    return max_areas


def find_largest_table(tables, max_areas):
    found_fit = [False for _ in range(len(tables))]

    for area, height, width in max_areas:
        for i, fit_found in enumerate(found_fit):
            if not fit_found:
                table_area, table_height, table_width = tables[i]
                if table_area <= area:
                    if (table_height <= height and table_width <= width) or \
                       (table_width <= height and table_height <= width):

                        found_fit[i] = True

    for i, fit_found in enumerate(found_fit):
        if fit_found:
            break

    return tables[i][1], tables[i][2]

def maximal_rectangle(m, n, house_plant, smallest_table_area, smallest_table_dim):

    left = [0] * n # initialize left as the leftmost boundary possible
    right = [n] * n # initialize right as the rightmost boundary possible
    height = [0] * n

    maxarea = 0

    areas = []

    for i in range(m):
        max_area = 0
        max_height = 0
        max_width = 0

        cur_left, cur_right = 0, n
        # update height
        for j in range(n):
            if house_plant[i][j] == '.': height[j] += 1
            else: height[j] = 0
        # update left
        for j in range(n):
            if house_plant[i][j] == '.': left[j] = max(left[j], cur_left)
            else:
                left[j] = 0
                cur_left = j + 1
        # update right
        for j in range(n-1, -1, -1):
            if house_plant[i][j] == '.': right[j] = min(right[j], cur_right)
            else:
                right[j] = n
                cur_right = j
        # update the area
        for j in range(n):
            if max_area < height[j] * (right[j] - left[j]) and smallest_table_area <= height[j] * (right[j] - left[j]) and smallest_table_dim <= height[j] and smallest_table_dim <= (right[j] - left[j]):
                max_area = height[j] * (right[j] - left[j])
                max_height = height[j]
                max_width = (right[j] - left[j])
                areas.append((max_area, max_height, max_width))

            if maxarea < height[j] * (right[j] - left[j]):
                maxarea = height[j] * (right[j] - left[j])

    areas.sort(key=lambda x: x[0], reverse=True)

    return areas


def main():
    n, m = [int(i) for i in input().split()]

    house_plant = []

    for _ in range(n):
        house_plant.append(list(input()))

    tables = []

    smallest_table_dim = 1000
    smallest_table_area = 1000

    # Read all tables
    for i in range(int(input())):
        length, width = [int(i) for i in input().split()]
        tables.append((length * width, length, width))  # Add area as a component

        if (length * width < smallest_table_area):
            smallest_table_area = length * width
        if (length < smallest_table_dim):
            smallest_table_dim = length
        if (width < smallest_table_dim):
            smallest_table_dim = width

    # Sort tables by area and use width as tiebreaker
    tables.sort(key=lambda x: (x[0], x[2]), reverse=True)

    #print(len(maximal_rectangle(n, m, house_plant)))
    #print(maximal_rectangle(n, m, house_plant, smallest_table_area, smallest_table_dim))

    #max_areas = maximal_rectangle(n, m, house_plant, smallest_table_area, smallest_table_dim)

    max_areas = get_max_areas(n, m, house_plant)

    print(max_areas)

    print(*find_largest_table(tables, max_areas))


if __name__ == '__main__':
    main()
