
//// ***************************** ////
/*
  Variable:

    holds a variable name. This variable name is associated with a symbol in the SymbolTable
    ... Variable must hold a ptr to a symbol in the symbol table
    ... Variable can getInt getDouble or getString

    ... when created, Variable finds out the type of the variable and sets the type apropriately 

    good news, i added a member variable string
*/

#include "globals.h"  
#include "symbol_table.h"


#ifndef __VARIABLE
#define __VARIABLE

class Expression;
class Animation_block;
class Symbol;

class Variable{
  public:
    Variable(string var_name, Expression* index_expression = NULL, int index = 0);

    Variable();
    ~Variable();

    Symbol*         get_symbol();
    void*           getValue();           // when the variable is a single value
    //int             getIntValue();          
    //double          getDoubleValue();         
    //string*         getStringPtrValue();        

    void*           getValue(int index); // when im getting an array variable value (note: objects withm ember variabels

    Gpl_type        getType();
    string          getName(){ return m_variable_name; }                //  return name of variable
    string          getVarName() { return m_variable_name; }
    string          getVarMemberName() {return m_member_variable_name;} //  return name of member variable

    Expression*     getExpression() { return m_expression; }

    bool            setMemberVariableString(string &str);
    bool            isMemberVariable() {return is_member_variable; }
    bool            is_array(){ return (m_expression ? true : false); }
  private:
    Gpl_type            m_type;
    string              m_variable_name;

    string              m_member_variable_name; // since i only set this when the member is a valid member variable.. i know this is good
    bool                is_member_variable;

    int                 m_index;

    Expression*         m_expression;
    Animation_block*    m_anim_block;

};

#endif


