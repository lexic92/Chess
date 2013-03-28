/* 
 * File:   Facade.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:19 PM
 */

#ifndef FACADE_H
#define	FACADE_H

//Standard Libary stuff
#include <string>
#include <list>

//my stuff
#include "ChessBoard.h"

class Facade
{
public:
	/*
	 Constructor. Makes a ChessBoard object.
	 */
	Facade();
	
	/*
	 Gets all the cells that contain pieces of a certain color.
	 */
	list<Cell> GetListOfCells(PieceColor color);
	
	/*
	 Gets all the valid moves that a cell can make.  If the cell is empty,
	 it will return an empty list.
	 */
	list<Move> GetValidMoves(Cell cell);
	
	/*
	 Both of these make a move.
	 They assume it's a valid move already.
	 */
	Move MakeMove(Cell startCell, Cell endCell);
	Move MakeMove(Move m);
	/*
	 1. Discards the current game.
	 2. Puts Pieces on the board for the start of a new game.
	 */
	void NewGame();
	
	/*
	 Saves the game to the file.
	 */
	void SaveGame(string fileName);
	
	/*
	 Loads the game from the file. ONLY UPDATES THE MODEL! So the model has an
	 updated move history, and also the board's piece pointers all point to the
	 right stuff. DOES NOT AFFECT THE VIEW.
	 */
	void LoadGame(string fileName);
	
	/*
	 Undo the most recent move.
	 */
	Move Undo();
	
	/*
	 Returns true if the next turn is supposed to be made by White.
	 Needless to say, false otherwise.
	*/
	bool WhitesTurn();
	
	/*
	 Returns true if that cell does not have a piece there.
	 */
	bool IsEmpty(int row, int column);
	
	/*
	 Returns true there is a piece on the board at that location, and of that color.
	 */
	bool IsAPieceOfThisColor(int row, int column, PieceColor color);
	
	/*
	 Returns the status of the game.
	 */
	bool GameIsOver();
	
	/*
	 Makes it so no one can take any more moves.
	 */
	void SayGameOver();
	
	/*
	 Allows players to take more moves again.
	 */
	void SayGameOn();
	
	/*
	 Returns the cell that has the king of that color.
	 */
	Cell FindKingsCell(PieceColor color);
	
	/*
	 Determines who made the move by finding out what the source cell's color is.
	 Then, it asks: What if, theoretically, the player was to MAKE that move?
	 Would that move allow the opponent to capture the king?
	 */
	bool PlayerLeavesOrPutsTheirKingInCheck(Move m);
	
	/*
	 Returns true if the movehistory has moves to be undid.
	 */
	bool CanUndo();
	
	/*
	 Returns an iterator to the beginning of the moves history.
	 */
	list<Move>::const_iterator GetMoveHistoryIterator();
	
	/*
	 Returns the end of the moves history (as an "iterator").
	 */
	list<Move>::const_iterator GetMoveHistoryEndIterator();
	
private:
	ChessBoard chessBoard;
	bool gameOver;
	
};

#endif	/* FACADE_H */

