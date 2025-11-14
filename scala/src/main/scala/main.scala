@main
def main(): Unit = {
  println("Liam Grey - 22467895\n\n")

  val players = Array(
    new HumanPlayer("p1", 1, 3),
    new ComputerPlayer("p2", 1, 0)
  )

  val game = new Game(players)
  game.start()
}
