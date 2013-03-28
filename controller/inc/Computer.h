/* 
 * File:   Computer.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:13 PM
 */

#ifndef COMPUTER_H
#define	COMPUTER_H
#include "IChessPlayer.h"
#include "IChessView.h"
//Standard library stuff
#include <iostream>
using namespace std;

class Computer : public IChessPlayer
{
public:
	/*
	 Constructor
	 */
	Computer(PieceColor color, Facade * facade);
	
	/*
	 Do nothing
         */
	void on_CellSelected(int row, int col, int button);
	
          /*
	 1-3.	StartTimerEvent
	 4.	Pause
	 5-8.	FinishTimerEvent
	*/
	void on_TimerEvent();
	
	/*
	 Sets the view.
	 */
	void SetView(IChessView * view);
        
           /*
         Tests the Computer class
         */
	static bool Test(ostream & os);
	
private:
	PieceColor color;
	Facade * facade;
	IChessView * view;
	list<Move> validMoves;
	list<Cell>::const_iterator cellsEnd; //an iterator like cells.end(), which I'll update.
	Cell startCell;
	int timerCountDown;
	

	/*
	 Makes a move,
	 Updates the view to reflect the move,
	 and clears the validMoves list for future use.
	 */
	void MoveAndUpdateView(Move m);
	
	/*
	 Picks a random move from validMoves, and then does that move.
	 */
	void MoveToRandomCell();
	
	/*
	 Given a set of cells, chooses one randomly and returns a copy of that cell.
	 cells: the list of cells
	 cellsEnd: an iterator to the end (like cells.end(), but it doesn't have to be).
	 */
	Cell ChooseARandomCell(list<Cell> cells, list<Cell>::const_iterator cellsEnd);
	
	/*
	 Given a set of moves, chooses one randomly and returns a copy of that move.
	 moves: the list of moves
	 */
	Move ChooseARandomMove(list<Move> moves);
	
	/*
	 1. Get the set of cells that have pieces.

	 2. While there are cells left...
		Choose a cell randomly.
		Get that cell's valid moves.
		If it has no valid moves,
			remove that cell from the list.
		Else,
			leave the while loop.

	 3. Now that you have a cell with valid moves, highlight them all.  Also, highlight yourself.

	 */
	void StartTimerEvent();
	
	
	
	
	/*
 
	 5. Choose one of the valid moves randomly, and move there. Update the view accordingly.

	 6. Unhighlight yourself and all the other cells.

	 7. Clear the validMoves list for future use.
 
	 8. Check for Checkmate, Stalemate, Check, or Normal.
		If Check or Normal
			Change turns.
	 */
	void FinishTimerEvent();
	
	/*
	 Checks at the end of the turn to see if opponent is in...
	 
	 1. checkmate (opponent is in range	& opponent has no valid moves),
	 2. stalemate (opponent is NOT in range & opponent has no valid moves),
	 3. check     (opponent is in range	& opponent DOES have valid moves),
	 4. [normal]  (opponent is NOT in range	& opponent DOES have valid moves).
	 
	 If the opponent is in checkmate or stalemate, it will display an appropriate 
	 message and end the game (so no one can make moves anymore until a new game is
	 called).
	 
	 If the opponent is in check, it will display an appropriate message, but continue
	 the game.
	 
	 If the opponent is in a normal situation, play will continue without any messages.
	 */
	void CheckForCheckmateStalemateCheckOrNormal();
	
	/*
	 Depending on the booleans, writes a message to TopLabel to describe the state of the
	 game. It also finds out if the game is over, and if so, ends the game.
	 */
	void WriteMessageAndEndGameIfApplicable(bool inRange, bool noValidMoves);
};

#endif	/* COMPUTER_H */

