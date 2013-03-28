/* 
 * File:   Rook.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:26 PM
 */

#ifndef ROOK_H
#define	ROOK_H
#include "Piece.h"
#include <iostream>
using namespace std;
class Rook : public Piece
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
	Rook(PieceColor color);
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
};


#endif	/* ROOK_H */

