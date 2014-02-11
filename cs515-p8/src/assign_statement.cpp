/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../include/assign_statement.h"
#include "../expression.h"
#include "../variable.h"
#include "../symbol_table.h"

Assign_statement::Assign_statement(Variable* var, int assign_type, Expression* expr)
{
  m_variable    = var;
  m_assign_type = (Assign_type) assign_type;
  m_expression        = expr;
}

Assign_statement::~Assign_statement()
{

}

// Assumes that the variable and expression are of correct type
void Assign_statement::execute(){
  // if m_variable->m_expression is set then the variable is an array element
  //    if the variable is_member_variable then the variable is a member variable and m_member_variable_name is set  
  //    else the variable is NOT a member variable and is merely an element in the array 
  // else the variable is NOT an array element and is merely a single variable
  //    if the variable is_member_variable then the variable is a member variable and m_member_variable_name is set  
  //    else the variable is NOT a member variable

  /*   Performs this function:

      //  get the current value, 
      //  perform assign operation,
      //  set the variable's symbol

  */
  int     lhv_int; // left hand value  ... of type: int, dobule, strings
  double  lhv_dbl;
  string  lhv_str;




    if(m_variable->isMemberVariable()){                   // with a member variable 

      switch(m_assign_type){
        case ASSIGN:
          switch(m_variable->getType()){
            case INT:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), m_expression->evaluateInteger());
              break;
            case DOUBLE:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), m_expression->evaluateDouble());
              break;
            case STRING:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), m_expression->evalString());
              break;
            case ANIMATION_BLOCK:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), (Animation_block*)m_expression->getValue());
            default:
            break;
            }
          break;
        case PLUS_ASSIGN:
          switch(m_variable->getType()){
            case INT:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->get_member_variable(m_variable->getVarMemberName(), lhv_int);
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), lhv_int + m_expression->evaluateInteger());
              break;
            case DOUBLE:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->get_member_variable(m_variable->getVarMemberName(), lhv_dbl);
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), lhv_dbl + m_expression->evaluateDouble());
              break;
            case STRING:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->get_member_variable(m_variable->getVarMemberName(), lhv_str);
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), lhv_str + m_expression->evalString());
              break;
            default:
            break;
            }
          break;
        case MINUS_ASSIGN:
          switch(m_variable->getType()){
            case INT:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->get_member_variable(m_variable->getVarMemberName(), lhv_int);
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), lhv_int - m_expression->evaluateInteger());
              break;
            case DOUBLE:
              ((Game_object*)m_variable->get_symbol()->value_ptr())->get_member_variable(m_variable->getVarMemberName(), lhv_dbl);
              ((Game_object*)m_variable->get_symbol()->value_ptr())->set_member_variable(m_variable->getVarMemberName(), lhv_dbl - m_expression->evaluateDouble());
              break;
            case STRING:
             // nope.jpg
             //m_variable->get_symbol()->set_member_variable(m_variable->getVarMemberName(), m_expression->evalString());
              break;
              default:
              break;
            }
          break;
          default:
          break;
      }// end switch

    } else {                                              // else its not a member variable but an object element of an array
      switch(m_assign_type){
        case ASSIGN:
          switch(m_variable->getType()){
            case INT:
              m_variable->get_symbol()->set(m_expression->evaluateInteger());
              break;
            case DOUBLE:
              m_variable->get_symbol()->set(m_expression->evaluateDouble());
              break;
            case STRING:
              m_variable->get_symbol()->set(m_expression->evalString());
              break;
              default:
              break;
            }
          break;
        case PLUS_ASSIGN:
          switch(m_variable->getType()){
            case INT:
              m_variable->get_symbol()->set(m_variable->get_symbol()->getValue<int>() + m_expression->evaluateInteger());
              break;
            case DOUBLE:
              m_variable->get_symbol()->set(m_variable->get_symbol()->getValue<double>() + m_expression->evaluateDouble());
              break;
            case STRING:
              m_variable->get_symbol()->set(m_variable->get_symbol()->getValue<string>() + m_expression->evalString());
              break;
              default:
              break;
            }

          break;
        case MINUS_ASSIGN:
          switch(m_variable->getType()){
            case INT:
              m_variable->get_symbol()->set(m_variable->get_symbol()->getValue<int>() - m_expression->evaluateInteger());
              break;
            case DOUBLE:
              m_variable->get_symbol()->set(m_variable->get_symbol()->getValue<double>() - m_expression->evaluateDouble());
              break;
            case STRING:
              // oops cannot do this.. error
              //m_variable->get_symbol()->set(m_variable->get_symbol()->getValue<string>() - m_expression->evalString());
              break;
              default:
              break;
            }
          break;
          default:
          break;
      }// end switch
    } //end else
  return;

}