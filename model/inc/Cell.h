/* 
 * File:   Cell.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:25 PM
 */

#ifndef CELL_H
#define	CELL_H
#include <iostream>
using namespace std;

class Cell
{
public:
	/*
	 Simple constructor.
	 */
	Cell(int row, int column);
	
	/*
	 Gets the row.
	 */
	int GetRow() const;
	
	/*
	 Gets the column.
	 */
	int GetColumn() const;
	
	/*
	 Tests this class.
	 */
	static bool Test(ostream & os);
	
	/*
	 Simple comparison by comparing their coordinates.
	 */
	bool operator==(const Cell & other) const;
	
	/*
	 Returns true if the cell is a valid chess board location.
	 That means
		 0 <= row <= 7
	 and
		0 <= column <= 7.
	 */
	bool IsOnTheBoard() const;
	
	//-------------------LOCATION CHANGERS------------------
	
	/*
	 Move up 1 (row--).
	 */
	void Up();
	
	
	/*
	 Move diagonally up and left 1 (row--, column--).
	 */
	void UpLeft();
	
	
	
	/*
	 Move diagonally up and right 1 (row--, column++).
	 */
	void UpRight();
	
	
	
	/*
	 Move down 1 (row++).
	 */
	void Down();
	
	
	
	/*
	 Move diagonally down and left 1 (row++, column--).
	 */
	void DownLeft();
	
	
	
	/*
	 Move diagonally down and right (row++, column++).
	 */
	void DownRight();
	
	
	
	/*
	 Move left 1 (column--).
	 */
	void Left();
	
	
	
	/*
	 Move right 1 (column++).
	 */
	void Right();
	
	
private:
	//Needless to say...
	int row;
	int column;
	
	/*
	The following functions test this class.
	*/
	static bool TestDirections(ostream & os);
	static bool TestIsOnTheBoard(ostream & os);
};

#endif	/* CELL_H */

