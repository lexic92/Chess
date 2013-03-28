/* 
 * File:   Piece.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:25 PM
 */

#ifndef PIECE_H
#define	PIECE_H

#include <list>
#include "Move.h" //Also uses "MyDefines.h" which Move.h has
#include "UnitTest.h"
class Piece
{
public:
	//Note: No test method because you can't make Piece objects.
	
	/*
	 Tests this class
	 */
	static bool Test(ostream & os);
	
	
	/*
	 Destructor 
	 (Virtual so that if the other pieces decide to have a destructor,
	 they'll work.)
	 */
	virtual ~Piece();
	
	
	
	/*
	 Gets legal moves (valid moving to an empty square, or valid capturing of the
	 opponents pieces, EVEN IF YOUR KING CAN GET CAPTURED ON THE NEXT TURN. It doesn't care.
	 
	 It's virtual because it's different depending on what type of piece you're referring to.
	 It's not PURE virtual because when I tried that I couldn't instantiate any 
	 derived pieces.
	 
	 PARAMETERS:
	 Cell cell:  The location of the piece you're calling this method on.
	 Piece * boardPointer: A pointer to the board (in ChessBoard class) so the piece you
		 call this method on can find out what other pieces are on the board.
	 */
	virtual list<Move> GetPossibleMovesRegardlessOfCheck(Cell cell, Piece *** boardPointer);
	
	
	
	
	/*
	 Return its type.
	 I think it's ok to put this in the header because it doesn't depend
	 on any other headers.
	 */
	PieceType GetType();
	
	
	
	
	
	/*
	 Return its color.
	 I think it's ok to put this in the header because it doesn't depend
	 on any other headers.
	 */
	PieceColor GetColor();
	
	
	
	
	
	
	/*
	 Constructor (that all pieces have in common)
	 */
	Piece(PieceType type, PieceColor color);
	
	
	
	
protected:
	PieceType type;
	PieceColor color;
	
};


#endif	/* PIECE_H */

