#include "animation_block.h"
#include "indent.h"
#include "gpl_assert.h"

#include "symbol_table.h"       // so that execute knows about the symbol that an  //
                                //animatioon block needs to execute on the proper game object //

using namespace std;

Animation_block::Animation_block(int forward_line, 
                                 Symbol *parameter, string name) 
                                 : Statement_block(-1)
{
    // m_forward_line is only used for debuggin
    m_forward_line = forward_line;
    m_name = name;

    // should do some error checking on parameter
    m_parameter_symbol = parameter;
    m_isbody_declared  = false;
}

void 
Animation_block::execute(Game_object *argument)
{
    // point the m_parameter_symbol to argument (since argument is the object using this animation block)
    // so that the next reference to the m_parameter_symbol references the real object we want to change 
    // (now i see why we should point the m_parameter_symbol back to what it was pointing to (the dummy object)
    // (since every time this execute function gets called we hae to assume that m_param_symbol wil change it's pointer)
    //  (so its not necessary but we should change the ptr)
    //
    // 
    // 
    //Game_object* tmp_ptr_to_dummy_object = (Game_object*)(m_parameter_symbol->get());

    /* now the animation_block's symbol pointer to the param arg 
        needs to set the value of the pointer to the game object within the 
        symbol TO the "argument" (THE CURRENT GAME OBJECT ) 
            (aka the real cur_object, not the fake dummy one)
    */

    m_parameter_symbol->set(argument);


    /* execute the execute() function written in the base class...
        executes the statements and uses the now set m_param_symbol->value 
        that point to the current object that owns this animation block */
    Statement_block::execute();

    /* reset the animation block's ptr to point to the dummy object*/ 
    /* not necessary, but it does seem dirty if its not reset...   */
    // m_parameter_symbol->set(tmp_ptr_to_dummy_object);

    //assert(false);
}

ostream &
Animation_block::print(ostream &os) const
{
    indent++; // edited to make tests work
    os << indent << "Animation_block[" << m_line;
    
    os << "]" << endl
       << indent << "{" << endl;
    indent++;
    os << indent << "animation block not implemented yet" << endl;
    indent--;
    os << indent << "}";
    indent--;
    return os;
}

ostream &
operator<<(ostream &os, const Animation_block &animation_block)
{
    return animation_block.print(os);
}

ostream &
operator<<(ostream &os, const Animation_block *animation_block)
{
    if (!animation_block)
    {
        os << indent << "NULL";
        return os;
    }

    return animation_block->print(os);
}
