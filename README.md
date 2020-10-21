# comp2113-gp-proposal
1. Team Members    
Zheng Yike, UID:  3035637541  
Liu Yiming, UID: 3035637539    
2. Game description  
Name: Gomoku   
Description: Gomoku is a board game with 2 players. It is usually played with Go pieces (black and white chess) on a 15×15 Go board.  
Rule: The two players use circle ('o') and cross ('x') signs respectively. They place one sign each turn by typing the coordinates of cells alternatively. For each round, the player could choose to place a sign, recall some steps (trace back to the previous state of the board), or skip his turn. The order of the two players is determined by the computer randomly. The first player uses circle signs and the second player uses cross signs. Every sign should be placed at one empty cell of the board. Anyone who first forms a row of 5 same signs will be the winner and the game is terminated.   
3. Features 
  1. Generation of random game sets or events  
    1. We will use random functions to determine the play order of the two players.  
    2. The algorithms for AI player will contain random functions based on calculated optimal choices.  
  2. Data structures for storing game status   
    1. We will use class to store the information of each sign on the board containing the position of row, column and type.  
    2. We will use class to store the information of the board, including the length and width of the board and the position of the last piece.  
  3. Dynamic memory management  
    1. By the function of recalling some steps, we will realize dynamic memory management.  
  4. File input/output (e.g., for loading/saving game status)  
    1. If legal coordinates are inputted or recalled, we refresh and display the updated chessboard by adding the coordinates into the class containing current board information.  
  5. Program codes in multiple files  
    1. We will use multiple files to realize multiple functions like 'generate chessboard', 'judge state of the game', 'strategy of AI player', 'judge legality', etc.  
