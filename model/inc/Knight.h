/* 
 * File:   Knight.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:29 PM
 */

#ifndef KNIGHT_H
#define	KNIGHT_H
#include "Piece.h"
#include <iostream>
using namespace std;

class Knight : public Piece
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
	Knight(PieceColor color);
private:
	/*
	 Note: This is the exact same as King's, since they both hop to their location.
	 */
	void AddMoveToListIfValid(list<Move> & moves, Cell myCell, Cell dest, Piece *** board);
};



#endif	/* KNIGHT_H */

