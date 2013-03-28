/* 
 * File:   Knight.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:25 PM
 */


#include "Knight.h"
using namespace std;

/*static*/
bool Knight::Test(ostream & os)
{
	os << "\n\n================== TESTING KING ============= " << endl;
	bool success = true;
	
	return success;
}
/*virtual*/
list<Move> Knight::GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board)
{
	list<Move> s;
	
	//List of possible cells where the Knight might be able to go.
	//Starts upperleft and goes clockwise.
	//NOTE: This is the same pattern no matter what color it is. (As opposed to Pawns.)
	
	int x = myCell.GetRow();
	int y = myCell.GetColumn();
	Cell dest1(x-1, y-2);
	Cell dest2(x-2, y-1);
	Cell dest3(x-2, y+1);
	Cell dest4(x-1, y+2);
	Cell dest5(x+1, y+2);
	Cell dest6(x+2, y+1);
	Cell dest7(x+2, y-1);
	Cell dest8(x+1, y-2);
	
	AddMoveToListIfValid(s, myCell, dest1, board);
	AddMoveToListIfValid(s, myCell, dest2, board);
	AddMoveToListIfValid(s, myCell, dest3, board);
	AddMoveToListIfValid(s, myCell, dest4, board);
	AddMoveToListIfValid(s, myCell, dest5, board);
	AddMoveToListIfValid(s, myCell, dest6, board);
	AddMoveToListIfValid(s, myCell, dest7, board);
	AddMoveToListIfValid(s, myCell, dest8, board);
	
	return s;
}
/*DONE*/
void Knight::AddMoveToListIfValid(list<Move> & moves, Cell myCell, Cell dest, Piece *** board)
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
Knight::Knight(PieceColor color) : Piece(KNIGHT, color)
{
	//does nothing
}