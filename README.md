COSC2451 - Programming Techniques

Assignment 2 - Poker Card Game

--------------------------------------------------------------------------------

MENU

Single player: choose the number of players and press OK to start the game

Multiplayer: Not supported

Mode: Choose AI level. There are easy and normal.

Quit: Exit the game.

--------------------------------------------------------------------------------

Variation: Five-card draw

RULES

Each player starts with 3000 chips. At the start of each round, the players must place an ante. The initial ante increases after every 4 rounds. The initial ante is maxed at 1000.

Each round has 4 phases as follow: Betting phase one, change card phase, betting phase 2, showdown phase.

Betting phases: ends when all the player have call, check or all in, or other players fold and there is a winner (in this case other phases are skipped). Each player is allowed to raise once. Unless the player with the status RAISE gets challenge by another raise (in this case the player can raise again), the betting phase ends when other players call or fold. The AI players have a delay of two seconds to make their decision. The player's name will turn red when it is their turn. 

Change card phase: The player is allowed to change at most three cards. The AI players are allowed to change any number of cards in their hands.

Showdown phase: The player with the best hands win the pot and the round ends. In the case where the winner all in and there is a side pot (which contain the bets from other players after the winner all in), the chips in the side pot will be returned to the respective players.

--------------------------------------------------------------------------------

PLAYER INPUT

Betting phases: Use Z X C V to do the action that display in each button on the screen. Pressing LEFT and RIGHT arrow keys to adjust the amount of chips for betting and raising. 

Change card phase: Use number keys 1 2 3 4 5 to pick the cards to be changed. The player can only change a maximum of three cards. Then press ENTER to change cards and end this phase.

At the end of a round. Press N to continue the game and start a new round.

When the game is at the player's turn. Press Q to quit the game.

--------------------------------------------------------------------------------

EXTRA FEATURES:

The game can receive input from both keyboard and mouse.

--------------------------------------------------------------------------------

OTHER NOTES:

Save and load functions are not implemented.

Assuming that the screen is never re-sized. Otherwise the display will misbehave or worse, the game is unplayable. It is best to leave the screen size as it is configured.