#ifndef I_CHESS_PLAYER_H
#define I_CHESS_PLAYER_H
#include "MyDefines.h"
#include "Facade.h"
#include "IChessView.h"
#include "ChessGuiDefines.h"
#include "Move.h"
#include "CommonFunctions.h"

/**
 * The IChessPlayer class provides an interface for a ChessController implementation to interact
 * with the player through, regardless of whether the player is a human or a computer.
 */
class IChessPlayer
{
public: //methods
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button) = 0;

	/**
	 * Handle when the timeout duration has passed.
	 */
	virtual void on_TimerEvent() = 0;
	
	/*
	 Sets the view.
	 */
	virtual void SetView(IChessView * view) = 0;
};

#endif
