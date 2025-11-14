import scala.io.StdIn.readLine

class HumanPlayer(private val _name: String, private val _startingPosition: Int, private val _suggestions: Int) extends Player(_name, _startingPosition, _suggestions) {

  override def handleMoveSuggestion(initialRoll: Int): Int = {
    var finalRoll = initialRoll

    if (suggestions > 0) {
      val useSuggestion = readLine("You have " + suggestions + " remaining suggestions, do you want to use one? (y/n): ")

      if (useSuggestion == "y") {
        suggestions -= 1

        var newPos = getPosition + initialRoll

        if (GameBoard.isInSnakes(newPos)) {
          println("You would have hit a snake, rolling again...")

          while (GameBoard.isInSnakes(newPos)) {
            finalRoll = Die.roll()
            newPos = position + finalRoll
          }
        }
        else if (GameBoard.isInLadders(newPos)) {
          println("You will hit a ladder, moving player")
        }
        else {
          println("Safe to move, moving player...")
        }

        Thread.sleep(500)
      }
    }

    finalRoll
  }
}
