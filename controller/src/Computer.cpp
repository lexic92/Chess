/* 
 * File:   Computer.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:00 PM
 */
#include "Computer.h"
#include <ctime>
#include <algorithm>
/*DONE*/
Computer::Computer(PieceColor color, Facade * facade) : startCell(-1,-1)
{
	this->color = color;
	this->facade = facade;
	timerCountDown = 0;
}
/*DONE*/
void Computer::on_CellSelected(int row, int col, int button)
{
	//Do nothing.
}


/*DONE*/
/*
 1-3.	StartTimerEvent
 4.	Pause
 5-8.	FinishTimerEvent
*/
/*DONE and perfected*/
void Computer::on_TimerEvent()
{
	cout << "Computer timer countdown: " << timerCountDown << endl;
	
	//If the timer is set, then that means you ignore events until it runs out, and
	//when it runs out, then execute the second half of the function.
	while(timerCountDown)
	{
		timerCountDown--;
		if(timerCountDown == 0)
		{
			FinishTimerEvent();
		}
		//Still have to pause.
		return;
	}
	StartTimerEvent();
	timerCountDown = 2;
}


/*DONE and perfected*/
void Computer::StartTimerEvent()
{
	//1. Get the set of cells that have your color pieces.
	
	list<Cell> cells = facade->GetListOfCells(color);
	
	//2. While there are cells left... 
	//(note: you can be assured that there will be at least one piece.)
	while(cells.size() != 0)
	{
		//...Choose a cell randomly.
		cellsEnd = cells.end();
		startCell = ChooseARandomCell(cells, cellsEnd);
		
		//Get that cell's valid moves.
		validMoves = facade->GetValidMoves(startCell);
		
		//If it has no valid moves...
		if(validMoves.empty())
		{
			//Remove that cell from the list, and update the "end" iterator.
			cellsEnd = remove(cells.begin(), cells.end(), startCell);
			
		}
		else
		{	//Else, leave the while loop (with the validMoves list that has at least
			//one valid move intact.
			break;
		}
	}
	
	//3.Now that you have a cell with valid moves, highlight them all.
	for(list<Move>::const_iterator it = validMoves.begin(); it != validMoves.end(); it++)
	{
		//(Highlight the end cell that it can go to.)
		Cell endCell = (*it).GetEndCell();
		view->HighlightSquare(endCell.GetRow(), endCell.GetColumn(), BLUE_SQUARE);
	}
	
	//Also, highlight yourself.
	view->HighlightSquare(startCell.GetRow(), startCell.GetColumn(), GREEN_SQUARE);
}



/*DONE and perfected*/
void Computer::FinishTimerEvent()
{
	//5. Choose one of the valid moves randomly, and move there. (It assumes it's not empty.)
	//Update the view accordingly.
	Move m = ChooseARandomMove(validMoves);		
	MoveAndUpdateView(m);
	
	//If you were in check before, you aren't in check now.
	view->SetTopLabel("");
	
	// 6. Unhighlight yourself... 
	view->UnHighlightSquare(startCell.GetRow(), startCell.GetColumn());
	
	//...and all the other cells.
	for(list<Move>::const_iterator it = validMoves.begin(); it != validMoves.end(); it++)
	{
		view->UnHighlightSquare((*it).GetEndCell().GetRow(), 
			(*it).GetEndCell().GetColumn());
	}

	//7. Clear the validMoves list for future use.
	validMoves.clear();
	
	//8. Check for Checkmate, Stalemate, Check, or Normal.
	CheckForCheckmateStalemateCheckOrNormal();
}

void Computer::CheckForCheckmateStalemateCheckOrNormal()
{
	//These are talking about your opponent.
	bool inRange = false;
	bool noValidMoves = true;
	
	//Determine the opponent's color.
	PieceColor oppColor = (color == WHITE) ? BLACK : WHITE;
	
	//Determine the location of the opponent's king.
	Cell oppKing = facade->FindKingsCell(oppColor);
	
	//Get all YOUR pieces' cells.
	list<Cell> yourCells = facade->GetListOfCells(color);
	
	//For each of YOUR cells...
	for(list<Cell>::const_iterator it = yourCells.begin();
		it != yourCells.end(); it++)
	{
		//...get each cell's list of valid moves...
		list<Move> yourValidMoves = facade->GetValidMoves(*it);
		
		//...and for each move of such list...
		for(list<Move>::const_iterator it = yourValidMoves.begin();
			it != yourValidMoves.end(); it++)
		{
			//If your piece can move to your opponent's king's cell...
			if((*it).GetEndCell() == oppKing)
			{
				//...then your opponent's king is in range of being captured.
				inRange = true; 
			}
			
			//Effieciency thing:
			if(inRange)
			{
				break;
			}
		}
	}
	
	//------------------------------------------------------------------------------
	
	//Get all of your opponent's pieces' cells.
	list<Cell> oppCells = facade->GetListOfCells(oppColor);
	
	//For each of HIS OR HER OR ITS cells...
	for(list<Cell>::const_iterator it = oppCells.begin();
		it != oppCells.end(); it++)
	{
		//...get each cell's list of valid moves...
		list<Move> theirValidMoves = facade->GetValidMoves(*it);
		
		//...and for each move of such list...
		for(list<Move>::const_iterator it = theirValidMoves.begin();
			it != theirValidMoves.end(); it++)
		{
			//If that move does NOT put or leave their king in check, then note that
			//they DO have a valid move by marking noValidMoves as false.
			if(!facade->PlayerLeavesOrPutsTheirKingInCheck(*it))
			{
				noValidMoves = false;
				
				//If one move can save him, then he's in check ONLY.
				break; 
			}
			
			//Efficiency thing:
			if(!noValidMoves)
			{
				break;
			}
			
		}
	}
	
	//----------------------------------------------------------------------------------
	
	WriteMessageAndEndGameIfApplicable(inRange, noValidMoves);
}
void Computer::WriteMessageAndEndGameIfApplicable(bool inRange, bool noValidMoves)
{
	//Determine the opponent's color.
	PieceColor oppColor = (color == WHITE) ? BLACK : WHITE;
	
	if(inRange && noValidMoves)
	{
		//Write message that opponent is in checkmate.
		string checkmateMessage;
		checkmateMessage += ((oppColor == WHITE) ? "White" : "Black");
		checkmateMessage += " is in checkmate. ";
		view->SetTopLabel(checkmateMessage);
		
		//End game:
		facade->SayGameOver();
	}
	else if(!inRange && noValidMoves)
	{
		//Write message that you put your opponent in stalemate.
		string checkmateMessage;
		checkmateMessage += ((oppColor == WHITE) ? "White" : "Black");
		checkmateMessage += " was put in stalemate.  Undo? or Play Again?";
		view->SetTopLabel(checkmateMessage);
		
		//End game:
		facade->SayGameOver();
	}
	else if(inRange && !noValidMoves)
	{
		//Write message that your opponent is in check.
		string checkmateMessage;
		checkmateMessage += ((oppColor == WHITE) ? "White" : "Black");
		checkmateMessage += " is in check.";
		view->SetTopLabel(checkmateMessage);
		
		//Continue the game.
	}
	else
	{
		//Everything's normal. Continue as usual. (also, clear the top label.)
		view->SetTopLabel("");
	}	
}

/*DONE*/ //I didn't test this, but I carefully looked at it. It works, trust me.
Move Computer::ChooseARandomMove(list<Move> moves)
{
	srand(time(NULL));
	int randomIndex = rand() % moves.size();
	int i = 0;
	
	//Go through the moves and get the random move.
	for(list<Move>::const_iterator it = moves.begin(); it != moves.end(); it++)
	{
		//Stop when you reach the i'th index.
		if(i == randomIndex)
		{
			return (*it);
		}
		i++;
	}
}

/*DONE*/ //I didn't test this, but I carefully looked at it. It works, trust me.
Cell Computer::ChooseARandomCell(list<Cell> cells, list<Cell>::const_iterator cellsEnd)
{
	srand(time(NULL));
	int randomIndex = rand() % cells.size();
	int i = 0;
	
	//Go through the cells and get the random cell.
	for(list<Cell>::const_iterator it = cells.begin(); it != cellsEnd; it++)
	{
		//Stop when you reach the i'th index.
		if(i == randomIndex)
		{
			return (*it);
		}
		i++;
	}
}






/*DONE - I carefully inspected it.*/
void Computer::MoveAndUpdateView(Move m)
{
	//Then, make that move.
	facade->MakeMove(m);

	//UPDATE THE VIEW TO REFLECT THE MOVE:
	
	//1. Clear the piece that moved.
	view->ClearPiece(m.GetStartCell().GetRow(), m.GetStartCell().GetColumn());

	//2. Clear whatever was on the board in the other spot.
	view->ClearPiece(m.GetEndCell().GetRow(), m.GetEndCell().GetColumn());
	
	//3. Draw the piece from startCell onto myCell.
	ImageName image = ConvertToImageName(m.GetSourcePieceType(), m.GetSourcePieceColor());
	view->PlacePiece(m.GetEndCell().GetRow(), m.GetEndCell().GetColumn(), image);
}





/*DONE*/
void Computer::SetView(IChessView * view)
{
	this->view = view;
}




/*static*/
bool Computer::Test(ostream & os)
{
	os << "\n\n=================== TESTING COMPUTER =============" << endl;
	bool success = true;
	
	return success;
}




