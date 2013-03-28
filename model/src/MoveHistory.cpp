/* 
 * File:   MoveHistory.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:24 PM
 */

#include "MoveHistory.h"
using namespace std;

/*static*/
bool MoveHistory::Test(ostream & os)
{
	os << "\n\n================== TESTING MOVEHISTORY ============= " << endl;
	bool success = true;
	
	if(!TestPushPopIterator(os)) success = false;
	if(!TestStackClear(os)) success = false;
	
	MoveHistory m;
	//Construct move objects
	Cell start(1,2);
	Cell end(3,4);
	Move move1(PAWN, WHITE, start, KNIGHT, BLACK, end);
	Move move2(KING, WHITE, start, KNIGHT, BLACK, end);

	//Test Size();
	TEST(m.Size() == 0);
	m.Push(move1);
	TEST(m.Size() == 1);
	m.Push(move2);
	TEST(m.Size() == 2);
	m.Pop();
	TEST(m.Size() == 1);
	
	return success;
}

/*static*/
bool MoveHistory::TestPushPopIterator(ostream & os)
{
	bool success = true;
	MoveHistory m;
	
	//Construct move objects
	Cell start(1,2);
	Cell end(3,4);
	Move move1(PAWN, WHITE, start, KNIGHT, BLACK, end);
	Move move2(KING, WHITE, start, KNIGHT, BLACK, end);
	
	//Test "void Push(Move m)"
	m.Push(move1);
	//Note: list::front() "Returns a reference to the first element in the list container."
	TEST(m.moves.front() == move1);
	TEST(m.moves.size() == 1);
	
	//Test "Move Pop()"
	TEST(m.Pop() == move1);
	TEST(m.moves.size() == 0);
	
	//Test "list<Move>::iterator GetIterator()"
	TEST(m.GetIterator() == m.moves.begin());
	
	return success;
}

/*static*/
bool MoveHistory::TestStackClear(ostream & os)
{
	bool success = true;
	MoveHistory m;
	
	//Construct move objects
	Cell start(1,2);
	Cell end(3,4);
	Move move1(PAWN, WHITE, start, KNIGHT, BLACK, end);
	Move move2(KING, WHITE, start, KNIGHT, BLACK, end);
	
	//Test stack-like behavior
	m.Push(move1);
	m.Push(move2);
	TEST(m.Pop() == move2);
	TEST(m.Pop() == move1);

	//Prove that the stack stores copies of the moves, so if you delete one,
	//you can still access the rest.
	m.Push(move1);
	m.Push(move1);
	m.Pop();
	TEST(m.Pop() == move1);
	
	//Test "void Clear()"
	assert(m.moves.size() == 0); //assumption for following test case
	m.Push(move1);
	m.Clear();
	TEST(m.moves.size() == 0);
	//now for any number of pushes
	m.Push(move1);
	m.Push(move1);
	m.Push(move1);
	m.Push(move1);
	m.Push(move1);
	m.Clear();
	TEST(m.moves.size() == 0);
	
	return success;
}

/*DONE*/
void MoveHistory::Push(Move m)
{
	//From cplusplus.com:
	//	void push_back ( const T& x );
	//Adds a new element at the end of the list, right after its current last element.
	//The content of this new element is initialized to a copy of x.
	//This effectively increases the list size by one.
	
	moves.push_back(m);
}

/*DONE*/
Move MoveHistory::Pop()
{
	assert(moves.size() != 0);
	
	//From cplusplus.com:
	//	reference back ( );
	//Returns a reference to the last element in the container.
	
	//So, I use Move's copy constructor in order to make a move object I can actually
	//return and have the caller have his/her own copy of the move, and not a reference
	//to a move that I'm going to delete.
	
	Move mostRecentMove = moves.back();
	
	//From cplusplus.com:
	//	void pop_back ( );
	//Removes the last element in the list container, effectively reducing the list size 
	//by one. This calls the removed element's destructor.
	moves.pop_back();
	
	return mostRecentMove;
}

/*DONE*/
list<Move>::const_iterator MoveHistory::GetIterator()
{
	// iterator begin ();
	//Returns an iterator referring to the first element in the list container.
	return moves.begin();
}
/*DONE*/
list<Move>::const_iterator MoveHistory::EndIterator()
{
	// iterator end ();
	return moves.end();
}
/*DONE*/
void MoveHistory::Clear()
{
	//From cplusplus.com:
	//	void clear ( );
	//All the elements in the list container are dropped: 
	//their destructors are called, and then they are removed from the list container,
	//leaving it with a size of 0.
	
	moves.clear();
}
/*DONE*/
int MoveHistory::Size()
{
	return moves.size();
}