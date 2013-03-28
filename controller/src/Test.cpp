/* 
 * File:   Test.cpp
 * Author: lexic92
 *
 * Created on April 6, 2012, 10:35 PM
 */

#include <cstdlib>
#include "UnitTest.h"
#include <iostream>
#include "CS240Exception.h"

//For tests:
#include "Computer.h"
#include "Cell.h"
#include "Human.h"
#include "MoveHistory.h"
#include "Move.h"
#include "ChessBoard.h"

//Pieces:
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using namespace std;
bool TestUserInterfaceStuff();
bool TestPieces();
bool TestMoreComplicatedClasses();

/*
 * Tests everything.
 */
int main(int argc, char** argv) 
{
	bool success = true;
	try
	{
	
		if(!TestUserInterfaceStuff()) success = false;
		if(!TestPieces()) success = false;
		if(!TestMoreComplicatedClasses()) success = false;
		
		cout << "\n\n";
		if (success) 
		{
			cout << "Tests Succeeded!" << endl;
		}
		else 
		{
			cout << "Tests Failed!" << endl;
		}
	}
	catch(CS240Exception & e)
	{
		cout << e.GetMessage() << endl;
		cout << "Tests Failed." << endl;
	}
	return 0;
}
bool TestUserInterfaceStuff()
{
	bool success = true;
	
	//TEST USER INTERFACE STUFF
	cout << "\n\n\n\n**************************************************************" << endl;
	cout << "                     Testing User Interface stuff" << endl;
	cout << "**************************************************************\n\n" << endl;
	if(!Computer::Test(cout)) success = false;
	if(!Human::Test(cout)) success = false;
	
	return success;
}
bool TestPieces()
{
	bool success = true;
	
	//TEST PIECES
	cout << "\n\n\n\n----------------------------------------------------------------" << endl;
	cout << "                         Testing pieces" << endl;
	cout << "-------------------------------------------------------------------------\n\n" << endl;
	if(!Pawn::Test(cout)) success = false;
	if(!Rook::Test(cout)) success = false;
	if(!Knight::Test(cout)) success = false;
	if(!Bishop::Test(cout)) success = false;
	if(!Queen::Test(cout)) success = false;
	if(!King::Test(cout)) success = false;
	if(!Piece::Test(cout)) success = false;
	
	return success;
}
bool TestMoreComplicatedClasses()
{
	bool success = true;
	
	//TEST MORE COMPLICATED CLASSES
	cout << "\n\n\n\n----------------------------------------------------------------------" << endl;
	cout << "                    Testing More Complicated Stuff" << endl;
	cout << "-------------------------------------------------------------------------\n\n" << endl;
	if(!ChessBoard::Test(cout)) success = false;
	if(!ChessBoard::TestPiecesGetPossibleMoves(cout)) success = false;
	
	return success;
}