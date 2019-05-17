"""https://www.urionlinejudge.com.br/judge/pt/problems/view/1310"""


def mss(receipt_vector, qty_days):
    global_max = current_max = receipt_vector[0]

    for i in range(1, qty_days):
        current_max = max(receipt_vector[i], current_max + receipt_vector[i])

        if current_max > global_max:
            global_max = current_max

    return global_max


while True:
    try:
        qty_days = int(input())
        daily_cost = int(input())
        receipt_vector = []
        for _ in range(qty_days):
            receipt_vector.append(int(input()) - daily_cost)

        print(max(0, mss(receipt_vector, qty_days)))
    except EOFError:
        break
