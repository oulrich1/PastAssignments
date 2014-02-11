/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../expression.h"
#include "../include/print_statement.h"

// set  the expression and get ready to execute.. :)
Print_statement::Print_statement(int line_number, Expression* expr)
{
  m_line_number = line_number;
  m_expr = expr;
}

// clean up the mess
Print_statement::~Print_statement()
{
  delete m_expr;
  m_expr = NULL;
}

// executes the print statement and prints teh evaluated strign
void Print_statement::execute(){
  if(!m_expr) return;
  
  string str_to_print = "";
  if(m_expr->getEvaluatedType() & (STRING | DOUBLE | INT)){           // if the evaluated type is a valid type, then we are good
    m_expr->evaluateString(str_to_print);                             // so then evaluate the string expression

    printf("gpl[%d]: %s\n", m_line_number, str_to_print.c_str());               // print the string to std out

  } else {
                                                                      // error, the expression is an invalid expression type
   // throw error if the expr in print() evaluates to Gameobject, Animationblock or invalid? 
  }
  return;
}
