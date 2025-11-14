from time import sleep
import random

BOARD_SIZE = 35
LADDERS = {
  2: 9,
  11: 28,
  19: 31
}
SNAKES = {
  12: 4,
  27: 13,
  30: 20
}


def roll_die():
  return random.randint(1, 6)


def setup_game():
  print("Liam Grey - 22467895\n\n")

  print("Game is starting...")
  sleep(0.5)

  # p2 is the computer
  players = {"p1": 1, "p2": 1}  # name: position
  suggestions = 3

  turn = random.choice(list(players.keys()))
  print(f"{turn} will move first", end="\n\n")

  return players, suggestions, turn


def handle_move_suggestion(currPlayerPos, roll, suggestions, turn):
  if turn == "p1" and suggestions > 0:
    useSuggestion = input(
        f"You have {suggestions} remaining suggestions, do you want to use one? (y/n): ")
    if useSuggestion == "y":
      suggestions -= 1

      newPos = currPlayerPos + roll

      if newPos in SNAKES:
        print("You would have hit a snake, rolling again...")
        sleep(0.5)
        while newPos in SNAKES:
          roll = roll_die()
          newPos = currPlayerPos + roll

      elif newPos in LADDERS:
        print("You will hit a ladder, moving player...")
        sleep(0.5)
      else:
        print("Safe to move, moving player...")

  return roll, suggestions


def move_player(currentPos, roll, turn):
  print(f"{turn} moves {roll} spaces")

  newPos = currentPos + roll

  if newPos in LADDERS:
    finalPos = LADDERS[newPos]

    diff = finalPos - newPos
    print(f"Hit a ladder! - moved {diff} spaces forwards")
  elif newPos in SNAKES:
    finalPos = SNAKES[newPos]

    diff = newPos - finalPos
    print(f"Hit a snake! - moved {diff} spaces backwards")
  else:
    finalPos = newPos

  return finalPos


def main():
  players, suggestions, turn = setup_game()
  playing = True

  while playing:
    currPlayerPos = players.get(turn)

    if turn == "p1":
      print("-- Your turn --")
      input("Press enter to roll the die...")
    else:
      # computer playing
      print("-- Opponents turn --")

    sleep(0.5)
    initialRoll = roll_die()
    print(f"{turn} rolled a {initialRoll}")
    sleep(0.3)

    finalRoll, suggestions = handle_move_suggestion(currPlayerPos, initialRoll,
                                                    suggestions,
                                                    turn)
    players[turn] = move_player(currPlayerPos, finalRoll, turn)

    if players[turn] >= BOARD_SIZE:
      print(f"Game over, {turn} wins")
      playing = False
    else:
      turn = "p1" if turn == "p2" else "p2"
      print("")


if __name__ == "__main__":
  main()
