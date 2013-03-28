################################################################################
# CS 240 Chess Project Makefile
#
# INSTRUCTIONS: This is a starting makefile for the chess project. You are to 
# keep this up-to-date as you add source files. In addition to keeping it 
# up-to-date with new files you create, you need to make the following changes 
# to this makefile:
# 
#	- compile the object files associated with the View into a shared library, 

#	- ** COMPLETE But need to add parameters
#	    add pseudo-targets for the different run modes (namely "runhh", "runhc",
#		"runch", and "runcc"),

#	- add a "test" pseudo-target (you will probably want to make a new executable
#		for this with its own main method),
#	- add a "lib" pseudo-target,
#	- edit the command associated with the memcheck pseudo-target (i.e.,
#		the valgrind command. See the note above it for details).
# 
# NOTES: 
# 1. All the code for the GUI side of this project is provided for you. As a 
# result, there are some things in this makefile which you do not need to alter.
# Such items will be clearly marked with comments.
# 2. Out-of-the-box, without making any changes to this initial makefile, 
# running "make run" will compile the code and bring up an empty GUI. 
################################################################################

 
############### --- BEGIN UNTOUCHABLE SECTION - Do Not Edit --- ################
# Macros for GUI libraries.
GTKMM = gtkmm-2.4
SIGC = sigc++-2.0
LIBGLADE = libglademm-2.4

# TODO Re-phrase: CFLAGS are the -I values needed to compile files using the 
# GTKMM, SIGC, and LIBGLADE libraries
CFLAGS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --cflags`
# TODO Re-phrase: LIBS are the paths to the static libraries for GTKMM, SIGC,
# and LIBGLADE needed for linking
LIBS   = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --libs`
####################### --- END UNTOUCHABLE SECTION --- ########################




##################################################################################################
##################################################################################################
#				FLAGS


#Compilation flags:
INCLUDES = -Imodel/inc/ -Iview/inc/ -Icontroller/inc/ -Iutils/inc/
DEBUG = -g -Wall


# Uncomment the flag on this next line to turn off the logging messages from the GUI.
LOG_FLAG = #'-DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO)'


STATIC_LIB_FILE_OPTIONS = -c -I utils/inc


STATIC_LIB_LINK_OPTIONS = -L staticlib -l cs240utils



##################################################################################################
##################################################################################################
#				OBJECTS

MY_OBJS =  controller/obj/Computer.o \
		controller/obj/Facade.o \
		controller/obj/Human.o \
		controller/obj/Controller.o \
		model/obj/Cell.o \
		model/obj/ChessBoard.o \
		model/obj/Move.o \
		model/obj/MoveHistory.o \
		model/obj/ChessXMLLoader.o \
		model/obj/Pawn.o \
		model/obj/Rook.o \
		model/obj/Knight.o \
		model/obj/Bishop.o \
		model/obj/Queen.o \
		model/obj/King.o \
		model/obj/Piece.o \
		controller/obj/CommonFunctions.o \
		model/obj/ChessXMLSaver.o
		

LIB_OBJS = view/obj/ChessView.o \
     		view/obj/ChessGuiBoardCell.o \
     	 	view/obj/ChessGuiBoard.o \
      		view/obj/ChessGui.o \
     	 	view/obj/ChessGuiImages.o \
     		view/obj/SelectDialog.o

STATIC_LIB_OBJS = utils/obj/CommandRunner.o \
		utils/obj/FileInputStream.o \
		utils/obj/FileSystem.o \
		utils/obj/HTMLToken.o \
		utils/obj/HTMLTokenizer.o \
		utils/obj/HTTPInputStream.o \
		utils/obj/StringUtil.o \
		utils/obj/URLInputStream.o

##################################################################################################
##################################################################################################
#				INCLUDES


MY_CONT_INCLUDES = controller/inc/Computer.h \
		controller/inc/Facade.h \
		controller/inc/Human.h \
		controller/inc/IChessController.h \
		controller/inc/IChessPlayer.h \
		controller/inc/CommonFunctions.h
		
MY_MODEL_INCLUDES = model/inc/Cell.h \
		model/inc/ChessBoard.h \
		model/inc/Move.h \
		model/inc/MoveHistory.h \
		model/inc/Piece.h \
		model/inc/ChessXMLLoader.h \
		model/inc/Pawn.h \
		model/inc/Rook.h \
		model/inc/Knight.h \
		model/inc/Bishop.h \
		model/inc/Queen.h \
		model/inc/King.h \
		model/inc/ChessXMLSaver.h
	
MY_VIEW_INCLUDES = view/inc/CS240Exception.h \
		view/inc/ChessGui.h \
		view/inc/ChessGuiBoard.h \
		view/inc/ChessGuiBoardCell.h \
		view/inc/ChessGuiDefines.h \
		view/inc/ChessGuiImages.h \
		view/inc/ChessView.h \
		view/inc/IChessView.h \
		view/inc/Inline.h \
		view/inc/SelectDialog.h


STATIC_LIB_INCLUDES = utils/inc/CS240Exception.h \
		utils/inc/CommandRunner.h \
		utils/inc/FileInputStream.h \
		utils/inc/FileSystem.h \
		utils/inc/HTMLToken.h \
		utils/inc/HTMLTokenizer.h \
		utils/inc/HTTPInputStream.h \
		utils/inc/InputStream.h \
		utils/inc/StringUtil.h \
		utils/inc/URLInputStream.h \
		utils/inc/UnitTest.h


##################################################################################################
##################################################################################################
#				RUN								

run: lib bin/chess
	export LD_LIBRARY_PATH=/users/ugrad/l/lexic92/Desktop/Chess/lib:$$LD_LIBRARY_PATH; bin/chess hh



##################################################################################################
##################################################################################################
#				RUNHH	

runhh: bin/chess 
	export LD_LIBRARY_PATH=lib/libcs240utils.so:/users/ugrad/l/lexic92/Desktop/Chess/lib; bin/chess hh
	


##################################################################################################
##################################################################################################
#				RUNHC	
runhc: bin/chess 
	export LD_LIBRARY_PATH=lib/libcs240utils.so:/users/ugrad/l/lexic92/Desktop/Chess/lib; bin/chess hc



##################################################################################################
##################################################################################################
#				RUNCH	
runch: bin/chess 
	export LD_LIBRARY_PATH=lib/libcs240utils.so:/users/ugrad/l/lexic92/Desktop/Chess/lib; bin/chess ch



##################################################################################################
##################################################################################################
#				RUNCC	
runcc: bin/chess 
	export LD_LIBRARY_PATH=lib/libcs240utils.so:/users/ugrad/l/lexic92/Desktop/Chess/lib; bin/chess cc



##################################################################################################
##################################################################################################
#				BIN

bin:  bin/chess

bin/chess: lib controller/obj/main.o $(MY_OBJS)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o bin/chess controller/obj/main.o $(MY_OBJS) staticlib/libcs240utils.a lib/libcs240utils.so
	chmod ugo+x bin/chess


bin/mchess: lib controller/obj/memcheck_main.o $(MY_OBJS)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o bin/mchess controller/obj/memcheck_main.o $(MY_OBJS) staticlib/libcs240utils.a lib/libcs240utils.so
	chmod ugo+x bin/mchess
	

# Main object file
controller/obj/main.o: controller/src/main.cpp view/inc/ChessGuiImages.h view/inc/ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o controller/obj/main.o -c $(LOG_FLAG)  controller/src/main.cpp staticlib/libcs240utils.a lib/libcs240utils.so



controller/obj/memcheck_main.o: controller/src/main.cpp view/inc/ChessGuiImages.h view/inc/ChessView.h
	g++ -DMEMCHECK $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o controller/obj/memcheck_main.o -c $(LOG_FLAG) controller/src/main.cpp staticlib/libcs240utils.a lib/libcs240utils.so




##################################################################################################
##################################################################################################
#				LIB

lib: lib/libcs240utils.so staticlib/libcs240utils.a



lib/libcs240utils.so: $(LIB_OBJS)
	g++ -shared -o lib/libcs240utils.so $(LIB_OBJS)


staticlib/libcs240utils.a : $(STATIC_LIB_OBJS)
	ar r staticlib/libcs240utils.a $(STATIC_LIB_OBJS)


##################################################################################################
##################################################################################################
#				CLEAN
clean:
	@rm -f model/obj/*.o
	@rm -f view/obj/*.o
	@rm -f controller/obj/*.o
	@rm -f bin/chess
	@rm -f bin/mchess
	@rm -f bin/test
	@rm -f utils/obj/*.o
	@rm -f staticlib/*.a
	@rm -f lib/*.so


##################################################################################################
##################################################################################################
#				MEMCHECK

# Run the executable for memory testing
# Instructions: Edit the command below so that it runs the  memory-check executable in Human-Human 
# mode (i.e., add necessary command  line arguments to the end of valgrind the command below).
	
memcheck: bin/mchess
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp bin/mchess hh


##################################################################################################
##################################################################################################
#				TEST

test: lib bin/test
	bin/test


bin/test: lib  $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(MY_OBJS)  controller/obj/Test.o
	g++ -o bin/test controller/obj/Test.o  $(MY_OBJS) staticlib/libcs240utils.a
	chmod ugo+x bin/test


##################################################################################################
##################################################################################################
#				OBJECT TARGETS




##################################################################################################
#				STATIC LIBRARY OBJECTS

#They depend on all of their includes because it's easier.
#All the library .o's, which depend on their corresponding .cpp's.

utils/obj/CommandRunner.o : utils/src/CommandRunner.cpp $(STATIC_LIB_INCLUDES)
	 g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/CommandRunner.cpp -o utils/obj/CommandRunner.o

utils/obj/FileInputStream.o : utils/src/FileInputStream.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/FileInputStream.cpp -o utils/obj/FileInputStream.o

utils/obj/FileSystem.o : utils/src/FileSystem.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/FileSystem.cpp -o utils/obj/FileSystem.o

utils/obj/HTMLToken.o : utils/src/HTMLToken.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/HTMLToken.cpp -o utils/obj/HTMLToken.o

utils/obj/HTMLTokenizer.o : utils/src/HTMLTokenizer.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/HTMLTokenizer.cpp -o utils/obj/HTMLTokenizer.o

utils/obj/HTTPInputStream.o : utils/src/HTTPInputStream.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/HTTPInputStream.cpp -o utils/obj/HTTPInputStream.o

utils/obj/StringUtil.o : utils/src/StringUtil.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/StringUtil.cpp -o utils/obj/StringUtil.o

utils/obj/URLInputStream.o : utils/src/URLInputStream.cpp $(STATIC_LIB_INCLUDES)
	g++ $(STATIC_LIB_FILE_OPTIONS) utils/src/URLInputStream.cpp -o utils/obj/URLInputStream.o




	


################################################################################
# Targets for executables and main object files

# Explanation: There are two different executables, with two different main 
# object files, because main.cpp needs to be built differently depending on 
# whether you are doing memory testing or not. This is because the GTK library,
# and other GUI tools, have memory leaks that we cannot figure out how to 
# suppress. Therefore, when building an executable for memory testing, we use a
# macro (MEMCHECK) to tell the compiler to not include the code that builds the
# GUI. So when we check for memory leaks during passoff, we don't have to use
# the GUI.

# Main executable
# Note: Once you have added the ability to make a library out of the View files, 
# the executable should be dependent on, and link in the library file, not the 
# .o files! That means, instead of linking in $(LIB_OBJS) below, you should link
# in the actual library file.


################################################################################
# Targets for YOUR object files...

controller/obj/Computer.o: controller/src/Computer.cpp $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c controller/src/Computer.cpp -o controller/obj/Computer.o $(CFLAGS)
	
controller/obj/Controller.o: controller/src/Controller.cpp $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c controller/src/Controller.cpp -o controller/obj/Controller.o $(CFLAGS)
	
controller/obj/Facade.o: controller/src/Facade.cpp $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c controller/src/Facade.cpp -o controller/obj/Facade.o
	
controller/obj/Human.o: controller/src/Human.cpp $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c controller/src/Human.cpp -o controller/obj/Human.o $(CFLAGS)
	
controller/obj/Test.o: controller/src/Test.cpp $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c controller/src/Test.cpp -o controller/obj/Test.o $(CFLAGS)

controller/obj/CommonFunctions.o: controller/src/CommonFunctions.cpp $(MY_CONT_INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c controller/src/CommonFunctions.cpp -o controller/obj/CommonFunctions.o $(CFLAGS)
	
model/obj/Cell.o: model/src/Cell.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Cell.cpp -o model/obj/Cell.o

model/obj/ChessBoard.o: model/src/ChessBoard.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/ChessBoard.cpp -o model/obj/ChessBoard.o

model/obj/Move.o: model/src/Move.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Move.cpp -o model/obj/Move.o
	
model/obj/MoveHistory.o: model/src/MoveHistory.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/MoveHistory.cpp -o model/obj/MoveHistory.o
	
model/obj/ChessXMLLoader.o: model/src/ChessXMLLoader.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/ChessXMLLoader.cpp -o model/obj/ChessXMLLoader.o	
	
model/obj/ChessXMLSaver.o: model/src/ChessXMLSaver.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/ChessXMLSaver.cpp -o model/obj/ChessXMLSaver.o	
	
	
	
	
######### CHESS PIECES ############
model/obj/Pawn.o: model/src/Pawn.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Pawn.cpp -o model/obj/Pawn.o	

model/obj/Rook.o: model/src/Rook.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Rook.cpp -o model/obj/Rook.o	

model/obj/Knight.o: model/src/Knight.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Knight.cpp -o model/obj/Knight.o	

model/obj/Bishop.o: model/src/Bishop.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Bishop.cpp -o model/obj/Bishop.o	

model/obj/Queen.o: model/src/Queen.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Queen.cpp -o model/obj/Queen.o	

model/obj/King.o: model/src/King.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/King.cpp -o model/obj/King.o	

model/obj/Piece.o: model/src/Piece.cpp $(MY__INCLUDES) $(MY_MODEL_INCLUDES) $(MY_VIEW_INCLUDES) $(STATIC_LIB_INCLUDES)
	g++ $(INCLUDES) -g -c model/src/Piece.cpp -o model/obj/Piece.o	


################################################################################
# Targets for GUI-related object files
# Instructions: These will have to be recompiled as position-independent code, 
# so that they can be put into a shared library.

view/obj/ChessView.o: view/src/ChessView.cpp view/inc/SelectDialog.h view/inc/ChessView.h controller/inc/IChessController.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o view/obj/ChessView.o -c -fPIC $(LOG_FLAG) view/src/ChessView.cpp

view/obj/ChessGuiBoardCell.o: view/src/ChessGuiBoardCell.cpp view/inc/ChessGuiBoardCell.h view/inc/ChessGuiImages.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o view/obj/ChessGuiBoardCell.o -c -fPIC view/src/ChessGuiBoardCell.cpp

view/obj/ChessGuiBoard.o: view/src/ChessGuiBoard.cpp view/inc/ChessGuiBoard.h view/inc/ChessGui.h view/inc/ChessGuiImages.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o view/obj/ChessGuiBoard.o -c -fPIC view/src/ChessGuiBoard.cpp

view/obj/ChessGui.o: view/src/ChessGui.cpp view/inc/ChessGui.h view/inc/ChessGuiImages.h view/inc/SelectDialog.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o view/obj/ChessGui.o -c -fPIC view/src/ChessGui.cpp

view/obj/ChessGuiImages.o: view/src/ChessGuiImages.cpp view/inc/ChessGuiImages.h view/inc/Inline.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o view/obj/ChessGuiImages.o -c -fPIC view/src/ChessGuiImages.cpp

view/obj/SelectDialog.o: view/src/SelectDialog.cpp
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o view/obj/SelectDialog.o -c -fPIC view/src/SelectDialog.cpp

