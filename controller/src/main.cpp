/* Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
 *
 * Copyright: For use by the students of CS 240 at BYU
 * 
 * Last edited: Wayne Robison, 21 Apr 2011
 * 
 * Instructions: Complete the connectController function
 */

#include <gtkmm/main.h>
#include <glib.h>
#include "ChessGuiImages.h"
#include "ChessView.h"

#include "Controller.h"
#include <iostream>
using namespace std;


/******************************************************************************/
/******************* EDIT THE connectController FUNCTION **********************/

//Create your instance of the IChessController interface here and connect it to
//the game object using the SetView method.  Don't forget to connect the game
//object to your IChessController object using the SetController method.
void connectController(ChessView& view, IChessController ** cont, int argc, char ** argv)
{
	// 1. Process command-line args
	string argument = argv[1];
	int argumentNumber = 0;
	if(argument == "hh")
	{
		argumentNumber = 0;
	}
	else if(argument == "hc")
	{
		argumentNumber = 1;
	}
	else if(argument == "ch")
	{
		argumentNumber = 2;
	}
	else if(argument == "cc")
	{
		argumentNumber = 3;
	}
	
	// 2. Initialize controller. This is tricky because it's a double pointer.
	// Example:
	//		(*cont) = new MyController(parameters);
	
	(*cont) = new Controller(argumentNumber);
 
	// 3. Connect the view and controller using the IChessController::SetView 
	// and IChessView::SetController methods
	(*cont)->SetView(&view);
	view.SetController(*cont);
	
	
}



/******************************************************************************/
/************ YOU DO NOT NEED TO EDIT ANYTHING BELOW HERE *********************/

///@def GLADE_FILE
///The loacation of the glade file relative to the loaction of the executable.
///See @link cs240chess.glade "Glade File" @endlink
#define GLADE_FILE "../view/cs240chess.glade"

///@def IMAGE_PATH
///Location of the default image directory relative to the exectuable
#define IMAGE_PATH "../view/images/"

///@def LOG_LEVEL_HIDE_MASK
///@brief Set the log levels (using the Glib log levels)
///that will be ignored by the Chess logging function.
///
///This mask will hide messages from being displayed to the command line before
///the GUI is initialized.  Set this flag at compile time using
///the compiler directive -D and OR-ed values of the Glib log levels. For example:
///@code
///g++ -g -o main.o (options) -DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO) main.cpp
///@endcode
///will prevent debug and info messages from being displayed.
#ifndef LOG_LEVEL_HIDE_MASK
#define LOG_LEVEL_HIDE_MASK (0)
#endif

///A handler for logging messages received before the GUI is initialized
///@ingroup chessgui
void ChessGui_log_handler(const gchar *log_domain,
						  GLogLevelFlags log_level,
						  const gchar *message, gpointer user_data)
{
    int level = log_level & (~LOG_LEVEL_HIDE_MASK & G_LOG_LEVEL_MASK);

    switch(level)
    {
        case G_LOG_LEVEL_DEBUG:
            std::cerr << "DEBUG::" << message << std::endl;
            break;
        case G_LOG_LEVEL_ERROR:
            std::cerr << "ERROR::" << message << std::endl;
            break;
        case G_LOG_LEVEL_CRITICAL:
            std::cerr << "CRITICAL::" << message << std::endl;
            break;
        case G_LOG_LEVEL_WARNING:
            std::cerr << "WARNING::" << message << std::endl;
            break;
        case G_LOG_LEVEL_MESSAGE:
            std::cerr << "MESSAGE::" << message << std::endl;
            break;
        case G_LOG_LEVEL_INFO:
            std::cerr << "INFO::" << message << std::endl;
            break;
        default:
            // Do Nothing--the message was hidden by the mask.
            break;
    }
}


int main(int argc,char ** argv)
{

	IChessController* controller = 0;	
	
	#ifndef MEMCHECK

	///Parses path to executable for loading default images and gladeFile
	std::string path(argv[0]);
	int dirFinder = path.find_last_of('/');
	path=path.substr(0,dirFinder+1);


	///Resolves the path of the executable with GLADE_FILE
	std::string gladeFile(path + GLADE_FILE);

	int logId = g_log_set_handler(0,G_LOG_LEVEL_MASK,ChessGui_log_handler,0);

	#endif

	try
	{
		#ifdef MEMCHECK
		
		ChessView game;
		
		connectController(game, &controller, argc, argv);

		game.run();

		#else
		
		Gtk::Main myapp(argc,argv);

		///Loads default images based off the path to the executable and IMAGE_PATH
		ChessGuiImages::LoadImages(std::string(path+IMAGE_PATH));

		///Initialize Chess view using glade file
		ChessView game(gladeFile);
				
		
		connectController(game, &controller, argc, argv);		
		
		
		///run game
		game.run(myapp);
		
		#endif

	}
	catch(std::exception & e)
	{
		g_warning(e.what());
		return 1;
	}
	catch(...)
	{
		g_warning("Unknown Error Occurred, Terminating");
		return 1;
	}


	#ifndef MEMCHECK
	g_log_remove_handler(0,logId);
	#endif
	
	delete controller;

	return 0;
}



