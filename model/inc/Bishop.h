/* 
 * File:   Bishop.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:30 PM
 */

#ifndef BISHOP_H
#define	BISHOP_H
#include "Piece.h"
#include <iostream>
using namespace std;

class Bishop : public Piece
{
public:
	/*
	 Tests this class
	 */
	static bool Test(ostream & os);
	
	/*virtual*/
	list<Move> GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board);
	
	/*virtual*/ 
	PieceType GetType();
	
	/*
	 Constructor
	 */
	Bishop(PieceColor color);
	
private:
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



#endif	/* BISHOP_H */

