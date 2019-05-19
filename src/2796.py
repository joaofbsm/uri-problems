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


def main():
    n, m = [int(i) for i in input().split()]

    house_plant = []

    for _ in range(n):
        house_plant.append(list(input()))

    tables = []

    # Read all tables
    for i in range(int(input())):
        c, l = [int(i) for i in input().split()]
        tables.append((c * l, c, l))  # Add area as a component

    # Sort tables by area and use width as tiebreaker
    tables.sort(key=lambda x: (x[0], x[2]), reverse=True)

    max_areas = get_max_areas(n, m, house_plant)

    print(*find_largest_table(tables, max_areas))


if __name__ == '__main__':
    main()
