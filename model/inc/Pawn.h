/* 
 * File:   Pawn.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:21 PM
 */

#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
#include <iostream>
using namespace std;

class Pawn : public Piece
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
	Pawn(PieceColor color);
	
private:
	/*
	  These add valid moves to "moves" depending on if a pawn is a certain color.
	 */
	void AddPossibleMovesIfBlack(list<Move> & moves, Cell myCell, Piece *** board);
	void AddPossibleMovesIfWhite(list<Move> & moves, Cell myCell, Piece *** board);
	/*
	 These add valid moves to "moves" depending on if a pawn can capture in
	 a particular direction. (If there's a piece there and it's not the same color.)
	 */
	void CheckDownwardLeft(list<Move> & moves, Cell myCell, Piece *** board);
	void CheckDownwardRight(list<Move> & moves, Cell myCell, Piece *** board);
	void CheckUpwardLeft(list<Move> & moves, Cell myCell, Piece *** board);
	void CheckUpwardRight(list<Move> & moves, Cell myCell, Piece *** board);
};


#endif	/* PAWN_H */

