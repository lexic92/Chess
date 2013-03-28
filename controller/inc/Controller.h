/* 
 * File:   Controller.h
 * Author: lexic92
 *
 * Created on April 10, 2012, 9:44 AM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H
#include "IChessController.h"
#include "IChessPlayer.h"
#include "Human.h"
#include "Computer.h"
#include "Facade.h"
#include "SelectDialog.h"
#include <vector>

class Controller : public IChessController
{
public:
	/*
	 Constructor.  h = human, c = computer.  
	 First letter represents white (who also goes first).
	 0: hh 
	 1: hc
	 2: ch
	 3: cc
	 */
	Controller(int argumentNumber);
	
	/*
	 Destructor.  Please delete anything called with New.
	 */
	~Controller();
	
	/*
	  Indicate to the player that the user clicked on the given
	  row and column with the mouse.
	  Call whoever's turn it is, and have them make a move.
	 */
	/*virtual*/ 
	void on_CellSelected(int row, int col, int button);
	
	///@param row where drag began
	///@param col where drag began
	/*virtual*/
	void on_DragStart(int row,int col);

	///@param row where drag ended
	///@param col where drag ended
	///@return true if the drag resulted in a successful drop
	/*virtual*/
	bool on_DragEnd(int row,int col);

	/*
	  Handle when the user selected the new game button.
		1. Delete move history
		2. Create fresh board.
	 */
	/*virtual*/
	void on_NewGame();

	/*
	  Handle when the user selected the save game button.
	  Use stored filename to export move history and board state to XML. (save game)
	 */
	/*virtual*/
	void on_SaveGame();

	/*
	  Handle when the user selected the save game as button.
	 
		1. Get the file string.
		2. Export move history and board state to XML. (save game)
		3. Store the filename.
	 */
	/*virtual*/
	void on_SaveGameAs();

	/*
	  Handle when the user selected the load game button.
	 
		1. Get the file string.
		2. Use it to load XML into a game state (discarding old stuff).
		3. Update board appearance based on the game state.
	 */
	/*virtual*/
	void on_LoadGame();

	/*
	 Handle when the user selected the undo move button.
	 
		1. Doesn't try to undo if you're already at the start of the game.
		2. Redraw the destination by clearing it if there was no capture,
		   or redrawing the captured piece.
		3. Redraw the source piece on it's source cell. 
		4. Remove all highlights.
	 */
	/*virtual*/
	void on_UndoMove();
		
	/*
	 Handle when the user selects to quit the game, either through the
	 quit button, the close X button, or the file menu.
	 */
	/*virtual*/
	void on_QuitGame();
		
	/*
	 Handle when a timer event has been signaled.
	 If it's the computer's turn, it'll take a turn.
	 */
	/*virtual*/
	void on_TimerEvent();
	
	/**
	 * Set the IChessView that this IChessController will handle inputs for.
	 */
	/*virtual*/
	void SetView(IChessView* view);
	
	/*
	 Makes new players, deletes the old players, erases the saveFile.
	 */
	void InstantiatePlayers();
	
	
	void InitializeNewGame();
	
private:
	IChessView * view;
	IChessPlayer * whitePlayer;
	IChessPlayer * blackPlayer;
	Facade chessFacade;
	string saveFile;
	int arg; //the type of game: hh, hc, ch, cc
	
	/*
	 This clears all the images off the board and puts images where a new game's pieces
	 would be.  It does not do anything to the model at all.
	 */
	void MakeBoardLookLikeNewGame();
	
	/*
	 1. Clear the piece that moved.
	 2. Clear whatever was on the board in the other spot.
	 3. Draw the piece from startCell onto myCell.
	 */
	void UpdateTheViewToReflectTheMove(Move m);
};


#endif	/* CONTROLLER_H */

