/* 
 * File:   ChessXMLLoader.cpp
 * Author: lexic92
 *
 * Created on April 11, 2012, 6:18 AM
 */

#include "ChessXMLLoader.h"

#include <cstdlib> //for atoi
#include <iostream>
#include <cassert>

using namespace std;

/*ALL OF THESE HAVE BEEN STEPPED THROUGH BY ME, AND THEY LOOK ACCURATE*/
/*(When compared to a sample load file)*/

/*DONE*/
void ChessXMLLoader::LoadGameFromFile(string fileName, Piece *** board, MoveHistory & moveHistory)
{
	
	string fileNameFullLength = "file://";
	fileNameFullLength += fileName;
	//Get tokenizer ready.

	URLInputStream urlInputStream(fileNameFullLength);
	HTMLTokenizer tokenizer(&urlInputStream);
	tok = &tokenizer;
	
	
	//currentToken now has <chessgame>.
	HTMLToken currentToken = GetNextNonTextToken();
	assert((currentToken.GetType() == TAG_START) && (currentToken.GetValue() == "chessgame"));
	
	
	//Parse the stuff between <board> and </board>.
	ParseBoardSection(board);
	
	
	//Parse the stuff between <history> and </history>.
	ParseHistorySection(board, moveHistory);
	
	//currentToken now has </chessgame>.
	currentToken = GetNextNonTextToken();
	cout << "currentToken </chessgame>: " << currentToken.GetValue() << endl;
	assert((currentToken.GetType() == TAG_END) && (currentToken.GetValue() == "chessgame"));
	
}
/*DONE*/
void ChessXMLLoader::ParseHistorySection(Piece *** board, MoveHistory & moveHistory)
{
	//currentToken now has <history>.
	HTMLToken currentToken = GetNextNonTextToken();
	assert((currentToken.GetType() == TAG_START) && (currentToken.GetValue() == "history"));
	
	//Make currentToken either have </history> or <move>, depending on if there was a move.
	currentToken = GetNextNonTextToken();
	
	//While the history has a move, parse it and add it to the history.
	while(currentToken.GetValue() == "move")
	{
		//Note: tok is now pointing to the thing after <move>, so it is assumed to
		//be the first of 2 or 3 <piece>'s.
		ParseMoveAndAddItToMoveHistory(moveHistory);
		
		//Make currentToken contain the next token after </move>.
		//(It's either <move> or </history>.)
		currentToken = GetNextNonTextToken();
	}
	//Now, tok points to the token after </history>, meaning it points to </chessgame>.
	
}
/*DONE*/
void ChessXMLLoader::ParseMoveAndAddItToMoveHistory(MoveHistory & moveHistory)
{
	//Next token must be the first of 2 or 3 <piece/>'s.
	HTMLToken pieceTag = GetNextNonTextToken();
	assert(pieceTag.GetValue() == "piece");
	
	//-----------------Get piece1's data----------------------
	string typeString = pieceTag.GetAttribute("type");
	string colorString = pieceTag.GetAttribute("color");
	string rowString = pieceTag.GetAttribute("row");
	string columnString = pieceTag.GetAttribute("column");
	
	//Convert the numbers to ints
	int startRow = atoi(rowString.c_str());
	int startColumn = atoi(columnString.c_str());
	
	
	
	
	//-----------------Get piece2's data.----------------------
	HTMLToken secondPieceTag = GetNextNonTextToken();
	
	//Should be the same type and color as piece1 if it was valid XML.
	assert(pieceTag.GetAttribute("type") == typeString);
	assert(pieceTag.GetAttribute("color") == colorString);
	string endRowString = secondPieceTag.GetAttribute("row");
	string endColumnString = secondPieceTag.GetAttribute("column");
	
	//Convert the row and column numbers to ints
	int endRow = atoi(endRowString.c_str());
	int endColumn = atoi(endColumnString.c_str());
	
	
	
	
	//--------------- Conclusions you can draw so far--------------
	
	//Start cell was from the first <piece> tag...
	Cell startCell(startRow, startColumn);
	
	//End cell was from the second <piece> tag...
	Cell endCell(endRow, endColumn);
	
	//Convert source piece's type & color from the first <piece> tag...
	PieceType sourceType = ConvertStringToPieceType(typeString);
	PieceColor sourceColor = ConvertStringToPieceColor(colorString);
	
	
	
	//----------------Get Capture data if applicable------------
	HTMLToken thirdPieceTagOrEndMoveTag = GetNextNonTextToken();

	
	//If it's TAG_END...
	if(thirdPieceTagOrEndMoveTag.GetType() == TAG_END)
	{
		//...then it's </move>, so there was no capture.
		assert(thirdPieceTagOrEndMoveTag.GetValue() == "move");
		
		//So, type & color are NOTYPE and NOCOLOR.
		//Make a move from it and add it to the MoveHistory.
		Move m(sourceType, sourceColor, startCell, NOTYPE, NOCOLOR, endCell);
		moveHistory.Push(m);
	}
	else
	{
		//Then there was a capture.
		assert(thirdPieceTagOrEndMoveTag.GetValue() == "piece");
		
		//Should be the same row and column as the piece2 
		//(where it ended up after the move).
		assert(thirdPieceTagOrEndMoveTag.GetAttribute("row") == endRowString);
		assert(thirdPieceTagOrEndMoveTag.GetAttribute("column") == endColumnString);
		
		//Get captured piece type and color...
		string captureTypeString = thirdPieceTagOrEndMoveTag.GetAttribute("type");
		string captureColorString = thirdPieceTagOrEndMoveTag.GetAttribute("color");
		PieceType captureType = ConvertStringToPieceType(captureTypeString);
		PieceColor captureColor = ConvertStringToPieceColor(captureColorString);
		
		//Make tok point after the move, like it should.
		HTMLToken blah = GetNextNonTextToken();
		
		//Make a move out of it and add it to the MoveHistory.
		Move m(sourceType, sourceColor, startCell, captureType, captureColor, endCell);
		moveHistory.Push(m);
	}
}

/*DONE - I carefully inspected it.*/
void ChessXMLLoader::ParseBoardSection(Piece *** board)
{
	//currentToken now has <board>.
	HTMLToken currentToken = GetNextNonTextToken();
	cout << "board: " << currentToken.GetValue() << endl;
	assert((currentToken.GetType() == TAG_START) && (currentToken.GetValue() == "board"));
	
	
	//While there is a <piece/>...
	//(always assume that if it's not TAG_END (for board), then it's a <piece/>.)
	currentToken = GetNextNonTextToken();
	while(currentToken.GetType() == TAG_START)
	{
		//Put it on the board.
		ParsePieceTagAndExtractData(currentToken, board);
		
		//Advance to next token.
		currentToken = GetNextNonTextToken();
	}
	
	//currentToken now has </board>.
	assert((currentToken.GetType() == TAG_END) && (currentToken.GetValue() == "board"));
}
/*DONE*/
void ChessXMLLoader::ParsePieceTagAndExtractData(HTMLToken pieceTag, Piece *** board)
{
	//Already assume the value is "piece" because it's in <board>.
	string typeString = pieceTag.GetAttribute("type");
	string colorString = pieceTag.GetAttribute("color");
	string rowString = pieceTag.GetAttribute("row");
	string columnString = pieceTag.GetAttribute("column");

	//Convert the numbers to ints
	int row = atoi(rowString.c_str());
	int column = atoi(columnString.c_str());

	//Convert the type and color to PieceType and PieceColor enum types
	PieceType type = ConvertStringToPieceType(typeString);
	PieceColor color = ConvertStringToPieceColor(colorString);

	//Put it on the board.
	GeneratePiece(type, color, row, column, board);
}
/*DONE*/
void ChessXMLLoader::GeneratePiece(PieceType type, PieceColor color, int row, 
	int column, Piece *** board)
{
	switch(type)
	{
	case PAWN: 
		board[row][column] = new Pawn(color);
		break;
	case ROOK:
		board[row][column] = new Rook(color);
		break;
	case KNIGHT:
		board[row][column] = new Knight(color);
		break;
	case BISHOP:
		board[row][column] = new Bishop(color);
		break;
	case QUEEN:
		board[row][column] = new Queen(color);
		break;
	case KING:
		board[row][column] = new King(color);
		break;
	}
}
/*DONE*/
PieceType ChessXMLLoader::ConvertStringToPieceType(string s)
{
	if(s == "pawn")
	{
		return PAWN;
	}
	if(s == "rook")
	{
		return ROOK;
	}
	if(s == "knight")
	{
		return KNIGHT;
	}
	if(s == "bishop")
	{
		return BISHOP;
	}
	if(s == "queen")
	{
		return QUEEN;
	}
	if(s == "king")
	{
		return KING;
	}
	//nothing should get this far.
	assert(1 == 2);
}
/*DONE*/
PieceColor ChessXMLLoader::ConvertStringToPieceColor(string s)
{
	if(s == "white")
	{
		return WHITE;
	}
	if(s == "black")
	{
		return BLACK;
	}
	//nothing should get this far.
	assert(1 == 2);
}
/*DONE*/
HTMLToken ChessXMLLoader::GetNextNonTextToken()
{
	//While there are more tokens...
	while(true)
	{
		HTMLToken token = (*tok).GetNextToken();
		cout << token.GetType() << endl;
		//If it's not text, return it.
		if(token.GetType() != TEXT)
		{
			return token;
		}
	}
}