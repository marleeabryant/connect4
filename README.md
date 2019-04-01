# connect4

# by Marlee Bryant

# tutorial video link: 

# To run the program type "make" into the command line once you are inside the directory
# After the program compiles without errors (which it should) type "make test" into the command line

# The opening screen should now appear, prompting you to enter a 1 for user v user game mode or a 2 for user v computer
# After you enter a 1 or a 2, the appropriate game mode is entered into
# You are now prompted for a height, so enter a number (40 and less displays properly on my screen) then press enter
# You are now prompted for a width, so enter a number (80 and less displays properly on my screen) then press enter

# The board should now be displayed, with an asterick at the top of the first column
# The top row of the board is an extra for column selection, so pieces cannot be placed in this row
# The red player starts in both game mode, and this is the user in user v computer mode
# At any point the game can be quit by pressing x, which will lead to a prompt of whether you would like to play again

# Press r to move the asterick right and l to move the asterick left
# When the asterick is above the column you'd like to place a piece in, press y and an R will appear in the lowest open space in the column
# For user v user mode, the black player will now go through the same process to make a play, and a B will appear instead of an R
# In user v computer mode, the computer will automatically make it's move
# This move will be represented by a B in the space the computer has selected

# The computer will first look for a move allowing it to win, and play it if it exists
# Next it will see if you are one move away from winning, and if so play in that space to block you
# If neither of these scenarios exist, it will make the move that seems the most advantageous
# It does so by placing a temporary piece in every column and seeing which results in the longest sequence of pieces

# If 4 in a row is achieved by either player, the board will be cleared so a winning message can be printed
# This message says which player won and the amount of times each player has won in the match
# If the board fills before either player gets 4 in a row, the board will clear so a tie message can be printed
# Once again both players scores in the match are printed

# You are now prompted whether you would like to play again, so enter y for yes or n for no, which will immediately terminate the program
# If you entered y, you will be prompted to enter a height and width again and a new board will be displayed with these dimensions
# For as long as you continue playing (pressing y when prompted), the score for the match will be recorded and displayed after every turn
