/* 
 * File:   ChessXMLSaver.cpp
 * Author: lexic92
 *
 * Created on April 11, 2012, 4:52 AM
 */

#include "ChessXMLSaver.h"

#include <iostream>
using namespace std;

/*DONE*/
void ChessXMLSaver::SaveGameToFile(string fileName, Piece *** board, MoveHistory & moveHistory)
{
	cout << "XML saver " << endl;
	
	OpenOutputFile(fileName);
	
	//If you got here and it was bad, then you should have handled an exception.
	assert(file.good());
	
	cout << "file was good" << endl;
	file << "<chessgame>\n";
	file <<		"\t<board>\n";
	PrintPiecesOnTheBoard(board);
	file <<		"\t</board>\n";
	file <<		"\t<history>\n";
	PrintMoveHistory(moveHistory);
	file <<		"\t</history>\n";
	file << "</chessgame>" << endl;
	
	//DO NOT FORGET THIS!!!
	file.close();
}
/*DONE*/
void ChessXMLSaver::PrintPiecesOnTheBoard(Piece *** board)
{
	//For each cell on the board...
	for(int row = 0; row < NUMROWS; row++)
	{
		for(int col = 0; col < NUMCOLS; col++)
		{
			//Get the piece at this location.
			Piece * p = board[row][col];
			
			//If there isn't a piece there, then don't print a <piece> child.
			if(p == NULL)
			{
				continue;
			}
			//But if there is a piece, print its data to the file.
			file << "\t\t<piece type=\"";
			file << ConvertPieceTypeToString(p->GetType()) << "\" ";
			file << "color=\"";
			file << ConvertPieceColorToString(p->GetColor()) << "\" ";
			file << "row=\"" << row << "\" column=\"" << col << "\"/>" << endl;
		}
	}	
}
/*DONE*/
void ChessXMLSaver::PrintMoveHistory(MoveHistory & m)
{
	//For every move in the move history...
	list<Move>::const_iterator it = m.GetIterator();
	for( ; it != m.EndIterator(); it++)
	{
		file << "\t\t<move>\n";
		file << "\t\t\t<piece type=\"";
		file << ConvertPieceTypeToString((*it).GetSourcePieceType()) << "\" ";
		file << "color=\"";
		file << ConvertPieceColorToString((*it).GetSourcePieceColor()) << "\" ";
		file << "row=\"";
		file << (*it).GetStartCell().GetRow() << "\" ";
		file << "column=\"";
		file << (*it).GetStartCell().GetColumn() << "\"/>" << endl;
		
		file << "\t\t\t<piece type=\"";
		file << ConvertPieceTypeToString((*it).GetSourcePieceType()) << "\" ";
		file << "color=\"";
		file << ConvertPieceColorToString((*it).GetSourcePieceColor()) << "\" ";
		file << "row=\"";
		file << (*it).GetEndCell().GetRow() << "\" ";
		file << "column=\"";
		file << (*it).GetEndCell().GetColumn() << "\"/>" << endl;
		
		if(HasCapturedPiece(*it))
		{
			file << "\t\t\t<piece type=\"";
			file << ConvertPieceTypeToString((*it).GetCapturedPieceType()) << "\" ";
			file << "color=\"";
			file << ConvertPieceColorToString((*it).GetCapturedPieceColor()) << "\" ";
			file << "row=\"";
			file << (*it).GetEndCell().GetRow() << "\" ";
			file << "column=\"";
			file << (*it).GetEndCell().GetColumn() << "\"/>" << endl;
		}
		file << "\t\t</move>" << endl;
	}
}
/*DONE*/
void ChessXMLSaver::OpenOutputFile(string fileName)
{
	const char * p_fileName = fileName.c_str();
	cout << "c_str: " << p_fileName << endl;
	file.open(p_fileName);
	
	cout << "is file good? " << file.good() << endl;
	//Leave early if it's bad.
	if(!file.good())
	{
		throw CS240Exception("ChessXMLSaver: Output file did not work.");
	}
}
/*DONE*/
string ChessXMLSaver::ConvertPieceColorToString(PieceColor color)
{
	switch(color)
	{
	case WHITE: 
		return "white";
	case BLACK:
		return "black";
	default:
		assert(1 == 2);
	}
}
/*DONE*/
string ChessXMLSaver::ConvertPieceTypeToString(PieceType type)
{
	switch(type)
	{
	case PAWN: 
		return "pawn";
	case ROOK:
		return "rook";
	case KNIGHT:
		return "knight";
	case BISHOP:
		return "bishop";
	case QUEEN:
		return "queen";
	case KING:
		return "king";
	default:
		assert(1 == 2);
	}
}
/*DONE*/
bool ChessXMLSaver::HasCapturedPiece(Move m)
{
	//If doesn't have captured piece...
	if((m.GetCapturedPieceType() == NOTYPE) && 
		(m.GetCapturedPieceColor() == NOCOLOR))
	{
		return false;
	}
	//If only one is true, then it's a faulty move.
	if((m.GetCapturedPieceType() == NOTYPE) ||
		(m.GetCapturedPieceColor() == NOCOLOR))
	{
		assert(1 == 2);
	}
	//Otherwise, it DOES have a captured pice.
	return true;
}