CC = g++
CPPFLAGS = -g -Wall -pedantic


LIBDIRS= -L/usr/X11R6/lib
LIBS = -lX11 -lglut -lGL -lGLU -lm -lfl

INC_DIRS=		include/
SRC_DIRS=		src/

INC=	-I$(INC_DIR)
SRC=		$(SRC)


VPATH = ./ $(SRC_DIRS) $(INC_DIRS) ../$(INC_DIRS)


C++SRC =  globals.cpp error.cpp gpl_assert.cpp gpl_type.cpp gpl.cpp indent.cpp \
					symbol_table.cpp variable.cpp expression.cpp \
					animation_block.cpp circle.cpp event_manager.cpp \
					game_object.cpp pixmap.cpp rectangle.cpp statement_block.cpp \
			   textbox.cpp triangle.cpp window.cpp \
				 statement.cpp \
				 print_statement.cpp if_statement.cpp for_statement.cpp exit_statement.cpp assign_statement.cpp

 
C++OBJ =  globals.o error.o gpl_assert.o gpl_type.o gpl.o indent.o \
				 symbol_table.o variable.o expression.o \
				 animation_block.o circle.o event_manager.o \
				 game_object.o pixmap.o rectangle.o statement_block.o \
				 textbox.o triangle.o window.o  \
				 statement.o \
				 print_statement.o if_statement.o for_statement.o exit_statement.o assign_statement.o 
#
#	using the compiled object files to build the target "gpl"
#		// if the object hasnt been built yet, then build it

gpl: y.tab.o lex.yy.o $(C++OBJ)
	$(CC) -g -o gpl y.tab.o lex.yy.o $(C++OBJ) -Iinclude/ $(LIBDIRS) $(LIBS)


#.c.o:
#	g++ $(CPPFLAGS) -I-$(VPATH) -o $@ $<

#
# compiling the gpl file
#	// and declare some preprocessor symbols 

# g++ -DSYMBOL_TABLE -DPRINT_SYMBOL_TABLE  $(CPPFLAGS) -Iinclude/ -c gpl.cpp

gpl.o: gpl.cpp 
	$(CC) -DSYMBOL_TABLE -DGRAPHICS  $(CPPFLAGS) -Iinclude/ -c gpl.cpp


y.tab.o: gpl.y
	bison -vyd gpl.y								
	$(CC) $(CPPFLAGS) -Iinclude/ -c y.tab.c	


# generating yacc program/parser
y.tab.c y.tab.h: gpl.y
	bison -vyd gpl.y


lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CPPFLAGS) -DYY_NO_UNPUT -Iinclude/ -c lex.yy.c


# generating scanner
lex.yy.c: gpl.l
	flex gpl.l

clean:
	rm -f $(C++OBJ) gpl gpl.exe lex.yy.c lex.yy.o \
	y.output y.tab.h y.tab.c y.tab.o \
	*.stackdump
