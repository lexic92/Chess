/* 
 * File:   Piece.cpp
 * Author: lexic92
 *
 * Created on April 8, 2012, 3:50 AM
 */
#include "Piece.h"
using namespace std;

/*static*/ 
bool Piece::Test(ostream & os)
{
	os << "\n\n================== TESTING PIECE ============= " << endl;
	bool success = true;
	
	//Test constructor and getters.
	Piece p(KING, WHITE);
	TEST(p.GetType() == KING);
	TEST(p.GetColor() == WHITE);
	TEST(p.type == KING);
	TEST(p.color == WHITE);
	
	return success;
}


//VIRTUAL FUNCTIONS-----------------------------------------
/*DONE*/
/*virtual*/
list<Move> Piece::GetPossibleMovesRegardlessOfCheck(Cell cell, Piece *** boardPointer)
{
	//Do nothing
}
//-------------------------------------------------------------



/*DONE*/
Piece::~Piece()
{
	//Do nothing
}


/*DONE*/
PieceType Piece::GetType()
{
	return type;
}

/*DONE*/
PieceColor Piece::GetColor()
{
	return color;
}

/*DONE*/
Piece::Piece(PieceType type, PieceColor color)
{
	this->type = type;
	this->color = color;
}

