/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../include/if_statement.h"
#include "../expression.h"

If_statement::If_statement(Gpl_type eval_type, Expression *expr, Statement_block* then_block, Statement_block* else_block)
{
  m_expr_eval_type  = eval_type;
  m_expr       = expr;          // condition (can be; INT, DOUBLE, STRING) 
  m_then_block = then_block;    // then block
  m_else_block = else_block;    // else block

}

If_statement::~If_statement()
{

}

void If_statement::execute(){
  if(m_expr_eval_type & (DOUBLE | INT)){
    if (m_expr->evaluateDouble()) {
      m_then_block->execute();

    } else {

      if(m_else_block){
        m_else_block->execute();
      }

    }
  } else if (m_expr_eval_type & (STRING)){
    string str = "";
    m_expr->evaluateString(str);
    if (str != "") {
      m_then_block->execute();

    } else { 
      if(m_else_block){
        m_else_block->execute();
      }

    }
  } // end IF int or double ELSE string conditional


  return ; 
}
