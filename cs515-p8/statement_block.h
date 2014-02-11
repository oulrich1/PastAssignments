/***
  This file is a placeholder for the Statement_block class you will write in 
  the next assignment p7.

  You may use it w/o modification in p6.

  You may use it as a starting point for your Statement_block class for p7.

  I have put in just enough for it to work in p6.

***/



#ifndef STATEMENT_BLOCK_H
#define STATEMENT_BLOCK_H

#include <iostream>

#include "include/statement.h"

#include "indent.h"
#include <vector>

class Game_object;

class Statement_block
{
  public:
    Statement_block(int block_line);

    // returns TRUE if size is 0 (where size is number of statements)
    bool empty();

    // executes all of this statement block's statements
    void execute();

    bool push_statement(Statement* stmt);
    bool set_statements(std::vector<Statement*> &vec);
  
    std::ostream &print(std::ostream &os) const;

  protected:
    std::vector<Statement*> m_statements_v;

    // line number statement block starts on (only used for debugging)
    int m_line; 
};


std::ostream & operator<<(std::ostream &os, const Statement_block &statement_block);

std::ostream & operator<<(std::ostream &os, const Statement_block *statement_block);

#endif // #ifndef STATEMENT_BLOCK_H
