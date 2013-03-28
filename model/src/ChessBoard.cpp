/* 
 * File:   ChessBoard.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:23 PM
 */
#include "ChessBoard.h"
using namespace std;
/*static*/
bool ChessBoard::TestBasicChessBoardFunctions(ostream & os)
{
	bool success = true;
	ChessBoard c;
	
	//Test constructor:
	os << "\n\nTesting Constructor: Note-- doesn't really test for HOW the board's\n" <<
		"piece memory was set aside though, so you might want to look\n" <<
		"into that if you are looking for a bug.\n\n" << endl;
		//Test for StartOfGame Setup with NULL pointers in the middle rows.
	if(!ChessBoard::TestCorrectSetupNullsAndPieceColors(os, c)) success = false;
	if(!ChessBoard::TestCorrectSetupPieceTypes(os, c)) success = false;
	
	//Have to do this or else it's LOSING THE POITERS TO THE HEAP
	//when it overwrites them to NULL below!
	c.ClearGame(); 
	
	//Test MakePiecePointersPointToNull();
	c.MakePiecePointersPointToNull();
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			TEST(c.board[currentRow][currentColumn] == NULL);
		}	
	}
	
	
	//Test DeletePieces();
	os << "\n\nDeletePieces(): See if it calls 'delete'. I can't test for this because\n" <<
		"that's like testing for invalid pointer accesses which will break\n" <<
		"my test driver.\n\n" << endl;
	
	
	//Test PutPiecesOnBoardForStartOfGame
	os << "Testing PutPiecesOnBoardForStartOfGame() ..." << endl;
	c.PutPiecesOnBoardForStartOfGame();
	if(!ChessBoard::TestCorrectSetupNullsAndPieceColors(os, c)) success = false;
	if(!ChessBoard::TestCorrectSetupPieceTypes(os, c)) success = false;
	
	
	//Test ClearGame();
	c.ClearGame();
	TEST(c.moveHistory.Size() == 0);
	//It should call "DeletePieces()"
	//It also calls "MakePiecePointersPointToNull" so I'll check that here.
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			TEST(c.board[currentRow][currentColumn] == NULL);
		}	
	}
	
	//Test NewGame();
	if(!ChessBoard::TestNewGame(os)) success = false;

	
	//Test Destructor
	os << "\n\nDestructor: Test this by checking with valgrind for memory leaks.\n" <<
		"I don't know how else to check for it. It's complicated syntax stuff.\n" << endl;
	
	return success;
}
/*static*/
bool ChessBoard::TestNewGame(ostream & os)
{
	bool success = true;
	
	ChessBoard c;
	c.ClearGame();
	
	//Put some random pieces on there so new game tests not only for putting correct pieces,
	//but for clearing the old game as well.
	c.board[6][1] = new Pawn(WHITE); 
	c.board[4][5] = new Pawn(WHITE); 
	c.board[3][3] = new Pawn(WHITE); 
	c.board[0][1] = new Pawn(WHITE); 
	
	c.NewGame();
	if(!ChessBoard::TestCorrectSetupPieceTypes(os, c)) success = false;
	
	return success;
}
/*static*/
bool ChessBoard::Test(ostream & os)
{
	os << "\n\n================== TESTING CHESSBOARD ============= " << endl;
	bool success = true;
	
	if(!ChessBoard::TestBasicChessBoardFunctions(os)) success = false;
	
	
	//Test "FindKingsCell(PieceColor color)"
	ChessBoard c;
	//The pieces should all be on the board in the appropriate places.
	Cell blackKing = c.FindKingsCell(BLACK);
	Cell whiteKing = c.FindKingsCell(WHITE);
	TEST((blackKing.GetRow() == 0) && (blackKing.GetColumn() == 4));
	TEST((whiteKing.GetRow() == 7) && (whiteKing.GetColumn() == 4));
	
	
	//Test "GetListsOfCells(color)"
	if(!ChessBoard::TestGetListsOfCells(os)) success = false;
	
	//Test "MakeMove" and "Undo"
	if(!ChessBoard::TestMakeMoveAndUndo(os)) success = false;
	
	//Test "PlayerLeavesOrPutsTheirKingInCheck(Move m)"
	if(!ChessBoard::TestPlayerLeavesOrPutsTheirKingInCheck(os)) success = false;
	
	//Test "GetValidMoves(Cell)"
	if(!ChessBoard::TestGetValidMoves(os)) success = false;
	
	return success;
}
/*static*/
bool ChessBoard::TestGetValidMoves(ostream & os)
{
	os << "\n\n\t============TESTING GET VALID MOVES =========\n" << endl;
	bool success = true;
	
	ChessBoard c;
	c.ClearGame();
	
	//Put some pieces on there to test.
	//This is same as PlayerLeavesOrPutsTheirKingInCheck's setup.
	c.board[7][0] = new King(BLACK); 
	c.board[5][0] = new Rook(BLACK); 
	c.board[3][5] = new Rook(BLACK); 
	c.board[1][5] = new King(WHITE); 
	c.board[2][0] = new Rook(WHITE); 
	
	//Now this part is different. I'm adding some pawns to block movement so there are
	//less valid moves to test for.
	c.board[1][4] = new Pawn(WHITE);
	c.board[0][4] = new Pawn(WHITE);
	c.board[0][6] = new Pawn(WHITE);
	c.board[2][6] = new Pawn(WHITE);
	
	Cell whiteKing(1,5);
	Cell whiteRook(2,0);
	Cell blackRook(5,0);
	
	list<Move> whiteKingValidMoves = c.GetValidMoves(whiteKing);
	list<Move> whiteRookValidMoves = c.GetValidMoves(whiteRook);
	list<Move> blackRookValidMoves = c.GetValidMoves(blackRook);
	
	list<Move> correctMovesWhiteKing;
	Cell whiteKingDest1(2,4);
	Cell whiteKingDest2(1,6);
	Move m1(KING, WHITE, whiteKing, NOTYPE, NOCOLOR, whiteKingDest1);
	Move m2(KING, WHITE, whiteKing, NOTYPE, NOCOLOR, whiteKingDest2);
	correctMovesWhiteKing.push_back(m1);
	correctMovesWhiteKing.push_back(m2);
	if(!CompareMoveLists(correctMovesWhiteKing, whiteKingValidMoves, os)) success = false;
	
	list<Move> correctMovesWhiteRook;
	Cell whiteRookDest(2,5);
	Move m3(ROOK, WHITE, whiteRook, NOTYPE, NOCOLOR, whiteRookDest);
	correctMovesWhiteRook.push_back(m3);
	if(!CompareMoveLists(correctMovesWhiteRook, whiteRookValidMoves, os)) success = false;
	
	list<Move> correctMovesBlackRook;
	Cell blackRookDest1(3,0);
	Cell blackRookDest2(4,0);
	Cell blackRookDest3(6,0);
	Cell blackRookDest4(2,0);
	Move m4(ROOK, BLACK, blackRook, NOTYPE, NOCOLOR, blackRookDest1);
	Move m5(ROOK, BLACK, blackRook, NOTYPE, NOCOLOR, blackRookDest2);
	Move m6(ROOK, BLACK, blackRook, NOTYPE, NOCOLOR, blackRookDest3);
	Move m7(ROOK, BLACK, blackRook, ROOK, WHITE, blackRookDest4);
	correctMovesBlackRook.push_back(m4);
	correctMovesBlackRook.push_back(m5);
	correctMovesBlackRook.push_back(m6);
	correctMovesBlackRook.push_back(m7);
	if(!CompareMoveLists(correctMovesBlackRook, blackRookValidMoves, os)) success = false;
	
	return success;
}
/*static*/
bool ChessBoard::TestPlayerLeavesOrPutsTheirKingInCheck(ostream & os)
{
	bool success = true;
	
	ChessBoard c;
	c.ClearGame();
	
	//Put some pieces on there to test.
	c.board[7][0] = new King(BLACK); 
	c.board[5][0] = new Rook(BLACK); 
	c.board[3][5] = new Rook(BLACK); 
	c.board[1][5] = new King(WHITE); 
	c.board[2][0] = new Rook(WHITE); 
	
	Cell whiteRook(2,0);
	Cell whiteRookDest1(2,1);
	Cell whiteRookDest2(2,5);
	Cell blackRook(5,0);
	Cell blackRookDest1(5,1);
	Cell blackRookDest2(4,0);
	Cell whiteKing(1,5);
	Cell whiteKingDest(1,4);
	
	//Test White Rook Leaving White King in Check:
	TEST(c.PlayerLeavesOrPutsTheirKingInCheck(whiteRook, whiteRookDest1));
	
	//Test White Rook Taking White King Out of Check:
	TEST(!c.PlayerLeavesOrPutsTheirKingInCheck(whiteRook, whiteRookDest2));
	
	//Test Black Rook Putting Black King in Check:
	TEST(c.PlayerLeavesOrPutsTheirKingInCheck(blackRook, blackRookDest1));
	
	//Test Black Rook Not Putting Black king in Check
	//(and it should return FALSE, EVEN THOUGH it leaves white King in check still,
	// since this function can determine which color to care about.)
	TEST(!c.PlayerLeavesOrPutsTheirKingInCheck(blackRook, blackRookDest2));
	
	//Test White King takes itself out of check (So you make sure you make the move and
	// THEN find the king's cell.)
	TEST(!c.PlayerLeavesOrPutsTheirKingInCheck(whiteKing, whiteKingDest));
	
	return success;
}
/*static*/
bool ChessBoard::TestMakeMoveAndUndo(ostream & os)
{
	bool success = true;
	
	//Starts out with a normal game setup.
	ChessBoard c;
	c.DeletePieces();
	
	//Put my own pieces on:
	Cell startCell(4,4);
	Cell endCell(3,5);
	c.board[4][4] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[3][5] = new Rook(BLACK); //Someone else's color (valid move)
	
	
	//=================== TEST "MakeMove(Move)" ======================
	Move m(PAWN, WHITE, startCell, ROOK, BLACK, endCell);
	c.MakeMove(m);
	if(!TestMakeMoveResult(c, os)) success = false;
	
	//======================== TEST UNDO==============================
	c.Undo();
	
	//Test that it removed the move from the MoveHistory:
	TEST(c.moveHistory.Size() == 0);
	
	//Test that the board was the way it started.
	Piece * whitePawn = c.board[4][4];
	Piece * blackRook = c.board[3][5];
	TEST(whitePawn->GetColor() == WHITE);
	TEST(whitePawn->GetType() == PAWN);
	TEST(blackRook->GetColor() == BLACK);
	TEST(blackRook->GetType() == ROOK);
	
	
	//================ TEST "MakeMove(startCell, endCell)". ============
	c.MakeMove(startCell, endCell);
	if(!TestMakeMoveResult(c, os)) success = false;
	
	return success;
}
/*static*/
bool ChessBoard::TestMakeMoveResult(ChessBoard & c, ostream & os)
{
	bool success = true;
	Cell startCell(4,4);
	Cell endCell(3,5);
	
	//Test that it added the correct move to the move history.
	TEST(c.moveHistory.Size() == 1);
	Move mh = c.moveHistory.Pop();
	TEST(mh.GetSourcePieceType() == PAWN);
	TEST(mh.GetSourcePieceColor() == WHITE);
	TEST(mh.GetCapturedPieceType() == ROOK);
	TEST(mh.GetCapturedPieceColor() == BLACK);
	TEST(mh.GetStartCell() == startCell);
	TEST(mh.GetEndCell() == endCell);
	
	//Put it back the way it was so I can test Undo like nothing happened.
	c.moveHistory.Push(mh);
	
	//Test that the board reflects the move.
	Piece * emptySpace = c.board[4][4];
	Piece * whitePawn = c.board[3][5];
	TEST(emptySpace == NULL);
	TEST(whitePawn->GetColor() == WHITE);
	TEST(whitePawn->GetType() == PAWN);

	return success;
}
/*static*/
bool ChessBoard::TestGetListsOfCells(ostream & os)
{
	//Test "GetListOfCells(PieceColor color)"
	bool success = true;
	
	//Starts out with a normal game setup.
	ChessBoard c; 
	
	list<Cell> whiteCells = c.GetListOfCells(WHITE);
	list<Cell> correctCells;
	Cell pawn1(6,0);
	Cell pawn2(6,1);
	Cell pawn3(6,2);
	Cell pawn4(6,3);
	Cell pawn5(6,4);
	Cell pawn6(6,5);
	Cell pawn7(6,6);
	Cell pawn8(6,7);
	Cell rook1(7,0);
	Cell knight1(7,1);
	Cell bishop1(7,2);
	Cell queen(7,3);
	Cell king(7,4);
	Cell bishop2(7,5);
	Cell knight2(7,6);
	Cell rook2(7,7);
	correctCells.push_back(pawn1);
	correctCells.push_back(pawn2);
	correctCells.push_back(pawn3);
	correctCells.push_back(pawn4);
	correctCells.push_back(pawn5);
	correctCells.push_back(pawn6);
	correctCells.push_back(pawn7);
	correctCells.push_back(pawn8);
	correctCells.push_back(rook1);
	correctCells.push_back(knight1);
	correctCells.push_back(bishop1);
	correctCells.push_back(queen);
	correctCells.push_back(king);
	correctCells.push_back(bishop2);
	correctCells.push_back(knight2);
	correctCells.push_back(rook2);
	
	if(!CompareCellLists(correctCells, whiteCells, os)) success = false;
	
	return success;
}
/*static*/
bool ChessBoard::CompareCellLists(list<Cell> correctCells, list<Cell> generatedCells, ostream & os)
{
	bool success = true;
	//For each correct cell, try and find it in the generatedCells list.
	for(list<Cell>::const_iterator it = correctCells.begin();
		it != correctCells.end(); it++)
	{
		//Find it... (or it will return generatedCells.end() if it was not found)
		list<Cell>::const_iterator item = find(generatedCells.begin(), 
			generatedCells.end(), (*it));
		
		TEST(item != generatedCells.end());
		//If found, remove it so the remaining cells will be only invalid cells.
		if(item != generatedCells.end())
		{
			generatedCells.remove(*it);
		}
		//Otherwise, print a message saying it wasn't found.
		else
		{
			os << "This cell is missing:" << endl;
			os << "CELL: " << (*it).GetRow() << (*it).GetColumn() << endl << endl;
		}
	}
	//Then print those invalid moves if there are any.
	if(!PrintAnyInvalidCellsRemaining(generatedCells, os)) success = false;
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::PrintAnyInvalidCellsRemaining(list<Cell> invalidCells, ostream & os)
{
	bool success = true;
	TEST(invalidCells.size() == 0);
	if(invalidCells.size() != 0)
	{
		os << "These cells should not have been added:\n" << endl;
		PrintListOfCells(invalidCells, os);
	}
	return success;
}
/*static*/
/*DONE*/
void ChessBoard::PrintListOfCells(list<Cell> cellsToPrint, ostream & os)
{
	for(list<Cell>::const_iterator it = cellsToPrint.begin();
		it != cellsToPrint.end(); it++)
	{
		os << "CELL: " << (*it).GetRow() << (*it).GetColumn() << endl;
	}
}
/*static*/
bool ChessBoard::TestPiecesGetPossibleMoves(ostream & os)
{
	bool success = true;
	//---------------------------------------------------------------------------
	//			TEST PIECES' GET POSSIBLE MOVES
	os << "\n\n============= TEST PIECES' GET POSSIBLE MOVES===============\n\n" << endl;
	
	if(!ChessBoard::TestKingsGetPossibleMovesRegardlessOfCheck(os)) success = false;
	if(!ChessBoard::TestKnightsGetPossibleMovesRegardlessOfCheck(os)) success = false;
	if(!ChessBoard::TestRooksGetPossibleMovesRegardlessOfCheck(os)) success = false;
	if(!ChessBoard::TestBishopsGetPossibleMovesRegardlessOfCheck(os)) success = false;
	if(!ChessBoard::TestQueensGetPossibleMovesRegardlessOfCheck(os)) success = false;
	if(!ChessBoard::TestPawnsGetPossibleMovesRegardlessOfCheck(os)) success = false;
	return success;
}
/*static*/
bool ChessBoard::TestCorrectSetupNullsAndPieceColors(ostream& os, ChessBoard & c)
{
	bool success = true;
	
	os << "Testing that rows 2-5 are NULL pointers..." << endl;
	//Check that all of rows 2-5 are NULL pointers.
	for (int currentRow = 2; currentRow < 6; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			TEST(c.board[currentRow][currentColumn] == NULL);
		}	
	}
	
	//Test the rest of the pieces:
	
	os << "Testing that pieces in rows 0 and 1 are black..." << endl;
	//Test rows 0 and 1's colors == BLACK
	for(int row = 0; row < 2; ++row)
	{
		for(int column = 0; column < NUMCOLS; ++column)
		{
			TEST((c.board[row][column])->GetColor() == BLACK);
		}
	}
	
	os << "Testing that pieces in rows 6 and 7 are white..." << endl;
	//Test rows 6 and 7's colors == WHITE
	for(int row = 6; row < NUMROWS; ++row)
	{
		for(int column = 0; column < NUMCOLS; ++column)
		{
			TEST((c.board[row][column])->GetColor() == WHITE);
		}
	}
	return success;
}
/*static*/
bool ChessBoard::TestCorrectSetupPieceTypes(ostream& os, ChessBoard & c)
{
	bool success = true;
	os << "Testing that pieces in rows 0 and 7 have correct types..." << endl;
	//Test that rows 0 and 7 have this sequence of types:
	for(int row = 0; row != 7; row = 7)
	{
		TEST((c.board[row][0])->GetType() == ROOK);
		TEST((c.board[row][1])->GetType() == KNIGHT);
		TEST((c.board[row][2])->GetType() == BISHOP);
		TEST((c.board[row][3])->GetType() == QUEEN);
		TEST((c.board[row][4])->GetType() == KING);
		TEST((c.board[row][5])->GetType() == BISHOP);
		TEST((c.board[row][6])->GetType() == KNIGHT);
		TEST((c.board[row][7])->GetType() == ROOK);
	}
	
	os << "Testing that pieces in rows 1 and 6 are all pawns..." << endl;
	//Test that rows 1 and 6 are all pawns.
	for(int row = 1; row != 6; row = 6)
	{
		for(int column = 0; column < NUMCOLS; ++column)
		{
			TEST((c.board[row][column])->GetType() == PAWN);
		}
	}
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestKingsGetPossibleMovesRegardlessOfCheck(ostream& os)
{
	os << "\n\t======TESTING KINGS GET POSSIBLE MOVES REGARDLESS OF CHECK=========" << endl;
	bool success = true;
	//Make a board setup testing every type of move:
	//1. Off the board 2. Your color 3. Someone else's color 4. Empty
	
	//This automatically puts pieces on the board, 
	//so take them off and put a special test setup on the board.
	ChessBoard c; 
	
	c.DeletePieces();
	c.board[7][0] = new King(BLACK); //You
	c.board[6][0] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[6][1] = new Pawn(BLACK); //Your color (invalid move)
	//[7][1] is empty. (valid move)
	//Everything else: off the board (invalid moves)
	
	//Generate moves based on this board setup
	Cell myCell(7,0);
	list<Move> generatedMoves = c.board[7][0]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);

	//Make correct moves and add them to the correct moves list.
	Cell whitePawnCell(6,0);
	Cell emptyCell(7,1);
	Move m1(KING, BLACK, myCell, PAWN, WHITE, whitePawnCell);
	Move m2(KING, BLACK, myCell, NOTYPE, NOCOLOR, emptyCell);
	list<Move> correctMoves;
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	
	//Test the generated moves.
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestKnightsGetPossibleMovesRegardlessOfCheck(ostream& os)
{
	os << "\n\t======TESTING KNIGHTS GET POSSIBLE MOVES REGARDLESS OF CHECK=========" << endl;
	bool success = true;
	//Make a board setup testing every type of move:
	//1. Off the board 2. Your color 3. Someone else's color 4. Empty
	
	//This automatically puts pieces on the board, 
	//so take them off and put a special test setup on the board.
	ChessBoard c; 
	c.DeletePieces();
	c.board[6][3] = new Knight(BLACK); //You
	c.board[7][1] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[5][1] = new Pawn(BLACK); //Your color (invalid move)
	//[4][2] is empty. (valid move)
	//[4][4] is empty. (valid move)
	//[5][5] is empty. (valid move)
	//[7][5] is empty. (valid move)
	//[8][4] is off the board. (invalid move)
	//[8][2] is off the board. (invalid move)
	
	
	//Generate moves based on this board setup
	Cell myCell(6,3);
	list<Move> generatedMoves = c.board[6][3]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);

	//Make correct moves and add them to the correct moves list.
	Cell whitePawnCell(7,1);
	Cell empty1(4,2);
	Cell empty2(4,4);
	Cell empty3(5,5);
	Cell empty4(7,5);
	Move m1(KNIGHT, BLACK, myCell, PAWN, WHITE, whitePawnCell);
	Move m2(KNIGHT, BLACK, myCell, NOTYPE, NOCOLOR, empty1);
	Move m3(KNIGHT, BLACK, myCell, NOTYPE, NOCOLOR, empty2);
	Move m4(KNIGHT, BLACK, myCell, NOTYPE, NOCOLOR, empty3);
	Move m5(KNIGHT, BLACK, myCell, NOTYPE, NOCOLOR, empty4);
	list<Move> correctMoves;
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	correctMoves.push_back(m3);
	correctMoves.push_back(m4);
	correctMoves.push_back(m5);
	
	//Test the generated moves.
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestRooksGetPossibleMovesRegardlessOfCheck(ostream& os)
{
	os << "\n\t======TESTING ROOKS GET POSSIBLE MOVES REGARDLESS OF CHECK=========" << endl;
	bool success = true;
	//Make a board setup testing every type of move:
	//1. Off the board 2. Your color 3. Someone else's color 4. Empty
	
	//This automatically puts pieces on the board, 
	//so take them off and put a special test setup on the board.
	ChessBoard c;
	c.DeletePieces();
	
	c.board[3][1] = new Rook(BLACK); //You
	c.board[1][1] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[3][4] = new Pawn(BLACK); //Your color (invalid move)
	c.board[4][1] = new Pawn(BLACK); //Your color (invalid move)
	//[3][2] is empty. (valid move)
	//[3][3] is empty. (valid move)
	//[3][0] is empty. (valid move)
	//[2][1] is empty. (valid move)
	//[3][-1] is off the board. (invalid move)
	//the rest of the positions are not up/down/left/right, or they're blocked.
	
	
	//Generate moves based on this board setup
	Cell myCell(3,1);
	list<Move> generatedMoves = c.board[3][1]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);

	//Make correct moves and add them to the correct moves list.
	Cell whitePawnCell(1,1);
	Cell empty1(3,2);
	Cell empty2(3,3);
	Cell empty3(3,0);
	Cell empty4(2,1);
	Move m1(ROOK, BLACK, myCell, PAWN, WHITE, whitePawnCell);
	Move m2(ROOK, BLACK, myCell, NOTYPE, NOCOLOR, empty1);
	Move m3(ROOK, BLACK, myCell, NOTYPE, NOCOLOR, empty2);
	Move m4(ROOK, BLACK, myCell, NOTYPE, NOCOLOR, empty3);
	Move m5(ROOK, BLACK, myCell, NOTYPE, NOCOLOR, empty4);
	list<Move> correctMoves;
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	correctMoves.push_back(m3);
	correctMoves.push_back(m4);
	correctMoves.push_back(m5);
	
	//Test the generated moves.
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestBishopsGetPossibleMovesRegardlessOfCheck(ostream& os)
{
	os << "\n\t======TESTING BISHOPS GET POSSIBLE MOVES REGARDLESS OF CHECK=========" << endl;
	bool success = true;
	//Make a board setup testing every type of move:
	//1. Off the board 2. Your color 3. Someone else's color 4. Empty
	
	//This automatically puts pieces on the board, 
	//so take them off and put a special test setup on the board.
	ChessBoard c;
	c.DeletePieces();
	
	c.board[3][2] = new Bishop(BLACK); //You
	c.board[1][0] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[1][4] = new Pawn(BLACK); //Your color (invalid move)
	c.board[4][3] = new Pawn(BLACK); //Your color (invalid move)
	//[2][1] is empty. (valid move)
	//[2][3] is empty. (valid move)
	//[4][1] is empty. (valid move)
	//[5][0] is empty. (valid move)
	//[6][-1] is off the board. (invalid move)
	//the rest of the positions are not diagonal, or they're blocked.
	
	
	//Generate moves based on this board setup
	Cell myCell(3,2);
	list<Move> generatedMoves = c.board[3][2]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);

	//Make correct moves and add them to the correct moves list.
	Cell whitePawnCell(1,0);
	Cell empty1(2,1);
	Cell empty2(2,3);
	Cell empty3(4,1);
	Cell empty4(5,0);
	Move m1(BISHOP, BLACK, myCell, PAWN, WHITE, whitePawnCell);
	Move m2(BISHOP, BLACK, myCell, NOTYPE, NOCOLOR, empty1);
	Move m3(BISHOP, BLACK, myCell, NOTYPE, NOCOLOR, empty2);
	Move m4(BISHOP, BLACK, myCell, NOTYPE, NOCOLOR, empty3);
	Move m5(BISHOP, BLACK, myCell, NOTYPE, NOCOLOR, empty4);
	list<Move> correctMoves;
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	correctMoves.push_back(m3);
	correctMoves.push_back(m4);
	correctMoves.push_back(m5);
	
	//Test the generated moves.
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestQueensGetPossibleMovesRegardlessOfCheck(ostream& os)
{
	os << "\n\t======TESTING QUEENS GET POSSIBLE MOVES REGARDLESS OF CHECK=========" << endl;
	bool success = true;
	//Make a board setup testing every type of move:
	//1. Off the board 2. Your color 3. Someone else's color 4. Empty
	
	//This automatically puts pieces on the board, 
	//so take them off and put a special test setup on the board.
	ChessBoard c;
	c.DeletePieces();
	
	c.board[3][2] = new Queen(BLACK); //You
	c.board[1][0] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[1][2] = new Pawn(WHITE); //Someone else's color (valid move)
	c.board[1][4] = new Pawn(BLACK); //Your color (invalid move)
	c.board[3][5] = new Pawn(BLACK); //Your color (invalid move)
	c.board[4][3] = new Pawn(BLACK); //Your color (invalid move)
	c.board[4][2] = new Pawn(BLACK); //Your color (invalid move)
	//[3][0] is empty. (valid move)
	//[3][1] is empty. (valid move)
	//[2][1] is empty. (valid move)
	//[4][1] is empty. (valid move)
	//[5][0] is empty. (valid move)
	//[2][3] is empty. (valid move)
	//[3][3] is empty. (valid move)
	//[3][4] is empty. (valid move)
	//[2][2] is empty. (valid move)
	//the rest of the positions are not diagonal, or they're blocked, or off the board.
	
	//Generate moves based on this board setup
	Cell myCell(3,2);
	list<Move> generatedMoves = c.board[3][2]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);

	
	//Make correct moves and add them to the correct moves list.
	list<Move> correctMoves;
	AddCorrectMovesForQueen(correctMoves);
	
	//Test the generated moves.
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	return success;
}
/*static*/
/*DONE*/
void ChessBoard::AddCorrectMovesForQueen(list<Move> & correctMoves)
{
	Cell myCell(3,2);
	Cell whitePawnCell1(1,0);
	Cell whitePawnCell2(1,2);
	Cell empty1(3,0);
	Cell empty2(3,1);
	Cell empty3(2,1);
	Cell empty4(4,1);
	Cell empty5(5,0);
	Cell empty6(2,3);
	Cell empty7(3,3);
	Cell empty8(3,4);
	Cell empty9(2,2);
	Move m1(QUEEN, BLACK, myCell, PAWN, WHITE, whitePawnCell1);
	Move m2(QUEEN, BLACK, myCell, PAWN, WHITE, whitePawnCell2);
	Move m3(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty1);
	Move m4(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty2);
	Move m5(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty3);
	Move m6(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty4);
	Move m7(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty5);
	Move m8(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty6);
	Move m9(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty7);
	Move m10(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty8);
	Move m11(QUEEN, BLACK, myCell, NOTYPE, NOCOLOR, empty9);
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	correctMoves.push_back(m3);
	correctMoves.push_back(m4);
	correctMoves.push_back(m5);
	correctMoves.push_back(m6);
	correctMoves.push_back(m7);
	correctMoves.push_back(m8);
	correctMoves.push_back(m9);
	correctMoves.push_back(m10);
	correctMoves.push_back(m11);
}
/*static*/
/*DONE*/
bool ChessBoard::TestPawnsGetPossibleMovesRegardlessOfCheck(ostream& os)
{
	os << "\n\t======TESTING PAWNS GET POSSIBLE MOVES REGARDLESS OF CHECK=========" << endl;
	bool success = true;
	
	//Make a board setup testing every type of move:
	//1. Off the board 
	//2. Capture left 
	//3. Capture right 
	//4. Your color 
	//5. Empty in front 
	//6. Can't capture 
	//7. Home row (able to move twice)
	//8. Blocked in front 
	//9. Not home row
	
	//This automatically puts pieces on the board, 
	//so take them off and put a special test setup on the board.
	ChessBoard c; 
	
	
	
	
	
	//1. Check Black pawns (goes downward)
	
	c.DeletePieces();
	//Yes, there are 4 "You"'s so I can test more scenarios.
	c.board[1][1] = new Pawn(BLACK); //You #1
	c.board[1][7] = new Pawn(BLACK); //You #2
	c.board[4][3] = new Pawn(BLACK); //You #3
	c.board[7][1] = new Pawn(BLACK); //You #4
	c.board[2][2] = new King(WHITE); //Someone else's color (valid move)
	c.board[2][6] = new King(WHITE); //Someone else's color (valid move)
	c.board[2][0] = new King(BLACK); //Your color (invalid move)
	c.board[2][1] = new King(BLACK); //Your color (invalid move)
	//[5][3] is empty. (valid move)
	//[2][7] is empty. (valid move)
	//[3][7] is empty. (valid move)
	
	if(!TestBlackPawnYou1(os, c)) success = false;
	if(!TestBlackPawnYou2(os, c)) success = false;
	if(!TestBlackPawnYou3(os, c)) success = false;
	if(!TestBlackPawnYou4(os, c)) success = false;

	
	
	
	
	
	//2. Check White pawns (goes upward)
	
	c.DeletePieces();
	//Yes, there are 4 "You"'s so I can test more scenarios.
	c.board[6][1] = new Pawn(WHITE); //You #1
	c.board[6][7] = new Pawn(WHITE); //You #2
	c.board[3][3] = new Pawn(WHITE); //You #3
	c.board[0][1] = new Pawn(WHITE); //You #4
	c.board[5][2] = new King(BLACK); //Someone else's color (valid move)
	c.board[5][6] = new King(BLACK); //Someone else's color (valid move)
	c.board[5][0] = new King(WHITE); //Your color (invalid move)
	c.board[5][1] = new King(WHITE); //Your color (invalid move)
	//[2][3] is empty. (valid move)
	//[5][7] is empty. (valid move)
	//[4][7] is empty. (valid move)
	
	if(!TestWhitePawnYou1(os, c)) success = false;
	if(!TestWhitePawnYou2(os, c)) success = false;
	if(!TestWhitePawnYou3(os, c)) success = false;
	if(!TestWhitePawnYou4(os, c)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestBlackPawnYou1(ostream& os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #1
	Cell myCell(1,1);
	list<Move> generatedMoves = c.board[1][1]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//Make correct moves and add them to the correct moves list.
	Cell whiteKingCell(2,2);
	Move m(PAWN, BLACK, myCell, KING, WHITE, whiteKingCell);
	list<Move> correctMoves;
	correctMoves.push_back(m);
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestBlackPawnYou2(ostream& os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #2
	Cell myCell(1,7);
	list<Move>generatedMoves = c.board[1][7]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//Make correct moves and add them to the correct moves list.
	Cell whiteKingCell(2,6);
	Cell emptyCell1(2,7);
	Cell emptyCell2(3,7);
	Move m1(PAWN, BLACK, myCell, KING, WHITE, whiteKingCell);
	Move m2(PAWN, BLACK, myCell, NOTYPE, NOCOLOR, emptyCell1);
	Move m3(PAWN, BLACK, myCell, NOTYPE, NOCOLOR, emptyCell2);
	list<Move> correctMoves;
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	correctMoves.push_back(m3);
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestBlackPawnYou3(ostream & os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #3
	Cell myCell(4,3);
	list<Move>generatedMoves = c.board[4][3]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//Make correct moves and add them to the correct moves list.
	Cell emptyCell(5,3);
	Move m(PAWN, BLACK, myCell, NOTYPE, NOCOLOR, emptyCell);
	list<Move> correctMoves;
	correctMoves.push_back(m);
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestBlackPawnYou4(ostream & os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #4
	Cell myCell(7,1);
	list<Move>generatedMoves = c.board[7][1]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//There are no correct moves.
	list<Move> correctMoves;
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestWhitePawnYou1(ostream & os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #1
	Cell myCell(6,1);
	list<Move> generatedMoves = c.board[6][1]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//Make correct moves and add them to the correct moves list.
	Cell blackKingCell(5,2);
	Move m(PAWN, WHITE, myCell, KING, BLACK, blackKingCell);
	list<Move> correctMoves;
	correctMoves.push_back(m);
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestWhitePawnYou2(ostream & os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #2
	Cell myCell(6,7);
	list<Move>generatedMoves = c.board[6][7]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//Make correct moves and add them to the correct moves list.
	Cell blackKingCell(5,6);
	Cell emptyCell1(5,7);
	Cell emptyCell2(4,7);
	Move m1(PAWN, WHITE, myCell, KING, BLACK, blackKingCell);
	Move m2(PAWN, WHITE, myCell, NOTYPE, NOCOLOR, emptyCell1);
	Move m3(PAWN, WHITE, myCell, NOTYPE, NOCOLOR, emptyCell2);
	list<Move> correctMoves;
	correctMoves.push_back(m1);
	correctMoves.push_back(m2);
	correctMoves.push_back(m3);
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestWhitePawnYou3(ostream & os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #3
	Cell myCell(3,3);
	list<Move>generatedMoves = c.board[3][3]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//Make correct moves and add them to the correct moves list.
	Cell emptyCell(2,3);
	Move m(PAWN, WHITE, myCell, NOTYPE, NOCOLOR, emptyCell);
	list<Move> correctMoves;
	correctMoves.push_back(m);
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
bool ChessBoard::TestWhitePawnYou4(ostream & os, ChessBoard & c)
{
	bool success = true;
	
	//----------------------------------------------------------------------
	//Generate moves based on this board setup for You #4
	Cell myCell(0,1);
	list<Move>generatedMoves = c.board[0][1]->GetPossibleMovesRegardlessOfCheck(myCell, c.board);
	
	//There are no correct moves.
	list<Move> correctMoves;
	
	//Test the generated move(s).
	if(!CompareMoveLists(correctMoves, generatedMoves, os)) success = false;
	
	return success;
}
/*static*/
/*DONE*/
void ChessBoard::PrintListOfMoves(list<Move> movesToPrint, ostream & os)
{
	for(list<Move>::const_iterator it = movesToPrint.begin();
		it != movesToPrint.end(); it++)
	{
		PrintMove((*it), os);
	}
}
/*static*/
/*DONE*/
void ChessBoard::PrintMove(Move m, ostream & os)
{
	os << "TYPE: " << m.GetSourcePieceType() << endl;
	os << "COLOR: " << m.GetSourcePieceColor() << endl;
	os << "STARTCELL: " << m.GetStartCell().GetRow() << m.GetStartCell().GetColumn() << endl;
	os << "CAPTUREDTYPE: " << m.GetCapturedPieceType() << endl;
	os << "CAPTUREDCOLOR: " << m.GetCapturedPieceColor() << endl;
	os << "ENDCELL: " << m.GetEndCell().GetRow() << m.GetEndCell().GetColumn() << endl;
	os << endl;
}
/*static*/
/*DONE*/
bool ChessBoard::PrintAnyInvalidMovesRemaining(list<Move> invalidMoves, ostream & os)
{
	bool success = true;
	TEST(invalidMoves.size() == 0);
	if(invalidMoves.size() != 0)
	{
		os << "These moves should not have been added:\n" << endl;
		PrintListOfMoves(invalidMoves, os);
	}
	return success;
}

/*static*/
/*DONE*/
bool ChessBoard::CompareMoveLists(list<Move> correctMoves, list<Move> generatedMoves, ostream & os)
{
	bool success = true;
	//For each correct move, try and find it in the generatedMoves list.
	for(list<Move>::const_iterator it = correctMoves.begin();
		it != correctMoves.end(); it++)
	{
		//Find it... (or it will return generatedMoves.end() if it was not found)
		list<Move>::const_iterator item = find(generatedMoves.begin(), 
			generatedMoves.end(), (*it));
		
		TEST(item != generatedMoves.end());
		//If found, remove it so the remaining moves will be only invalid moves.
		if(item != generatedMoves.end())
		{
			generatedMoves.remove(*it);
		}
		//Otherwise, print a message saying it wasn't found.
		else
		{
			os << "This move is missing:" << endl;
			PrintMove((*it), os);
		}
	}
	//Then print those invalid moves if there are any.
	if(!PrintAnyInvalidMovesRemaining(generatedMoves, os)) success = false;
	return success;
}
/*DONE*/
ChessBoard::ChessBoard()
{
	//1. Initialize board piece pointers.
	board = new Piece** [NUMROWS];
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		board[currentRow] = new Piece*[NUMCOLS];
	}
	//2. Prevent invalid pointers from remaining.
	MakePiecePointersPointToNull();
	
	//3. Then leave them all NULL except for the cells that are supposed
	//to have pieces on them.
	PutPiecesOnBoardForStartOfGame();
}

/*DONE*/
void ChessBoard::DeletePieces()
{
	//Note: Got this looping structure from the same website 
	//(see Chessboard()'s description in ChessBoard.h)
	
	//Go through all of board's Piece pointers.
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			//If it points to something, delete the piece it points to.
			//[We assume it's pointing to a piece and I tried to check that 
			//assumption with an assert, but typeid().name() returned numbers
			//in front of the classes, so I'm like, "*sigh* fine........"
			if(board[currentRow][currentColumn] != NULL)
			{
				delete board[currentRow][currentColumn];
			}
		}	
	}
	//This is to prevent myself from trying to access deleted heap data.
	MakePiecePointersPointToNull();
}
/*DONE*/
void ChessBoard::MakePiecePointersPointToNull()
{
	// Make all of the pointers point to NULL.
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			 board[currentRow][currentColumn] = NULL;
		}	
	}
}
/*DONE*/
ChessBoard::~ChessBoard()
{
	DeletePieces();
	DeletePiecePointers();
	delete[] board;
}
/*DONE*/
void ChessBoard::DeletePiecePointers()
{
	//Go through all of board's pointers to Piece pointers.
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		//Delete what the Piece ** points to 
		//(it points to the first element of an array of piece pointers).
		delete[] board[currentRow];
	}
}
/*DONE*/
Move ChessBoard::Undo()
{
	Move latestMove = moveHistory.Pop();
	
	
	//Make shorthand aliases for this function...
	Cell startCell = latestMove.GetStartCell();
	Cell endCell = latestMove.GetEndCell();
	Piece * startCellPiece = board[startCell.GetRow()][startCell.GetColumn()];
	Piece * endCellPiece = board[endCell.GetRow()][endCell.GetColumn()];
	PieceType capturedType = latestMove.GetCapturedPieceType();
	PieceColor capturedColor = latestMove.GetCapturedPieceColor();
	
	
	//Check that startcell and endcell are consistent with the latest move.
	assert(startCellPiece == NULL); //It moved FROM here so this is empty.
	assert(endCellPiece != NULL); //It moved TO here so this is NOT empty.
	assert(endCellPiece->GetColor() == latestMove.GetSourcePieceColor()); //source ended up in end.
	assert(endCellPiece->GetType() == latestMove.GetSourcePieceType()); //source ended up in end.
	
	
	
	
	//=========== MOVE THE SOURCE PIECE FROM ENDCELL TO STARTCELL ==============
	board[startCell.GetRow()][startCell.GetColumn()] = endCellPiece;
	
	
	
	
	//================REVIVE THE CAPTURED PIECE, IF ANY====================
	
	//If there was no captured piece...
	if(capturedType == NOTYPE || capturedColor == NOCOLOR)
	{
		// (Check for consistency here)
		assert((capturedType == NOTYPE) && (capturedColor == NOCOLOR));
		
		//...make endCell point to NULL. DO NOT DELETE IT!!! It's pointing to the same piece that
		//startCell is pointing to! startCell still needs that piece alive!!!!
		board[endCell.GetRow()][endCell.GetColumn()] = NULL;
	}
	//If there WAS a captured piece...
	else
	{
		//...make sure they didn't capture their own color...
		assert(capturedColor != latestMove.GetSourcePieceColor());
		
		//...and make endCell point to a NEW piece object with the 
		//captured piece's type and color.
		RevivePiece(capturedType, capturedColor, endCell);
		
	} 
	return latestMove;
}
/*DONE*/
void ChessBoard::RevivePiece(PieceType capturedType, PieceColor capturedColor, Cell endCell)
{
	switch(capturedType)
	{
	case PAWN:
		board[endCell.GetRow()][endCell.GetColumn()] = 
			new Pawn(capturedColor);
		break;
	case ROOK:
		board[endCell.GetRow()][endCell.GetColumn()] = 
			new Rook(capturedColor);
		break;
	case KNIGHT:
		board[endCell.GetRow()][endCell.GetColumn()] = 
			new Knight(capturedColor);
		break;
	case BISHOP:
		board[endCell.GetRow()][endCell.GetColumn()] = 
			new Bishop(capturedColor);
		break;
	case QUEEN:
		board[endCell.GetRow()][endCell.GetColumn()] = 
			new Queen(capturedColor);
		break;
	case KING:
		board[endCell.GetRow()][endCell.GetColumn()] = 
			new King(capturedColor);
		break;
	default:
		assert(1 == 2); //Should never happen.
		break;
	}
}	
/*DONE*/
Move ChessBoard::MakeMove(Cell startCell, Cell endCell)
{
	//Validate start and end cells
	ValidateStartAndEndCells(startCell, endCell);
	
	//========================= MAKE A MOVE OBJECT========================
	//Get piece pointers
	Piece * startPiece = board[startCell.GetRow()][startCell.GetColumn()];
	Piece * capturedPiece = board[endCell.GetRow()][endCell.GetColumn()];
	
	//Allocate memory...
	PieceType sourceType;
	PieceColor sourceColor;
	PieceType capturedType;
	PieceColor capturedColor;
	
	//Get start piece info
	sourceType = startPiece->GetType();
	sourceColor = startPiece->GetColor();
	
	//Get captured piece info
	if(capturedPiece != NULL)
	{
		capturedType = capturedPiece->GetType();
		capturedColor = capturedPiece->GetColor();
	}
	else
	{
		capturedType = NOTYPE;
		capturedColor = NOCOLOR;
	}
	
	//Put it all into a move object
	Move m(sourceType, sourceColor, startCell, capturedType, capturedColor, endCell);
	
	//Pass it off to the true Move function.
	return MakeMoveActualFunction(m);
}
/*DONE*/
Move ChessBoard::MakeMove(Move m)
{
	//Assert that it's a valid move.
	ValidateMove(m);
	
	//Now that that is settled, pass it off to the true Move function.
	return MakeMoveActualFunction(m);
}
/*DONE*/
Move ChessBoard::MakeMoveActualFunction(Move m)
{
	//==================UPDATE THE MODEL TO REFLECT THE MOVE====================
	//Get piece pointers
	Piece * startPiece = board[m.GetStartCell().GetRow()][m.GetStartCell().GetColumn()];
	Piece * capturedPiece = board[m.GetEndCell().GetRow()][m.GetEndCell().GetColumn()];
	
	//1. If there was a capture, delete the piece before you overwrite the pointer.
	if(capturedPiece != NULL)
	{
		delete capturedPiece;
		//No need to make it null, since it's going to be overwritten anyway.
	}
	
	//2. The destination cell now points to the start piece, overwriting the invalid pointer.
	//(or overwriting NULL, which is also fine.)
	board[m.GetEndCell().GetRow()][m.GetEndCell().GetColumn()] = startPiece;
	
	//3. The source cell is supposed to be empty now (so set it to NULL).
	board[m.GetStartCell().GetRow()][m.GetStartCell().GetColumn()] = NULL;
	
	//4. Add the move to the MoveHistory.
	moveHistory.Push(m);
	
	//5. Give the move to the GUI so it can use it to update the view.
	return m;
}
/*INCOMPLETE - needs to catch the exception.*/
void ChessBoard::SaveGameAsXML(string fileName)
{
	chessXMLSaver.SaveGameToFile(fileName, board, moveHistory);
}

void ChessBoard::LoadGameFromXML(string fileName)
{
	//1. Discards the current game.
	ClearGame();
	
	//2. Parses the XML from the file and initializes the board to that game state
	// by updating the ChessBoard's piece pointers and move history.
	chessXMLLoader.LoadGameFromFile(fileName, board, moveHistory);
}

/*DONE*/
void ChessBoard::ClearGame()
{
	DeletePieces();
	MakePiecePointersPointToNull();
	moveHistory.Clear();
}
/*DONE*/
void ChessBoard::PutPiecesOnBoardForStartOfGame()
{
	//Initialize row 0:
	board[0][0] = new Rook(BLACK);
	board[0][1] = new Knight(BLACK);
	board[0][2] = new Bishop(BLACK);
	board[0][3] = new Queen(BLACK);
	board[0][4] = new King(BLACK);
	board[0][5] = new Bishop(BLACK);
	board[0][6] = new Knight(BLACK);
	board[0][7] = new Rook(BLACK);
	
	//Initialize row 1:
	board[1][0] = new Pawn(BLACK);
	board[1][1] = new Pawn(BLACK);
	board[1][2] = new Pawn(BLACK);
	board[1][3] = new Pawn(BLACK);
	board[1][4] = new Pawn(BLACK);
	board[1][5] = new Pawn(BLACK);
	board[1][6] = new Pawn(BLACK);
	board[1][7] = new Pawn(BLACK);
	
	//Initialize row 6:
	board[6][0] = new Pawn(WHITE);
	board[6][1] = new Pawn(WHITE);
	board[6][2] = new Pawn(WHITE);
	board[6][3] = new Pawn(WHITE);
	board[6][4] = new Pawn(WHITE);
	board[6][5] = new Pawn(WHITE);
	board[6][6] = new Pawn(WHITE);
	board[6][7] = new Pawn(WHITE);
	
	//Initialize row 7:
	board[7][0] = new Rook(WHITE);
	board[7][1] = new Knight(WHITE);
	board[7][2] = new Bishop(WHITE);
	board[7][3] = new Queen(WHITE);
	board[7][4] = new King(WHITE);
	board[7][5] = new Bishop(WHITE);
	board[7][6] = new Knight(WHITE);
	board[7][7] = new Rook(WHITE);
}
/*DONE*/
void ChessBoard::NewGame()
{
	ClearGame();
	PutPiecesOnBoardForStartOfGame();
}
/*DONE*/
list<Move> ChessBoard::GetValidMoves(Cell cell)
{
	Piece * piece = board[cell.GetRow()][cell.GetColumn()];
	
	//If there isn't a piece there, then there are no valid moves.
	if(piece == NULL)
	{
		list<Move> emptyList;
		return emptyList;
	}
	
	//Get the possible moves for the piece in that cell.
	list<Move> possibleMoves = piece->GetPossibleMovesRegardlessOfCheck(cell, board);
	list<Move> validMoves;
	
	//For each possible move...
	for(list<Move>::const_iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++)
	{
		//If it puts or leaves their king in check (it can figure out by using
		//the color of the source cell), don't include it in valid moves. 
		if(!PlayerLeavesOrPutsTheirKingInCheck(*it))
		{
			validMoves.push_back(*it);
		}
	}
	return validMoves;
}

/*DONE.*/
bool ChessBoard::PlayerLeavesOrPutsTheirKingInCheck(Cell startCell, Cell endCell)
{
	//Check for valid arguments:
	ValidateStartAndEndCells(startCell, endCell);
	
	//=========MAKE A MOVE OBJECT BASED OFF OF STARTCELL AND ENDCELL:=======
	
	//Get piece pointers
	Piece * startPiece = board[startCell.GetRow()][startCell.GetColumn()];
	Piece * capturedPiece = board[endCell.GetRow()][endCell.GetColumn()];
	
	//Allocate memory...
	PieceType sourceType;
	PieceColor sourceColor;
	PieceType capturedType;
	PieceColor capturedColor;
	
	//Get start piece info
	sourceType = startPiece->GetType();
	sourceColor = startPiece->GetColor();
	
	//Get captured piece info
	if(capturedPiece != NULL)
	{
		capturedType = capturedPiece->GetType();
		capturedColor = capturedPiece->GetColor();
	}
	else
	{
		capturedType = NOTYPE;
		capturedColor = NOCOLOR;
	}
	
	//Put it all into a move object
	Move m(sourceType, sourceColor, startCell, capturedType, capturedColor, endCell);

	//================ PASS IT OFF TO THE REAL FUNCTION================
	return PlayerLeavesOrPutsTheirKingInCheckActualFunction(m);
	
}
/*DONE*/
void ChessBoard::ValidateStartAndEndCells(Cell startCell, Cell endCell)
{
	 //Asserts that...
	//1. startCell and endCell are both on the board.
	assert(startCell.IsOnTheBoard());
	assert(endCell.IsOnTheBoard());
	
	// (Get piece pointers)
	Piece * startPiece = board[startCell.GetRow()][startCell.GetColumn()];
	Piece * capturedPiece = board[endCell.GetRow()][endCell.GetColumn()];
	
	 //2. startCell has a piece on it.
	assert(startPiece != NULL);
	
	
	if(capturedPiece != NULL)
	{
		//3. If there was a capture, that piece has a type and color.
		assert(capturedPiece->GetType() != NOTYPE);
		assert(capturedPiece->GetColor() != NOCOLOR);
		
		//4. If there was a capture, the startCell piece's color is different
		//   than the endCell piece's color.
		assert(capturedPiece->GetColor() != startPiece->GetColor());
	}
	
}
/*DONE*/
void ChessBoard::ValidateMove(Move m)
{
	// (Get piece pointers)
	Piece * startPiece = board[m.GetStartCell().GetRow()][m.GetStartCell().GetColumn()];
	Piece * capturedPiece = board[m.GetEndCell().GetRow()][m.GetEndCell().GetColumn()];
	
	//Asserts that...
	//1. m's startCell and endCell are both on the board.
	assert(m.GetStartCell().IsOnTheBoard());
	assert(m.GetEndCell().IsOnTheBoard());
	
	//2. startCell has a piece on it.
	assert(startPiece != NULL);
	
	
	//3. startCell piece's type is the same as the move's claimed start type.
	assert(startPiece->GetType() == m.GetSourcePieceType());
	
	//4. startCell piece's color is the same as the move's claimed start color.
	assert(startPiece->GetColor() == m.GetSourcePieceColor());
	
	if(capturedPiece != NULL)
	{
		//5. If endCell has a piece, its type is the same as the move's claimed
		//   captured type.
		assert(capturedPiece->GetType() == m.GetCapturedPieceType());
		
		//6. If endCell has a piece, its color is the same as the move's claimed
		//   captured color.
		assert(capturedPiece->GetColor() == m.GetCapturedPieceColor());
	}
	else
	{
		//7. If endCell doesn't have a piece, the move's claimed captured type is NOTYPE.
		assert(m.GetCapturedPieceType() == NOTYPE);
		
		//8. If endCell doesn't have a piece, the move's claimed captured color is NOCOLOR.
		assert(m.GetCapturedPieceColor() == NOCOLOR);
	}
}
/*DONE*/
bool ChessBoard::PlayerLeavesOrPutsTheirKingInCheck(Move m)
{
	//Asserts:
	ValidateMove(m);
	
	//================ PASS IT OFF TO THE REAL FUNCTION================
	return PlayerLeavesOrPutsTheirKingInCheckActualFunction(m);
}
/*DONE*/
bool ChessBoard::PlayerLeavesOrPutsTheirKingInCheckActualFunction(Move m)
{
	MakeMove(m);
	
	//Find the king's cell AFTER you made the move, in case you moved the king.
	PieceColor playersColor = m.GetSourcePieceColor();
	Cell kingsCell = FindKingsCell(playersColor);
	
	//Get a list of opponent's cells.
	PieceColor opponentsColor = ((playersColor == WHITE) ? BLACK : WHITE);
	list<Cell> opponentsPiecesCells = GetListOfCells(opponentsColor);
	
	//For each of the opponents' pieces...
	for(list<Cell>::const_iterator it = opponentsPiecesCells.begin(); 
		it != opponentsPiecesCells.end(); it++)
	{
		Cell currentCell = (*it);
		Piece * currentPiece = board[currentCell.GetRow()][currentCell.GetColumn()];
		
		//...get its possible moves...
		list<Move> piecesPossibleMoves = 
			currentPiece->GetPossibleMovesRegardlessOfCheck(currentCell, board);
		
		//... and for each of that piece's possible moves...
		for(list<Move>::const_iterator it = piecesPossibleMoves.begin(); 
		it != piecesPossibleMoves.end(); it++)
		{
			Move currentMove = (*it);
			Cell endCell = currentMove.GetEndCell();
			
			//...if it lets them capture the king, then say that the original
			//move leaves or puts the king in check.
			if(endCell == kingsCell)
			{
				Undo();
				return true;
			}
		}
		
	}
	//If you got this far, then that move would not put that player's king in check.
	Undo(); //DON'T FORGET THIS!!!
	return false;
}
/*DONE*/
Cell ChessBoard::FindKingsCell(PieceColor color)
{
	//Iterate through the whole board.
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			Piece * piece = board[currentRow][currentColumn];
			
			//Don't try to access a null pointer.
			if(piece == NULL)
			{
				continue;
			}
			//If this is the King of the given color, then return the a cell
			//with its coordinates.
			if(piece->GetColor() == color && piece->GetType() == KING)
			{
				Cell kingsCell(currentRow, currentColumn);
				return kingsCell;
			}
		}	
	}
	//If you got this far, something was wrong. The king should always be on the board.
	assert(1 == 2);
}

/*DONE*/
list<Cell> ChessBoard::GetListOfCells(PieceColor color)
{
	list<Cell> listOfCells;
	
	//Iterate through the board, adding cells that have pieces of the given color.
	for (int currentRow = 0; currentRow < NUMROWS; ++currentRow) 
	{
		for (int currentColumn = 0; currentColumn < NUMCOLS; ++currentColumn) 
		{
			//If there is a piece at this location...
			Piece * currentPiece = board[currentRow][currentColumn];
			if(currentPiece!= NULL)
			{
				//... and it's the right color...
				if(currentPiece->GetColor() == color)
				{
					//...then  make a cell with these coordinates and add
					//it to the list.
					Cell cell(currentRow, currentColumn);
					listOfCells.push_back(cell);
				}
				
			}
		}
	}
	return listOfCells;
}
/*DONE*/
bool ChessBoard::WhitesTurn()
{
	//Since white goes first, then it is white's turn if the number of moves is 0, (so white
	//can be first), 2, (so white can be third), 4, 6, ... and so on.
	//So it returns true if the moves history size is a multiple of two.
	return ((moveHistory.Size() % 2) == 0);
}
/*DONE*/
bool ChessBoard::IsEmpty(int row, int column)
{
	return (board[row][column] == NULL);
}

/*DONE*/
bool ChessBoard::IsAPieceOfThisColor(int row, int column, PieceColor color)
{
	if(board[row][column] == NULL)
	{
		return false;
	}
	return (board[row][column]->GetColor() == color);
}
/*DONE*/
bool ChessBoard::CanUndo()
{
	return moveHistory.Size();
}

list<Move>::const_iterator ChessBoard::GetMoveHistoryIterator()
{
	return moveHistory.GetIterator();
}

list<Move>::const_iterator ChessBoard::GetMoveHistoryEndIterator()
{
	return moveHistory.EndIterator();
}