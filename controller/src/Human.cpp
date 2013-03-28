/* 
 * File:   Human.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:00 PM
 */
const int youNeedHelp = 1;
#include "Human.h"
#include "UnitTest.h"
Human::Human(PieceColor color, Facade * facade) : firstSelection(true), startCell(-1,-1)
{
	if(youNeedHelp) cout << "Human: Contstructor..." << endl;
	this->color = color;
	this->facade = facade;
}
void Human::on_CellSelected(int row, int col, int button)
{
	if(youNeedHelp) cout << "Human: On cell selected..." << endl;
	if(firstSelection)
	{
		FirstSelection(row, col);
	}
	else
	{
		SecondSelection(row, col);
	}
}
void Human::FirstSelection(int row, int col)
{
	//If the cell is not a piece of your color, don't highlight anything.
	if(!facade->IsAPieceOfThisColor(row, col, color))
	{
		if(youNeedHelp) cout << "NO: Returning..." << endl;
		return;
	}


	//Otherwise, store it as startCell, and highlight the selected square in yellow.
	view->HighlightSquare(row, col, YELLOW_SQUARE);


	//Get valid moves and highlight their squares.
	Cell myCell(row, col);
	validMoves = facade->GetValidMoves(myCell);


	//For each move, highlight the endCell.
	for(list<Move>::const_iterator it = validMoves.begin(); it != validMoves.end(); it++)
	{
		//Highlight the end cell that it can go to.
		Cell endCell = (*it).GetEndCell();
		view->HighlightSquare(endCell.GetRow(), endCell.GetColumn(), RED_SQUARE);
	}

	//Next time, it will be your second selection.
	firstSelection = false;

	//Store start cell.
	startCell = myCell;
}
/*DONE*/
void Human::SecondSelection(int row, int col)
{
	//If the cell is not one of the highlighted cells, then erase the original
	//highlighted cells.
	Cell myCell(row, col);
	for(list<Move>::const_iterator it = validMoves.begin(); it != validMoves.end(); it++)
	{
		//If this is a valid cell, then make a move.
		if(myCell == ((*it).GetEndCell()))
		{
			MoveAndUpdateView(*it);
			
			//If you were in check before, you aren't in check now.
			view->SetTopLabel("");
		}
	}


	
	//Either way, whether you moved or not, unhighlight YOUR cell and every
	//other possible-moves cell.
	view->UnHighlightSquare(startCell.GetRow(), startCell.GetColumn());
	for(list<Move>::const_iterator it = validMoves.begin(); it != validMoves.end(); it++)
	{
		view->UnHighlightSquare((*it).GetEndCell().GetRow(), 
			(*it).GetEndCell().GetColumn());
	}

	//Clear the validMoves list for future use.
	validMoves.clear();

	//Next time you click, it will be your first selection.
	firstSelection = true;
	
	CheckForCheckmateStalemateCheckOrNormal();
}

/*DONE*/
void Human::on_TimerEvent()
{
	//Does nothing.
}
/*DONE*/
void Human::SetView(IChessView * view)
{
	this->view = view;
}

/*DONE - I carefully inspected it.*/
void Human::MoveAndUpdateView(Move m)
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


void Human::CheckForCheckmateStalemateCheckOrNormal()
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
void Human::WriteMessageAndEndGameIfApplicable(bool inRange, bool noValidMoves)
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

/*static*/
bool Human::Test(ostream & os)
{
	os << "\n\n=================== TESTING HUMAN =============" << endl;
	bool success = true;
	Facade * f = NULL;
	Human h(WHITE, f);
	Cell cell(0,0);
	
	//Test ConvertToImageName.
	Move m(PAWN, WHITE, cell, NOTYPE, NOCOLOR, cell);
	ImageName image1 = ConvertToImageName(m.GetSourcePieceType(), m.GetSourcePieceColor());
	ImageName image2 = ConvertToImageName(ROOK, WHITE);
	ImageName image3 = ConvertToImageName(BISHOP, BLACK);
	ImageName image4 = ConvertToImageName(QUEEN, BLACK);
	ImageName image5 = ConvertToImageName(KING, BLACK);
	TEST(image1 == W_PAWN);
	TEST(image2 == W_ROOK);
	TEST(image3 == B_BISHOP);
	TEST(image4 == B_QUEEN);
	TEST(image5 == B_KING);
	
	return success;
}