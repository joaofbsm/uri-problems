"""https://www.urionlinejudge.com.br/judge/pt/problems/view/1487"""

# Choose atraction with better cost benefit given the restriction of time remaining
def choose_best_attraction(attractions, time_remaining):
    for cost_benefit, attraction_duration, attraction_score in attractions:
        if attraction_duration <= time_remaining:
            return attraction_score, time_remaining - attraction_duration

    return 0, time_remaining


def main():
    # Read indefinite number of instances. Stop when num_attractions equals 0.
    instance_number = 1
    while True:
        num_attractions, time_available = [int(i) for i in input().split()]
        if num_attractions == 0:
            break

        time_remaining = time_available
        total_score = 0

        # Store atractions together with their cost benefit (score/minute)
        attractions = []
        for _ in range(num_attractions):
            attraction_duration, attraction_score = [int(i) for i in input().split()]
            cost_benefit = attraction_score / attraction_duration
            attractions.append((cost_benefit, attraction_duration, attraction_score))

        # Order list in decreasing order of cost_benefit
        attractions.sort(key=lambda x: x[0], reverse=True)

        # Choose best attractions until time limit is reached
        while True:
            chosen_score, time_remaining = choose_best_attraction(attractions, time_remaining)
            if chosen_score == 0:
                break
            else:
                total_score += chosen_score

        print('Instancia {}\n{}\n'.format(instance_number, total_score))

        instance_number += 1


if __name__ == '__main__':
    main()