/* 
 * File:   ChessXMLSaver.h
 * Author: lexic92
 *
 * Created on April 11, 2012, 4:53 AM
 */

#ifndef CHESSXMLSAVER_H
#define	CHESSXMLSAVER_H

#include "Piece.h"
#include "MoveHistory.h"
#include "CS240Exception.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

class ChessXMLSaver
{
public:
	/*
	 Saves the game with that board and that move history to the given file name in
	 special XML format.
	 */
	void SaveGameToFile(string fileName, Piece *** board, MoveHistory & moveHistory);
	
	
private:
	ofstream file;
	
	/*
	 Goes through each board cell, and if there's a piece, prints an XML entity for it
	 to "file."
	 */
	void PrintPiecesOnTheBoard(Piece *** board);
	
	/*
	 Goes through each move in the move history, and prints an XML entity for it to "file."
	 */
	void PrintMoveHistory(MoveHistory & m);
	
	/*
	 Opens the file.
	 Throws: CS240Exception if file didn't work.
	 */
	void OpenOutputFile(string fileName);
	
	/*
	 Converts the enum to a string for XML output.
	 Types of piece colors: "white" "black"
	 */
	string ConvertPieceColorToString(PieceColor color);
	
	/*
	 Converts the enum to a string for XML output.
	 Types of piece types: "pawn" "rook" "bishop" "queen" "king"
	 */
	string ConvertPieceTypeToString(PieceType type);
	
	/*
	 Returns true if it that move's captured piece type is not NOTYPE,
	 AND it's captured piece color is not NOCOLOR.
	 In other words, it returns true if a piece was captured in that move.
	 */
	bool HasCapturedPiece(Move m);
	
};




#endif	/* CHESSXMLSAVER_H */

