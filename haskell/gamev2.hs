import Control.Concurrent (threadDelay)
import Data.List (find)
import Data.Maybe (isJust)
import System.Random (randomRIO)

data Player = Player {name :: String, position :: Int} deriving (Show)

data BoardFeature = Feature {startPos :: Int, endPos :: Int} deriving (Show)

data GameState = GameState {players :: [Player], suggestions :: Int, turn :: Int} deriving (Show)

boardSize :: Int
boardSize = 35

ladders :: [BoardFeature]
ladders =
  [ Feature {startPos = 2, endPos = 9},
    Feature {startPos = 11, endPos = 28},
    Feature {startPos = 19, endPos = 31}
  ]

snakes :: [BoardFeature]
snakes =
  [ Feature {startPos = 12, endPos = 4},
    Feature {startPos = 27, endPos = 13},
    Feature {startPos = 30, endPos = 20}
  ]

isInLadders :: Int -> Bool
isInLadders position =
  isJust (find (\ladder -> startPos ladder == position) ladders)

isInSnakes :: Int -> Bool
isInSnakes position =
  isJust (find (\snake -> startPos snake == position) snakes)

getLadderEnd :: Int -> Int
getLadderEnd position =
  let feature = find (\ladder -> startPos ladder == position) ladders
   in maybe position endPos feature

getSnakeEnd :: Int -> Int
getSnakeEnd position =
  let feature = find (\snake -> startPos snake == position) snakes
   in maybe position endPos feature

rollDie :: IO Int
rollDie = randomRIO (1, 6)

waitForKey :: IO ()
waitForKey = do
  putStrLn "Press enter to roll..."
  getChar
  return ()

rollUntilSafe :: Int -> IO Int
rollUntilSafe currentPosition = do
  roll <- rollDie
  let newPosition = currentPosition + roll
  if isInSnakes newPosition
    then rollUntilSafe currentPosition
    else return roll

data SuggestionResult
  = SnakeHit
  | LadderHit
  | SafeMove

handleSuggestion :: Int -> GameState -> SuggestionResult
handleSuggestion roll gs
  | isInSnakes newPos = SnakeHit
  | isInLadders newPos = LadderHit
  | otherwise = SafeMove
  where
    newPos = position (players gs !! turn gs) + roll

handleMoveSuggestion :: Int -> GameState -> IO (Int, Int)
handleMoveSuggestion initialRoll gs = do
  if turn gs == 0 && suggestions gs > 0
    then do
      putStr $ "You have " ++ show (suggestions gs) ++ " remaining suggestions, do you want to use one (y/n): "
      useSuggestion <- getLine
      if useSuggestion == "y"
        then do
          let updatedSuggestions = suggestions gs - 1
          let newPos = position (players gs !! turn gs) + initialRoll

          case handleSuggestion initialRoll gs of
            SnakeHit -> do
              putStrLn "You would have hit a snake, rolling again...\n"
              threadDelay 500000
              finalRoll <- rollUntilSafe (position (players gs !! turn gs))
              return (finalRoll, updatedSuggestions)
            LadderHit -> do
              putStrLn "You will hit a ladder, moving player...\n"
              threadDelay 500000
              return (initialRoll, updatedSuggestions)
            SafeMove -> do
              putStrLn "Safe to move, moving player..."
              return (initialRoll, updatedSuggestions)
        else return (initialRoll, suggestions gs)
    else return (initialRoll, suggestions gs)

printTurn :: Int -> Int -> Int -> IO ()
printTurn startPos rolledPos finalPos
  | finalPos < rolledPos = putStrLn $ "Hit a snake! - moved " ++ show diff ++ " spaces backwards\n"
  | finalPos > rolledPos = putStrLn $ "Hit a ladder! - moved " ++ show diff ++ " spaces forwards\n"
  | otherwise = return ()
  where
    diff = abs (rolledPos - finalPos)

calculateFinalPosition :: Int -> Int -> Int
calculateFinalPosition currentPos roll
  | isInSnakes newPos = getSnakeEnd newPos
  | isInLadders newPos = getLadderEnd newPos
  | otherwise = newPos
  where
    newPos = currentPos + roll

performTurn :: Int -> GameState -> GameState
performTurn finalRoll gs =
  let currentPlayer = players gs !! turn gs
      startPos = position currentPlayer

      finalPosition = calculateFinalPosition startPos finalRoll

      updatedPlayer = currentPlayer {position = finalPosition}
      updatedPlayers = take (turn gs) (players gs) ++ [updatedPlayer] ++ drop (turn gs + 1) (players gs)
      nextTurn = (turn gs + 1) `mod` length updatedPlayers
   in GameState {players = updatedPlayers, turn = nextTurn, suggestions = suggestions gs}

gameLoop :: GameState -> IO ()
gameLoop gs = do
  let currentPlayer = players gs !! turn gs

  if turn gs == 0
    then do
      putStrLn "-- Your turn --"
      waitForKey
    else
      putStrLn "-- Opponent's turn --"

  threadDelay 500000
  initialRoll <- rollDie
  putStrLn $ name currentPlayer ++ " rolled a " ++ show initialRoll
  threadDelay 300000

  (finalRoll, updatedSuggestions) <- handleMoveSuggestion initialRoll gs
  putStrLn $ name currentPlayer ++ " moves " ++ show finalRoll ++ " spaces\n"

  let newState = performTurn finalRoll gs

  printTurn
    (position currentPlayer)
    (position currentPlayer + finalRoll)
    (position (players newState !! turn gs))

  if position currentPlayer >= boardSize
    then putStrLn $ "Game over, " ++ name currentPlayer ++ " wins"
    else gameLoop newState

setupGame :: IO GameState
setupGame = do
  putStrLn "Game is starting..."
  threadDelay 500000

  let players = [Player {name = "p1", position = 1}, Player {name = "p2", position = 1}]
  let suggestions = 3

  turn <- randomRIO (0, 1)
  putStrLn $ name (players !! turn) ++ " will move first\n"

  return GameState {players, suggestions, turn}

main :: IO ()
main =
  do
    initialState <- setupGame
    gameLoop initialState