# Simulate a sports tournament

import csv
import sys
import random
import math

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            row['rating'] = int(row['rating'])
            teams.append(row)

    counts = {}
    for simulation in range(N):
        victor = simulate_tournament(teams)
        if victor in counts:
            counts[victor] += 1
        else:
            counts[victor] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    champ = teams
    # 2 ^ number of rounds = number of teams. log_2(number of teams) = number of rounds
    for round in range(int(math.log2(len(champ)))):
        champ = simulate_round(champ)
    return champ[0]['team']


if __name__ == "__main__":
    main()
