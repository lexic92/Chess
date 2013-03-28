/* 
 * File:   Pawn.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:20 PM
 */


#include "Pawn.h"
using namespace std;

/*static*/
bool Pawn::Test(ostream & os)
{
	os << "\n\n================== TESTING PAWN ============= " << endl;
	bool success = true;
	
	return success;
}

/*virtual*/
list<Move> Pawn::GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board)
{
	list<Move> moves;
	
	//Behaves differently depending on the color.
	if(color == BLACK)
	{
		AddPossibleMovesIfBlack(moves, myCell, board);
	}
	//color = WHITE:
	else
	{
		AddPossibleMovesIfWhite(moves, myCell, board);
	}
	
	return moves;
}
/*DONE*/
void Pawn::AddPossibleMovesIfBlack(list<Move> & moves, Cell myCell, Piece *** board)
{
	Cell downward = myCell;
	downward.Down();

	//CASE 1: Empty positions in front that are not blocked?
	
	
	
	//If you're on your home row (for black, that would be row 1), then you can
	//move forward 2 if possible. Otherwise, you can only move 1.
	int maxForwardSpaces = ((myCell.GetRow() == 1) ? 2 : 1);
	
	//Add forward moves if you're not blocked by anybody
	//(whether your color or not, since you can't capture in front of you.)
	for(int i = 0; i < maxForwardSpaces; i++)
	{
		//If the cell in question is on the board...
		if(downward.IsOnTheBoard())
		{
			Piece * piece = board[downward.GetRow()][downward.GetColumn()];
			
			//...and no one is there...
			if(piece == NULL)
			{
				//...then add that move.
				//Must be in correct order! Add move, THEN update downward.
				Move m(type, color, myCell, NOTYPE, NOCOLOR, downward);
				moves.push_back(m);
				downward.Down();
			}
			else
			{
				//No need to test 2 spaces in front, you're blocked anyway.
				break;
			}
		}
	}

	
	
	
	//CASE 2: Can you capture somebody? (CANNOT GO THERE IF IT'S EMPTY)
	CheckDownwardLeft(moves, myCell, board);
	CheckDownwardRight(moves, myCell, board);
}
/*DONE*/
void Pawn::AddPossibleMovesIfWhite(list<Move> & moves, Cell myCell, Piece *** board)
{
	Cell upward = myCell;
	upward.Up();

	//CASE 1: Empty positions in front that are not blocked?
	
	
	
	
	//If you're on your home row (for white, that would be row 6), then you can
	//move forward 2 if possible. Otherwise, you can only move 1.
	int maxForwardSpaces = ((myCell.GetRow() == 6) ? 2 : 1);
	
	//Add forward moves if you're not blocked by anybody
	//(whether your color or not, since you can't capture in front of you.)
	for(int i = 0; i < maxForwardSpaces; i++)
	{
		//If the cell in question is on the board...
		if(upward.IsOnTheBoard())
		{
			Piece * piece = board[upward.GetRow()][upward.GetColumn()];
			
			//...and no one is there...
			if(piece == NULL)
			{
				//...then add that move.
				//Must be in correct order! Add move, THEN update upward.
				Move m(type, color, myCell, NOTYPE, NOCOLOR, upward);
				moves.push_back(m);
				upward.Up();
			}
			else
			{
				//No need to test 2 spaces in front, you're blocked anyway.
				break;
			}
		}
	}
	
	

	//CASE 2: Can you capture somebody? (CANNOT GO THERE IF IT'S EMPTY)
	CheckUpwardLeft(moves, myCell, board);
	CheckUpwardRight(moves, myCell, board);
}
/*DONE*/
void Pawn::CheckDownwardLeft(list<Move> & moves, Cell myCell, Piece *** board)
{
	Cell downwardLeft = myCell;
	downwardLeft.DownLeft();
	
	//If you're not going off the board...
	if(downwardLeft.IsOnTheBoard())
	{
		Piece * downwardLeftPiece = board[downwardLeft.GetRow()][downwardLeft.GetColumn()];
		
		//And you're capturing somebody...
		if(downwardLeftPiece != NULL)
		{
			//...who is not your color...
			if(downwardLeftPiece->GetColor() != color)
			{
				//Then you can add that move.
				Move m(type, color, myCell, downwardLeftPiece->GetType(),
					downwardLeftPiece->GetColor(), downwardLeft);
				moves.push_back(m);
			}
		}
	}
}
/*DONE*/
void Pawn::CheckDownwardRight(list<Move> & moves, Cell myCell, Piece *** board)
{
	Cell downwardRight = myCell;
	downwardRight.DownRight();
	
	//If you're not going off the board...
	if(downwardRight.IsOnTheBoard())
	{
		Piece * downwardRightPiece = board[downwardRight.GetRow()][downwardRight.GetColumn()];
		
		//And you're capturing somebody...
		if(downwardRightPiece != NULL)
		{
			//...who is not your color...
			if(downwardRightPiece->GetColor() != color)
			{
				//Then you can add that move.
				Move m(type, color, myCell, downwardRightPiece->GetType(),
					downwardRightPiece->GetColor(), downwardRight);
				moves.push_back(m);
			}
		}
	}
}
/*DONE*/
void Pawn::CheckUpwardLeft(list<Move> & moves, Cell myCell, Piece *** board)
{
	Cell upwardLeft = myCell;
	upwardLeft.UpLeft();
	
	//If you're not going off the board...
	if(upwardLeft.IsOnTheBoard())
	{
		Piece * upwardLeftPiece = board[upwardLeft.GetRow()][upwardLeft.GetColumn()];
		
		//And you're capturing somebody...
		if(upwardLeftPiece != NULL)
		{
			//...who is not your color...
			if(upwardLeftPiece->GetColor() != color)
			{
				//Then you can add that move.
				Move m(type, color, myCell, upwardLeftPiece->GetType(),
					upwardLeftPiece->GetColor(), upwardLeft);
				moves.push_back(m);
			}
		}
	}
}
/*DONE*/
void Pawn::CheckUpwardRight(list<Move> & moves, Cell myCell, Piece *** board)
{
	Cell upwardRight = myCell;
	upwardRight.UpRight();
	
	//If you're not going off the board...
	if(upwardRight.IsOnTheBoard())
	{
		Piece * upwardRightPiece = board[upwardRight.GetRow()][upwardRight.GetColumn()];
		
		//And you're capturing somebody...
		if(upwardRightPiece != NULL)
		{
			//...who is not your color...
			if(upwardRightPiece->GetColor() != color)
			{
				//Then you can add that move.
				Move m(type, color, myCell, upwardRightPiece->GetType(),
					upwardRightPiece->GetColor(), upwardRight);
				moves.push_back(m);
			}
		}
	}
}



/*DONE*/
Pawn::Pawn(PieceColor color) : Piece(PAWN, color)
{
	//does nothing
}