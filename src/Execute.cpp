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
    code_translater[InstructionCodeType::Add_I]=&ExecuteCode::add_i;
    code_translater[InstructionCodeType::Add_F]=&ExecuteCode::add_f;
    code_translater[InstructionCodeType::Sub_I]=&ExecuteCode::sub_i;
    code_translater[InstructionCodeType::Sub_F]=&ExecuteCode::sub_f;
    code_translater[InstructionCodeType::Mul_I]=&ExecuteCode::mul_i;
    code_translater[InstructionCodeType::Mul_F]=&ExecuteCode::mul_f;
    code_translater[InstructionCodeType::Div_I]=&ExecuteCode::div_i;
    code_translater[InstructionCodeType::Div_F]=&ExecuteCode::div_f;
    code_translater[InstructionCodeType::Mod_I]=&ExecuteCode::mod_i;
    code_translater[InstructionCodeType::Output]=&ExecuteCode::output;
    code_translater[InstructionCodeType::Input]=&ExecuteCode::input;
    code_translater[InstructionCodeType::Jump]=&ExecuteCode::jump;
    code_translater[InstructionCodeType::Jump_True]=&ExecuteCode::jump_true;
    code_translater[InstructionCodeType::Jump_False]=&ExecuteCode::jump_false;
}


//***************Execute*****************//


void ExecuteCode::execute()
{
    size_t size=code.size();

    for(;code_counter<size;++code_counter)
    {
        (this->*code_translater[code[code_counter].type])();
    }
}


/***Pop Stack ***/


inline Stack ExecuteCode::pop()
{
    Stack st=data_stack.top();
    
    data_stack.pop();

    return st;
}


/*** Push PushI/PushF/PushS/PushB ***/


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


/*** Calculate Add/Sub/Mul/Div/Mod ***/


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

void ExecuteCode::sub_i()
{
    Stack st;

    int buf=pop().i_val;

    st.i_val=pop().i_val-buf;

    data_stack.push(st);
}

void ExecuteCode::sub_f()
{
    Stack st;

    double buf=pop().f_val;

    st.f_val=pop().f_val-buf;

    data_stack.push(st);
}

void ExecuteCode::mul_i()
{
    Stack st;

    st.i_val=pop().i_val*pop().i_val;

    data_stack.push(st);
}

void ExecuteCode::mul_f()
{
    Stack st;

    st.f_val=pop().f_val*pop().f_val;

    data_stack.push(st);
}

void ExecuteCode::div_i()
{
    Stack st;

    int buf=pop().i_val;

    st.i_val=pop().i_val/buf;

    data_stack.push(st);
}

void ExecuteCode::div_f()
{
    Stack st;

    double buf=pop().f_val;

    st.f_val=pop().f_val/buf;

    data_stack.push(st);
}

void ExecuteCode::mod_i()
{
    Stack st;

    int buf=pop().i_val;

    st.i_val=pop().i_val%buf;

    data_stack.push(st);
}


/*** Standard Input/Output ***/


void ExecuteCode::output()
{
    printf("%s",pop().s_val.c_str());
}

void ExecuteCode::input()
{
    Stack st;

    std::cin>>st.s_val;

    data_stack.push(st);
}


/*** Jump ***/


void jump()
{
    code_counter=code[code_counter].opr_i;
}

void jump_true()
{
    if(pop().b_val)
    {
        code_counter=code[code_counter].opr_i;
    }
}

void jump_false()
{
    if(!pop().b_val)
    {
        code_counter=code[code_counter].opr_i;
    }
}