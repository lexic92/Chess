/* 
 * File:   Facade.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:12 PM
 */
#include <Facade.h>
using namespace std;
/*DONE*/
Facade::Facade() : gameOver(false)
{
	
}
/*DONE*/
list<Cell> Facade::GetListOfCells(PieceColor color)
{
	return chessBoard.GetListOfCells(color);
}
/*DONE*/
list<Move> Facade::GetValidMoves(Cell cell)
{
	return chessBoard.GetValidMoves(cell);
}
/*DONE*/
Move Facade::MakeMove(Move m)
{
	return chessBoard.MakeMove(m);
}

/*DONE*/
Move Facade::MakeMove(Cell startCell, Cell endCell)
{
	return chessBoard.MakeMove(startCell, endCell);
}

/*DONE*/
void Facade::NewGame()
{
	chessBoard.NewGame();
}
/*DONE*/
void Facade::SaveGame(string fileName)
{
	chessBoard.SaveGameAsXML(fileName);
}

/*DONE*/
void Facade::LoadGame(string fileName)
{
	chessBoard.LoadGameFromXML(fileName);
}

/*DONE*/
Move Facade::Undo()
{
	return chessBoard.Undo();
}
/*DONE*/
bool Facade::WhitesTurn()
{
	return chessBoard.WhitesTurn();
}
/*DONE*/
bool Facade::IsAPieceOfThisColor(int row, int column, PieceColor color)
{
	return chessBoard.IsAPieceOfThisColor(row, column, color);
}
/*DONE*/
bool Facade::GameIsOver()
{
	return gameOver;
}

/*DONE*/
void Facade::SayGameOver()
{
	gameOver = true;
}
/*DONE*/
void Facade::SayGameOn()
{
	gameOver = false;
}

/*DONE*/
Cell Facade::FindKingsCell(PieceColor color)
{
	return chessBoard.FindKingsCell(color);
}

/*DONE*/
bool Facade::PlayerLeavesOrPutsTheirKingInCheck(Move m)
{
	return chessBoard.PlayerLeavesOrPutsTheirKingInCheck(m);
}

/*DONE*/
bool Facade::CanUndo()
{
	return chessBoard.CanUndo();
}
/*DONE*/
list<Move>::const_iterator Facade::GetMoveHistoryIterator()
{
	return chessBoard.GetMoveHistoryIterator();
}


/*DONE*/
list<Move>::const_iterator Facade::GetMoveHistoryEndIterator()
{
	return chessBoard.GetMoveHistoryEndIterator();
}