/* 
 * File:   Cell.cpp
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:24 PM
 */

#include "Cell.h"
#include "UnitTest.h"
using namespace std;
/*static*/
bool Cell::Test(ostream & os)
{
	os << "\n\n================== TESTING CELL ============= " << endl;
	bool success = true;
	
	//Test Constructor
	Cell c(1,2);
	TEST(c.row == 1);
	TEST(c.column == 2);
	
	//Test Getters
	TEST(c.GetRow() == 1);
	TEST(c.row == 1); //Make sure GetX didn't modify x.
	TEST(c.GetColumn() == 2);
	TEST(c.column == 2); //Make sure GetY didn't modify y.
	
	
	//Test operator==
	Cell c2(1,2);
	TEST(c == c2);
	Cell c3(1,3);
	TEST(!(c == c3));
	Cell c4(2,2);
	TEST(!(c == c4));
	
	if(!TestDirections(os)) success = false;
	
	if(!TestIsOnTheBoard(os)) success = false;
	
	return success;
}
/*static*/
bool Cell::TestDirections(ostream & os)
{
	bool success = true;
	//Test every direction
	Cell c5(5,5);
	c5.Up();
	TEST((c5.row == 4) && (c5.column == 5));
	c5.Down();
	TEST((c5.row == 5) && (c5.column == 5));
	c5.Left();
	TEST((c5.row == 5) && (c5.column == 4));
	c5.Right();
	TEST((c5.row == 5) && (c5.column == 5));
	c5.UpLeft();
	TEST((c5.row == 4) && (c5.column == 4));
	c5.UpRight();
	TEST((c5.row == 3) && (c5.column == 5));
	c5.DownLeft();
	TEST((c5.row == 4) && (c5.column == 4));
	c5.DownRight();
	TEST((c5.row == 5) && (c5.column == 5));
	return success;
}
/*static*/
bool Cell::TestIsOnTheBoard(ostream & os)
{
	bool success = true;
	//If both coordinates are wrong:
	Cell c(-1,-1);
	Cell c2(8,8);
	TEST(!c.IsOnTheBoard());
	TEST(!c2.IsOnTheBoard());
	
	//If both coordinates are valid:
	Cell c3(0,0);
	Cell c4(7,7);
	TEST(c3.IsOnTheBoard());
	TEST(c4.IsOnTheBoard());
	
	//If only the row is wrong:
	Cell c5(-1,0);
	Cell c6(8,0);
	TEST(!c5.IsOnTheBoard());
	TEST(!c6.IsOnTheBoard());
	
	//If only the column is wrong:
	Cell c7(0,-1);
	Cell c8(0,8);
	TEST(!c7.IsOnTheBoard());
	TEST(!c8.IsOnTheBoard());
	
	return success;
}
/*DONE*/
int Cell::GetRow() const
{
	return row;
}
	
/*DONE*/
int Cell::GetColumn() const
{
	return column;
}
/*DONE*/
Cell::Cell(int row, int column)
{
	//Just store the pointers.
	this->row = row;
	this->column = column;
}
/*DONE*/
bool Cell::operator==(const Cell & other) const
{
	return ((row == other.row) && (column == other.column));
}
/*DONE*/
bool Cell::IsOnTheBoard() const
{
	return (0 <= row) && (row <= 7) && (0 <= column) && (column <= 7);
}
/*DONE*/
void Cell::Up()
{
	row--;
}


/*DONE*/
void Cell::UpLeft()
{
	Up();
	Left();
}

/*DONE*/
void Cell::UpRight()
{
	Up();
	Right();
}
/*DONE*/
void Cell::Down()
{
	row++;
}

/*DONE*/
void Cell::DownLeft()
{
	Down();
	Left();
}



/*DONE*/
void Cell::DownRight()
{
	Down();
	Right();
}



/*DONE*/
void Cell::Left()
{
	column--;
}



/*DONE*/
void Cell::Right()
{
	column++;
}