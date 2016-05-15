COSC2451 - Programming Techniques

Assignment 2 - Poker Card Game

Variation: Five-card draw

Rules:

Each player starts with 3000 chips. At the start of each round, the players must place an ante. The initial ante increases after every 4 rounds. The initial ante is maxed at 1000.

Each round has 4 phases as follow: Betting phase one, change card phase, betting phase 2, showdown phase.

Betting phases: ends when all the player have call, check or all in, or other players fold and there is a winner (in this case other phases are skipped). Each player is allowed to raise once. Unless the player with the status RAISE gets challenge by another raise (in this case the player can raise again), the betting phase ends when other players call or fold.

Change card phase: The player is allowed to change at most 3 cards. The AI players are allowed to change any number of cards in their hands.

Showdown phase: The player with the best hands win the pot and the round ends. In the case where the winner all in and there is a side pot (which contain the bets from other players after the winner all in), the chips in the side pot will be returned to the respective players.

--------------------------------------------------------------------------------
