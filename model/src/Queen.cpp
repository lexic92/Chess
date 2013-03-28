/* 
 * File:   Queen.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:25 PM
 */

#include "Queen.h"
using namespace std;

/*static*/
bool Queen::Test(ostream & os)
{
	os << "\n\n================== TESTING QUEEN ============= " << endl;
	bool success = true;
	
	return success;
}

/*virtual*/
list<Move> Queen::GetPossibleMovesRegardlessOfCheck(Cell myCell, Piece *** board)
{
	list<Move> moves;
	
	//NOTE: This is the same pattern no matter what color it is. (As opposed to Pawns.)
	AddMovesAbove(moves, myCell, board);
	AddMovesBelow(moves, myCell, board);
	AddMovesLeft(moves, myCell, board);
	AddMovesRight(moves, myCell, board);
	
	AddMovesUpLeft(moves, myCell, board);
	AddMovesUpRight(moves, myCell, board);
	AddMovesDownLeft(moves, myCell, board);
	AddMovesDownRight(moves, myCell, board);
	
	return moves;
}
/*DONE*/
void Queen::AddMovesAbove(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesBelow(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesLeft(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesRight(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesUpLeft(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesUpRight(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesDownLeft(list<Move> & moves, Cell myCell, Piece *** board)
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
void Queen::AddMovesDownRight(list<Move> & moves, Cell myCell, Piece *** board)
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
Queen::Queen(PieceColor color) : Piece(QUEEN, color)
{
	//does nothing
}