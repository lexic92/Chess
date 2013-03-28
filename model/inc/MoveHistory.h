/* 
 * File:   MoveHistory.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:24 PM
 */

#ifndef MOVEHISTORY_H
#define	MOVEHISTORY_H
#include "Move.h"

//Standard library stuff
#include <list>
#include  <cassert>
#include <iostream>

using namespace std;

class MoveHistory
{
public:
	/*
	TThe following functions test this class.
	*/
	static bool Test(ostream & os);
	static bool TestPushPopIterator(ostream & os);
	static bool TestStackClear(ostream & os);
	
	
	
	/*
	 Push a move on the Move History "stack."
	 It creates a copy of the argument you give it.
	 */
	void Push(Move m);
	
	
	
	
	
	
	/*
	 Pop a move off the Move History "stack."
	 It gives you an entire copy of the move.
	 PRECONDITION: The move history is not empty. (Has an assert.)
	 */
	Move Pop();
	
	
	
	
	
	/*
	 Return an iterator pointing to the bottom of the stack,
	 intended for you to increment it to go through the list.

	 //EXAMPLE OF HOW TO USE IT:

			// list::begin
			#include <iostream>
			#include <list>
			using namespace std;

			int main ()
			{
			  int myints[] = {75,23,65,42,13};
			  list<int> mylist (myints,myints+5);

			  list<int>::iterator it;

			  cout << "mylist contains:";
			  for ( it=mylist.begin() ; it != mylist.end(); it++ )
			    cout << " " << *it;

			  cout << endl;

			  return 0;
			}

	 */
	list<Move>::const_iterator GetIterator();
	
	/*
	 Gets an iterator pointing to the "end", which you should use in sync with the starting
	 iterator from "GetIterator()".
	 */
	list<Move>::const_iterator EndIterator();
	
	/*
	 Removes all elements from the list, leaving it with a size of 0.
	 */
	void Clear();
	
	/*
	 Returns the number of moves in the move history.
	 */
	int Size();
	
private:
	list<Move> moves;
	
	
};


#endif	/* MOVEHISTORY_H */

