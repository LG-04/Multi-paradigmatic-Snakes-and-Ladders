abstract class Player(private val _name : String, private val _startingPosition : Int, private val _suggestions : Int) {
  
  protected val name: String = _name
  protected var position: Int = _startingPosition
  protected var suggestions: Int = _suggestions

  def move(roll : Int) : Unit = {
    println(name + " moves " + roll + " spaces")
    
    val newPos = position + roll
    var finalPos = newPos
    
    if (GameBoard.isInLadders(newPos)) {
      finalPos = GameBoard.getLadderEnd(newPos)
      val diff = finalPos - newPos 
      println("Hit a ladder! - moved " + diff + " spaces forwards")
    }
    else if (GameBoard.isInSnakes(newPos)) {
      finalPos = GameBoard.getSnakeEnd(newPos)
      val diff = newPos - finalPos
      println("Hit a snake! - moved " + diff + " space backwards")
    }
    
    position = finalPos
  }
  
  def handleMoveSuggestion(initialRoll : Int): Int
  
  def getName: String = name
  def getPosition : Int = position
  def getSuggestions : Int = suggestions
}
