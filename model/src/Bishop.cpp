/* 
 * File:   Bishop.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:25 PM
 */
#include "Bishop.h"
using namespace std;

/*static*/
bool Bishop::Test(ostream & os)
{
	os << "\n\n================== TESTING BISHOP ============= " << endl;
	bool success = true;
	
	return success;
}

/*virtual*/
list<Move> Bishop::GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board)
{
	list<Move> moves;

	//NOTE: This is the same pattern no matter what color it is. (As opposed to Pawns.)
	AddMovesUpLeft(moves, myCell, board);
	AddMovesUpRight(moves, myCell, board);
	AddMovesDownLeft(moves, myCell, board);
	AddMovesDownRight(moves, myCell, board);
	
	return moves;
}

/*DONE*/
void Bishop::AddMovesUpLeft(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "upLeft" to be one upLeft myCell. It will be updated throughout this function.
	Cell upLeft = myCell;
	upLeft.UpLeft();
	
	while(true)
	{
		//If the upLeft cell in question is off the board, stop trying to get up-moves.
		if(!upLeft.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "upLeft" for the next round.
		if(board[upLeft.GetRow()][upLeft.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update upLeft.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, upLeft);
			moves.push_back(m);
			upLeft.UpLeft();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[upLeft.GetRow()][upLeft.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), upLeft);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
void Bishop::AddMovesUpRight(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "upRight" to be one upRight myCell. It will be updated throughout this function.
	Cell upRight = myCell;
	upRight.UpRight();
	
	while(true)
	{
		//If the upRight cell in question is off the board, stop trying to get up-moves.
		if(!upRight.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "upRight" for the next round.
		if(board[upRight.GetRow()][upRight.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update upRight.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, upRight);
			moves.push_back(m);
			upRight.UpRight();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[upRight.GetRow()][upRight.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), upRight);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
void Bishop::AddMovesDownLeft(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "downLeft" to be one downLeft myCell. It will be updated throughout this function.
	Cell downLeft = myCell;
	downLeft.DownLeft();
	
	while(true)
	{
		//If the downLeft cell in question is off the board, stop trying to get up-moves.
		if(!downLeft.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "downLeft" for the next round.
		if(board[downLeft.GetRow()][downLeft.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update downLeft.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, downLeft);
			moves.push_back(m);
			downLeft.DownLeft();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[downLeft.GetRow()][downLeft.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), downLeft);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
void Bishop::AddMovesDownRight(list<Move> & moves, Cell myCell, Piece *** board)
{
	//Initialize "downRight" to be one downRight myCell. It will be updated throughout this function.
	Cell downRight = myCell;
	downRight.DownRight();
	
	while(true)
	{
		//If the downRight cell in question is off the board, stop trying to get up-moves.
		if(!downRight.IsOnTheBoard())
		{
			return;
		}
		//If it's empty, add an empty move. Then update "downRight" for the next round.
		if(board[downRight.GetRow()][downRight.GetColumn()] == NULL)
		{
			//Must be in correct order! Add move, THEN update downRight.
			Move m(type, color, myCell, NOTYPE, NOCOLOR, downRight);
			moves.push_back(m);
			downRight.DownRight();
		}
		//If it's not empty, and it's not your color, then add it as a move. 
		//Either way, break, because you're blocked either way from going further.
		else
		{
			Piece * piece = board[downRight.GetRow()][downRight.GetColumn()];
			if(piece->GetColor() != color)
			{
				Move m(type, color, myCell, piece->GetType(),
					piece->GetColor(), downRight);
				moves.push_back(m);
			}
			return;
			
		}
	}
}
/*DONE*/
Bishop::Bishop(PieceColor color) : Piece(BISHOP, color)
{
	//does nothing
}
