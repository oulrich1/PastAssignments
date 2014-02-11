/*

*/

%{  // bison syntax to indicate the start of the header
  // the header is copied directly into y.tab.c

extern int yylex();
extern int yyerror(char *);
extern int line_count;  // from expr.l, used for statement blocks

#include <string>
using namespace std;

#include "parser.h"
#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>

Game_object*        tmp_gameObj;
string              tmp_gameObj_NAME;
Animation_block*    tmp_animBlock;

stack<Statement_block*> statement_block_stack;
vector<Symbol*>         forward_animation_block_vector;  // to keep track of the list of forward declarations to know which has no body

Symbol_table* symbolTable = Symbol_table::instance();       // create symbol table
int error = Expression::initialize_operation_functions();   // set up the operation table
    // appearantly i needed to return something.. g++ was whining, not sure why
    // just raelized that i cannot call functions from up here...

void evaluateExpr_AND_setArraySize(string *var_name, Expression *expr, int *array_size){

    string  str = "";
    int arraySize = 0;
    Gpl_type expressed_type = expr->getEvaluatedType();
    
    //cout << "in bison, evaluated type of expression: " << *$2 << " " ;
    //cout << (int)expressed_type << endl;


    //$4->printTree();
    //cout << endl;
    //cout << " -------------- " << endl;
   

    if(expressed_type & (STRING)) {
        expr->evaluateString(str);
        Error::error(Error::INVALID_ARRAY_SIZE,    //  error type
                        *var_name,                       //  Var name 
                        str
                    );  
        arraySize = 1;
    } else if(expressed_type & (DOUBLE)) {
        // invalid array initialization 
        Error::error(Error::INVALID_ARRAY_SIZE,    //  error type
                        *var_name,                                   //  Var name 
                        toString(expr->evaluateDouble())     //  Value that was used
                    );  
        arraySize = 1;
    } else if(expressed_type & INT) {

        arraySize = expr->evaluateInteger();   // this is where i finds the VALUE OF THE ARRAY SIZE

        if(arraySize <= 0){
            Error::error(Error::INVALID_ARRAY_SIZE,    //  error type
                            *var_name,                                   //  Var name 
                            toString(arraySize)     //  Value that was used
                        );  
            arraySize = 1;
        }

    }

    *array_size = arraySize;
    return ;
}

bool left_type_greater_or_equal_bit_position_compared_to_right_type(Gpl_type &left_type, Gpl_type &right_type){
    return (left_type > (right_type - (left_type & right_type)));
}

Gpl_type highest_bit(Gpl_type &type){
    int num = (int) type;
    int iter = 1;
    while((num = num >> 1)){
        iter = iter << 1;
    } 
    return (Gpl_type)iter;
}

%} // bison syntax to indicate the end of the header

// The union is used to declare the variable yylval which is used to
// pass data between the flex generated lexer and the bison generated parser

// the "%union" is bison syntax

%union {
 int            union_int;
 double         union_double;                // makes this known as a double as well
 std::string*   union_string;               // MUST be a pointer to a string (this sucks!)
 Expression*    union_expression;
 Variable*      union_variable;

 Gpl_type		union_gpltype;
 Operator_type  union_gploperator;           // any Operator_type.. geometric or math

 Game_object*   union_gameobject;
 Statement*     union_statement;
 Statement_block* union_statementblock;
 Window::Keystroke union_keystroke;
}


// TERMINATING TOKEN SYMBOLS  

//%token T_VARIABLE                 

%token <union_int>           T_FALSE
%token <union_int>           T_TRUE

%token <union_int>           T_INT_CONSTANT   // VALUE CONSTANTS
%token <union_double>		 T_DOUBLE_CONSTANT
%token <union_string>		 T_STRING_CONSTANT
%token <union_string>		 T_ID			  // Variable name as a string identifier

%token <union_int>			 T_PRINT          // associated with int line number // TODO: other line numbers like: "if"
%token <union_int>           T_EXIT

%token   T_INT                                // TYPE IDENTIFIERS
%token   T_DOUBLE
%token   T_STRING

%token T_MINUS
%token T_PLUS
%token T_DIVIDE
%token T_ASTERISK
%token T_MOD

%token T_AND
%token T_OR

%token T_NOT
%token T_EQUAL
%token T_GREATER
%token T_LESS


%token T_RANDOM
%token T_FLOOR
%token T_ABS
%token T_SQRT

%token T_ATAN
%token T_ACOS
%token T_ASIN
%token T_TAN
%token T_COS
%token T_SIN

%token T_NEAR
%token T_TOUCHES


%token T_CONSTANT

%token T_ELSE
%token T_IF

%token T_LKEY
%token T_KKEY
%token T_JKEY
%token T_HKEY
%token T_FKEY

%token T_DKEY
%token T_SKEY
%token T_AKEY
%token T_WKEY
%token T_SPACE

%token T_MOUSE
%token T_RIGHTMOUSE
%token T_MIDDLEMOUSE
%token T_LEFTMOUSE

%token T_DOWNARROW
%token T_UPARROW
%token T_RIGHTARROW
%token T_LEFTARROW


%token T_COMMA
%token T_SEMIC

%token T_FORWARD
%token T_INITIALIZATION

%token T_TRIANGLE
%token T_PIXMAP
%token T_CIRCLE
%token T_RECTANGLE
%token T_TEXTBOX


%token T_ANIMATION

%token T_F1
%token T_FOR

%token T_ON

%token T_LEFTMOUSE_DOWN
%token T_LEFTMOUSE_UP
%token T_MIDDLEMOUSE_DOWN
%token T_MIDDLEMOUSE_UP
%token T_MOUSE_DRAG
%token T_MOUSE_MOVE
%token T_PERIOD

%token T_RIGHTMOUSE_DOWN
%token T_RIGHTMOUSE_UP

%token T_LESS_EQUAL
%token T_GREATER_EQUAL
%token T_NOT_EQUAL
%token T_PLUS_ASSIGN
%token T_MINUS_ASSIGN


%token T_ASSIGN

%token T_RBRACKET
%token T_LBRACKET

%token T_RBRACE
%token T_LBRACE

%token T_RPAREN
%token T_LPAREN

//%token UNARY_OP
//%token T_IF_NO_ELSE  // i guess its not necessary to declare these unassociated tokens?



// grammar symbols that have values associated with them need to be

// NON-TERMINATING TOKEN SYMBOLS 

//%type animation_block
//%type animation_parameter

//%type block
//%type block_list

//%type declaration   
//%type declaration_list

//%type forward_declaration
%type<union_string> check_animation_parameter


//%type initialization_block
%type<union_keystroke> keystroke
//
//
//%type on_block
//%type parameter
//

%type<union_statement> statement
%type<union_statement> assign_statement
%type<union_statement> exit_statement
%type<union_statement> for_statement
%type<union_statement> if_statement
%type<union_statement> print_statement

%type<union_statementblock> statement_block
%type<union_statementblock> if_block

//%type statement_block_creator
//%type statement_list

%type <union_int>         variable_declaration      //union_int for line number

%type <union_expression>  expression                
%type <union_expression>  primary_expression 
%type <union_expression>  optional_initializer

%type <union_variable>    variable 
%type <union_gpltype>     simple_type
%type <union_gploperator> math_operator
%type <union_gploperator> geometric_operator

%type <union_gameobject>  object_declaration
%type <union_int>     object_type
//%type parameter_list_or_empty
//%type parameter_list 


// ASSOCIATIVE-PROPERTY DECLARATIONS 
//  HIGHEST PRESCEDENCE ON BOTOM

%right    T_ASSIGN
%right    T_PLUS_ASSIGN     T_MINUS_ASSIGN
 
%left     T_OR
%left     T_AND   

//%left     T_NOT_EQUAL
//%left     T_EQUAL
//%left     T_LESS_EQUAL
//%left     T_GREATER_EQUAL 
//%left     T_GREATER      
//%left     T_LESS    

%left     T_EQUAL   T_NOT_EQUAL
%left     T_LESS    T_GREATER T_LESS_EQUAL  T_GREATER_EQUAL       

%left     T_PLUS     T_MINUS               
%left     T_ASTERISK T_DIVIDE T_MOD

%right    T_NOT
%nonassoc UNARY_OP            // used for two rules MINUS, NOT

%left     T_IF 
%nonassoc T_IF_NO_ELSE
%left     T_ELSE 

// End token declarations



// GRAMMER RULES DEFINED BELOW //  
%%

//---------------------------------------------------------------------
program:
    declaration_list block_list 
    { 
        // check all animation blocks for to see if the body has been declared..
         int v_size = forward_animation_block_vector.size();
         for(int iter = 0; iter < v_size; iter++){
            if( !((Animation_block*)(forward_animation_block_vector[iter])->value_ptr())->isBodyDeclared() ){
                // then the body has not been declared for this animation block
                Error::error(Error::NO_BODY_PROVIDED_FOR_FORWARD, ((Animation_block*)(forward_animation_block_vector[iter])->value_ptr())->name() );
            }
         }
    }
    ;
//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration { }
    | empty { }
        ;
//---------------------------------------------------------------------
declaration:   
    variable_declaration T_SEMIC { }
    | object_declaration T_SEMIC { }
    | forward_declaration T_SEMIC { }
        ;
//---------------------------------------------------------------------
variable_declaration:
    simple_type T_ID optional_initializer {  // ideally the initlizater would return a value or NULL
		

         // neither types of T_ID may exist (array or single)
        if(!symbolTable->isInTable(*$2) && !symbolTable->isInTable(*$2+"[0]")){
            string  str = "";  //temp string with data to be copied over to a symbol
            if($3 == 0){  // if the expression is null tehn set default values
                   
                    if($1 & INT)
                        symbolTable->insert($1, *$2, 0);
                    if($1 & DOUBLE)
                        symbolTable->insert($1, *$2, 0.0);
                    if($1 & STRING)
                        symbolTable->insert($1, *$2, &str);
            } else {
               
                // the expression tree is created and now must be evaluated 
                // 
                    Gpl_type expressed_type = $3->getEvaluatedType();

                    //cout << "in bison, evaluated type of expression: " << *$2 << " " ;
                    //cout << (int)expressed_type << endl;

                    //$3->printTree();
                    //cout << endl;
                    //cout << " -------------- " << endl;

                    if($1 & STRING){
                        if(expressed_type){
                            $3->evaluateString(str);
                        } else {   // its an invalid expression tree .. for reasons forseen by operators
                            str = "";
                        }
                        symbolTable->insert($1, *$2, &str);
                    } else if($1 & DOUBLE){
                        if((expressed_type & (INT | DOUBLE)) && !(expressed_type & STRING) ){  // correct type
                            symbolTable->insert($1, *$2, $3->evaluateDouble());
                        } else {
                            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *$2);
                            symbolTable->insert($1, *$2, 0);
                        }

                    } else if($1 & INT){ // i want to create an integer from the expression
                        if((expressed_type & INT) && !(expressed_type & (DOUBLE | STRING)) ){  
                            symbolTable->insert($1, *$2, $3->evaluateInteger());
                        } else {
                            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *$2);
                             symbolTable->insert($1, *$2, 0);
                        }

                    }



            }
        } else { // duplicate
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
        }
	}
    | simple_type T_ID T_LBRACKET expression T_RBRACKET { 

			if($4){  // if its a valid expression

				if(!symbolTable->isInTable(*$2) && !symbolTable->isInTable(*$2+"[0]")){

                    int arraySize = 0;
                    evaluateExpr_AND_setArraySize($2, $4, &arraySize);

					int strLength = strlen($2->c_str());// length of variabled so that i can just memcpy it 
                                                        //over to the "REAL" variable name, named variable_name[i]
					char* tmp = (char*) malloc(strLength + 3 + (arraySize/10)+1);     
                          // "some_string[n]"  such that n can be $4/10 + 1 characters long given $4
                          //     is an integer greater than 0
					memcpy(tmp, (void*)$2->c_str(), strLength);

                    string str = "";
					for(int i = arraySize-1; i >= 0; i--){
						sprintf(tmp+strLength,"[%d]", i);              
							if($1 & INT){
								symbolTable->insert($1, tmp, 0);
                            }
							if($1 & DOUBLE){
								symbolTable->insert($1, tmp, 0.0);
                            }
							if($1 & STRING){
								symbolTable->insert($1, tmp, &str);
                            }
					}
					free(tmp);
				} else{ // duplicate
					Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
				}
			} else {
                // actually its an invalid expression..
			//	Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, *$2, );
			}
		} 
        ;

//---------------------------------------------------------------------
simple_type:
    T_INT  { $$ = INT; }
    | T_DOUBLE { $$ = DOUBLE; }
    | T_STRING { $$ = STRING; }
        ;

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression { $$ = $2; } // when some variable now EQUAL some expression (some expressed or executed expression)
    | empty { $$ = 0; } // $$ = NULL;
        ;

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID  // matches the declaration of an object.. 
    {                  //need to create new object before parame
        switch($1){
            case T_TRIANGLE:
                tmp_gameObj = new Triangle(); 
                break;
            case T_PIXMAP:
                tmp_gameObj = new Pixmap();
                break;
            case T_CIRCLE:
                tmp_gameObj = new Circle();  
                break;
            case T_RECTANGLE:
                tmp_gameObj = new Rectangle();
                break;
            case T_TEXTBOX:
                tmp_gameObj = new Textbox(); 
                break;
        }

        if(!symbolTable->insert(GAME_OBJECT, *$2, tmp_gameObj)){ // inserts a ptr to dynamically created gameobject
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
            //delete tmp_gameObj;
            //tmp_gameObj = NULL;
        } 

        tmp_gameObj_NAME = *$2;

    } T_LPAREN parameter_list_or_empty T_RPAREN { 
        // object_type, symbol_name ( NULL )
        // object_type, symbol_name ( paramlist )
        // BUT ACTUALLY: the parameters are set when the parameters are matched
        // setting teh parameters within the actions of the symbol parameter_list
        // NOW THE PARAMETERS ARE SET
    }
    | object_type T_ID T_LBRACKET expression T_RBRACKET 
    { 
        tmp_gameObj = NULL;

        if(symbolTable->isInTable(*$2) || symbolTable->isInTable(*$2+"[0]")){
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
        } else {
            int arraySize = 0;
            evaluateExpr_AND_setArraySize($2, $4, &arraySize);
        
            // now i have the array size..
            for(int i = 0; i < arraySize; i++){
                switch($1){
                    case T_TRIANGLE:
                        tmp_gameObj = new Triangle(); 
                        break;
                    case T_PIXMAP:
                        tmp_gameObj = new Pixmap();
                        break;
                    case T_CIRCLE:
                        tmp_gameObj = new Circle();  
                        break;
                    case T_RECTANGLE:
                        tmp_gameObj = new Rectangle();
                        break;
                    case T_TEXTBOX:
                        tmp_gameObj = new Textbox(); 
                        break;
                }

                symbolTable->insert(GAME_OBJECT, *$2 + "[" + toString(i) + "]", tmp_gameObj ); // now it's inserted
            } // end for
            tmp_gameObj = NULL;
        }// end else


    } // end array of object declaration
        ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE {      $$ = T_TRIANGLE; }
    | T_PIXMAP {         $$ = T_PIXMAP; }
    | T_CIRCLE {       $$ = T_CIRCLE; }
    | T_RECTANGLE {   $$ = T_RECTANGLE; }
    | T_TEXTBOX {      $$ = T_TEXTBOX;  }
        ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    parameter_list 
    { 
    }
    | empty 
    {
     }
        ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter 
    { }
    | parameter 
    { }
        ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression {                   
                string str = "";

                Gpl_type param_type;                         
                if(tmp_gameObj->get_member_variable_type(*$1, param_type) != OK){
                    Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, tmp_gameObj->type(), *$1);
                } else {

                    Gpl_type expressed_type = $3->getEvaluatedType();

                    if(param_type & ANIMATION_BLOCK){
                        if( expressed_type & ANIMATION_BLOCK ){  


                            // need to only set the animation block parameter if teh animation block that i am setting
                            // has a parameter that is of the same type of that as the object that needs to
                            // use the animation block..
                            // 
                            //  if the animationblock has a parameter Gameobject whos type is the same as tmp_gameObj->type
                            Symbol* anim_param_symbol = ((Animation_block*)(symbolTable->find($3->getNameOfVariable()))->value_ptr())->get_parameter_symbol();
                            if((anim_param_symbol->getGplTypeENUM() & GAME_OBJECT) &&
                                 (((Game_object*)anim_param_symbol->value_ptr())->type() == (tmp_gameObj->type())) ) 
                            {
                                tmp_gameObj->set_member_variable(*$1, (Animation_block*)(symbolTable->find($3->getNameOfVariable()))->value_ptr() );
                            } else {
                                Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, tmp_gameObj_NAME, $3->getNameOfVariable());
                            }
                        } else {
                            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *$1);
                             tmp_gameObj->set_member_variable(*$1, 0);
                        } 
                    } else if(param_type & STRING){
                        if(expressed_type){
                            $3->evaluateString(str);
                        } else {   
                            str = "";
                        }
                        tmp_gameObj->set_member_variable(*$1, str);
                    } else if(param_type & DOUBLE){
                        if((expressed_type & (INT | DOUBLE)) && !(expressed_type & STRING) ){  // correct type
                            tmp_gameObj->set_member_variable(*$1, $3->evaluateDouble());
                        } else {
                            Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, tmp_gameObj_NAME, *$1);
                            tmp_gameObj->set_member_variable(*$1, 0.0);
                        }

                    } else if(param_type & INT){ // i want to create an integer from the expression
                        if((expressed_type & INT) && !(expressed_type & (DOUBLE | STRING)) ){  
                            tmp_gameObj->set_member_variable(*$1, $3->evaluateInteger());
                        } else {
                            Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, tmp_gameObj_NAME, *$1);
                             tmp_gameObj->set_member_variable(*$1, 0);
                        }
                    } else {
                        /// reduntant
                        Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, tmp_gameObj->type(), *$1);
                    }
                }//  end check for known object parameter


    };

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN 
    { 
        // insert the *$3 and *$5 into the symbol table
        
        // ASSERT THAT tmp_gameObj_NAME HAS BEEN SET (this is the name of the object within the paraens of the anim block
        //  ASSERT THAT tmp_gameObj_NAME was already inserted into symbol table
        // so lets check to see if any of the names we use have been declared before..
        string animation_block_name = *$3;

        if(symbolTable->find(animation_block_name)){
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, animation_block_name);
        } else {

            symbolTable->insert(ANIMATION_BLOCK, 
                                animation_block_name, 
                                new Animation_block(0, symbolTable->find(tmp_gameObj_NAME), animation_block_name) );
                                // the 0 (first param) is a forward line number 
                                // second: the game object specified in the parameter of the forward declartion

            forward_animation_block_vector.push_back(symbolTable->find(animation_block_name));

        }

    }
        ;

//---------------------------------------------------------------------
block_list:
    block_list block { }
    | empty { }
        ;

//---------------------------------------------------------------------
block:
    initialization_block { }        // p8
    | animation_block { }           // p8
    | on_block { }                  // p7
        ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block 
    {
        Event_manager::instance()->push_statement_block(Window::INITIALIZE, $2); 
    }    // p8
        ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID
    { // 
        Symbol* anim_block_symbol = symbolTable->find(*$2);
        if(!anim_block_symbol){
         // the animation block does not exist
            Error::error(Error::NO_FORWARD_FOR_ANIMATION_BLOCK, *$2);
        } 
        else if(((Animation_block*)anim_block_symbol->value_ptr())->isBodyDeclared() == true){
            Error::error(Error::PREVIOUSLY_DEFINED_ANIMATION_BLOCK, *$2);
        }
    } 
    T_LPAREN check_animation_parameter T_RPAREN T_LBRACE 
    { 
        Symbol* anim_block_symbol = symbolTable->find(*$2);
        if(anim_block_symbol){

            if(((Animation_block*)anim_block_symbol->value_ptr())->isBodyDeclared() == true) {
                // this case is handled before the left curly brace (but after the T_ID is matched
            } else if(anim_block_symbol->getGplTypeENUM() & ANIMATION_BLOCK) {

                /* pushed the animation block on the stack */
                /* check to see if this param has the same name as param in forward*/
                Symbol* param_symbol = ((Animation_block*)anim_block_symbol->value_ptr())->get_parameter_symbol();
                if(*$5 == param_symbol->getName()){
                    // then if the types match then push else error( anim param does not match forward
                    // (this check is done in the check_animation_parameter production)

                    statement_block_stack.push((Animation_block*)anim_block_symbol->value_ptr());


                } else { // this anim_block body's current paramter doesnt match the name of the forward declaration
                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
                }

                /* now the statements will be matched and placed into the animation_block */

            } else { // then the animation block name has already been declared as a variable with a different type
                // NOTE: error is probably incorrect, 
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
            }
            
        } 

    }   // and then check this stuff.. and take action if matched!
    statement_list T_RBRACE end_of_statement_block 
    { // assuming: statement_list list of statements was pushed into the vector of statements for the animation block //
    
         //  the symbol that owns this animation block has a member variable that points to this animation block
         //  so i can pop the ptr without worrying about where it goes or where to put it



        Symbol* anim_block_symbol = symbolTable->find(*$2);
        if(anim_block_symbol){
            ((Animation_block*)anim_block_symbol->value_ptr())->bodyHasBeenDeclared(true);
            statement_block_stack.pop();
         } // else the animation forward declaration has NOT been declared..



    }
        ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID 
    { 
        if(!symbolTable->find(*$2)){
                switch($1){
                    case T_TRIANGLE:
                        tmp_gameObj = new Triangle(); 
                        break;
                    case T_PIXMAP:
                        tmp_gameObj = new Pixmap();
                        break;
                    case T_CIRCLE:
                        tmp_gameObj = new Circle();  
                        break;
                    case T_RECTANGLE:
                        tmp_gameObj = new Rectangle();
                        break;
                    case T_TEXTBOX:
                        tmp_gameObj = new Textbox(); 
                        break;
                    default:

                    break;
                }

            tmp_gameObj_NAME = *$2;

            tmp_gameObj->never_animate();
            tmp_gameObj->never_draw();

            symbolTable->insert(GAME_OBJECT, tmp_gameObj_NAME, tmp_gameObj);
        
        } else {
            Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
        }


        tmp_gameObj = NULL;
    }
        ;

//---------------------------------------------------------------------
check_animation_parameter:
    T_TRIANGLE T_ID 
    { 
        Symbol* object_symbol = symbolTable->find(*$2);
        if(object_symbol){
            // is the object_symbol->value type the same as this action's expectation?
            if(object_symbol->getGplTypeENUM() & GAME_OBJECT){
                if(((Game_object*)object_symbol->value_ptr())->type() == "Triangle"){
                    // NOTE: that the object that uses this animation block will be pointed to
                    //     when all gameobejcts are executed therefore..animation block is executed...
                    //     ... this is where the curparam ptr in anim_blcok is set to object that uses anim_block
                } else { 
                    // object is not of correct game object type 
                    //Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, );
                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
                }
            } else {
                // object is not of correct type
               Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
            }

        } 

        $$ = $2;
    }
    | T_PIXMAP T_ID 
    { 
        Symbol* object_symbol = symbolTable->find(*$2);
        if(object_symbol){
            // is the object_symbol->value type the same as this action's expectation?
            if(object_symbol->getGplTypeENUM() & GAME_OBJECT){
                if(((Game_object*)object_symbol->value_ptr())->type() == "Pixmap"){
                    // NOTE: that the object that uses this animation block will be pointed to
                    //     when all gameobejcts are executed therefore..animation block is executed...
                    //     ... this is where the curparam ptr in anim_blcok is set to object that uses anim_block
                } else { 
                    // object is not of correct type ( incorrect game object type )
                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 

                }
            } else {
                // object is not of correct type
               Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
            }

        }        
        $$ = $2;
    }
    | T_CIRCLE T_ID 
    { 
        Symbol* object_symbol = symbolTable->find(*$2);
        if(object_symbol){
            // is the object_symbol->value type the same as this action's expectation?
            if(object_symbol->getGplTypeENUM() & GAME_OBJECT){
                if(((Game_object*)object_symbol->value_ptr())->type() == "Circle"){


                } else { 
                    // object is not of correct type ( incorrect game object type )

                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
                }
            } else {
                // object is not of correct type
               Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
            }

        } 
        $$ = $2;
    }
    | T_RECTANGLE T_ID 
    { 
        Symbol* object_symbol = symbolTable->find(*$2);
        if(object_symbol){
            // is the object_symbol->value type the same as this action's expectation?
            if(object_symbol->getGplTypeENUM() & GAME_OBJECT){
                if(((Game_object*)object_symbol->value_ptr())->type() == "Rectangle"){

                } else { 
                    // object is not of correct type ( incorrect game object type )

                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
                }
            } else {
                // object is not of correct type
               Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
            }

        } 
        $$ = $2;
    }
    | T_TEXTBOX T_ID 
    {
        Symbol* object_symbol = symbolTable->find(*$2);
        if(object_symbol){
            // is the object_symbol->value type the same as this action's expectation?
            if(object_symbol->getGplTypeENUM() & GAME_OBJECT){
                if(((Game_object*)object_symbol->value_ptr())->type() == "Textbox"){

                } else { 
                    // object is not of correct type ( incorrect game object type )

                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
                }
            } else {
                // object is not of correct type
               Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
            }

        }
        $$ = $2;
    }
        ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block 
    { 

        Event_manager::instance()->push_statement_block($2, $3);

    }
        ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE { $$ = Window::SPACE; }
    | T_LEFTARROW {$$ = Window::LEFTARROW; }
    | T_RIGHTARROW {$$ = Window::RIGHTARROW; }
    | T_UPARROW {$$ = Window::UPARROW; }
    | T_DOWNARROW {$$ = Window::DOWNARROW; }
    | T_LEFTMOUSE_DOWN {$$ = Window::LEFTMOUSE_DOWN; }
    | T_MIDDLEMOUSE_DOWN {$$ = Window::MIDDLEMOUSE_DOWN; }
    | T_RIGHTMOUSE_DOWN {$$ = Window::RIGHTMOUSE_DOWN; }
    | T_LEFTMOUSE_UP    {$$ = Window::LEFTMOUSE_UP; }
    | T_MIDDLEMOUSE_UP {$$ = Window::MIDDLEMOUSE_UP; }
    | T_RIGHTMOUSE_UP {$$ = Window::RIGHTMOUSE_UP; }
    | T_MOUSE_MOVE {$$ = Window::MOUSE_MOVE; }
    | T_MOUSE_DRAG  { $$ = Window::MOUSE_DRAG;}
    | T_F1 {$$ = Window::F1; }
    | T_AKEY {$$ = Window::AKEY; }
    | T_SKEY {$$ = Window::SKEY; }
    | T_DKEY {$$ = Window::DKEY; }
    | T_FKEY {$$ = Window::FKEY; }
    | T_HKEY {$$ = Window::HKEY; }
    | T_JKEY {$$ = Window::JKEY; }
    | T_KKEY {$$ = Window::KKEY; }
    | T_LKEY {$$ = Window::LKEY; }
    | T_WKEY {$$ = Window::WKEY; }
        ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block 
    { 
        $$ = statement_block_stack.top();
        $$->push_statement($2);
        statement_block_stack.pop();
    }
    | statement_block 
    { 
        $$ = $1;
    }
        ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator
     statement_list 
    T_RBRACE end_of_statement_block 
    {

        $$ = statement_block_stack.top();
        statement_block_stack.pop();
    }
        ;

//---------------------------------------------------------------------
statement_block_creator:
{
    statement_block_stack.push(new Statement_block(42));
}
    // this goes to nothing so that you can put an action here in p7
        ;

//---------------------------------------------------------------------
end_of_statement_block:
{
   
} 
    // this goes to nothing so that you can put an action here in p7
        ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement 
    {
        // Left recursive grammer, but this evaluates left to right.. (left bottom to right top)
        //global_statement_list_vector.push_back($2);
        statement_block_stack.top()->push_statement($2);
        //cout << ($2)->get_line_number()<< endl;
    }
    | empty { }
        ;

//---------------------------------------------------------------------
statement:
    if_statement { $$ = $1; }
    | for_statement { $$ = $1;  }
    | assign_statement T_SEMIC { $$ = $1;  }
    | print_statement T_SEMIC { $$ = $1; }
    | exit_statement T_SEMIC {  $$ = $1; }
        ;

//---------------------------------------------------------------------
if_statement:
    T_IF 
    T_LPAREN expression T_RPAREN
     if_block %prec T_IF_NO_ELSE 
    {
        Gpl_type eval_type = (Gpl_type) $3->getEvaluatedType();
        if(!(eval_type & (GAME_OBJECT | ANIMATION_BLOCK | DOUBLE | STRING))){
            $$ = new If_statement(eval_type, $3, $5);
        } else { //error... invalid expression used for "if" conditional
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
             $$ = NULL;
        }
    }
    | T_IF 
    T_LPAREN expression T_RPAREN 
    if_block T_ELSE if_block 
      { 
        Gpl_type eval_type = (Gpl_type) $3->getEvaluatedType();
        if(!(eval_type & (GAME_OBJECT | ANIMATION_BLOCK | DOUBLE | STRING))){
             $$ = new If_statement(eval_type, $3, $5, $7);
        } else { //error... invalid expression used for "if" conditional
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
             $$ = NULL;
        }
      }
        ;

//---------------------------------------------------------------------
for_statement:
    T_FOR
     T_LPAREN 
        statement_block_creator assign_statement end_of_statement_block T_SEMIC
         expression T_SEMIC                                                         
        statement_block_creator assign_statement end_of_statement_block 
    T_RPAREN 
    statement_block 
    { 
        // push the assignment statement onto the new statement block (initializer statement block)
        // push the other  assignment statement onto... etc       (each should only hold one block)
        // create the for_statement  (initlaizer_statement_block, expression, assignment_statement, for_statement_block)

        if(!($7->getEvaluatedType() & (DOUBLE | STRING | GAME_OBJECT | ANIMATION_BLOCK))){
            Statement_block* right_assign_statement_block =  statement_block_stack.top();
             statement_block_stack.pop();
            Statement_block* left_initalizer_assign_statement_block =  statement_block_stack.top();
             statement_block_stack.pop();

            left_initalizer_assign_statement_block->push_statement($4);
            right_assign_statement_block->push_statement($10);      

            $$ = new For_statement(left_initalizer_assign_statement_block, $7, right_assign_statement_block, $13);
        } else {
            //error , expression is of invalid type.. cannot check for a condition on that matter
            Error::error(Error::INVALID_TYPE_FOR_FOR_STMT_EXPRESSION);
            $$ = new For_statement(0, 0, 0, $13);
            //$$ = NULL;
        }

        //return; 

    }

        ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN {
        if($3->getEvaluatedType() & (STRING | DOUBLE | INT)) {
            $$ = new Print_statement($1, $3); 
        } else {
            // error, incorrect type passed to function "print"
            Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
             $$ = NULL;
        }
    }

        ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN 
    {
        Gpl_type eval_type = $3->getEvaluatedType();
        if((eval_type & INT) && !(eval_type & (DOUBLE | STRING))) {
            $$ = new Exit_statement($1, $3); 
        } else {
            // error, incorrect type passed to function "print"
            Error::error(Error::EXIT_STATUS_MUST_BE_AN_INTEGER, gpl_type_to_string(eval_type));
            $$ = NULL;
        }
     }
        ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression 
    {   
        // assert that he variable does exist since it was matched
        // check to see if the variable CAN be assigned the value that expression evaluates to 
        // is the left type a bit position greater than or equal to the right type
        Gpl_type var_type = $1->getType();
        Gpl_type expr_type = $3->getEvaluatedType();

        if(left_type_greater_or_equal_bit_position_compared_to_right_type(var_type, expr_type)){
              // then: change the value in the symbol table at variable->get_symbol() to expression

            if(var_type & (INT | DOUBLE | STRING | ANIMATION_BLOCK)){
                $$ =  new Assign_statement($1, 0, $3);
            } else {
                Error::error(Error::INVALID_LHS_OF_ASSIGNMENT, $1->getVarName(), gpl_type_to_string(var_type));
                $$ =  NULL;
            }

        } else {
            //error.. cannot assign expression of type.. to variable of type...
           Error::error(Error::ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(var_type), gpl_type_to_string(highest_bit(expr_type)));
           $$ =  NULL;
        }
      

    }
    | variable T_PLUS_ASSIGN expression 
    { 
        Gpl_type var_type = $1->getType();
        Gpl_type expr_type = $3->getEvaluatedType();
        if(left_type_greater_or_equal_bit_position_compared_to_right_type(var_type, expr_type)){
              // then: change the value in the symbol table at variable->get_symbol() to expression
            if(var_type & (INT | DOUBLE | STRING)){
                $$ =  new Assign_statement($1, 1, $3);
            } else {
                Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT, $1->getVarName(), gpl_type_to_string(var_type));
                $$ =  NULL;
            }
            
        } else {
            //error.. cannot assign expression of type.. to variable of type...
            Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(var_type), gpl_type_to_string(highest_bit(expr_type)));
            $$ =  NULL;

        }
      
    }
    | variable T_MINUS_ASSIGN expression 
    { 
        Gpl_type var_type = $1->getType();
        Gpl_type expr_type = $3->getEvaluatedType();
        if(left_type_greater_or_equal_bit_position_compared_to_right_type(var_type, expr_type)){
              // then: change the value in the symbol table at variable->get_symbol() to expression
            if(var_type & (INT | DOUBLE)){
                $$ =  new Assign_statement($1, 2, $3);
            } else {
                Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT, $1->getVarName(), gpl_type_to_string(var_type));
                $$ =  NULL;
            }
            
        } else {
            //error.. cannot assign expression of type.. to variable of type...
            Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(var_type), gpl_type_to_string(highest_bit(expr_type)));
            $$ =  NULL;
        }
      
    }
        ;

//---------------------------------------------------------------------
variable: 
    T_ID 
    {   
        if(symbolTable->isInTable(*$1)){
            $$ = new Variable(*$1); 
            //cout << endl;
            //cout << "using variable with name: " << *$1 <<  endl;
            //cout << endl;
        }
        else{
            Error::error(Error::UNDECLARED_VARIABLE, (*$1)); 
            symbolTable->insert(INT, *$1, 0);   //creating dummy symbol with the same name
            $$ = new Variable(*$1);   // create it anyways.. for error checking

        }
    }
    | T_ID T_LBRACKET expression T_RBRACKET     // its an array value being used.. check if its an int
    { 
        string variable_name = *$1; 
        Gpl_type expr_type = $3->getEvaluatedType();


        if(symbolTable->isInTable(variable_name)){
            // not an array
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, variable_name);
            $$ = new Variable(variable_name, 0, 0); 
        } else {
            if(!(expr_type & (ANIMATION_BLOCK | GAME_OBJECT | DOUBLE | STRING))){
                int arrayIndex = $3->evaluateInteger();
                string variable = variable_name + "[" + toString(0) + "]";
                if(symbolTable->isInTable(variable)){
                    $$ = new Variable(variable_name, $3, arrayIndex); 
                }
            } else {
                string message = "";
                message = "A " + gpl_type_to_string(expr_type) + " expression";
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                                 variable_name,
                                 message);
                symbolTable->insert(INT, *$1+"["+toString(0)+"]", 0);   //creating dummy symbol with the same name
                $$ = new Variable(variable_name, $3 , 0); 
            }
        }
    }
    | T_ID T_PERIOD T_ID     // find the T_ID.T_ID //
    { // if the T_ID exists in the symbol table then its a valid variable..
        Symbol* objectSymbol;
        objectSymbol = symbolTable->find(*$1);
        if(objectSymbol){
            // ten if the right T_ID exists as a member variable in that object.. then cool ...
            // .. and tehn return a new variable some how..
            //  thinking..................................
            //  the object is in the symbol table..
            //   it is used as a variable in an expression
            //   the variable holds the name of the variable.
            //   + it could hold the member variable string.. 
            Gpl_type type = objectSymbol->getGplTypeENUM();
            Game_object* gameObj;
            switch(type){
                case GAME_OBJECT:
                     gameObj = (Game_object*)objectSymbol->value_ptr();
                    if(gameObj->get_member_variable_type(*$3,type) == OK){  // check type of member variable, and is it a member variabl?
                        // now what? its a member variable.. and i know its type..
                        // usualy variables are used in expressions .. so an expression is going to evaluate this..
                        // IDEA: imma createa a new variable named *$1 and store within it a member string *$3
                        $$ = new Variable(*$1);
                        $$->setMemberVariableString(*$3);

                    } else {  // you broke it, that is not a member variable of the left T_ID gameobject

                        Error::error(Error::UNDECLARED_MEMBER, *$1, *$3); 
                        symbolTable->insert(INT, *$1 + "." + *$3, 0);  // the dummy symbol has to be something different else variable getValue gets the value fromobject.. bad value since its an object:
                        $$ = new Variable(*$1 + "." + *$3);
                    }
                break;
                default:
                        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1, *$3); 
                        symbolTable->insert(INT, *$1 + "." + *$3, 0);   
                        $$ = new Variable(*$1 + "." + *$3);
                break;

            }


        } else {
            // not declared
            Error::error(Error::UNDECLARED_VARIABLE, *$1); 
            symbolTable->insert(INT, *$1, 0);   //creating dummy symbol with the same name
            $$ = new Variable(*$1);   // create it anyways.. for error checking

        }




    } 
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID 
    { 

        /*
            Does the symbol exist
            Is the value that the symbol holds a gameobject pointer, 
            is the type of the game object OK?
            Does the expression evaluate to an integer properly? (as indexes should)

            if all is well, then:
                set the new variable: (name, expression, index)
        */

        Symbol* objectSymbol;
        objectSymbol = symbolTable->find(*$1 + "[" + toString(0) + "]");
        if(objectSymbol){

            Gpl_type type = objectSymbol->getGplTypeENUM();
            Game_object* gameObj;

            int index;          // index value of the evaluated expression

            switch(type){       // if it defaults then the LHS is incorrect type
                case GAME_OBJECT:

                        gameObj = (Game_object*)objectSymbol->value_ptr();
                        if(gameObj->get_member_variable_type(*$6,type) == OK){  // check type of member variable, and is it a member variabl?

                            if(!($3->getEvaluatedType() & (ANIMATION_BLOCK | GAME_OBJECT | DOUBLE | STRING))){
                                index = $3->evaluateInteger();
                                $$ = new Variable(*$1, $3, index);
                                $$->setMemberVariableString(*$6);
                                 //cout << *$1 << "[" <<$3->evaluateInteger() << "]" << *$6 << endl;
                            } else {
                                string message = "";
                                message = "A " + gpl_type_to_string($3->getEvaluatedType()) + " expression";
                                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                                                 *$1,
                                                 message);
                                $$ = new Variable(*$1); 
                            }

                        } else {  // you broke it, that is not a member variable of the left T_ID gameobject

                            Error::error(Error::UNDECLARED_MEMBER, *$1, *$6); 
                            symbolTable->insert(INT, *$1 + "." + *$6, 0);   //creating dummy symbol with the same name
                            $$ = new Variable(*$1 + "." + *$6);
                        }

                break;
                default:
                        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1, *$6); 
                        symbolTable->insert(INT, *$1 + "." + *$6, 0);   //creating dummy symbol with the same name
                        $$ = new Variable(*$1 + "." + *$6);
                    break;

            }


        } else if(symbolTable->isInTable(*$1)){
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$ = new Variable(*$1);   // create it anyways.. for error checking
        } else  {
            // not declared
            Error::error(Error::UNDECLARED_VARIABLE, *$1); 
            symbolTable->insert(INT, *$1+"["+toString(0)+"]", 0);   //creating dummy symbol with the same name
            $$ = new Variable(*$1);   // create it anyways.. for error checking

        }
    } 
        ;

//---------------------------------------------------------------------
// NOTE: truested to ensure that the epsression does in fact evlaute to something...
expression:               // operators with 1 or 2 child expressions     (unless its a primary expression)
    primary_expression                  
    { 
        $$ = $1; 
    }
    | expression T_OR expression        
    {
        $$ = new Expression($1,$3, OR);
        if($$->getEvaluatedType() == 0){
            if($1->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(OR));
            } 
            else if($3->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(OR));
            }
            delete $$;
            $$ = new Expression(INT, 0);
            
        }
    } 
    | expression T_AND expression       
    { 
        $$ = new Expression($1,$3, AND); 
        if($$->getEvaluatedType() == 0){
            if($1->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(AND));
            } 
            else if($3->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(AND));
            }
            delete $$;
            $$ = new Expression(INT, 0);
        }
    }
    | expression T_LESS_EQUAL expression { $$ = new Expression($1,$3, LESS_THAN_EQUAL);}
    | expression T_GREATER_EQUAL  expression {$$ = new Expression($1,$3, GREATER_THAN_EQUAL); }
    | expression T_LESS expression      { $$ = new Expression($1,$3, LESS_THAN); }
    | expression T_GREATER  expression  { $$ = new Expression($1,$3, GREATER_THAN);}
    | expression T_EQUAL expression     { $$ = new Expression($1,$3, EQUAL);}
    | expression T_NOT_EQUAL expression { $$ = new Expression($1,$3, NOT_EQUAL);}
    | expression T_PLUS expression      
    { 
        $$ = new Expression($1,$3, PLUS);
        //cout <<  (int)$1->getEvaluatedType() <<    " + " << (int)$3->getEvaluatedType()  << endl;
    }
    | expression T_MINUS expression     
    { 
        
        $$ = new Expression($1,$3, MINUS);
        if($$->getEvaluatedType() == 0){
            if($1->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MINUS));
            } 
            else if($3->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MINUS));
            }
            delete $$;
            $$ = new Expression(INT, 0);

        }
    }
    | expression T_ASTERISK expression  
    { 
        $$ = new Expression($1,$3, MULTIPLY);
        if($$->getEvaluatedType() == 0){
            if($1->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MULTIPLY));
            } 
            else if($3->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MULTIPLY));
            }
            delete $$;
            $$ = new Expression(INT, 0);
        }
    }
    | expression T_DIVIDE expression    
    { 
        $$ = new Expression($1,$3, DIVIDE);
        if($$->getEvaluatedType() == 0){
            if($1->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(DIVIDE));
            } 
            else if($3->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(DIVIDE));
            }
            delete $$;
            $$ = new Expression(INT, 0);
        }
    }
    | expression T_MOD expression       
    { 
        $$ = new Expression($1,$3, MOD);
        if($$->getEvaluatedType() == 0){
            if($1->getEvaluatedType() & (STRING|DOUBLE)){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MOD));
            } 
            else if($3->getEvaluatedType() & (STRING|DOUBLE)){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MOD));
            }
            delete $$;
            $$ = new Expression(INT, 0);
        }

    }
    | T_MINUS  expression %prec UNARY_OP 
    { 
        $$ = new Expression($2, UNARY_MINUS);
        if($$->getEvaluatedType() == 0){
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(UNARY_MINUS));
                delete $$;
                $$ = new Expression(INT, 0);
        }
    }  
    | T_NOT  expression   %prec UNARY_OP
    {  
        $$ = new Expression($2, NOT); 
        if($$->getEvaluatedType() == 0){
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(NOT));
                delete $$;
                $$ = new Expression(INT, 0);
        }
    }
    | math_operator T_LPAREN expression T_RPAREN
     { 
        if($3->getEvaluatedType() & (INT | DOUBLE)){
            $$ = new Expression($3, $1); // correct type to evaluate in future circumstance
        } else {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string($1));
            $$ = new Expression(INT, 0); // moving on, placing a value 0 instead  (no strings allowed)
        }
    }
    | variable geometric_operator variable 
    {
        //if left variable is not a game_object 
        // then: error
        //if right variable is not a game_object 
        // then: error
        if(!($1->getType() & GAME_OBJECT)){
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, $1->getVarName());
            $$ = new Expression(INT, 0);

        }
        else if(!($3->getType() & GAME_OBJECT)){
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, $3->getVarName());
            $$ = new Expression(INT, 0);
        }
        else {
            $$ = new Expression($1, $3, $2); 
        }
        
    }
        ;

//---------------------------------------------------------------------
primary_expression:    //constant terminal node values
    T_LPAREN  expression T_RPAREN   { $$ = $2;}
    | variable                      {  $$ = new Expression($1); }
    | T_INT_CONSTANT                { $$ = new Expression(INT, $1);  }
    | T_TRUE                        { $$ = new Expression(INT, 1); }
    | T_FALSE                       { $$ = new Expression(INT, 0); }
    | T_DOUBLE_CONSTANT             { $$ = new Expression(DOUBLE, $1); }
    | T_STRING_CONSTANT             { $$ = new Expression(STRING, $1); }
        ;

//---------------------------------------------------------------------
geometric_operator:
    T_TOUCHES { $$ = TOUCHES; }
    | T_NEAR { $$ = NEAR; }
        ;

//---------------------------------------------------------------------
math_operator:
    T_SIN { $$ = SIN; }
    | T_COS { $$ = COS; }
    | T_TAN { $$ = TAN;}
    | T_ASIN { $$ = ASIN;}
    | T_ACOS {$$ = ACOS; }
    | T_ATAN { $$ = ATAN;}
    | T_SQRT   { $$ = SQRT;}
    | T_ABS { $$ = ABS; }
    | T_FLOOR { $$ = FLOOR;}
    | T_RANDOM { $$ = RANDOM;}
        ;

//---------------------------------------------------------------------
empty:
    // empty goes to nothing so that you can use empty in productions
    // when you want a production to go to nothing
        ;
