/* 
 * File:   Queen.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:30 PM
 */

#ifndef QUEEN_H
#define	QUEEN_H
#include "Piece.h"
#include <iostream>
using namespace std;

class Queen : public Piece
{
public:
	/*
	 Tests this class
	 */
	static bool Test(ostream & os);	
	
	/*virtual*/
	list<Move> GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board);
	
	/*
	 Constructor
	 */
	Queen(PieceColor color);
private:
	/*
	 The following functions look for moves that are upward, downward, left, and right,
	 respectively. Each checks for all 4 conditions: empty, capture, your color, 
	 or off the board.
	 */
	void AddMovesAbove(list<Move> & moves, Cell myCell, Piece *** board);
	void AddMovesBelow(list<Move> & moves, Cell myCell, Piece *** board);
	void AddMovesLeft(list<Move> & moves, Cell myCell, Piece *** board);
	void AddMovesRight(list<Move> & moves, Cell myCell, Piece *** board);
	
	/*
	 The following functions look for moves that are diagonally upleft, upright, 
	 downleft, and downright, respectively. Each checks for all 4 conditions: 
	 empty, capture, your color, or off the board.
	 */
	void AddMovesUpLeft(list<Move> & moves, Cell myCell, Piece *** board);
	void AddMovesUpRight(list<Move> & moves, Cell myCell, Piece *** board);
	void AddMovesDownLeft(list<Move> & moves, Cell myCell, Piece *** board);
	void AddMovesDownRight(list<Move> & moves, Cell myCell, Piece *** board);
};



#endif	/* QUEEN_H */

