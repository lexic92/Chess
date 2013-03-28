/* 
 * File:   Rook.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:25 PM
 */

#include "Rook.h"
using namespace std;

/*static*/
bool Rook::Test(ostream & os)
{
	os << "\n\n================== TESTING ROOK ============= " << endl;
	bool success = true;
	
	return success;
}

/*virtual*/
/*DONE*/
list<Move> Rook::GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board)
{
	list<Move> moves;

	//NOTE: This is the same pattern no matter what color it is. (As opposed to Pawns.)
	AddMovesAbove(moves, myCell, board);
	AddMovesBelow(moves, myCell, board);
	AddMovesLeft(moves, myCell, board);
	AddMovesRight(moves, myCell, board);
	
	return moves;
}
/*DONE*/
void Rook::AddMovesAbove(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "above" to be one above myCell. It will be updated throughout this function.
	Cell above = myCell;
	above.Up();
	
	while(true)
	{
		//If the above cell in question is off the board, stop trying to get up-moves.
		if(!above.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "above" for the next round.
		if(board[above.GetRow()][above.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update above.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, above);
			moves.push_back(m);
			above.Up();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[above.GetRow()][above.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), above);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
void Rook::AddMovesBelow(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "below" to be one below myCell. It will be updated throughout this function.
	Cell below = myCell;
	below.Down();
	
	while(true)
	{
		//If the below cell in question is off the board, stop trying to get up-moves.
		if(!below.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "below" for the next round.
		if(board[below.GetRow()][below.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update below.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, below);
			moves.push_back(m);
			below.Down();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[below.GetRow()][below.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), below);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
void Rook::AddMovesLeft(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "left" to be one left myCell. It will be updated throughout this function.
	Cell left = myCell;
	left.Left();
	
	while(true)
	{
		//If the left cell in question is off the board, stop trying to get up-moves.
		if(!left.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "left" for the next round.
		if(board[left.GetRow()][left.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update left.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, left);
			moves.push_back(m);
			left.Left();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[left.GetRow()][left.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), left);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
void Rook::AddMovesRight(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "right" to be one right myCell. It will be updated throughout this function.
	Cell right = myCell;
	right.Right();
	
	while(true)
	{
		//If the right cell in question is off the board, stop trying to get up-moves.
		if(!right.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "right" for the next round.
		if(board[right.GetRow()][right.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update right.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, right);
			moves.push_back(m);
			right.Right();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[right.GetRow()][right.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), right);
				moves.push_back(m);
			}
			return;
			
		}
	}
}

/*DONE*/
Rook::Rook(PieceColor color) : Piece(ROOK, color)
{
	//does nothing
}