#include "symbol_table.h"
// init of static class field
Symbol_table* Symbol_table::M_ST = 0;
map<string, Symbol* >* Symbol_table::m_symbol_table = 0;

//-------------------------------------------//
/*                                           */
/* Definitions of class Symbol_table methods */
/*                                           */
//-------------------------------------------//

Symbol_table::Symbol_table()  {  }

	// -----------------------------------
	// Symbol_table::instance()
	// -----------------------------------
  //    create a PRIVATELY accessible Symbol_table 
  //    by using a PRIVATE constructor
Symbol_table* Symbol_table::instance(){
  if(M_ST == 0){
    M_ST = new Symbol_table();
  }
  return M_ST;
}

int Symbol_table::insert(Gpl_type T, const string &key, int value){	
	return _insert(T, key, &value);
}
int Symbol_table::insert(Gpl_type T, const string &key, double value){
	return _insert(T, key, &value);
}
int Symbol_table::insert(Gpl_type T, const string &key, string *value){
	return _insert(T, key, value);
}
int Symbol_table::insert(Gpl_type T, const string &key, Game_object *value){
	return _insert(T, key, value);
}
int Symbol_table::insert(Gpl_type T, const string &key, Animation_block *value){
	return _insert(T, key, value);
}

int Symbol_table::_insert(Gpl_type T, const string &key, void* value){
	map<string, Symbol*>::iterator symbol_it;

	if(m_symbol_table == 0){
		m_symbol_table = new map<string, Symbol*>;	
	}
	symbol_it = m_symbol_table->find(key);

	if(symbol_it == m_symbol_table->end()){ // then insert
	//	(*m_symbol_table)[key] = new Symbol_table::Symbol(key, value, T);
		m_symbol_table->insert( 
				pair<string, Symbol*>(key, new Symbol(T, key, value)) 
			);
	} else {// already in the table 
		return 0;  

	}

	return 1;
}


int Symbol_table::print(ostream &out){
	// for all items in symbol table, print the item
	if(!m_symbol_table)
		return 0;
	
	for(map<string, Symbol*>::iterator iter = m_symbol_table->begin();
			iter != m_symbol_table->end();
			iter++){
			 // assert that symbols in the table shoudl be valid symbols
				out << iter->second->getType()  << " "     		// as in:  int i 42
							<< iter->first;
				if(iter->second->m_type_name & INT){
					out << " " << iter->second->getValue<int>()	   ;
				} else if(iter->second->m_type_name & DOUBLE) {
					out << " " << iter->second->getValue<double>()  ;
				} else if(iter->second->m_type_name & STRING) {
					out <<  " " << "\"" << iter->second->getValue<string>() << "\""  ;
				} else if(iter->second->m_type_name & GAME_OBJECT) {
					cout << endl;
					((Game_object*)iter->second->value_ptr())->print(out);
				} else if(iter->second->m_type_name & ANIMATION_BLOCK) {
					cout << endl;
					((Animation_block*)iter->second->value_ptr())->print(out);
				}
				out << endl;
	}//endfor

	return 1;
}

/* static */ // reutnrs TRUE if the key exists in the table
bool Symbol_table::isInTable( const string &key){
	if(m_symbol_table){
		if(m_symbol_table->find(key) == m_symbol_table->end())
			return false;

		return true;
	}
	return false;
}

/* static */	// returns the Symbol ptr associatd with the key
Symbol* 
Symbol_table::find(const string &key){
	if(m_symbol_table){
		map<string, Symbol* >::iterator map_iter;
		map_iter = m_symbol_table->find(key);
		if(map_iter == m_symbol_table->end())
			return NULL;

		return map_iter->second; // return the symbol ptr
	}
	return NULL;
}

/* static */
bool Symbol_table::get_type(string* name, Gpl_type &type){
	bool symbol_exists = Symbol_table::isInTable(*name);
	if(symbol_exists){
		type = ((*m_symbol_table)[*name])->getGplTypeENUM(); //
		return true;
	} 
	return false;
}

bool Symbol_table::get(string name, int &value){
	Symbol* symbol = Symbol_table::find(name);
	if(symbol){
		if(symbol->getGplTypeENUM() == INT){
			value = symbol->getValue<int>();
			return true;
		}	
		// else return false;
	} 
	return false;
}
bool Symbol_table::get(string name, double &value){
	Symbol* symbol = Symbol_table::find(name);
	if(symbol){
		if(symbol->getGplTypeENUM() == DOUBLE){
			value = symbol->getValue<double>();
			return true;
		}	
		// else return false;
	} 
	return false;
}
bool Symbol_table::get(string name, string &value){
	Symbol* symbol = Symbol_table::find(name);
	if(symbol){
		if(symbol->getGplTypeENUM() == STRING){
			value = symbol->getValue<string>();
			return true;
		}	
		// else return false;
	} 
	return false;
}
bool Symbol_table::get_type(string name, Gpl_type &type){
	return get_type(&name, type);
}
bool Symbol_table::set(string name, int value){
	Symbol* symbol = Symbol_table::find(name);
	if(symbol){
		if(symbol->getGplTypeENUM() == INT){
			if(symbol->setInt(value)){
				return true;
			}
		}	
	}
	return false;
}


//-------------------------------------------------//
/*																								 */
/* Definitions of class Symbol_table::Symbol method*/
/*																								 */
// take a key, value, and typename to store
//   BASED ON TYPE and num BYTES, allocates storage
//     for data and copies data over from BISON to
//     Symbol 
//   SYMBOL HAS A COPY OF THE DATA
//-------------------------------------------------//

  /* Symbol Constructor */
Symbol::Symbol(Gpl_type &T, const string &key,  void* value){
	m_key   = new string(key);
	m_type_name = T;

	//  *value -> *m_value
	// i need to allocate enough memory for each type
	//  if int, then 32 bit double is 64bit, ... string.. strlength == num bytes
	if(T & INT){
		m_value = malloc(sizeof(int)); // 32 bits;
		memcpy(m_value, value, sizeof(int));
	} else if(T & DOUBLE){
		m_value = malloc(sizeof(double)); // 64 bits;
		memcpy(m_value, value, sizeof(double));
	} else if(T & STRING){
		m_value = new string(((string*)value)->c_str());
	} else if(T & GAME_OBJECT){
		m_value = value;// = malloc(sizeof(*value)); 
		//memcpy(m_value, value, sizeof(*value));
	} else if(T & ANIMATION_BLOCK){
		m_value = value;//= malloc(sizeof(*value)); 
		//memcpy(m_value, value, sizeof(*value));
	} else {
		m_value = NULL; // invalid or not known
	}


}


//-------------------------------------------------//
/*																								 */
/*   Symbol   methods/functions						    	   */ 
/*																								 */
//-------------------------------------------------//

bool Symbol::isValidSymbol(){
	if(m_value) 
		return true;
	return false;
}

/* Setter functions */
bool Symbol::set(int value)
{
	*(int*)m_value = value;
		return true;
}
bool Symbol::set(double value)
{
	*(double*)m_value = value;
		return true;
}
bool Symbol::set(string value)
{
	delete (string*)m_value;
	m_value = new string(value.c_str());
		return true;
}
bool Symbol::set(Game_object* value)
{
	m_value = (void*)value;
		return true;
}
bool Symbol::set(Animation_block* value)
{
	m_value = (void*)value;
		return true;
}