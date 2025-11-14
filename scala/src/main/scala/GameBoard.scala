object GameBoard {
  
  val BOARD_SIZE = 35

  private val LADDERS = Array(
    new BoardFeature(2, 9),
    new BoardFeature(11, 28),
    new BoardFeature(19, 31)
  )

  private val SNAKES = Array(
    new BoardFeature(12, 4),
    new BoardFeature(27, 12),
    new BoardFeature(30, 20)
  )

  def isInSnakes(position : Int) : Boolean = {
    SNAKES.exists(s => s.getStart == position)
  }

  def getSnakeEnd(startPos : Int) : Int = {
    SNAKES.find(s => s.getStart == startPos).get.getEnd
  }

  def isInLadders(position: Int): Boolean = {
    LADDERS.exists(l => l.getStart == position)
  }

  def getLadderEnd(startPos: Int): Int = {
    LADDERS.find(l => l.getStart == startPos).get.getEnd
  }
}
