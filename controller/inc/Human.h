/* 
 * File:   Human.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:13 PM
 */

#ifndef HUMAN_H
#define	HUMAN_H
#include "IChessPlayer.h"
#include "IChessView.h"
//Standard library stuff
#include <iostream>
using namespace std;

class Human : public IChessPlayer
{
public:
	/*
	 Constructor
	 */
	Human(PieceColor color, Facade * facade);
	
	
	/*
	 Human selects a chess move.
	 
	 1. If(first selection)
		Get that piece's possible moves.
		Highlight them.
	 Else
		If the cell is a possible move
			 Move (also updating the Model)
			 Unhighlight all highlighted pieces
			 CHANGE TURNS
         */
	void on_CellSelected(int row, int col, int button);
	
          /*
        * Does nothing.
        */
	void on_TimerEvent();
        
          /*
         Tests the Human class
         */
	static bool Test(ostream & os);
	
	/*
	 Sets the view.
	 */
	void SetView(IChessView * view);
	
private:
	bool firstSelection;
	PieceColor color;
	Facade * facade;
	IChessView * view;
	list<Move> validMoves;
	Cell startCell;
	
	void FirstSelection(int row, int col);
	void SecondSelection(int row, int column);
	
	/*
	 Makes a move,
	 Updates the view to reflect the move,
	 and clears the validMoves list for future use.
	 */
	void MoveAndUpdateView(Move m);
	
	
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

#endif	/* HUMAN_H */

