/* 
 * File:   ChessXMLLoader.h
 * Author: lexic92
 *
 * Created on April 11, 2012, 6:18 AM
 */

#ifndef CHESSXMLLOADER_H
#define	CHESSXMLLOADER_H

#include <string>
#include "MoveHistory.h"
#include "HTMLTokenizer.h"
#include "URLInputStream.h"
#include "CS240Exception.h"
#include "HTMLToken.h"

//Pieces:
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class ChessXMLLoader
{
public:
	/*
	 Loads the game that's stored as XML in the file with the given name into the chessboard.
	 
	 */
	void LoadGameFromFile(string fileName, Piece *** board, MoveHistory & moveHistory);
	
	
	
private:
	HTMLTokenizer * tok;
	
	/*
	 Gets the next token that isn't text. (so it skips whitespace.)
	 PRECONDITION: There EXISTS another nontext token.
	 */
	HTMLToken GetNextNonTextToken();
	/*
	 Converts a string to a PieceColor enum.
	 */
	PieceColor ConvertStringToPieceColor(string s);
	
	/*
	 Converts a string to a PieceType enum.
	 */
	PieceType ConvertStringToPieceType(string s);
	
	/*
	 Creates a new piece on the given board, of the given type and color, 
	 and at the given coordinate.
	 */
	void GeneratePiece(PieceType type, PieceColor color, int row, int column, Piece *** board);
	
	/*
	 Puts a piece on the board for a <piece..../> tag. (Gets the data out of the tag too.)
	 */
	void ParsePieceTagAndExtractData(HTMLToken pieceTag, Piece *** board);
	
	/*
	 Parses the stuff between <board> and </board>.
	 
	 PRECONDITION: The tokenizer's next token is <board>.
	 POSTCONDITION: The tokenizer's next token is <history>.
	 */
	void ParseBoardSection(Piece *** board);
	
	/*
	 Parses stuff between <move> and </move>, and adds the move to the
	 move history.
	 
	 PRECONDITION: 
		tok: it is pointing to the thing after <move>, which is assumed to
			be the first of 2 or 3 <piece/>'s.
	 POSTCONDITON: 
		tok: its next token is whatever is after </move>.
	 */
	void ParseMoveAndAddItToMoveHistory(MoveHistory & moveHistory);
	
	/*
	 Parses stuff between <history> and <history>.
	 */
	void ParseHistorySection(Piece *** board, MoveHistory & moveHistory);
	
	
};


#endif	/* CHESSXMLLOADER_H */

