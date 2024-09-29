# MemoryGame
First Project of 2024

A popular children’s game is the Memory game, in which a set of 16 cards containing pairs of matching objects are shuffled and dealt in a 4×4 grid, face down.  
In the solitaire version, a player can turn over any two cards and if they match, can remove them from the board.  Otherwise, they are turned over and the player gets to turn over two more cards.  
The objective is to remove all of the cards as quickly as possible.  For this assignment, you are to write an OpenGL version of this game.  It should have the following properties: 
1. Cards should be picked by pressing down on the left mouse button.
2. You should use some sort of animation to simulate the card being flipped over.
3. Once  two  cards  are  flipped,  you  should  wait  for  a  second  or  two  and  then  either  remove the cards or flip them back over (again, using some simple animation).  You should use the glutTimerFuncton handle the time delay.
4. You should keep track of the number of turns a player has made somewhere on the screen.
5. You should attach a menu to the right mouse button which allows the player to either quit the game, or restart a game.
6. Your program should be robust in that it handles things like clicking on an empty square,clicking on a card already picked, resizing the window, etc.
