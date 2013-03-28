/* 
 * File:   MyDefines.h
 * Author: lexic92
 *
 * Created on April 7, 2012, 10:51 PM
 */

#ifndef MYDEFINES_H
#define	MYDEFINES_H

enum PieceColor
{
	WHITE = 0,
	BLACK = 1,
	NOCOLOR = 2
};

enum PieceType
{
	PAWN = 0,
	ROOK = 1,
	KNIGHT = 2,
	BISHOP = 3,
	QUEEN = 4,
	KING = 5,
	NOTYPE = 6
};
//Board dimensions
const int NUMROWS = 8;
const int NUMCOLS = 8;
#endif	/* MYDEFINES_H */

