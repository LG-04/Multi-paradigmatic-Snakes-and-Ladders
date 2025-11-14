import scala.io.StdIn.readLine
import scala.util.Random

class Game(private val players : Array[Player]) {

  private var turn : Int = 0
  private var playing = true

  def start(): Unit = {
    setup()
    play()
  }

  private def setup() : Unit = {
    turn = Random().between(0, 2)
  }

  private def play() : Unit = {
    while (playing) {
      val currentPlayer = players(turn)

      if (turn == 0) {
        println("-- Your turn --")
        println("Press enter to roll the die...")
        readLine()
      }
      else {
        println("-- Opponents turn --")
      }

      Thread.sleep(300)
      val initialRoll = Die.roll()
      println(currentPlayer.getName + " rolled a " + initialRoll)
      Thread.sleep(300)

      val finalRoll = currentPlayer.handleMoveSuggestion(initialRoll)
      currentPlayer.move(finalRoll)

      if (currentPlayer.getPosition >= GameBoard.BOARD_SIZE) {
        println("Game over, " + currentPlayer.getName + " wins")
        playing = false
      }
      else {
        turn = 1 - turn
        println()
      }
    }
  }
}
