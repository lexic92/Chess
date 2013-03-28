/* 
 * File:   King.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:25 PM
 */


#include "King.h"
using namespace std;


/*static*/
bool King::Test(ostream & os)
{
	os << "\n\n================== TESTING KING ============= " << endl;
	bool success = true;
	
	return success;
}
/*DONE*/
/*virtual*/
list<Move> King::GetPossibleMovesRegardlessOfCheck(const Cell myCell, Piece *** board)
{
	list<Move> s;
	Cell dest(myCell); //dest is a cell that I will continually update.
	
	//Find info for each direction relative to where the King is at.
	//The destination cell starts in the position 1 up and 1 left from the
	//king, and then goes clockwise around the king.
	
	//NOTE: This is the same pattern no matter what color it is. (As opposed to Pawns.)
	
	dest.UpLeft();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Right();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Right();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Down();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Down();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Left();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Left();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	dest.Up();
	AddMoveToListIfValid(s, myCell, dest, board);
	
	return s;
}
/*DONE*/
void King::AddMoveToListIfValid(list<Move> & moves, Cell myCell, Cell dest, Piece *** board)
{
	//CASE 1: Destination cell is not a valid board location.
	//In this case, don't add a move for that destination.
	if(!dest.IsOnTheBoard())
	{
		return;
	}
	
	Piece * otherPiece = board[dest.GetRow()][dest.GetColumn()];
	
	//CASE 2: Destination cell does not have any piece there. (it points to NULL.)
	if(otherPiece == NULL)
	{
		Move m(type, color, myCell, NOTYPE, NOCOLOR, dest);
		moves.push_back(m);
		return;
	}
	
	//CASE 3: Destination cell has a piece that's your own color. 
	//(Then don't add a move for that destination.)
	if(otherPiece->GetColor() == color)
	{
		return;
	}
	
	//CASE 4: You captured somebody! Good for you!!!! :]
	Move m(type, color, myCell, otherPiece->GetType(), otherPiece->GetColor(), dest);
	moves.push_back(m);
}

/*DONE*/
King::King(PieceColor color) : Piece(KING, color)
{
	//does nothing
}