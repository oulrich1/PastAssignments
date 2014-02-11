#include "variable.h"
#include "expression.h"

// ---------------------- //
//  Variable Definitions  //

Variable::Variable(string var_name, Expression* index_expression, int index){
  if(index_expression){
    m_variable_name = var_name;// + "[" + toString(index) + "]";
    m_expression = index_expression;
    m_index = index;
  } else {
    m_variable_name = var_name;
    m_expression = NULL; 
    m_index = index;
  }

  Symbol_table* symbolTable = Symbol_table::instance();
  Gpl_type TYPE;
  string var_name_tmp = m_variable_name + (m_expression ? "["+toString(0)+"]" : "");
  if(symbolTable->get_type(&var_name_tmp, TYPE)){  // if it exists then set the type 
    m_type = TYPE;
  } else {
    m_type = INVALID_TYPE;   // which means that i forced to insert the variable into the expression 
                             // even though it doesnt actually exist in the symbol table
    // THIS IS BAD
  }

  m_member_variable_name = "";
  is_member_variable     = false;

} // END CONSTRUCTOR

Variable::Variable(){
  m_variable_name =   "";
  m_type          =   INVALID_TYPE;
  m_expression    =   NULL;

  m_member_variable_name = "";
  is_member_variable     = false;

  m_index                = 0;
  m_expression = NULL;
  m_anim_block = NULL;
}
Variable::~Variable(){
  if(m_expression)
    delete m_expression;
}

Symbol* Variable::get_symbol(){
  if(m_expression){
    int index = m_expression->evaluateInteger();
    Symbol* element = (Symbol_table::instance()->find(m_variable_name + "[" + toString(index) + "]")); 
    if(!element){
      Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_variable_name, toString(index));
      return (Symbol_table::instance()->find(m_variable_name + "[" + toString(0) + "]"));
    } else {
      return element;
    }
  } else {
    return (Symbol_table::instance()->find(m_variable_name));
  }
  return NULL;
}

void* Variable::getValue(){
  if(m_type){ // just a safeguard against invalid types (shoudnt happn
    if(is_member_variable){
      assert(m_type == GAME_OBJECT);

      Game_object* gameObj;
      Gpl_type type;
      void* retval;

      gameObj = ((Game_object*)(Symbol_table::instance()->find(m_variable_name))->value_ptr()); 
      if(gameObj->get_member_variable_type(m_member_variable_name, type) == OK){  // dont care about the type.. its  a void p
       retval = gameObj->get_member_variable_voidptr(m_member_variable_name);
      }
      return  retval;
    } 
    return (void*)(Symbol_table::instance()->find(m_variable_name))->value_ptr();
  }
  return 0;
}


//////////////////////////////
//////ARRAY OF VARIABLES//////
void*  Variable::getValue(int index){
  if(m_type){
    // ideally i would check to see if the expresstion has changed in some way.. by askign the expr tree
    //  but naw ill just evaluate the expression anyways .
    if(is_member_variable){
      assert(m_type == GAME_OBJECT);
      Game_object* gameObj;
      Gpl_type type;
      void* retval;

      gameObj = (Game_object*)((Symbol_table::instance()->find(m_variable_name + "[" + toString(index) + "]" ))->value_ptr()); 
      if(gameObj->get_member_variable_type(m_member_variable_name, type) == OK){
       retval = gameObj->get_member_variable_voidptr(m_member_variable_name);
      }
      return  retval;
    } 
    // if the array is out of bounds, use index 0
    if(!Symbol_table::instance()->find(m_variable_name + "[" + toString(index) + "]" )){
      Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, m_variable_name, toString(index));
      index = 0;
    }
    return (void*)(Symbol_table::instance()->find(m_variable_name + "[" + toString(index) + "]" ))
            ->value_ptr();
  }
  return 0;
}



Gpl_type Variable::getType(){
  if(is_member_variable){  // get the type of the member variable if this variable is a member variable
    Gpl_type type;
    string var_name = m_variable_name + (m_expression ? "["+toString(0)+"]" : "");
    ((Game_object*)(Symbol_table::instance()->find(var_name))->value_ptr())
      ->get_member_variable_type(m_member_variable_name, type);
    return type;
  }
  return m_type;
}


bool   Variable::setMemberVariableString(string &str){
  is_member_variable = true;
  m_member_variable_name = str;
  //cout << str << " is a member of " << m_variable_name << endl;
  return true;
}
