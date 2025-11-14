package main

import (
	"fmt"
	"math/rand"
	"time"
)

const BOARD_SIZE int = 35

var LADDERS = map[int]int{
	2:  9,
	11: 28,
	19: 31,
}

var SNAKES = map[int]int{
	12: 4,
	27: 13,
	30: 20,
}

type Player struct {
	name     string
	position int
}

func rollDie() int {
	return rand.Intn(6) + 1
}

func setupGame() (players []Player, suggestions int, turn int) {
	fmt.Println("Game is starting...")
	time.Sleep(500 * time.Millisecond)

	players = []Player{
		{"p1", 1},
		{"p2", 1},
	}

	suggestions = 3
	turn = rand.Intn(2)

	fmt.Printf("%s will move first\n\n", players[turn].name)

	return players, suggestions, turn
}

func handleMoveSuggestion(currentPlayerPos int, roll int, suggestions int, turn int) (finalRoll int, updatedSuggestions int) {
	finalRoll = roll
	updatedSuggestions = suggestions

	if turn == 0 && suggestions > 0 {
		var useSuggestion string
		fmt.Printf("You have %d remaining suggestions, do you want to use one? (y/n): ", suggestions)
		fmt.Scanln(&useSuggestion)

		if useSuggestion == "y" {
			updatedSuggestions = suggestions - 1

			newPos := currentPlayerPos + roll

			if _, ok := SNAKES[newPos]; ok {
				fmt.Println("You would have hit a snake, rolling again...")
				time.Sleep(500 * time.Millisecond)
				for {
					finalRoll = rollDie()
					newPos = currentPlayerPos + finalRoll

					if _, ok := SNAKES[newPos]; !ok {
						break
					}
				}
			} else if _, ok := LADDERS[newPos]; ok {
				fmt.Println("You will hit a ladder, moving player...")
				time.Sleep(500 * time.Millisecond)
			} else {
				fmt.Println("Safe to move, moving player...")
			}
		}
	}

	return finalRoll, updatedSuggestions
}

func movePlayer(players []Player, currentPlayerPos int, roll int, turn int) (finalPos int) {
	fmt.Printf("%s moves %d spaces\n", players[turn].name, roll)

	newPos := currentPlayerPos + roll

	if _, ok := LADDERS[newPos]; ok {
		finalPos = LADDERS[newPos]

		diff := finalPos - newPos
		fmt.Printf("Hit a ladder! - moved %d spaces forwards\n", diff)
	} else if _, ok := SNAKES[newPos]; ok {
		finalPos = SNAKES[newPos]

		diff := newPos - finalPos
		fmt.Printf("Hit a snake! - moved %d spaces backwards\n", diff)
	} else {
		finalPos = newPos
	}

	return finalPos
}

func main() {
	rand.Seed(time.Now().UnixNano())

	players, suggestions, turn := setupGame()
	playing := true

	for playing {
		currentPlayerPos := players[turn].position

		if turn == 0 {
			fmt.Println("-- Your turn --")
			fmt.Println("Press enter to roll the die...")
			fmt.Scanln()
		} else {
			fmt.Println("-- Opponents turn --")
		}

		time.Sleep(500 * time.Millisecond)
		initialRoll := rollDie()
		fmt.Printf("%s rolled a %d\n", players[turn].name, initialRoll)
		time.Sleep(300 * time.Millisecond)

		finalRoll, updatedSuggestions := handleMoveSuggestion(currentPlayerPos, initialRoll, suggestions, turn)
		suggestions = updatedSuggestions
		players[turn].position = movePlayer(players, currentPlayerPos, finalRoll, turn)

		if players[turn].position >= BOARD_SIZE {
			fmt.Printf("Game over, %s wins\n", players[turn].name)
			playing = false
		} else {
			turn = 1 - turn
			fmt.Printf("\n")
		}
	}
}
