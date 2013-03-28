/* 
 * File:   ChessBoard.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:24 PM
 */

#ifndef CHESSBOARD_H
#define	CHESSBOARD_H
#include "MyDefines.h"
#include "Piece.h"
#include "MoveHistory.h"
#include "ChessXMLSaver.h"
#include "ChessXMLLoader.h"

//Standard Libary stuff:
#include <iostream>
#include <cassert>
#include <typeinfo> //for typeid()
#include <algorithm> //for checking the moves lists when testing all the pieces

//Pieces:
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"



class ChessBoard
{
public:
	//--------------------------2 Tests:-----------------------------
	
	/*
	 Tests this class.
	 */
	static bool Test(ostream & os);
	
	
	/*
	 Tests Pieces for possible moves 
	 (Those functions are tested here so  I can instantiate a chessboard 
	 easily and stuff, since pieces don't know about the chess board, 
	 but those functions need a pointer to a working chessboard.)
	 */
	static bool TestPiecesGetPossibleMoves(ostream & os);
	
	//---------------------------------------------------------------
	
	
	
	
	/*
	 Constructor
	 
	 1. Initialize Board Piece pointers.
	 Got the idea from:
	 http://stackoverflow.com/questions/1768294/how-to-allocate-a-2d-array-of-pointers-in-c
	 See that site for more info.
	 
	 2. Make the board's piece pointers point to correct Piece objects, 
	 or NULL for when there's no Piece object in a cell.
	
	 */
	ChessBoard();
	
	/*
	 Calls DeletePieces().
	 
	 From http://stackoverflow.com/questions/1768294/
		how-to-allocate-a-2d-array-of-pointers-in-c:
	 Be careful to delete the contained pointers, the row arrays, and the 
	 column array all separately and in the correct order.
	 */
	~ChessBoard();
	
	/*
	 Go through board & move history and generate XML.
	 */
	void SaveGameAsXML(string fileName);
	
	/*
	 1. Discards the current game.
	 
	 2. Parses the XML from the file and initializes the board to that game state
	 by updating the ChessBoard's piece pointers and move history.
	 */
	void LoadGameFromXML(string fileName);
	
	/*
	 1. Discards the current game (by calling ClearGame()).
	 
	 2. Puts Pieces on the board for the start of a new game.
	 */
	void NewGame();
	
	/*
	 Gives a list of possible moves for that location.
	 If there isn't a piece there, returns an empty list.
	 [I don't know if that's good or not. I haven't thought this far.]
	 */
	list<Move> GetValidMoves(Cell cell);
	
	
	/*
	 Returns a list of cells that have pieces of the given color.
	 */
	list<Cell> GetListOfCells(PieceColor color);
	
	/*
	 Pop the lastest move off of the MoveHistory. (It returns it and also
	 removes it from the MoveHistory.)
	 */
	Move Undo();
	
	/*
	 Updates the ChessBoard piece pointers to reflect the move.  If a piece was
	 captured, it will be deleted (to avoid memory leaks).
	 
	 It also asserts that the move is valid (to a degree).
	 */
	Move MakeMove(Move m);
	Move MakeMove(Cell startCell, Cell endCell);
	
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
	 Determines who made the move by finding out what the source cell's color is.
	 Then, it asks: What if, theoretically, the player was to MAKE that move?
	 Would that move allow the opponent to capture the king?
	 
	 Both do the same thing.
	 The first two functions both assert that their arguments are valid, and then
	 they pass on the arguments to the "actual function."
	 */
	bool PlayerLeavesOrPutsTheirKingInCheck(Move m);
	
	/*
	 PRECONDITION: The king of that color is on the board. (This should always be true.)
	 Iterates the board until it finds the cell that has the king of the given color.
	 */
	Cell FindKingsCell(PieceColor color);
	
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
	Piece*** board;
	MoveHistory moveHistory;
	ChessXMLSaver chessXMLSaver;
	ChessXMLLoader chessXMLLoader;
	
	/*
	 Deletes all piece objects that the board's piece pointers point to.
	 
	 Makes the pointers point to NULL right afterwards to prevent accessing
	 bad memory.
	 */
	void DeletePieces();
	
	/*
	 If you called DeletePieces, then the PIECE OBJECTS are no longer in the heap.
	 BUT, there are still arrays of PIECE POINTERS on the heap, and each piece pointer
	 of each of mentioned arrays pointed to the piece we deleted.  But the POINTERS are
	 on the heap too! So this deletes those pointers so they're NO LONGER IN THE HEAP.
	 */
	void DeletePiecePointers();
	
	/*
	 Discards the current game without saving by:
	 1. Calling DeletePieces
	 2. Making all of board's Piece pointers point to NULL.
	 2. Clearing the move history data structure.
	 */
	void ClearGame();
	
	
	/*
	 Modifies the board's pointers by creating new pieces on the heap.
	 
	 PRECONDITION: The pointers aren't needed for deleting what they point
	 to anymore.
	 
	 PRECONDITION: The pointers are all NULL (because rows 2-5 will be left untouched).
	 
	 NOTE:  Rows are from top to bottom, and columns are from left to right.
		0	1	2	3	4	5	6	7    (?, col)
	 
	 0	rook	knight	bishop	queen	king	bishop	knight	rook
	 
	 1	pawn	pawn	pawn	pawn	pawn	pawn	pawn	pawn
	 
	 2
				[black side]
	 3
	 
	 4
	 
	 5			[white side]
		
	 6	pawn	pawn	pawn	pawn	pawn	pawn	pawn	pawn
	 
	 7	rook	knight	bishop	queen	king	bishop	knight	rook
	 (row, ?)
	
	 */
	void PutPiecesOnBoardForStartOfGame();
	
	/*
	 Simply modifies the board's pointers, overwriting them to point to NULL.
	 
	 PRECONDITION: The pointers aren't needed for deleting what they point
	 to anymore.
	 */
	void MakePiecePointersPointToNull();

	

	bool PlayerLeavesOrPutsTheirKingInCheck(Cell startCell, Cell endCell);
	bool PlayerLeavesOrPutsTheirKingInCheckActualFunction(Move m);
	
	/*
	 Part of the Undo function.
	 Makes endCell point to a NEW piece object with the captured piece's type and color.
	 */
	void RevivePiece(PieceType capturedType, PieceColor capturedColor, Cell endCell);
	
	/*
	 Used to assert valid arguments to MakeMove(startCell, endCell).
	 
	 Asserts that...
		1. startCell and endCell are both on the board.
		2. startCell has a piece on it.
		3. If there was a capture, that piece has a type and color.
		4. If there was a capture, the startCell piece's color is different
		   than the endCell piece's color.
	 */
	void ValidateStartAndEndCells(Cell startCell, Cell endCell);
	
	/*
	 Used to assert valid arguments to MakeMove(Move).
	 
	 Asserts that...
		1. m's startCell and endCell are both on the board.
		2. startCell has a piece on it.
		3. startCell piece's type is the same as the move's claimed start type.
		4. startCell piece's color is the same as the move's claimed start color.
		5. If endCell has a piece, its type is the same as the move's claimed
		   captured type.
		6. If endCell has a piece, its color is the same as the move's claimed
		   captured color.
		7. If endCell doesn't have a piece, the move's claimed captured type is NOTYPE.
		8. If endCell doesn't have a piece, the move's claimed captured color is NOCOLOR.
	 */
	void ValidateMove(Move m);
	
	/*
	 PRECONDITION: the move is valid (to a degree).
	 
	 Updates the model to reflect the move, and adds the move to the moveHistory.
	 */
	Move MakeMoveActualFunction(Move m);
	//-------------------------- TESTS ---------------------------------
	
	/*
	 The following functions test this class.
	 */
	static bool TestBasicChessBoardFunctions(ostream & os);
	static bool TestCorrectSetupNullsAndPieceColors(ostream& os, ChessBoard & c);
	static bool TestCorrectSetupPieceTypes(ostream& os, ChessBoard & c);
	static bool TestGetListsOfCells(ostream & os);
	static bool CompareCellLists(list<Cell> correctCells, list<Cell> generatedCells, ostream & os);
	static bool PrintAnyInvalidCellsRemaining(list<Cell> invalidCells, ostream & os);
	static void PrintListOfCells(list<Cell> cellsToPrint, ostream & os);
	static bool TestMakeMoveAndUndo(ostream & os);
	static bool TestMakeMoveResult(ChessBoard & c, ostream & os); //Highly coupled subfunction.
	static bool TestNewGame(ostream & os);
	static bool TestPlayerLeavesOrPutsTheirKingInCheck(ostream & os);
	static bool TestGetValidMoves(ostream & os);
	
	// . . . . . . . . . . . . . . . TEST EACH PIECE. . . . . . . . . . . . . . . 
	// I have to test each piece's GetPossibleMoves methods HERE in the 
	//ChessBoard class so that I can instantiate a chessboard.
	
	
	static bool TestKingsGetPossibleMovesRegardlessOfCheck(ostream& os);
	static bool TestKnightsGetPossibleMovesRegardlessOfCheck(ostream& os);
	static bool TestRooksGetPossibleMovesRegardlessOfCheck(ostream& os);
	static bool TestBishopsGetPossibleMovesRegardlessOfCheck(ostream& os);
	static bool TestQueensGetPossibleMovesRegardlessOfCheck(ostream& os);
	static void AddCorrectMovesForQueen(list<Move> & correctMoves);
	static bool TestPawnsGetPossibleMovesRegardlessOfCheck(ostream& os);
	static bool TestBlackPawnYou1(ostream& os, ChessBoard & c);
	static bool TestBlackPawnYou2(ostream& os, ChessBoard & c);
	static bool TestBlackPawnYou3(ostream& os, ChessBoard & c);
	static bool TestBlackPawnYou4(ostream& os, ChessBoard & c);
	static bool TestWhitePawnYou1(ostream& os, ChessBoard & c);
	static bool TestWhitePawnYou2(ostream& os, ChessBoard & c);
	static bool TestWhitePawnYou3(ostream& os, ChessBoard & c);
	static bool TestWhitePawnYou4(ostream& os, ChessBoard & c);
	
	// . . . . . . . . . . CONVENIENCE STUFF FOR PIECE TESTS STUFF. . . . . . . . . .
	 /*
	 Prints a list of moves.
	 */
	static void PrintListOfMoves(list<Move> movesToPrint, ostream & os);
	/*
	 Print a single move.
	 */
	static void PrintMove(Move m, ostream & os);
	/*
	 IF the list has moves remaining,
		Prints a message saying that the moves on this list should not have 
		been added, and prints the list of moves.
	 ELSE,
		Prints nothing.
	 
	 Meant to be used after you removed all the correct moves from the 
	 list of generated moves.
	 */
	static bool PrintAnyInvalidMovesRemaining(list<Move> invalidMoves, ostream & os);
	
	/*
	 Prints informative messages to the ostream saying which moves are missing from
	 generatedMoves, and which moves are on generatedMoves which shouldn't be.
	 (Basically, the ways the two lists differ.)
	 
	 NOTE: This function uses "find" from <algorithm>
	 
	   cplusplus.com:
		find(first, last, value)   - range is [first, last).
		Returns an iterator to the first element in the range that is equal
		to the given element. If it was not found, it will return 
		[whateveritwas].end() iterator.
	*/
	static bool CompareMoveLists(list<Move> correctMoves, list<Move> generatedMoves,
		ostream & os);
};

#endif	/* CHESSBOARD_H */

