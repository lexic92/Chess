/* 
 * File:   CommonFunctions.cpp
 * Author: lexic92
 *
 * Created on April 11, 2012, 12:07 AM
 */

#include <cstdlib>

using namespace std;
#include "CommonFunctions.h"
#include <cassert>

/*DONE*/
ImageName ConvertToImageName(PieceType type, PieceColor color)
{
	switch(type)
	{
	case PAWN: 
		return (color == WHITE) ? W_PAWN : B_PAWN;
	case ROOK:
		return (color == WHITE) ? W_ROOK : B_ROOK;
	case KNIGHT:
		return (color == WHITE) ? W_KNIGHT : B_KNIGHT;
	case BISHOP:
		return (color == WHITE) ? W_BISHOP : B_BISHOP;
	case QUEEN:
		return (color == WHITE) ? W_QUEEN : B_QUEEN;
	case KING:
		return (color == WHITE) ? W_KING : B_KING;
	default:
		assert(1 == 2);
	}
}
