// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
// Author: Daniel Schulte <danschultewhpc@gmail.com>, (C) 2010
//
// Copyright: For use by the students of CS 240 at BYU
//
//
///@file ChessView.h Interface for the ChessView class
///@ingroup backend

#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H


#include <string>
#include <vector>
#include <map>
#include <glibmm/refptr.h>
#include <libglademm.h>
#include <sigc++/sigc++.h>
#include <gtkmm/main.h>

#include "ChessGuiDefines.h"
#include "ChessGui.h"
#include "IChessView.h"
#include "IChessController.h"


///@def LOG_LEVEL_HIDE_MASK
///@brief Set the log levels (using the Glib log levels)
///that will be ignored by the Chess logging function.
///
///This mask will hide messages from being displayed in the ChessGui message box,
///it will not prevent them from being sent to the command line when not using
///the GUI.  Set this flag at compile time using
///the compiler directive -D and OR-ed values of the Glib log levels. For example:
///@code
///g++ -g -o ChessView.o (options) -DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO) ChessView.cpp
///@endcode
///will prevent debug and info messages from being displayed.
#ifndef LOG_LEVEL_HIDE_MASK
#define LOG_LEVEL_HIDE_MASK (0)
#endif


//add you defines here*****************************************************************************



///@brief This class is the main interface between the Students code and the provided GUI
///
///The Student will implement each of the signal handlers found in this class.
///It is permitted to add member data and functions.
//The constructor and the destructor should be finished to suit the needs
///of the student.
///@note Access the @link chessguiconv convenience functions @endlink
///using the pointer ChessView::gui
///@ingroup backend
class ChessView : public IChessView
{
	private:

		///Access to the user interface
		ChessGui * gui;
		///Log-id (for memory management)
		guint logId;
		
		IChessController* controller;
		
		int timeoutMilliseconds;

		bool memTest;

	public:
		///@param gladefile See @link cs240chess.glade "Glade File" @endlink
		///@param argc The number of commandline arguments passed to this program.
		///@param argv Pointers to the commandline argument strings passed to this program.
		ChessView(std::string gladefile);

		ChessView();

		~ChessView();

		///allows Gtk::Main to handle showing and hiding the window on exit
		void run(Gtk::Main & app);
		void run();

		///@name Student Implemented Functions
		///@{

		///Connected to (activated by) ChessGui::signal_cell_selected()
		///@param row 1-8, top to bottom
		///@param col 1-8, left to right
		///@param button 1=left mouse button, 2=middle mouse button, 3=right mouse  button
		void on_CellSelected(int row, int col, int button);


		///Connected to (activated by) ChessGui::signal_new_selected()
		void on_NewGame();

		///Connected to (activated by) ChessGui::signal_save_selected()
		void on_SaveGame();

		///Connected to (activated by) ChessGui::signal_save_as_selected()
		void on_SaveGameAs();

		///Connected to (activated by) ChessGui::signal_load_selected()
		void on_LoadGame();

		///Connected to (activated by) ChessGui::signal_undo_selected()
		void on_UndoMove();

		///Connected to (activated by) ChessGui::signal_quit_selected()
		void on_QuitGame();
		
		///This method will be called every tenth of a second.
		bool on_TimerEvent();


		///@param row where drag began
		///@param col where drag began
		void on_DragStart(int row,int col);

		///@param row where drag ended
		///@param col where drag ended
		///@return true if the drag resulted in a successful drop
		bool on_DragEnd(int row,int col);
		///@}
		
		///Place text in area above the chess board
		///@ingroup chessguiconv
		///@param text
		virtual void SetTopLabel(const std::string & text);
		///Place text in area below the chess board
		///@ingroup chessguiconv
		///@param text
		virtual void SetBottomLabel(const std::string & text);

		///Clear all data in the Message Area
		///@ingroup chessguiconv
		virtual void ClearMessageArea();
		///Write a string to the Message Area
		///@ingroup chessguiconv
		///@param message
		virtual void WriteMessageArea(const std::string & message);

		///Set text in the Statusbar located at the bottom of the ChessGui
		///@ingroup chessguiconv
		///@param status
		virtual void SetStatusBar(const std::string & status);

		///Opens a Gtk::FileChooserDialog in the FILE_SAVE mode
		///@ingroup chessguiconv
		///@return Path to the file selected
		virtual std::string SelectSaveFile();
		///Opens a Gtk::FileChooserDialog in the FILE_OPEN mode
		///@ingroup chessguiconv
		///@return Path to the file selected
		virtual std::string SelectLoadFile();


		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		///@param color RRGGBBAA hexadecimal value see @link ChessGuiDefines.h @endlink
		virtual void HighlightSquare(signed int row,signed int col,guint32  color);

		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		virtual void UnHighlightSquare(signed int row,signed int col);

		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		///@param piece valid piece as define in ImageName
		virtual void PlacePiece(signed int row,signed int col, ImageName piece);

		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		virtual void ClearPiece(signed int row,signed int col);
		
		virtual void SetController(IChessController* controller);
		
		virtual void SetTimeoutMilliseconds(int milliseconds);
		
	private:
		void InitializeChessGui(const std::string& gladefile);
		void CleanupChessGui();
		
		void InitializeTimer();

};

///Log handler to be set to g_log
///user_data must be a valid pointer to an initiated ChessGui
void log_handler(const gchar *log_domain,
				 GLogLevelFlags log_level,
				 const gchar *message, gpointer user_data);


#endif

