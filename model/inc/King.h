/* 
 * File:   King.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:30 PM
 */

#ifndef KING_H
#define	KING_H
#include "Piece.h"
#include <iostream>
using namespace std;

class King : public Piece
{
public:
	/*
	 Tests this class
	 */
	static bool Test(ostream & os);	
	
	/*
	 See Piece.h
	 */
	/*virtual*/
	list<Move> GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board);
	
	/*
	 Constructor
	 */
	King(PieceColor color);
	
private:
	/*
	 Based on the current state of the board, this function will make a move
	 object containing the King's type, color, and cell, and the opponent's 
	 captured piece's type, color, and cell (if there is an opponent's piece in
	 the destination cell).  Then it will add it to the given list.
	 
	 However, if there is a piece of the King's own color, then it won't add anything
	 because you can't capture your own piece.
	 
	 Also, if a particular move is OFF of the board, it won't add it.
	 
	 If there was no opponent there, it'll still add a move to the list.
	 
	 moves: a reference to the list you want to add the move to.
	 myCell: The cell that the King is currently at.
	 dest: The cell in question, where the king might move.
	 board: a pointer to the board (which is in the heap).
	 */
	void AddMoveToListIfValid(list<Move> & moves, Cell myCell, Cell dest, Piece *** board);
};



#endif	/* KING_H */

