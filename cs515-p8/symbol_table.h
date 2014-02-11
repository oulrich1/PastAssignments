
// DECLARATIONS OF BOTH:

// SYMBOL TABLE

// and

// SYMBOL

#include "globals.h"

using namespace std;

#ifndef ___SYMBOLTABLE
#define ___SYMBOLTABLE
class Symbol;

class Symbol_table{
  public:
	 static Symbol_table* instance();
		int					print(ostream &out);
		
		//inserts the TYPE T, variable_name key, and the value into the table
		// interface functions
		int insert(Gpl_type T, const string &key, int value);
		int insert(Gpl_type T, const string &key, double value);
		int insert(Gpl_type T, const string &key, string *value);
		int insert(Gpl_type T, const string &key, Game_object *value);
		int insert(Gpl_type T, const string &key, Animation_block *value);
		//int insert_dummy( const string &key);

		static bool 		isInTable(const string &key);    					//returns true if the key exists in the symbol table

		static bool 		get_type(string* name, Gpl_type &type);

//		static bool get(string *name, int    &ret_val);
//		static bool get(string *name, double &ret_val);
//		static bool get(string *name, string &ret_val);
		
		

		bool get(string name, int &value);
		bool get(string name, double &value);
		bool get(string name, string &value);
		bool get_type(string name, Gpl_type &type);
		bool set(string name, int value); // used for mouse_x, mouse_y

  private:
		int _insert(Gpl_type T, const string &key, void* value);

   ///


    Symbol_table();  //private CONSTRUCTOR
    
		static Symbol_table* M_ST;
    static map<string, Symbol* >* m_symbol_table; // static map of symbols

  public:
  	static Symbol* 	find(const string &key); 							// returns a ptr to a symbol containign the key.

};

#endif


#ifndef ___SYMBOL
#define ___SYMBOL
class Symbol{
  public:
    Symbol(Gpl_type &T, const string &key,  void* value);
		bool isValidSymbol();

		/* returns void* */
		void* value_ptr(){
			return m_value;
		}
		void* get(){
			return m_value;
		}

		string getName(){ 
			return *m_key;
		}

		template <typename R_TYPE>
		R_TYPE getValue(){ 
			return *(R_TYPE*)m_value;
		}
		string getType(){
			if(m_type_name & INT)
				return "int";
			else if(m_type_name & DOUBLE)
				return "double";
			else if(m_type_name & STRING)
				return "string";
			else if(m_type_name & GAME_OBJECT)
				return "game_object";
			else if(m_type_name & ANIMATION_BLOCK)
				return "animation_block";
			return "UNKNOWN_TYPE";
		}
		Gpl_type getGplTypeENUM(){ 
			return m_type_name;
		}
		bool setInt(int value){ 
			*(int*)m_value = value; 
			return true;
		}

		bool set(int value);
		bool set(double value);
		bool set(string value);
		bool set(Game_object* value);
		bool set(Animation_block* value);



		Gpl_type		m_type_name;
	private:
		string*			m_key;
		void*				m_value;
};
#endif