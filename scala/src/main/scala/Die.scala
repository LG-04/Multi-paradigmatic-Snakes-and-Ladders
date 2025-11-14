import scala.util.Random

object Die {

  def roll(): Int = {
    new Random().between(1, 7)
  }
}
