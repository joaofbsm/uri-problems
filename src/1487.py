"""https://www.urionlinejudge.com.br/judge/pt/problems/view/1487"""


def main():
    instance_number = 1
    while True:
        num_attractions, time_available = [int(i) for i in input().split()]

        if num_attractions == 0:
            break
        time_remaining = time_available

        smallest_duration = 999999

        total_score = 0
        attractions = []
        for _ in range(num_attractions):
            attraction_duration, attraction_score = [int(i) for i in input().split()]
            cost_benefit = attraction_score / attraction_duration
            attractions.append((cost_benefit, attraction_duration, attraction_score))
            if attraction_duration < smallest_duration:
                smallest_duration = attraction_duration

        # Order list in decreasing order of cost_benefit
        attractions.sort(key=lambda x: x[0], reverse=True)

        last_index = 0

        while time_remaining >= smallest_duration:
            for i in range(last_index, len(attractions)):
                a = attractions[i]
                if a[1] <= time_remaining:
                    total_score += a[2]
                    time_remaining -= a[1]
                    last_index = i

                    break

        print('Instancia {}\n{}\n'.format(instance_number, total_score))

        instance_number += 1


if __name__ == '__main__':
    main()
