#ifndef I_CHESS_VIEW_H
#define I_CHESS_VIEW_H

#include "ChessGui.h"

class IChessController;

/**
 * This interface must be implemented by the main ChessView class found in ChessView.h
 * and this interface should also be the one that the students use to communicate
 * to the ChessView class.
 */
class IChessView
{
public:
	///Place text in area above the chess board
	///@ingroup chessguiconv
	///@param text
	virtual void SetTopLabel(const std::string & text) = 0;
	///Place text in area below the chess board
	///@ingroup chessguiconv
	///@param text
	virtual void SetBottomLabel(const std::string & text) = 0;

	///Clear all data in the Message Area
	///@ingroup chessguiconv
	virtual void ClearMessageArea() = 0;
	///Write a string to the Message Area
	///@ingroup chessguiconv
	///@param message
	virtual void WriteMessageArea(const std::string & message) = 0;

	///Set text in the Statusbar located at the bottom of the ChessGui
	///@ingroup chessguiconv
	///@param status
	virtual void SetStatusBar(const std::string & status) = 0;

	///Opens a Gtk::FileChooserDialog in the FILE_SAVE mode
	///@ingroup chessguiconv
	///@return Path to the file selected
	virtual std::string SelectSaveFile() = 0;
	///Opens a Gtk::FileChooserDialog in the FILE_OPEN mode
	///@ingroup chessguiconv
	///@return Path to the file selected
	virtual std::string SelectLoadFile() = 0;


	///@ingroup chessguiconv
	///@param row 0 <= row < NUM_COL, top to bottom
	///@param col  0 <= row < NUM_COL, left to right
	///@param color RRGGBBAA hexadecimal value see @link ChessGuiDefines.h @endlink
	virtual void HighlightSquare(signed int row,signed int col,guint32  color) = 0;

	///@ingroup chessguiconv
	///@param row 0 <= row < NUM_COL, top to bottom
	///@param col  0 <= row < NUM_COL, left to right
	virtual void UnHighlightSquare(signed int row,signed int col) = 0;

	///@ingroup chessguiconv
	///@param row 0 <= row < NUM_COL, top to bottom
	///@param col  0 <= row < NUM_COL, left to right
	///@param piece valid piece as define in ImageName
	virtual void PlacePiece(signed int row,signed int col, ImageName piece) = 0;

	///@ingroup chessguiconv
	///@param row 0 <= row < NUM_COL, top to bottom
	///@param col  0 <= row < NUM_COL, left to right
	virtual void ClearPiece(signed int row,signed int col) = 0;
	
	/**
	 * Set the IChessController that this IChessView will pass all of its inputs to.
	 */
	virtual void SetController(IChessController* controller) = 0;
};

#endif
