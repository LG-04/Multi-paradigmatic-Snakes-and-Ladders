class ComputerPlayer(private val _name: String, private val _startingPosition: Int, private val _suggestions: Int) extends Player(_name, _startingPosition, _suggestions) {

  override def handleMoveSuggestion(initialRoll: Int): Int = initialRoll
}
