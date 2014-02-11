/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 5 "gpl.y"
  // bison syntax to indicate the start of the header
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



/* Line 268 of yacc.c  */
#line 162 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_FALSE = 258,
     T_TRUE = 259,
     T_INT_CONSTANT = 260,
     T_DOUBLE_CONSTANT = 261,
     T_STRING_CONSTANT = 262,
     T_ID = 263,
     T_PRINT = 264,
     T_EXIT = 265,
     T_INT = 266,
     T_DOUBLE = 267,
     T_STRING = 268,
     T_MINUS = 269,
     T_PLUS = 270,
     T_DIVIDE = 271,
     T_ASTERISK = 272,
     T_MOD = 273,
     T_AND = 274,
     T_OR = 275,
     T_NOT = 276,
     T_EQUAL = 277,
     T_GREATER = 278,
     T_LESS = 279,
     T_RANDOM = 280,
     T_FLOOR = 281,
     T_ABS = 282,
     T_SQRT = 283,
     T_ATAN = 284,
     T_ACOS = 285,
     T_ASIN = 286,
     T_TAN = 287,
     T_COS = 288,
     T_SIN = 289,
     T_NEAR = 290,
     T_TOUCHES = 291,
     T_CONSTANT = 292,
     T_ELSE = 293,
     T_IF = 294,
     T_LKEY = 295,
     T_KKEY = 296,
     T_JKEY = 297,
     T_HKEY = 298,
     T_FKEY = 299,
     T_DKEY = 300,
     T_SKEY = 301,
     T_AKEY = 302,
     T_WKEY = 303,
     T_SPACE = 304,
     T_MOUSE = 305,
     T_RIGHTMOUSE = 306,
     T_MIDDLEMOUSE = 307,
     T_LEFTMOUSE = 308,
     T_DOWNARROW = 309,
     T_UPARROW = 310,
     T_RIGHTARROW = 311,
     T_LEFTARROW = 312,
     T_COMMA = 313,
     T_SEMIC = 314,
     T_FORWARD = 315,
     T_INITIALIZATION = 316,
     T_TRIANGLE = 317,
     T_PIXMAP = 318,
     T_CIRCLE = 319,
     T_RECTANGLE = 320,
     T_TEXTBOX = 321,
     T_ANIMATION = 322,
     T_F1 = 323,
     T_FOR = 324,
     T_ON = 325,
     T_LEFTMOUSE_DOWN = 326,
     T_LEFTMOUSE_UP = 327,
     T_MIDDLEMOUSE_DOWN = 328,
     T_MIDDLEMOUSE_UP = 329,
     T_MOUSE_DRAG = 330,
     T_MOUSE_MOVE = 331,
     T_PERIOD = 332,
     T_RIGHTMOUSE_DOWN = 333,
     T_RIGHTMOUSE_UP = 334,
     T_LESS_EQUAL = 335,
     T_GREATER_EQUAL = 336,
     T_NOT_EQUAL = 337,
     T_PLUS_ASSIGN = 338,
     T_MINUS_ASSIGN = 339,
     T_ASSIGN = 340,
     T_RBRACKET = 341,
     T_LBRACKET = 342,
     T_RBRACE = 343,
     T_LBRACE = 344,
     T_RPAREN = 345,
     T_LPAREN = 346,
     UNARY_OP = 347,
     T_IF_NO_ELSE = 348
   };
#endif
/* Tokens.  */
#define T_FALSE 258
#define T_TRUE 259
#define T_INT_CONSTANT 260
#define T_DOUBLE_CONSTANT 261
#define T_STRING_CONSTANT 262
#define T_ID 263
#define T_PRINT 264
#define T_EXIT 265
#define T_INT 266
#define T_DOUBLE 267
#define T_STRING 268
#define T_MINUS 269
#define T_PLUS 270
#define T_DIVIDE 271
#define T_ASTERISK 272
#define T_MOD 273
#define T_AND 274
#define T_OR 275
#define T_NOT 276
#define T_EQUAL 277
#define T_GREATER 278
#define T_LESS 279
#define T_RANDOM 280
#define T_FLOOR 281
#define T_ABS 282
#define T_SQRT 283
#define T_ATAN 284
#define T_ACOS 285
#define T_ASIN 286
#define T_TAN 287
#define T_COS 288
#define T_SIN 289
#define T_NEAR 290
#define T_TOUCHES 291
#define T_CONSTANT 292
#define T_ELSE 293
#define T_IF 294
#define T_LKEY 295
#define T_KKEY 296
#define T_JKEY 297
#define T_HKEY 298
#define T_FKEY 299
#define T_DKEY 300
#define T_SKEY 301
#define T_AKEY 302
#define T_WKEY 303
#define T_SPACE 304
#define T_MOUSE 305
#define T_RIGHTMOUSE 306
#define T_MIDDLEMOUSE 307
#define T_LEFTMOUSE 308
#define T_DOWNARROW 309
#define T_UPARROW 310
#define T_RIGHTARROW 311
#define T_LEFTARROW 312
#define T_COMMA 313
#define T_SEMIC 314
#define T_FORWARD 315
#define T_INITIALIZATION 316
#define T_TRIANGLE 317
#define T_PIXMAP 318
#define T_CIRCLE 319
#define T_RECTANGLE 320
#define T_TEXTBOX 321
#define T_ANIMATION 322
#define T_F1 323
#define T_FOR 324
#define T_ON 325
#define T_LEFTMOUSE_DOWN 326
#define T_LEFTMOUSE_UP 327
#define T_MIDDLEMOUSE_DOWN 328
#define T_MIDDLEMOUSE_UP 329
#define T_MOUSE_DRAG 330
#define T_MOUSE_MOVE 331
#define T_PERIOD 332
#define T_RIGHTMOUSE_DOWN 333
#define T_RIGHTMOUSE_UP 334
#define T_LESS_EQUAL 335
#define T_GREATER_EQUAL 336
#define T_NOT_EQUAL 337
#define T_PLUS_ASSIGN 338
#define T_MINUS_ASSIGN 339
#define T_ASSIGN 340
#define T_RBRACKET 341
#define T_LBRACKET 342
#define T_RBRACE 343
#define T_LBRACE 344
#define T_RPAREN 345
#define T_LPAREN 346
#define UNARY_OP 347
#define T_IF_NO_ELSE 348




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 100 "gpl.y"

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



/* Line 293 of yacc.c  */
#line 402 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 414 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   478

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNRULES -- Number of states.  */
#define YYNSTATES  229

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   348

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    14,    17,    20,    24,
      30,    32,    34,    36,    39,    41,    42,    49,    55,    57,
      59,    61,    63,    65,    67,    69,    73,    75,    79,    86,
      89,    91,    93,    95,    97,   100,   101,   102,   114,   117,
     120,   123,   126,   129,   132,   136,   138,   140,   142,   144,
     146,   148,   150,   152,   154,   156,   158,   160,   162,   164,
     166,   168,   170,   172,   174,   176,   178,   180,   182,   186,
     188,   194,   195,   196,   199,   201,   203,   205,   208,   211,
     214,   220,   228,   242,   247,   252,   256,   260,   264,   266,
     271,   275,   282,   284,   288,   292,   296,   300,   304,   308,
     312,   316,   320,   324,   328,   332,   336,   339,   342,   347,
     351,   355,   357,   359,   361,   363,   365,   367,   369,   371,
     373,   375,   377,   379,   381,   383,   385,   387,   389,   391
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    96,   108,    -1,    96,    97,    -1,   134,
      -1,    98,    59,    -1,   101,    59,    -1,   107,    59,    -1,
      99,     8,   100,    -1,    99,     8,    87,   130,    86,    -1,
      11,    -1,    12,    -1,    13,    -1,    85,   130,    -1,   134,
      -1,    -1,   103,     8,   102,    91,   104,    90,    -1,   103,
       8,    87,   130,    86,    -1,    62,    -1,    63,    -1,    64,
      -1,    65,    -1,    66,    -1,   105,    -1,   134,    -1,   105,
      58,   106,    -1,   106,    -1,     8,    85,   130,    -1,    60,
      67,     8,    91,   114,    90,    -1,   108,   109,    -1,   134,
      -1,   110,    -1,   111,    -1,   116,    -1,    61,   119,    -1,
      -1,    -1,    67,     8,   112,    91,   115,    90,    89,   113,
     122,    88,   121,    -1,   103,     8,    -1,    62,     8,    -1,
      63,     8,    -1,    64,     8,    -1,    65,     8,    -1,    66,
       8,    -1,    70,   117,   119,    -1,    49,    -1,    57,    -1,
      56,    -1,    55,    -1,    54,    -1,    71,    -1,    73,    -1,
      78,    -1,    72,    -1,    74,    -1,    79,    -1,    76,    -1,
      75,    -1,    68,    -1,    47,    -1,    46,    -1,    45,    -1,
      44,    -1,    43,    -1,    42,    -1,    41,    -1,    40,    -1,
      48,    -1,   120,   123,   121,    -1,   119,    -1,    89,   120,
     122,    88,   121,    -1,    -1,    -1,   122,   123,    -1,   134,
      -1,   124,    -1,   125,    -1,   128,    59,    -1,   126,    59,
      -1,   127,    59,    -1,    39,    91,   130,    90,   118,    -1,
      39,    91,   130,    90,   118,    38,   118,    -1,    69,    91,
     120,   128,   121,    59,   130,    59,   120,   128,   121,    90,
     119,    -1,     9,    91,   130,    90,    -1,    10,    91,   130,
      90,    -1,   129,    85,   130,    -1,   129,    83,   130,    -1,
     129,    84,   130,    -1,     8,    -1,     8,    87,   130,    86,
      -1,     8,    77,     8,    -1,     8,    87,   130,    86,    77,
       8,    -1,   131,    -1,   130,    20,   130,    -1,   130,    19,
     130,    -1,   130,    80,   130,    -1,   130,    81,   130,    -1,
     130,    24,   130,    -1,   130,    23,   130,    -1,   130,    22,
     130,    -1,   130,    82,   130,    -1,   130,    15,   130,    -1,
     130,    14,   130,    -1,   130,    17,   130,    -1,   130,    16,
     130,    -1,   130,    18,   130,    -1,    14,   130,    -1,    21,
     130,    -1,   133,    91,   130,    90,    -1,   129,   132,   129,
      -1,    91,   130,    90,    -1,   129,    -1,     5,    -1,     4,
      -1,     3,    -1,     6,    -1,     7,    -1,    36,    -1,    35,
      -1,    34,    -1,    33,    -1,    32,    -1,    31,    -1,    30,
      -1,    29,    -1,    28,    -1,    27,    -1,    26,    -1,    25,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   342,   342,   356,   357,   361,   362,   363,   367,   426,
     468,   469,   470,   475,   476,   482,   481,   516,   557,   558,
     559,   560,   561,   566,   569,   576,   578,   584,   648,   676,
     677,   682,   683,   684,   689,   698,   709,   697,   762,   804,
     828,   851,   873,   894,   919,   929,   930,   931,   932,   933,
     934,   935,   936,   937,   938,   939,   940,   941,   942,   943,
     944,   945,   946,   947,   948,   949,   950,   951,   956,   962,
     970,   982,   990,   998,  1005,  1010,  1011,  1012,  1013,  1014,
    1019,  1031,  1047,  1084,  1098,  1113,  1139,  1160,  1184,  1199,
    1227,  1279,  1354,  1358,  1373,  1387,  1388,  1389,  1390,  1391,
    1392,  1393,  1398,  1414,  1428,  1442,  1457,  1466,  1475,  1484,
    1508,  1509,  1510,  1511,  1512,  1513,  1514,  1519,  1520,  1525,
    1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1538
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_FALSE", "T_TRUE", "T_INT_CONSTANT",
  "T_DOUBLE_CONSTANT", "T_STRING_CONSTANT", "T_ID", "T_PRINT", "T_EXIT",
  "T_INT", "T_DOUBLE", "T_STRING", "T_MINUS", "T_PLUS", "T_DIVIDE",
  "T_ASTERISK", "T_MOD", "T_AND", "T_OR", "T_NOT", "T_EQUAL", "T_GREATER",
  "T_LESS", "T_RANDOM", "T_FLOOR", "T_ABS", "T_SQRT", "T_ATAN", "T_ACOS",
  "T_ASIN", "T_TAN", "T_COS", "T_SIN", "T_NEAR", "T_TOUCHES", "T_CONSTANT",
  "T_ELSE", "T_IF", "T_LKEY", "T_KKEY", "T_JKEY", "T_HKEY", "T_FKEY",
  "T_DKEY", "T_SKEY", "T_AKEY", "T_WKEY", "T_SPACE", "T_MOUSE",
  "T_RIGHTMOUSE", "T_MIDDLEMOUSE", "T_LEFTMOUSE", "T_DOWNARROW",
  "T_UPARROW", "T_RIGHTARROW", "T_LEFTARROW", "T_COMMA", "T_SEMIC",
  "T_FORWARD", "T_INITIALIZATION", "T_TRIANGLE", "T_PIXMAP", "T_CIRCLE",
  "T_RECTANGLE", "T_TEXTBOX", "T_ANIMATION", "T_F1", "T_FOR", "T_ON",
  "T_LEFTMOUSE_DOWN", "T_LEFTMOUSE_UP", "T_MIDDLEMOUSE_DOWN",
  "T_MIDDLEMOUSE_UP", "T_MOUSE_DRAG", "T_MOUSE_MOVE", "T_PERIOD",
  "T_RIGHTMOUSE_DOWN", "T_RIGHTMOUSE_UP", "T_LESS_EQUAL",
  "T_GREATER_EQUAL", "T_NOT_EQUAL", "T_PLUS_ASSIGN", "T_MINUS_ASSIGN",
  "T_ASSIGN", "T_RBRACKET", "T_LBRACKET", "T_RBRACE", "T_LBRACE",
  "T_RPAREN", "T_LPAREN", "UNARY_OP", "T_IF_NO_ELSE", "$accept", "program",
  "declaration_list", "declaration", "variable_declaration", "simple_type",
  "optional_initializer", "object_declaration", "$@1", "object_type",
  "parameter_list_or_empty", "parameter_list", "parameter",
  "forward_declaration", "block_list", "block", "initialization_block",
  "animation_block", "$@2", "$@3", "animation_parameter",
  "check_animation_parameter", "on_block", "keystroke", "if_block",
  "statement_block", "statement_block_creator", "end_of_statement_block",
  "statement_list", "statement", "if_statement", "for_statement",
  "print_statement", "exit_statement", "assign_statement", "variable",
  "expression", "primary_expression", "geometric_operator",
  "math_operator", "empty", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    96,    96,    97,    97,    97,    98,    98,
      99,    99,    99,   100,   100,   102,   101,   101,   103,   103,
     103,   103,   103,   104,   104,   105,   105,   106,   107,   108,
     108,   109,   109,   109,   110,   112,   113,   111,   114,   115,
     115,   115,   115,   115,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   118,   118,
     119,   120,   121,   122,   122,   123,   123,   123,   123,   123,
     124,   124,   125,   126,   127,   128,   128,   128,   129,   129,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   131,   131,   131,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     2,     2,     2,     3,     5,
       1,     1,     1,     2,     1,     0,     6,     5,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     6,     2,
       1,     1,     1,     1,     2,     0,     0,    11,     2,     2,
       2,     2,     2,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       5,     0,     0,     2,     1,     1,     1,     2,     2,     2,
       5,     7,    13,     4,     4,     3,     3,     3,     1,     4,
       3,     6,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     129,     0,   129,     4,     1,    10,    11,    12,     0,    18,
      19,    20,    21,    22,     3,     0,     0,     0,     0,     0,
       2,    30,     0,     5,   129,     6,    15,     7,     0,     0,
       0,    29,    31,    32,    33,     0,     0,     0,     8,    14,
       0,     0,    71,    34,    35,    66,    65,    64,    63,    62,
      61,    60,    59,    67,    45,    49,    48,    47,    46,    58,
      50,    53,    51,    54,    57,    56,    52,    55,     0,     0,
     114,   113,   112,   115,   116,    88,     0,     0,   128,   127,
     126,   125,   124,   123,   122,   121,   120,   119,     0,   111,
      13,    92,     0,     0,     0,   129,   129,     0,    44,     0,
       0,     0,     0,   106,   107,     0,   118,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    17,     0,     0,    23,    26,    24,
       0,    74,     0,    38,    28,    90,     0,   110,   109,   102,
     101,   104,   103,   105,    94,    93,    99,    98,    97,    95,
      96,   100,     0,     0,    16,     0,     0,     0,     0,     0,
      72,    73,    75,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,   108,    27,    25,     0,     0,
       0,    71,    70,    78,    79,    77,     0,     0,     0,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
      86,    87,    85,    36,    91,    83,    84,    71,    72,   129,
      80,    69,     0,     0,     0,    71,    72,     0,    72,    81,
      68,     0,    37,    71,     0,    72,     0,     0,    82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    15,    16,    38,    17,    41,    18,
     126,   127,   128,    19,    20,    31,    32,    33,    97,   209,
     100,   173,    34,    68,   210,   211,   212,   182,   130,   161,
     162,   163,   164,   165,   166,    89,    90,    91,   108,    92,
     131
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -201
static const yytype_int16 yypact[] =
{
    -201,    50,   372,  -201,  -201,  -201,  -201,  -201,   -63,  -201,
    -201,  -201,  -201,  -201,  -201,    -7,    45,     6,    58,     8,
     -44,  -201,    61,  -201,   -72,  -201,    10,  -201,   -19,    81,
     399,  -201,  -201,  -201,  -201,     0,    30,    30,  -201,  -201,
      30,     1,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,   -19,   -17,
    -201,  -201,  -201,  -201,  -201,   -68,    30,    30,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,    30,    -8,
     338,  -201,     7,   233,   244,    91,  -201,    11,  -201,    93,
      14,    97,    30,  -201,  -201,   112,  -201,  -201,   101,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,  -201,  -201,    22,    20,    53,  -201,  -201,
       2,  -201,    85,  -201,  -201,  -201,   258,  -201,  -201,     4,
       4,  -201,  -201,  -201,   319,   349,    99,   170,   170,   170,
     170,    99,   142,    30,  -201,    91,    21,    29,    33,    46,
    -201,  -201,  -201,  -201,    79,    80,    82,   -53,   134,   135,
     155,   173,   181,    88,   113,  -201,   338,  -201,    30,    30,
      30,  -201,  -201,  -201,  -201,  -201,    30,    30,    30,  -201,
    -201,  -201,  -201,  -201,   102,   187,   153,   189,   222,   101,
     338,   338,   338,  -201,  -201,  -201,  -201,   -19,  -201,  -201,
     158,  -201,    64,   138,    86,   -19,  -201,    30,  -201,  -201,
    -201,   269,  -201,  -201,   101,  -201,   108,   -19,  -201
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,   131,
    -201,  -201,    55,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,   -14,   -28,   -41,  -200,     9,     3,
    -201,  -201,  -201,  -201,  -185,  -106,   -34,  -201,  -201,  -201,
       5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      43,    96,   138,    93,    22,     3,    94,    21,   213,   101,
      75,   156,   157,    36,   208,    37,   220,    28,   222,   102,
     111,   112,   113,    29,   167,   226,    30,   106,   107,    39,
     186,   187,   188,    70,    71,    72,    73,    74,    75,   225,
      98,   158,   103,   104,    76,     9,    10,    11,    12,    13,
       4,    77,    23,    24,   105,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    25,    26,    27,   136,    35,
      42,   159,    75,   156,   157,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,    44,
     160,    69,    95,   167,    75,   156,   157,    40,   122,   125,
     129,   133,   132,   158,   134,   135,   167,   153,   167,    75,
     154,   155,   178,   109,   110,   111,   112,   113,   167,   176,
     179,    88,   117,   118,   180,   158,   109,   110,   111,   112,
     113,   114,   115,   159,   116,   117,   118,   181,   183,   184,
     199,   185,   189,   190,   196,   197,   198,   168,   169,   170,
     171,   172,   200,   201,   202,   159,   109,   110,   111,   112,
     113,   114,   115,   191,   116,   117,   118,   109,   110,   111,
     112,   113,   114,   115,   218,   116,   117,   118,   194,   119,
     120,   192,   224,   221,   109,   110,   111,   112,   113,   193,
     195,   203,   119,   120,   121,   204,   215,   217,   227,   228,
      99,   219,   137,   109,   110,   111,   112,   113,   114,   115,
     177,   116,   117,   118,     0,   216,     0,     0,   214,     0,
       0,     0,   119,   120,   121,     0,     0,     0,     0,     0,
       0,     0,   175,   119,   120,   121,   109,   110,   111,   112,
     113,   114,   115,   205,   116,   117,   118,   109,   110,   111,
     112,   113,   114,   115,     0,   116,   117,   118,   109,   110,
     111,   112,   113,   114,   115,     0,   116,   117,   118,   119,
     120,   121,   109,   110,   111,   112,   113,   114,   115,   206,
     116,   117,   118,   109,   110,   111,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,   119,   120,   121,     0,     0,     0,     0,     0,
       0,     0,   207,   119,   120,   121,     0,     0,     0,   123,
       0,     0,     0,     0,   119,   120,   121,     0,   223,     0,
     124,     0,     0,   109,   110,   111,   112,   113,   119,   120,
     121,   116,   117,   118,   174,     0,     0,     0,     0,   119,
     120,   121,   109,   110,   111,   112,   113,   114,   115,     0,
     116,   117,   118,   109,   110,   111,   112,   113,   114,     0,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
     120,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     0,   119,
     120,   121,     8,     0,     9,    10,    11,    12,    13,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     0,
       0,     0,     0,    55,    56,    57,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,     0,     0,
      60,    61,    62,    63,    64,    65,     0,    66,    67
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-201))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      28,    42,   108,    37,    67,     0,    40,     2,   208,    77,
       8,     9,    10,    85,   199,    87,   216,    61,   218,    87,
      16,    17,    18,    67,   130,   225,    70,    35,    36,    24,
      83,    84,    85,     3,     4,     5,     6,     7,     8,   224,
      68,    39,    76,    77,    14,    62,    63,    64,    65,    66,
       0,    21,    59,     8,    88,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    59,     8,    59,   102,     8,
      89,    69,     8,     9,    10,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,     8,
      88,    91,    91,   199,     8,     9,    10,    87,    91,     8,
      95,     8,    91,    39,    90,     8,   212,    85,   214,     8,
      90,    58,    91,    14,    15,    16,    17,    18,   224,   153,
      91,    91,    23,    24,    91,    39,    14,    15,    16,    17,
      18,    19,    20,    69,    22,    23,    24,    91,    59,    59,
     181,    59,     8,     8,   178,   179,   180,    62,    63,    64,
      65,    66,   186,   187,   188,    69,    14,    15,    16,    17,
      18,    19,    20,     8,    22,    23,    24,    14,    15,    16,
      17,    18,    19,    20,    88,    22,    23,    24,    90,    80,
      81,     8,   223,   217,    14,    15,    16,    17,    18,     8,
      77,    89,    80,    81,    82,     8,    38,    59,    90,   227,
      69,   215,    90,    14,    15,    16,    17,    18,    19,    20,
     155,    22,    23,    24,    -1,   212,    -1,    -1,   209,    -1,
      -1,    -1,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    80,    81,    82,    14,    15,    16,    17,
      18,    19,    20,    90,    22,    23,    24,    14,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,    24,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    24,    80,
      81,    82,    14,    15,    16,    17,    18,    19,    20,    90,
      22,    23,    24,    14,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    80,    81,    82,    -1,    -1,    -1,    86,
      -1,    -1,    -1,    -1,    80,    81,    82,    -1,    59,    -1,
      86,    -1,    -1,    14,    15,    16,    17,    18,    80,    81,
      82,    22,    23,    24,    86,    -1,    -1,    -1,    -1,    80,
      81,    82,    14,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    24,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    82,    60,    -1,    62,    63,    64,    65,    66,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      71,    72,    73,    74,    75,    76,    -1,    78,    79
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,    96,   134,     0,    11,    12,    13,    60,    62,
      63,    64,    65,    66,    97,    98,    99,   101,   103,   107,
     108,   134,    67,    59,     8,    59,     8,    59,    61,    67,
      70,   109,   110,   111,   116,     8,    85,    87,   100,   134,
      87,   102,    89,   119,     8,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    54,    55,    56,    57,    68,
      71,    72,    73,    74,    75,    76,    78,    79,   117,    91,
       3,     4,     5,     6,     7,     8,    14,    21,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    91,   129,
     130,   131,   133,   130,   130,    91,   120,   112,   119,   103,
     114,    77,    87,   130,   130,   130,    35,    36,   132,    14,
      15,    16,    17,    18,    19,    20,    22,    23,    24,    80,
      81,    82,    91,    86,    86,     8,   104,   105,   106,   134,
     122,   134,    91,     8,    90,     8,   130,    90,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,    85,    90,    58,     9,    10,    39,    69,
      88,   123,   124,   125,   126,   127,   128,   129,    62,    63,
      64,    65,    66,   115,    86,    90,   130,   106,    91,    91,
      91,    91,   121,    59,    59,    59,    83,    84,    85,     8,
       8,     8,     8,     8,    90,    77,   130,   130,   130,   120,
     130,   130,   130,    89,     8,    90,    90,    90,   128,   113,
     118,   119,   120,   121,   122,    38,   123,    59,    88,   118,
     121,   130,   121,    59,   120,   128,   121,    90,   119
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 343 "gpl.y"
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
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 356 "gpl.y"
    { }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 357 "gpl.y"
    { }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 361 "gpl.y"
    { }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 362 "gpl.y"
    { }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 363 "gpl.y"
    { }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 367 "gpl.y"
    {  // ideally the initlizater would return a value or NULL
		

         // neither types of T_ID may exist (array or single)
        if(!symbolTable->isInTable(*(yyvsp[(2) - (3)].union_string)) && !symbolTable->isInTable(*(yyvsp[(2) - (3)].union_string)+"[0]")){
            string  str = "";  //temp string with data to be copied over to a symbol
            if((yyvsp[(3) - (3)].union_expression) == 0){  // if the expression is null tehn set default values
                   
                    if((yyvsp[(1) - (3)].union_gpltype) & INT)
                        symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), 0);
                    if((yyvsp[(1) - (3)].union_gpltype) & DOUBLE)
                        symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), 0.0);
                    if((yyvsp[(1) - (3)].union_gpltype) & STRING)
                        symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), &str);
            } else {
               
                // the expression tree is created and now must be evaluated 
                // 
                    Gpl_type expressed_type = (yyvsp[(3) - (3)].union_expression)->getEvaluatedType();

                    //cout << "in bison, evaluated type of expression: " << *$2 << " " ;
                    //cout << (int)expressed_type << endl;

                    //$3->printTree();
                    //cout << endl;
                    //cout << " -------------- " << endl;

                    if((yyvsp[(1) - (3)].union_gpltype) & STRING){
                        if(expressed_type){
                            (yyvsp[(3) - (3)].union_expression)->evaluateString(str);
                        } else {   // its an invalid expression tree .. for reasons forseen by operators
                            str = "";
                        }
                        symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), &str);
                    } else if((yyvsp[(1) - (3)].union_gpltype) & DOUBLE){
                        if((expressed_type & (INT | DOUBLE)) && !(expressed_type & STRING) ){  // correct type
                            symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), (yyvsp[(3) - (3)].union_expression)->evaluateDouble());
                        } else {
                            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *(yyvsp[(2) - (3)].union_string));
                            symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), 0);
                        }

                    } else if((yyvsp[(1) - (3)].union_gpltype) & INT){ // i want to create an integer from the expression
                        if((expressed_type & INT) && !(expressed_type & (DOUBLE | STRING)) ){  
                            symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), (yyvsp[(3) - (3)].union_expression)->evaluateInteger());
                        } else {
                            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *(yyvsp[(2) - (3)].union_string));
                             symbolTable->insert((yyvsp[(1) - (3)].union_gpltype), *(yyvsp[(2) - (3)].union_string), 0);
                        }

                    }



            }
        } else { // duplicate
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[(2) - (3)].union_string));
        }
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 426 "gpl.y"
    { 

			if((yyvsp[(4) - (5)].union_expression)){  // if its a valid expression

				if(!symbolTable->isInTable(*(yyvsp[(2) - (5)].union_string)) && !symbolTable->isInTable(*(yyvsp[(2) - (5)].union_string)+"[0]")){

                    int arraySize = 0;
                    evaluateExpr_AND_setArraySize((yyvsp[(2) - (5)].union_string), (yyvsp[(4) - (5)].union_expression), &arraySize);

					int strLength = strlen((yyvsp[(2) - (5)].union_string)->c_str());// length of variabled so that i can just memcpy it 
                                                        //over to the "REAL" variable name, named variable_name[i]
					char* tmp = (char*) malloc(strLength + 3 + (arraySize/10)+1);     
                          // "some_string[n]"  such that n can be $4/10 + 1 characters long given $4
                          //     is an integer greater than 0
					memcpy(tmp, (void*)(yyvsp[(2) - (5)].union_string)->c_str(), strLength);

                    string str = "";
					for(int i = arraySize-1; i >= 0; i--){
						sprintf(tmp+strLength,"[%d]", i);              
							if((yyvsp[(1) - (5)].union_gpltype) & INT){
								symbolTable->insert((yyvsp[(1) - (5)].union_gpltype), tmp, 0);
                            }
							if((yyvsp[(1) - (5)].union_gpltype) & DOUBLE){
								symbolTable->insert((yyvsp[(1) - (5)].union_gpltype), tmp, 0.0);
                            }
							if((yyvsp[(1) - (5)].union_gpltype) & STRING){
								symbolTable->insert((yyvsp[(1) - (5)].union_gpltype), tmp, &str);
                            }
					}
					free(tmp);
				} else{ // duplicate
					Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[(2) - (5)].union_string));
				}
			} else {
                // actually its an invalid expression..
			//	Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, *$2, );
			}
		}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 468 "gpl.y"
    { (yyval.union_gpltype) = INT; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 469 "gpl.y"
    { (yyval.union_gpltype) = DOUBLE; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 470 "gpl.y"
    { (yyval.union_gpltype) = STRING; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 475 "gpl.y"
    { (yyval.union_expression) = (yyvsp[(2) - (2)].union_expression); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 476 "gpl.y"
    { (yyval.union_expression) = 0; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 482 "gpl.y"
    {                  //need to create new object before parame
        switch((yyvsp[(1) - (2)].union_int)){
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

        if(!symbolTable->insert(GAME_OBJECT, *(yyvsp[(2) - (2)].union_string), tmp_gameObj)){ // inserts a ptr to dynamically created gameobject
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[(2) - (2)].union_string));
            //delete tmp_gameObj;
            //tmp_gameObj = NULL;
        } 

        tmp_gameObj_NAME = *(yyvsp[(2) - (2)].union_string);

    }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 509 "gpl.y"
    { 
        // object_type, symbol_name ( NULL )
        // object_type, symbol_name ( paramlist )
        // BUT ACTUALLY: the parameters are set when the parameters are matched
        // setting teh parameters within the actions of the symbol parameter_list
        // NOW THE PARAMETERS ARE SET
    }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 517 "gpl.y"
    { 
        tmp_gameObj = NULL;

        if(symbolTable->isInTable(*(yyvsp[(2) - (5)].union_string)) || symbolTable->isInTable(*(yyvsp[(2) - (5)].union_string)+"[0]")){
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[(2) - (5)].union_string));
        } else {
            int arraySize = 0;
            evaluateExpr_AND_setArraySize((yyvsp[(2) - (5)].union_string), (yyvsp[(4) - (5)].union_expression), &arraySize);
        
            // now i have the array size..
            for(int i = 0; i < arraySize; i++){
                switch((yyvsp[(1) - (5)].union_int)){
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

                symbolTable->insert(GAME_OBJECT, *(yyvsp[(2) - (5)].union_string) + "[" + toString(i) + "]", tmp_gameObj ); // now it's inserted
            } // end for
            tmp_gameObj = NULL;
        }// end else


    }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 557 "gpl.y"
    {      (yyval.union_int) = T_TRIANGLE; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 558 "gpl.y"
    {         (yyval.union_int) = T_PIXMAP; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 559 "gpl.y"
    {       (yyval.union_int) = T_CIRCLE; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 560 "gpl.y"
    {   (yyval.union_int) = T_RECTANGLE; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 561 "gpl.y"
    {      (yyval.union_int) = T_TEXTBOX;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 567 "gpl.y"
    { 
    }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 570 "gpl.y"
    {
     }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 577 "gpl.y"
    { }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 579 "gpl.y"
    { }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 584 "gpl.y"
    {                   
                string str = "";

                Gpl_type param_type;                         
                if(tmp_gameObj->get_member_variable_type(*(yyvsp[(1) - (3)].union_string), param_type) != OK){
                    Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, tmp_gameObj->type(), *(yyvsp[(1) - (3)].union_string));
                } else {

                    Gpl_type expressed_type = (yyvsp[(3) - (3)].union_expression)->getEvaluatedType();

                    if(param_type & ANIMATION_BLOCK){
                        if( expressed_type & ANIMATION_BLOCK ){  


                            // need to only set the animation block parameter if teh animation block that i am setting
                            // has a parameter that is of the same type of that as the object that needs to
                            // use the animation block..
                            // 
                            //  if the animationblock has a parameter Gameobject whos type is the same as tmp_gameObj->type
                            Symbol* anim_param_symbol = ((Animation_block*)(symbolTable->find((yyvsp[(3) - (3)].union_expression)->getNameOfVariable()))->value_ptr())->get_parameter_symbol();
                            if((anim_param_symbol->getGplTypeENUM() & GAME_OBJECT) &&
                                 (((Game_object*)anim_param_symbol->value_ptr())->type() == (tmp_gameObj->type())) ) 
                            {
                                tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), (Animation_block*)(symbolTable->find((yyvsp[(3) - (3)].union_expression)->getNameOfVariable()))->value_ptr() );
                            } else {
                                Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, tmp_gameObj_NAME, (yyvsp[(3) - (3)].union_expression)->getNameOfVariable());
                            }
                        } else {
                            Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, *(yyvsp[(1) - (3)].union_string));
                             tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), 0);
                        } 
                    } else if(param_type & STRING){
                        if(expressed_type){
                            (yyvsp[(3) - (3)].union_expression)->evaluateString(str);
                        } else {   
                            str = "";
                        }
                        tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), str);
                    } else if(param_type & DOUBLE){
                        if((expressed_type & (INT | DOUBLE)) && !(expressed_type & STRING) ){  // correct type
                            tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), (yyvsp[(3) - (3)].union_expression)->evaluateDouble());
                        } else {
                            Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, tmp_gameObj_NAME, *(yyvsp[(1) - (3)].union_string));
                            tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), 0.0);
                        }

                    } else if(param_type & INT){ // i want to create an integer from the expression
                        if((expressed_type & INT) && !(expressed_type & (DOUBLE | STRING)) ){  
                            tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), (yyvsp[(3) - (3)].union_expression)->evaluateInteger());
                        } else {
                            Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, tmp_gameObj_NAME, *(yyvsp[(1) - (3)].union_string));
                             tmp_gameObj->set_member_variable(*(yyvsp[(1) - (3)].union_string), 0);
                        }
                    } else {
                        /// reduntant
                        Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, tmp_gameObj->type(), *(yyvsp[(1) - (3)].union_string));
                    }
                }//  end check for known object parameter


    }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 649 "gpl.y"
    { 
        // insert the *$3 and *$5 into the symbol table
        
        // ASSERT THAT tmp_gameObj_NAME HAS BEEN SET (this is the name of the object within the paraens of the anim block
        //  ASSERT THAT tmp_gameObj_NAME was already inserted into symbol table
        // so lets check to see if any of the names we use have been declared before..
        string animation_block_name = *(yyvsp[(3) - (6)].union_string);

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
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 676 "gpl.y"
    { }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 677 "gpl.y"
    { }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 682 "gpl.y"
    { }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 683 "gpl.y"
    { }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 684 "gpl.y"
    { }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 690 "gpl.y"
    {
        Event_manager::instance()->push_statement_block(Window::INITIALIZE, (yyvsp[(2) - (2)].union_statementblock)); 
    }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 698 "gpl.y"
    { // 
        Symbol* anim_block_symbol = symbolTable->find(*(yyvsp[(2) - (2)].union_string));
        if(!anim_block_symbol){
         // the animation block does not exist
            Error::error(Error::NO_FORWARD_FOR_ANIMATION_BLOCK, *(yyvsp[(2) - (2)].union_string));
        } 
        else if(((Animation_block*)anim_block_symbol->value_ptr())->isBodyDeclared() == true){
            Error::error(Error::PREVIOUSLY_DEFINED_ANIMATION_BLOCK, *(yyvsp[(2) - (2)].union_string));
        }
    }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 709 "gpl.y"
    { 
        Symbol* anim_block_symbol = symbolTable->find(*(yyvsp[(2) - (7)].union_string));
        if(anim_block_symbol){

            if(((Animation_block*)anim_block_symbol->value_ptr())->isBodyDeclared() == true){
                // this case is handled before the left curly brace (but after the T_ID is matched
            } else if(anim_block_symbol->getGplTypeENUM() & ANIMATION_BLOCK){

                /* pushed the animation block on the stack */
                /* check to see if this param has the same name as param in forward*/
                Symbol* param_symbol = ((Animation_block*)anim_block_symbol->value_ptr())->get_parameter_symbol();
                if(*(yyvsp[(5) - (7)].union_string) == param_symbol->getName()){
                    // then if the types match then push else error( anim param does not match forward
                    // (this check is done in the check_animation_parameter production)

                    statement_block_stack.push((Animation_block*)anim_block_symbol->value_ptr());


                } else { // this anim_block body's current paramter doesnt match the name of the forward declaration
                    Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD); 
                }

                /* now the statements will be matched and placed into the animation_block */

            } else { // then the animation block name has already been declared as a variable with a different type
                // NOTE: error is probably incorrect, 
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[(2) - (7)].union_string));
            }
            
        } 

    }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 742 "gpl.y"
    { // assuming: statement_list list of statements was pushed into the vector of statements for the animation block //
    
         //  the symbol that owns this animation block has a member variable that points to this animation block
         //  so i can pop the ptr without worrying about where it goes or where to put it



        Symbol* anim_block_symbol = symbolTable->find(*(yyvsp[(2) - (11)].union_string));
        if(anim_block_symbol){
            ((Animation_block*)anim_block_symbol->value_ptr())->bodyHasBeenDeclared(true);
            statement_block_stack.pop();
         } // else the animation forward declaration has NOT been declared..



    }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 763 "gpl.y"
    { 
        if(!symbolTable->find(*(yyvsp[(2) - (2)].union_string))){
                switch((yyvsp[(1) - (2)].union_int)){
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

            tmp_gameObj_NAME = *(yyvsp[(2) - (2)].union_string);

            tmp_gameObj->never_animate();
            tmp_gameObj->never_draw();

            symbolTable->insert(GAME_OBJECT, tmp_gameObj_NAME, tmp_gameObj);
        
        } else {
            Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *(yyvsp[(2) - (2)].union_string));
        }


        tmp_gameObj = NULL;
    }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 805 "gpl.y"
    { 
        Symbol* object_symbol = symbolTable->find(*(yyvsp[(2) - (2)].union_string));
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

        (yyval.union_string) = (yyvsp[(2) - (2)].union_string);
    }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 829 "gpl.y"
    { 
        Symbol* object_symbol = symbolTable->find(*(yyvsp[(2) - (2)].union_string));
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
        (yyval.union_string) = (yyvsp[(2) - (2)].union_string);
    }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 852 "gpl.y"
    { 
        Symbol* object_symbol = symbolTable->find(*(yyvsp[(2) - (2)].union_string));
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
        (yyval.union_string) = (yyvsp[(2) - (2)].union_string);
    }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 874 "gpl.y"
    { 
        Symbol* object_symbol = symbolTable->find(*(yyvsp[(2) - (2)].union_string));
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
        (yyval.union_string) = (yyvsp[(2) - (2)].union_string);
    }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 895 "gpl.y"
    {
        Symbol* object_symbol = symbolTable->find(*(yyvsp[(2) - (2)].union_string));
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
        (yyval.union_string) = (yyvsp[(2) - (2)].union_string);
    }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 920 "gpl.y"
    { 

        Event_manager::instance()->push_statement_block((yyvsp[(2) - (3)].union_keystroke), (yyvsp[(3) - (3)].union_statementblock));

    }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 929 "gpl.y"
    { (yyval.union_keystroke) = Window::SPACE; }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 930 "gpl.y"
    {(yyval.union_keystroke) = Window::LEFTARROW; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 931 "gpl.y"
    {(yyval.union_keystroke) = Window::RIGHTARROW; }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 932 "gpl.y"
    {(yyval.union_keystroke) = Window::UPARROW; }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 933 "gpl.y"
    {(yyval.union_keystroke) = Window::DOWNARROW; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 934 "gpl.y"
    {(yyval.union_keystroke) = Window::LEFTMOUSE_DOWN; }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 935 "gpl.y"
    {(yyval.union_keystroke) = Window::MIDDLEMOUSE_DOWN; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 936 "gpl.y"
    {(yyval.union_keystroke) = Window::RIGHTMOUSE_DOWN; }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 937 "gpl.y"
    {(yyval.union_keystroke) = Window::LEFTMOUSE_UP; }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 938 "gpl.y"
    {(yyval.union_keystroke) = Window::MIDDLEMOUSE_UP; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 939 "gpl.y"
    {(yyval.union_keystroke) = Window::RIGHTMOUSE_UP; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 940 "gpl.y"
    {(yyval.union_keystroke) = Window::MOUSE_MOVE; }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 941 "gpl.y"
    { (yyval.union_keystroke) = Window::MOUSE_DRAG;}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 942 "gpl.y"
    {(yyval.union_keystroke) = Window::F1; }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 943 "gpl.y"
    {(yyval.union_keystroke) = Window::AKEY; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 944 "gpl.y"
    {(yyval.union_keystroke) = Window::SKEY; }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 945 "gpl.y"
    {(yyval.union_keystroke) = Window::DKEY; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 946 "gpl.y"
    {(yyval.union_keystroke) = Window::FKEY; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 947 "gpl.y"
    {(yyval.union_keystroke) = Window::HKEY; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 948 "gpl.y"
    {(yyval.union_keystroke) = Window::JKEY; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 949 "gpl.y"
    {(yyval.union_keystroke) = Window::KKEY; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 950 "gpl.y"
    {(yyval.union_keystroke) = Window::LKEY; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 951 "gpl.y"
    {(yyval.union_keystroke) = Window::WKEY; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 957 "gpl.y"
    { 
        (yyval.union_statementblock) = statement_block_stack.top();
        (yyval.union_statementblock)->push_statement((yyvsp[(2) - (3)].union_statement));
        statement_block_stack.pop();
    }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 963 "gpl.y"
    { 
        (yyval.union_statementblock) = (yyvsp[(1) - (1)].union_statementblock);
    }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 973 "gpl.y"
    {

        (yyval.union_statementblock) = statement_block_stack.top();
        statement_block_stack.pop();
    }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 982 "gpl.y"
    {
    statement_block_stack.push(new Statement_block(42));
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 990 "gpl.y"
    {
   
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 999 "gpl.y"
    {
        // Left recursive grammer, but this evaluates left to right.. (left bottom to right top)
        //global_statement_list_vector.push_back($2);
        statement_block_stack.top()->push_statement((yyvsp[(2) - (2)].union_statement));
        //cout << ($2)->get_line_number()<< endl;
    }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1005 "gpl.y"
    { }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1010 "gpl.y"
    { (yyval.union_statement) = (yyvsp[(1) - (1)].union_statement); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1011 "gpl.y"
    { (yyval.union_statement) = (yyvsp[(1) - (1)].union_statement);  }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1012 "gpl.y"
    { (yyval.union_statement) = (yyvsp[(1) - (2)].union_statement);  }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1013 "gpl.y"
    { (yyval.union_statement) = (yyvsp[(1) - (2)].union_statement); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1014 "gpl.y"
    {  (yyval.union_statement) = (yyvsp[(1) - (2)].union_statement); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1022 "gpl.y"
    {
        Gpl_type eval_type = (Gpl_type) (yyvsp[(3) - (5)].union_expression)->getEvaluatedType();
        if(!(eval_type & (GAME_OBJECT | ANIMATION_BLOCK | DOUBLE | STRING))){
            (yyval.union_statement) = new If_statement(eval_type, (yyvsp[(3) - (5)].union_expression), (yyvsp[(5) - (5)].union_statementblock));
        } else { //error... invalid expression used for "if" conditional
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
             (yyval.union_statement) = NULL;
        }
    }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1034 "gpl.y"
    { 
        Gpl_type eval_type = (Gpl_type) (yyvsp[(3) - (7)].union_expression)->getEvaluatedType();
        if(!(eval_type & (GAME_OBJECT | ANIMATION_BLOCK | DOUBLE | STRING))){
             (yyval.union_statement) = new If_statement(eval_type, (yyvsp[(3) - (7)].union_expression), (yyvsp[(5) - (7)].union_statementblock), (yyvsp[(7) - (7)].union_statementblock));
        } else { //error... invalid expression used for "if" conditional
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
             (yyval.union_statement) = NULL;
        }
      }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1054 "gpl.y"
    { 
        // push the assignment statement onto the new statement block (initializer statement block)
        // push the other  assignment statement onto... etc       (each should only hold one block)
        // create the for_statement  (initlaizer_statement_block, expression, assignment_statement, for_statement_block)

        if(!((yyvsp[(7) - (13)].union_expression)->getEvaluatedType() & (DOUBLE | STRING | GAME_OBJECT | ANIMATION_BLOCK))){
            Statement_block* right_assign_statement_block =  statement_block_stack.top();
             statement_block_stack.pop();
            Statement_block* left_initalizer_assign_statement_block =  statement_block_stack.top();
             statement_block_stack.pop();

            left_initalizer_assign_statement_block->push_statement((yyvsp[(4) - (13)].union_statement));
            right_assign_statement_block->push_statement((yyvsp[(10) - (13)].union_statement));      

            (yyval.union_statement) = new For_statement(left_initalizer_assign_statement_block, (yyvsp[(7) - (13)].union_expression), right_assign_statement_block, (yyvsp[(13) - (13)].union_statementblock));
        } else {
            //error , expression is of invalid type.. cannot check for a condition on that matter
            Error::error(Error::INVALID_TYPE_FOR_FOR_STMT_EXPRESSION);
            (yyval.union_statement) = new For_statement(0, 0, 0, (yyvsp[(13) - (13)].union_statementblock));
            //$$ = NULL;
        }

        //return; 

    }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1084 "gpl.y"
    {
        if((yyvsp[(3) - (4)].union_expression)->getEvaluatedType() & (STRING | DOUBLE | INT)) {
            (yyval.union_statement) = new Print_statement((yyvsp[(1) - (4)].union_int), (yyvsp[(3) - (4)].union_expression)); 
        } else {
            // error, incorrect type passed to function "print"
            Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
             (yyval.union_statement) = NULL;
        }
    }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1099 "gpl.y"
    {
        Gpl_type eval_type = (yyvsp[(3) - (4)].union_expression)->getEvaluatedType();
        if((eval_type & INT) && !(eval_type & (DOUBLE | STRING))) {
            (yyval.union_statement) = new Exit_statement((yyvsp[(1) - (4)].union_int), (yyvsp[(3) - (4)].union_expression)); 
        } else {
            // error, incorrect type passed to function "print"
            Error::error(Error::EXIT_STATUS_MUST_BE_AN_INTEGER, gpl_type_to_string(eval_type));
            (yyval.union_statement) = NULL;
        }
     }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1114 "gpl.y"
    {   
        // assert that he variable does exist since it was matched
        // check to see if the variable CAN be assigned the value that expression evaluates to 
        // is the left type a bit position greater than or equal to the right type
        Gpl_type var_type = (yyvsp[(1) - (3)].union_variable)->getType();
        Gpl_type expr_type = (yyvsp[(3) - (3)].union_expression)->getEvaluatedType();

        if(left_type_greater_or_equal_bit_position_compared_to_right_type(var_type, expr_type)){
              // then: change the value in the symbol table at variable->get_symbol() to expression

            if(var_type & (INT | DOUBLE | STRING | ANIMATION_BLOCK)){
                (yyval.union_statement) =  new Assign_statement((yyvsp[(1) - (3)].union_variable), 0, (yyvsp[(3) - (3)].union_expression));
            } else {
                Error::error(Error::INVALID_LHS_OF_ASSIGNMENT, (yyvsp[(1) - (3)].union_variable)->getVarName(), gpl_type_to_string(var_type));
                (yyval.union_statement) =  NULL;
            }

        } else {
            //error.. cannot assign expression of type.. to variable of type...
           Error::error(Error::ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(var_type), gpl_type_to_string(highest_bit(expr_type)));
           (yyval.union_statement) =  NULL;
        }
      

    }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1140 "gpl.y"
    { 
        Gpl_type var_type = (yyvsp[(1) - (3)].union_variable)->getType();
        Gpl_type expr_type = (yyvsp[(3) - (3)].union_expression)->getEvaluatedType();
        if(left_type_greater_or_equal_bit_position_compared_to_right_type(var_type, expr_type)){
              // then: change the value in the symbol table at variable->get_symbol() to expression
            if(var_type & (INT | DOUBLE | STRING)){
                (yyval.union_statement) =  new Assign_statement((yyvsp[(1) - (3)].union_variable), 1, (yyvsp[(3) - (3)].union_expression));
            } else {
                Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT, (yyvsp[(1) - (3)].union_variable)->getVarName(), gpl_type_to_string(var_type));
                (yyval.union_statement) =  NULL;
            }
            
        } else {
            //error.. cannot assign expression of type.. to variable of type...
            Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(var_type), gpl_type_to_string(highest_bit(expr_type)));
            (yyval.union_statement) =  NULL;

        }
      
    }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1161 "gpl.y"
    { 
        Gpl_type var_type = (yyvsp[(1) - (3)].union_variable)->getType();
        Gpl_type expr_type = (yyvsp[(3) - (3)].union_expression)->getEvaluatedType();
        if(left_type_greater_or_equal_bit_position_compared_to_right_type(var_type, expr_type)){
              // then: change the value in the symbol table at variable->get_symbol() to expression
            if(var_type & (INT | DOUBLE)){
                (yyval.union_statement) =  new Assign_statement((yyvsp[(1) - (3)].union_variable), 2, (yyvsp[(3) - (3)].union_expression));
            } else {
                Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT, (yyvsp[(1) - (3)].union_variable)->getVarName(), gpl_type_to_string(var_type));
                (yyval.union_statement) =  NULL;
            }
            
        } else {
            //error.. cannot assign expression of type.. to variable of type...
            Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR, gpl_type_to_string(var_type), gpl_type_to_string(highest_bit(expr_type)));
            (yyval.union_statement) =  NULL;
        }
      
    }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1185 "gpl.y"
    {   
        if(symbolTable->isInTable(*(yyvsp[(1) - (1)].union_string))){
            (yyval.union_variable) = new Variable(*(yyvsp[(1) - (1)].union_string)); 
            //cout << endl;
            //cout << "using variable with name: " << *$1 <<  endl;
            //cout << endl;
        }
        else{
            Error::error(Error::UNDECLARED_VARIABLE, (*(yyvsp[(1) - (1)].union_string))); 
            symbolTable->insert(INT, *(yyvsp[(1) - (1)].union_string), 0);   //creating dummy symbol with the same name
            (yyval.union_variable) = new Variable(*(yyvsp[(1) - (1)].union_string));   // create it anyways.. for error checking

        }
    }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1200 "gpl.y"
    { 
        string variable_name = *(yyvsp[(1) - (4)].union_string); 
        Gpl_type expr_type = (yyvsp[(3) - (4)].union_expression)->getEvaluatedType();


        if(symbolTable->isInTable(variable_name)){
            // not an array
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, variable_name);
            (yyval.union_variable) = new Variable(variable_name, 0, 0); 
        } else {
            if(!(expr_type & (ANIMATION_BLOCK | GAME_OBJECT | DOUBLE | STRING))){
                int arrayIndex = (yyvsp[(3) - (4)].union_expression)->evaluateInteger();
                string variable = variable_name + "[" + toString(0) + "]";
                if(symbolTable->isInTable(variable)){
                    (yyval.union_variable) = new Variable(variable_name, (yyvsp[(3) - (4)].union_expression), arrayIndex); 
                }
            } else {
                string message = "";
                message = "A " + gpl_type_to_string(expr_type) + " expression";
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                                 variable_name,
                                 message);
                symbolTable->insert(INT, *(yyvsp[(1) - (4)].union_string)+"["+toString(0)+"]", 0);   //creating dummy symbol with the same name
                (yyval.union_variable) = new Variable(variable_name, (yyvsp[(3) - (4)].union_expression) , 0); 
            }
        }
    }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1228 "gpl.y"
    { // if the T_ID exists in the symbol table then its a valid variable..
        Symbol* objectSymbol;
        objectSymbol = symbolTable->find(*(yyvsp[(1) - (3)].union_string));
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
                    if(gameObj->get_member_variable_type(*(yyvsp[(3) - (3)].union_string),type) == OK){  // check type of member variable, and is it a member variabl?
                        // now what? its a member variable.. and i know its type..
                        // usualy variables are used in expressions .. so an expression is going to evaluate this..
                        // IDEA: imma createa a new variable named *$1 and store within it a member string *$3
                        (yyval.union_variable) = new Variable(*(yyvsp[(1) - (3)].union_string));
                        (yyval.union_variable)->setMemberVariableString(*(yyvsp[(3) - (3)].union_string));

                    } else {  // you broke it, that is not a member variable of the left T_ID gameobject

                        Error::error(Error::UNDECLARED_MEMBER, *(yyvsp[(1) - (3)].union_string), *(yyvsp[(3) - (3)].union_string)); 
                        symbolTable->insert(INT, *(yyvsp[(1) - (3)].union_string) + "." + *(yyvsp[(3) - (3)].union_string), 0);  // the dummy symbol has to be something different else variable getValue gets the value fromobject.. bad value since its an object:
                        (yyval.union_variable) = new Variable(*(yyvsp[(1) - (3)].union_string) + "." + *(yyvsp[(3) - (3)].union_string));
                    }
                break;
                default:
                        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *(yyvsp[(1) - (3)].union_string), *(yyvsp[(3) - (3)].union_string)); 
                        symbolTable->insert(INT, *(yyvsp[(1) - (3)].union_string) + "." + *(yyvsp[(3) - (3)].union_string), 0);   
                        (yyval.union_variable) = new Variable(*(yyvsp[(1) - (3)].union_string) + "." + *(yyvsp[(3) - (3)].union_string));
                break;

            }


        } else {
            // not declared
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[(1) - (3)].union_string)); 
            symbolTable->insert(INT, *(yyvsp[(1) - (3)].union_string), 0);   //creating dummy symbol with the same name
            (yyval.union_variable) = new Variable(*(yyvsp[(1) - (3)].union_string));   // create it anyways.. for error checking

        }




    }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1280 "gpl.y"
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
        objectSymbol = symbolTable->find(*(yyvsp[(1) - (6)].union_string) + "[" + toString(0) + "]");
        if(objectSymbol){

            Gpl_type type = objectSymbol->getGplTypeENUM();
            Game_object* gameObj;

            int index;          // index value of the evaluated expression

            switch(type){       // if it defaults then the LHS is incorrect type
                case GAME_OBJECT:

                        gameObj = (Game_object*)objectSymbol->value_ptr();
                        if(gameObj->get_member_variable_type(*(yyvsp[(6) - (6)].union_string),type) == OK){  // check type of member variable, and is it a member variabl?

                            if(!((yyvsp[(3) - (6)].union_expression)->getEvaluatedType() & (ANIMATION_BLOCK | GAME_OBJECT | DOUBLE | STRING))){
                                index = (yyvsp[(3) - (6)].union_expression)->evaluateInteger();
                                (yyval.union_variable) = new Variable(*(yyvsp[(1) - (6)].union_string), (yyvsp[(3) - (6)].union_expression), index);
                                (yyval.union_variable)->setMemberVariableString(*(yyvsp[(6) - (6)].union_string));
                                 //cout << *$1 << "[" <<$3->evaluateInteger() << "]" << *$6 << endl;
                            } else {
                                string message = "";
                                message = "A " + gpl_type_to_string((yyvsp[(3) - (6)].union_expression)->getEvaluatedType()) + " expression";
                                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                                                 *(yyvsp[(1) - (6)].union_string),
                                                 message);
                                (yyval.union_variable) = new Variable(*(yyvsp[(1) - (6)].union_string)); 
                            }

                        } else {  // you broke it, that is not a member variable of the left T_ID gameobject

                            Error::error(Error::UNDECLARED_MEMBER, *(yyvsp[(1) - (6)].union_string), *(yyvsp[(6) - (6)].union_string)); 
                            symbolTable->insert(INT, *(yyvsp[(1) - (6)].union_string) + "." + *(yyvsp[(6) - (6)].union_string), 0);   //creating dummy symbol with the same name
                            (yyval.union_variable) = new Variable(*(yyvsp[(1) - (6)].union_string) + "." + *(yyvsp[(6) - (6)].union_string));
                        }

                break;
                default:
                        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *(yyvsp[(1) - (6)].union_string), *(yyvsp[(6) - (6)].union_string)); 
                        symbolTable->insert(INT, *(yyvsp[(1) - (6)].union_string) + "." + *(yyvsp[(6) - (6)].union_string), 0);   //creating dummy symbol with the same name
                        (yyval.union_variable) = new Variable(*(yyvsp[(1) - (6)].union_string) + "." + *(yyvsp[(6) - (6)].union_string));
                    break;

            }


        } else if(symbolTable->isInTable(*(yyvsp[(1) - (6)].union_string))){
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *(yyvsp[(1) - (6)].union_string));
            (yyval.union_variable) = new Variable(*(yyvsp[(1) - (6)].union_string));   // create it anyways.. for error checking
        } else  {
            // not declared
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[(1) - (6)].union_string)); 
            symbolTable->insert(INT, *(yyvsp[(1) - (6)].union_string)+"["+toString(0)+"]", 0);   //creating dummy symbol with the same name
            (yyval.union_variable) = new Variable(*(yyvsp[(1) - (6)].union_string));   // create it anyways.. for error checking

        }
    }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1355 "gpl.y"
    { 
        (yyval.union_expression) = (yyvsp[(1) - (1)].union_expression); 
    }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1359 "gpl.y"
    {
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), OR);
        if((yyval.union_expression)->getEvaluatedType() == 0){
            if((yyvsp[(1) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(OR));
            } 
            else if((yyvsp[(3) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(OR));
            }
            delete (yyval.union_expression);
            (yyval.union_expression) = new Expression(INT, 0);
            
        }
    }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1374 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), AND); 
        if((yyval.union_expression)->getEvaluatedType() == 0){
            if((yyvsp[(1) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(AND));
            } 
            else if((yyvsp[(3) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(AND));
            }
            delete (yyval.union_expression);
            (yyval.union_expression) = new Expression(INT, 0);
        }
    }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1387 "gpl.y"
    { (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), LESS_THAN_EQUAL);}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1388 "gpl.y"
    {(yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), GREATER_THAN_EQUAL); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1389 "gpl.y"
    { (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), LESS_THAN); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1390 "gpl.y"
    { (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), GREATER_THAN);}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1391 "gpl.y"
    { (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), EQUAL);}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1392 "gpl.y"
    { (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), NOT_EQUAL);}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1394 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), PLUS);
        //cout <<  (int)$1->getEvaluatedType() <<    " + " << (int)$3->getEvaluatedType()  << endl;
    }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1399 "gpl.y"
    { 
        
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), MINUS);
        if((yyval.union_expression)->getEvaluatedType() == 0){
            if((yyvsp[(1) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MINUS));
            } 
            else if((yyvsp[(3) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MINUS));
            }
            delete (yyval.union_expression);
            (yyval.union_expression) = new Expression(INT, 0);

        }
    }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1415 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), MULTIPLY);
        if((yyval.union_expression)->getEvaluatedType() == 0){
            if((yyvsp[(1) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MULTIPLY));
            } 
            else if((yyvsp[(3) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MULTIPLY));
            }
            delete (yyval.union_expression);
            (yyval.union_expression) = new Expression(INT, 0);
        }
    }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1429 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), DIVIDE);
        if((yyval.union_expression)->getEvaluatedType() == 0){
            if((yyvsp[(1) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(DIVIDE));
            } 
            else if((yyvsp[(3) - (3)].union_expression)->getEvaluatedType() & STRING){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(DIVIDE));
            }
            delete (yyval.union_expression);
            (yyval.union_expression) = new Expression(INT, 0);
        }
    }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1443 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_expression),(yyvsp[(3) - (3)].union_expression), MOD);
        if((yyval.union_expression)->getEvaluatedType() == 0){
            if((yyvsp[(1) - (3)].union_expression)->getEvaluatedType() & (STRING|DOUBLE)){
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(MOD));
            } 
            else if((yyvsp[(3) - (3)].union_expression)->getEvaluatedType() & (STRING|DOUBLE)){
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(MOD));
            }
            delete (yyval.union_expression);
            (yyval.union_expression) = new Expression(INT, 0);
        }

    }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1458 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[(2) - (2)].union_expression), UNARY_MINUS);
        if((yyval.union_expression)->getEvaluatedType() == 0){
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(UNARY_MINUS));
                delete (yyval.union_expression);
                (yyval.union_expression) = new Expression(INT, 0);
        }
    }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1467 "gpl.y"
    {  
        (yyval.union_expression) = new Expression((yyvsp[(2) - (2)].union_expression), NOT); 
        if((yyval.union_expression)->getEvaluatedType() == 0){
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(NOT));
                delete (yyval.union_expression);
                (yyval.union_expression) = new Expression(INT, 0);
        }
    }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1476 "gpl.y"
    { 
        if((yyvsp[(3) - (4)].union_expression)->getEvaluatedType() & (INT | DOUBLE)){
            (yyval.union_expression) = new Expression((yyvsp[(3) - (4)].union_expression), (yyvsp[(1) - (4)].union_gploperator)); // correct type to evaluate in future circumstance
        } else {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string((yyvsp[(1) - (4)].union_gploperator)));
            (yyval.union_expression) = new Expression(INT, 0); // moving on, placing a value 0 instead  (no strings allowed)
        }
    }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1485 "gpl.y"
    {
        //if left variable is not a game_object 
        // then: error
        //if right variable is not a game_object 
        // then: error
        if(!((yyvsp[(1) - (3)].union_variable)->getType() & GAME_OBJECT)){
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, (yyvsp[(1) - (3)].union_variable)->getVarName());
            (yyval.union_expression) = new Expression(INT, 0);

        }
        else if(!((yyvsp[(3) - (3)].union_variable)->getType() & GAME_OBJECT)){
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, (yyvsp[(3) - (3)].union_variable)->getVarName());
            (yyval.union_expression) = new Expression(INT, 0);
        }
        else {
            (yyval.union_expression) = new Expression((yyvsp[(1) - (3)].union_variable), (yyvsp[(3) - (3)].union_variable), (yyvsp[(2) - (3)].union_gploperator)); 
        }
        
    }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1508 "gpl.y"
    { (yyval.union_expression) = (yyvsp[(2) - (3)].union_expression);}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1509 "gpl.y"
    {  (yyval.union_expression) = new Expression((yyvsp[(1) - (1)].union_variable)); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1510 "gpl.y"
    { (yyval.union_expression) = new Expression(INT, (yyvsp[(1) - (1)].union_int));  }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1511 "gpl.y"
    { (yyval.union_expression) = new Expression(INT, 1); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1512 "gpl.y"
    { (yyval.union_expression) = new Expression(INT, 0); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1513 "gpl.y"
    { (yyval.union_expression) = new Expression(DOUBLE, (yyvsp[(1) - (1)].union_double)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1514 "gpl.y"
    { (yyval.union_expression) = new Expression(STRING, (yyvsp[(1) - (1)].union_string)); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1519 "gpl.y"
    { (yyval.union_gploperator) = TOUCHES; }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1520 "gpl.y"
    { (yyval.union_gploperator) = NEAR; }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1525 "gpl.y"
    { (yyval.union_gploperator) = SIN; }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1526 "gpl.y"
    { (yyval.union_gploperator) = COS; }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1527 "gpl.y"
    { (yyval.union_gploperator) = TAN;}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1528 "gpl.y"
    { (yyval.union_gploperator) = ASIN;}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1529 "gpl.y"
    {(yyval.union_gploperator) = ACOS; }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1530 "gpl.y"
    { (yyval.union_gploperator) = ATAN;}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1531 "gpl.y"
    { (yyval.union_gploperator) = SQRT;}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1532 "gpl.y"
    { (yyval.union_gploperator) = ABS; }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1533 "gpl.y"
    { (yyval.union_gploperator) = FLOOR;}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1534 "gpl.y"
    { (yyval.union_gploperator) = RANDOM;}
    break;



/* Line 1806 of yacc.c  */
#line 3680 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



