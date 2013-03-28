/* 
 * File:   Controller.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:23 PM
 */
#include "Controller.h"
#include <iostream>
using namespace std;
const int youNeedHelp = 1;

/*INCOMPLETE - need to take arguments and make human/computer player combinations.*/
Controller::Controller(int argumentNumber)
{
	if(youNeedHelp) cout << "constructor..." << endl;
	arg = argumentNumber;
	InstantiatePlayers();
	saveFile = "";
}
void Controller::InitializeNewGame()
{
	saveFile = "";
	delete whitePlayer;
	delete blackPlayer;
	InstantiatePlayers();
}
void Controller::InstantiatePlayers()
{
	if(arg == 0) //hh
	{
		whitePlayer = new Human(WHITE, &chessFacade);
		blackPlayer = new Human(BLACK, &chessFacade);
	}
	else if(arg == 1) //hc
	{
		whitePlayer = new Human(WHITE, &chessFacade);
		blackPlayer = new Computer(BLACK, &chessFacade);
	}
	else if(arg == 2) //ch
	{
		whitePlayer = new Computer(WHITE, &chessFacade);
		blackPlayer = new Human(BLACK, &chessFacade);
	}
	else //cc
	{
		whitePlayer = new Computer(WHITE, &chessFacade);
		blackPlayer = new Computer(BLACK, &chessFacade);
	}
}
/*INCOMPLETE*/
Controller::~Controller()
{
	delete whitePlayer;
	delete blackPlayer;
}
/*virtual*/
/*DONE*/
void Controller::on_CellSelected(int row, int col, int button)
{
	
	
	//If the game is over, don't do anything.
	//Now, it will never change whose turn it is because it won't be able to make
	//moves anymore.
	if(chessFacade.GameIsOver())
	{
		return;
	}
	if(youNeedHelp) cout << "Controller: on cell selected..." << endl;
	//Just pass it on to the current player.
	if(chessFacade.WhitesTurn())
	{
		view->SetBottomLabel("~*~*~*~ White's Turn ~*~*~*~");
		whitePlayer->on_CellSelected(row, col, button);
	}
	else
	{
		view->SetBottomLabel("~*~*~*~ Black's Turn ~*~*~*~");
		blackPlayer->on_CellSelected(row, col, button);
	}
}

/*DONE*/
/*virtual*/
void Controller::on_DragStart(int row,int col)
{
	if(youNeedHelp) cout << "Controller: On drag start..." << endl;
}

/*DONE*/
/*virtual*/
bool Controller::on_DragEnd(int row,int col)
{
	if(youNeedHelp) cout << "Controller: On drag end..." << endl;
	return false;
}


/*virtual*/
/*DONE*/
void Controller::on_NewGame()
{
	chessFacade.NewGame();
	InitializeNewGame();
	MakeBoardLookLikeNewGame();
	
	//No longer in checkmate or stalemate.
	chessFacade.SayGameOn();
	view->SetTopLabel("");
}
/*DONE*/
void Controller::MakeBoardLookLikeNewGame()
{
	//Clear any pieces that were there, and remove any highlights.
	for(int row = 0; row < 8; row++)
	{
		for(int column = 0; column < 8; column++)
		{
			view->ClearPiece(row, column);
			view->UnHighlightSquare(row, column);
		}
	}
	
	//Initialize the board with all the pieces.
	
	view->PlacePiece(0, 0, B_ROOK);
	view->PlacePiece(0, 1, B_KNIGHT);
	view->PlacePiece(0, 2, B_BISHOP);
	view->PlacePiece(0, 3, B_QUEEN);
	view->PlacePiece(0, 4, B_KING);
	view->PlacePiece(0, 5, B_BISHOP);
	view->PlacePiece(0, 6, B_KNIGHT);
	view->PlacePiece(0, 7, B_ROOK);
	
	view->PlacePiece(1,0, B_PAWN);
	view->PlacePiece(1,1, B_PAWN);
	view->PlacePiece(1,2, B_PAWN);
	view->PlacePiece(1,3, B_PAWN);
	view->PlacePiece(1,4, B_PAWN);
	view->PlacePiece(1,5, B_PAWN);
	view->PlacePiece(1,6, B_PAWN);
	view->PlacePiece(1,7, B_PAWN);
	
	view->PlacePiece(6,0, W_PAWN);
	view->PlacePiece(6,1, W_PAWN);
	view->PlacePiece(6,2, W_PAWN);
	view->PlacePiece(6,3, W_PAWN);
	view->PlacePiece(6,4, W_PAWN);
	view->PlacePiece(6,5, W_PAWN);
	view->PlacePiece(6,6, W_PAWN);
	view->PlacePiece(6,7, W_PAWN);
	
	view->PlacePiece(7, 0, W_ROOK);
	view->PlacePiece(7, 1, W_KNIGHT);
	view->PlacePiece(7, 2, W_BISHOP);
	view->PlacePiece(7, 3, W_QUEEN);
	view->PlacePiece(7, 4, W_KING);
	view->PlacePiece(7, 5, W_BISHOP);
	view->PlacePiece(7, 6, W_KNIGHT);
	view->PlacePiece(7, 7, W_ROOK);
}
/*virtual*/
/*DONE*/
void Controller::on_SaveGame()
{
	cout  << "on_SaveGame" << endl;
	//If the save file has not been initialized, then do what "on_SaveGameAs()" does.
	if(saveFile == "")
	{
		on_SaveGameAs();
	}
	else
	{
		cout << "else statement" << endl;
		cout << saveFile << endl;
		try
		{
			chessFacade.SaveGame(saveFile);
			cout << "done saving" << endl;
		}
		catch(...)
		{
			cout << "could not save" << endl;
		}
		
	}
	
}

/*virtual*/
/*INCOMPLETE - IDK If it needs to throw an exception?*/
void Controller::on_SaveGameAs()
{
	string fileName = view->SelectSaveFile();
	cout << "filename != ''?  " << (fileName != "") << endl;
	cout << "filename is " << fileName << endl;
	//If it's empty, do nothing (they must have canceled).
	if(fileName != "")
	{
		try
		{
			chessFacade.SaveGame(fileName);
			saveFile = fileName;
			cout << "saved as" << endl;
		}
		catch(...)
		{
			//If the output file did not work.
			cout << "Could not save." << endl;
		}
	}
}


/*virtual*/
void Controller::on_LoadGame()
{
	
	
	if(youNeedHelp) cout << "Controller: On load game..." << endl;
	string loadFile = view->SelectLoadFile();
	
	try
	{
		if(loadFile == "")
		{
			//User must have pushed cancel.
			return;
		}
		//This only affects the model, so I need to make the view reflect this.
		chessFacade.LoadGame(loadFile);
		
		//I will simulate the moves to make the board look like this, so the controller
		//only needs to know about moves (like it already does), and the model has
		//more encapsulation.

		MakeBoardLookLikeNewGame();

		list<Move>::const_iterator it = chessFacade.GetMoveHistoryIterator();
		list<Move>::const_iterator end = chessFacade.GetMoveHistoryEndIterator();

		//For each move in the move history...
		for(; it != end; it++)
		{
			UpdateTheViewToReflectTheMove(*it);
		}
		//Clear CM or SM after the load.
		view->SetTopLabel("");
	}
	catch(...)
	{		
		cout << "exception" << endl;
	}
}
/*DONE*/
void Controller::UpdateTheViewToReflectTheMove(Move m)
{
	//1. Clear the piece that moved.
	view->ClearPiece(m.GetStartCell().GetRow(), m.GetStartCell().GetColumn());

	//2. Clear whatever was on the board in the other spot.
	view->ClearPiece(m.GetEndCell().GetRow(), m.GetEndCell().GetColumn());
	
	//3. Draw the piece from startCell onto myCell.
	ImageName image = ConvertToImageName(m.GetSourcePieceType(), m.GetSourcePieceColor());
	view->PlacePiece(m.GetEndCell().GetRow(), m.GetEndCell().GetColumn(), image);
}

/*virtual*/
void Controller::on_UndoMove()
{
	//No longer in checkmate or stalemate.
	chessFacade.SayGameOn();
	view->SetTopLabel("");
	
	//Don't try to undo it you can't undo anything.
	if(!chessFacade.CanUndo())
	{
		return;
	}
	
	
	//Undo the move (and get it to see what it was):
	Move m = chessFacade.Undo();
 

	//UPDATE THE VIEW TO REFLECT THE UNDO:
	
	//1. Redraw the destination by clearing it if there was no capture...
	if(m.GetCapturedPieceColor() == NOCOLOR && m.GetCapturedPieceType() == NOTYPE)
	{
		view->ClearPiece(m.GetEndCell().GetRow(), m.GetEndCell().GetColumn());
	}
	//...or redrawing the captured piece.
	else
	{
		ImageName image = ConvertToImageName(m.GetCapturedPieceType(), 
			m.GetCapturedPieceColor());
		view->PlacePiece(m.GetEndCell().GetRow(), m.GetEndCell().GetColumn(), image);
	}
	
	//2. Redraw the source piece on it's source cell. 
	ImageName image = ConvertToImageName(m.GetSourcePieceType(), 
			m.GetSourcePieceColor());
	view->PlacePiece(m.GetStartCell().GetRow(), m.GetStartCell().GetColumn(), image);
	
	//3. Remove all highlights.
	for(int row = 0; row < 8; row++)
	{
		for(int column = 0; column < 8; column++)
		{
			view->UnHighlightSquare(row, column);
		}
	}
}


/*virtual*/
void Controller::on_QuitGame()
{
	if(youNeedHelp) cout << "Controller: On quit game..." << endl;
}


/*virtual*/
/*DONE*/
void Controller::on_TimerEvent()
{
	
	//If the game is over, don't do anything.
	//Now, it will never change whose turn it is because it won't be able to make
	//moves anymore.
	if(chessFacade.GameIsOver())
	{
		return;
	}
	
	//if(youNeedHelp) cout << "Controller: On timer event..." << endl;
	
	//If the game is not over, just pass it on to the current player.
	if(chessFacade.WhitesTurn())
	{
		view->SetBottomLabel("~*~*~*~ White's Turn ~*~*~*~");
		whitePlayer->on_TimerEvent();
	}
	else
	{
		view->SetBottomLabel("~*~*~*~ Black's Turn ~*~*~*~");
		blackPlayer->on_TimerEvent();
	}
}


/*virtual*/
/*DONE*/
void Controller::SetView(IChessView * view)
{
	if(youNeedHelp) cout << "Controller: Set view..." << endl;
	this->view = view;
	whitePlayer->SetView(view);
	blackPlayer->SetView(view);
	
	//Set up the pieces
	on_NewGame();
}