/*
  ALWAYS include parser.h instead of y.tab.h

  Here is why:

    Since the union created by bison contains several gpl objects,
    a forward class declaration, or including the .h file must be 
    done before the union is created.

    Bison generates y.tab.h where the union is created. 
    I can't find a way to get bison to generate a y.tab.h that includes 
    forward class declarations and #include's, so I created this file.


*/

#ifndef PARSER_H
#define PARSER_H
// for each type used in the union, you will need to 
// put the appropriate include here
// since it is bad programming practive to include "using namespace std"
// in a .h file, you will have to put "std::string" in the union instead
// of "string"
#include "error.h"

#include "window.h"
#include "event_manager.h"

#include  "gpl_assert.h"
#include  "gpl_type.h"
#include "game_object.h"

#include "symbol_table.h"

#include "variable.h"
#include "expression.h"
#include "statement.h"

#include "if_statement.h"
#include "print_statement.h"
#include "exit_statement.h"
#include "for_statement.h"
#include "assign_statement.h"


#include "game_object.h"
#include "triangle.h"
#include "pixmap.h"
#include "circle.h"
#include "rectangle.h"
#include "textbox.h"    

#include "animation_block.h"
#include "statement_block.h"


//#include <string>				 // using namespace std is declared in BOTH gpl.l and .y


#include "y.tab.h"

#endif // #ifndef PARSER_H
