/* 
 * File:   Move.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:24 PM
 */

#include "Move.h"
using namespace std;


/*static*/
bool Move::Test(ostream & os)
{
	os << "\n\n================== TESTING MOVE ============= " << endl;
	bool success = true;
	
	//Construct move object
	Cell start(1,2);
	Cell end(3,4);
	Move m(PAWN, WHITE, start, KNIGHT, BLACK, end);
	
	//Test Constructor
	TEST(m.sourcePieceType == PAWN);
	TEST(m.sourcePieceColor == WHITE);
	TEST(m.sourceStartCell == start);
	TEST(m.capturedPieceType == KNIGHT);
	TEST(m.capturedPieceColor == BLACK);
	TEST(m.sourceEndCell == end);
	
	//Test Getters
	TEST(m.GetSourcePieceType() == PAWN);
	TEST(m.GetSourcePieceColor() == WHITE);
	TEST(m.GetStartCell() == start);
	TEST(m.GetCapturedPieceType() == KNIGHT);
	TEST(m.GetCapturedPieceColor() == BLACK);
	TEST(m.GetEndCell() == end);
	
	//Test operator==
	//Construct identical move object
	Move m2(PAWN, WHITE, start, KNIGHT, BLACK, end);
	
	//Construct different move object (barely different)
	Move m3(KING, WHITE, start, KNIGHT, BLACK, end);
	
	//Construct different move object (barely different)
	Move m4(PAWN, BLACK, start, KNIGHT, BLACK, end);
	
	//Construct different move object (barely different)
	Move m5(PAWN, WHITE, end, KNIGHT, BLACK, end);
	
	//Construct different move object (barely different)
	Move m6(PAWN, WHITE, start, PAWN, BLACK, end);
	
	//Construct different move object (barely different)
	Move m7(PAWN, WHITE, start, KNIGHT, WHITE, end);
	
	//Construct different move object (barely different)
	Move m8(PAWN, WHITE, start, KNIGHT, BLACK, start);
	
	TEST(m == m2);
	TEST(!(m == m3));
	TEST(!(m == m4));
	TEST(!(m == m5));
	TEST(!(m == m6));
	TEST(!(m == m7));
	TEST(!(m == m8));
	
	
	
	return success;
}

/*explicit*/
Move::Move(PieceType sourcePieceType, PieceColor sourcePieceColor, Cell _sourceStartCell,
	PieceType capturedPieceType, PieceColor capturedPieceColor, Cell _sourceEndCell) :
	sourceStartCell(_sourceStartCell), sourceEndCell(_sourceEndCell)
{
	this->sourcePieceType = sourcePieceType;
	this->sourcePieceColor = sourcePieceColor;
	
	this->capturedPieceType = capturedPieceType;
	this->capturedPieceColor = capturedPieceColor;
}

/*DONE*/
PieceType Move::GetSourcePieceType() const
{
	return sourcePieceType;
}

/*DONE*/
PieceColor Move::GetSourcePieceColor() const
{
	return sourcePieceColor;
}

/*DONE*/
Cell Move::GetStartCell() const
{
	return sourceStartCell;
}

/*DONE*/
PieceType Move::GetCapturedPieceType() const
{
	return capturedPieceType;
}

/*DONE*/
PieceColor Move::GetCapturedPieceColor() const
{
	return capturedPieceColor;
}

/*DONE*/
Cell Move::GetEndCell() const
{
	return sourceEndCell;
}

/*DONE*/
bool Move::operator==(const Move & other) const
{
	return ( (sourcePieceType == other.sourcePieceType) &&
		(sourcePieceColor == other.sourcePieceColor) &&
		(sourceStartCell == other.sourceStartCell) &&
		(capturedPieceType == other.capturedPieceType) &&
		(capturedPieceColor == other.capturedPieceColor) &&
		(sourceEndCell == other.sourceEndCell) );
}