/* 
 * File:   Move.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 8:24 PM
 */

#ifndef MOVE_H
#define	MOVE_H
#include <iostream>
#include "MyDefines.h" //for enums PieceType and PieceColor.
#include "Cell.h"
#include "UnitTest.h"
using namespace std;

class Move
{
public:
	/*
	 Tests this class
	 */
	static bool Test(ostream & os);
	
	/*
	 Constructor
	 It's explicit because I want to ensure people use the correct enum types.
	 (explicit means that it doesn't do implicit conversions to the constructor.)
	 
	 CELL MUST ALWAYS TAKE A COPY, NOT A REFERENCE.  Because I will be editing the
	 cell I pass in after I pass it in.
	 */
	explicit Move(PieceType sourcePieceType, PieceColor sourcePieceColor, 
		Cell sourceStartCell, PieceType capturedPieceType,
		PieceColor capturedPieceColor, Cell sourceEndCell);
	
	/*
	 Get source piece type
	 */
	PieceType GetSourcePieceType() const;

	/*
	 Get source piece color
	 */
	PieceColor GetSourcePieceColor() const;
	
	/*
	 Get the start cell (where the source piece was BEFORE the move).
	 */
	Cell GetStartCell() const;
	
	/*
	 Get captured piece type (note: if none was captured, it's type will be NOTYPE.)
	 */
	PieceType GetCapturedPieceType() const;
	
	/*
	 Get Get captured piece type (note: if none was captured, it's type will be NOCOLOR.)
	 */
	PieceColor GetCapturedPieceColor() const;
	
	/*
	 Gets the end cell (where the source piece was AFTER the move).
	 */
	Cell GetEndCell() const;
	
	/*
	 Does simple comparison based on data.
	 */
	bool operator==(const Move & other) const;
	
	
private:
	PieceType sourcePieceType;
	PieceColor sourcePieceColor;
	Cell sourceStartCell;
	
	PieceType capturedPieceType;
	PieceColor capturedPieceColor;
	Cell sourceEndCell;
	
	
};

#endif	/* MOVE_H */

