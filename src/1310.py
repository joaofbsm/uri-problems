"""https://www.urionlinejudge.com.br/judge/pt/problems/view/1310"""


def main():
    while True:
        try:
            qty_days = int(input())
            daily_cost = int(input())

            # Calculate the Max Subarray Sum while reading it for the first time
            global_max = current_max = int(input()) - daily_cost
            for i in range(1, qty_days):
                day_receipt = int(input()) - daily_cost
                current_max = max(day_receipt, current_max + day_receipt)

                if current_max > global_max:
                    global_max = current_max

            # Using this if is faster than using max()
            if 0 > global_max:
                print('0')
            else:
                print(global_max)
        except EOFError:
            break


if __name__ == '__main__':
    main()
