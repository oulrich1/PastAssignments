#include "event_manager.h"
#include "gpl_assert.h"
using namespace std;

/* static */ Event_manager *Event_manager::m_instance = 0;

/* static */ 
Event_manager * Event_manager::instance()
{
  if (!m_instance)
    m_instance = new Event_manager();
  return m_instance;
}

Event_manager::Event_manager()
{
  keystroke_mappedto_stmt_block_v = new vector<Statement_block*>[Window::NUMBER_OF_KEYS];
}

Event_manager::~Event_manager()
{
  delete m_instance;
}


void 
Event_manager::execute_handlers(Window::Keystroke keystroke)
{
  int v_size;  // number of elements in the vector at the [keystroke] index in the array of vectors of stmt_blocks
  if(keystroke >= 0 && keystroke < Window::NUMBER_OF_KEYS){
    v_size = (keystroke_mappedto_stmt_block_v[keystroke]).size();
    for(int iter = 0 ; iter < v_size; iter++){
      (keystroke_mappedto_stmt_block_v[keystroke])[iter]->execute();  // vector<int*> y; *(y[0])
    } // end while
  } // end if

}

bool Event_manager::push_statement_block(Window::Keystroke keystroke, Statement_block* stmt_block){
   (keystroke_mappedto_stmt_block_v[keystroke]).push_back(stmt_block);
   return true;
}
