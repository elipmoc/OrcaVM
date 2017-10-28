#include "OrcaVM.hpp"
#include "Execute.hpp"

ExecuteCode::ExecuteCode(const std::vector<InstructionCode>& code,const int entry_point=0)
{
    this->code_counter=entry_point;
    this->code=code;
    this->init_code_translater();
}

void ExecuteCode::init_code_translater()
{
    code_translater[InstructionCodeType::Push_I]=&ExecuteCode::push_i;
    code_translater[InstructionCodeType::Push_F]=&ExecuteCode::push_f;
    code_translater[InstructionCodeType::Push_S]=&ExecuteCode::push_s;
    code_translater[InstructionCodeType::Push_B]=&ExecuteCode::push_b;
    code_translater[InstructionCodeType::AddI]=&ExecuteCode::add_i;
    code_translater[InstructionCodeType::AddF]=&ExecuteCode::add_f;
}

void ExecuteCode::execute()
{
    size_t size=code.size();

    for(;code_counter<size;++code_counter)
    {
        (this->*code_translater[code[code_counter].type])();
    }

    std::cout<<data_stack.top().i_val<<std::endl;
}

inline Stack ExecuteCode::pop()
{
    Stack st=data_stack.top();
    
    data_stack.pop();

    return st;
}

void ExecuteCode::push_i()
{
    Stack st;

    st.i_val=code[code_counter].opr_i;

    data_stack.push(st);
}

void ExecuteCode::push_f()
{
    Stack st;

    st.f_val=code[code_counter].opr_f;

    data_stack.push(st);
}

void ExecuteCode::push_s()
{
    Stack st;

    st.s_val=code[code_counter].opr_s;

    data_stack.push(st);
}

void ExecuteCode::push_b()
{
    Stack st;

    st.b_val=code[code_counter].opr_b;

    data_stack.push(st);
}

void ExecuteCode::add_i()
{
    Stack st;

    st.i_val=pop().i_val+pop().i_val;

    data_stack.push(st);
}

void ExecuteCode::add_f()
{
    Stack st;

    st.f_val=pop().f_val+pop().f_val;

    data_stack.push(st);
}