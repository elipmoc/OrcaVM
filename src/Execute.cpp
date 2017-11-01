#include "OrcaVM.hpp"
#include "Execute.hpp"

ExecuteCode::ExecuteCode(const std::vector<InstructionCode>& code,const int entry_point=0)
{
    this->code_counter=entry_point;
    this->code=code;
    this->init_code_translater();

    static_memory=new Memory[Static_Memory_Size];
}

ExecuteCode::~ExecuteCode()
{
    delete[] static_memory;
}

void ExecuteCode::init_code_translater()
{
    code_translater[InstructionCodeType::Push_I]=&ExecuteCode::push_i;
    code_translater[InstructionCodeType::Push_F]=&ExecuteCode::push_f;
    code_translater[InstructionCodeType::Push_S]=&ExecuteCode::push_s;
    code_translater[InstructionCodeType::Push_B]=&ExecuteCode::push_b;
    code_translater[InstructionCodeType::Add_I]=&ExecuteCode::add_i;
    code_translater[InstructionCodeType::Add_F]=&ExecuteCode::add_f;
    code_translater[InstructionCodeType::Add_S]=&ExecuteCode::add_s;
    code_translater[InstructionCodeType::Sub_I]=&ExecuteCode::sub_i;
    code_translater[InstructionCodeType::Sub_F]=&ExecuteCode::sub_f;
    code_translater[InstructionCodeType::Mul_I]=&ExecuteCode::mul_i;
    code_translater[InstructionCodeType::Mul_F]=&ExecuteCode::mul_f;
    code_translater[InstructionCodeType::Div_I]=&ExecuteCode::div_i;
    code_translater[InstructionCodeType::Div_F]=&ExecuteCode::div_f;
    code_translater[InstructionCodeType::Mod_I]=&ExecuteCode::mod_i;
    code_translater[InstructionCodeType::L_I]=&ExecuteCode::l_i;
    code_translater[InstructionCodeType::L_F]=&ExecuteCode::l_f;
    code_translater[InstructionCodeType::G_I]=&ExecuteCode::g_i;
    code_translater[InstructionCodeType::G_F]=&ExecuteCode::g_f;
    code_translater[InstructionCodeType::LE_I]=&ExecuteCode::le_i;
    code_translater[InstructionCodeType::LE_F]=&ExecuteCode::le_f;
    code_translater[InstructionCodeType::GE_I]=&ExecuteCode::ge_i;
    code_translater[InstructionCodeType::GE_F]=&ExecuteCode::ge_f;
    code_translater[InstructionCodeType::E_I]=&ExecuteCode::e_i;
    code_translater[InstructionCodeType::E_F]=&ExecuteCode::e_f;
    code_translater[InstructionCodeType::NE_I]=&ExecuteCode::ne_i;
    code_translater[InstructionCodeType::NE_F]=&ExecuteCode::ne_f;    
    code_translater[InstructionCodeType::Output]=&ExecuteCode::output;
    code_translater[InstructionCodeType::Input]=&ExecuteCode::input;
    code_translater[InstructionCodeType::Jump]=&ExecuteCode::jump;
    code_translater[InstructionCodeType::Jump_True]=&ExecuteCode::jump_true;
    code_translater[InstructionCodeType::Jump_False]=&ExecuteCode::jump_false;
    code_translater[InstructionCodeType::G_Store_I]=&ExecuteCode::g_store_i;
    code_translater[InstructionCodeType::G_Store_F]=&ExecuteCode::g_store_f;
    code_translater[InstructionCodeType::G_Store_S]=&ExecuteCode::g_store_s;
    code_translater[InstructionCodeType::G_Store_B]=&ExecuteCode::g_store_b;
    code_translater[InstructionCodeType::G_Load_I]=&ExecuteCode::g_load_i;
    code_translater[InstructionCodeType::G_Load_F]=&ExecuteCode::g_load_f;
    code_translater[InstructionCodeType::G_Load_S]=&ExecuteCode::g_load_s;
    code_translater[InstructionCodeType::G_Load_B]=&ExecuteCode::g_load_b;
}


/*** Execute ***/


void ExecuteCode::execute()
{
    size_t size=code.size();

    for(;code_counter<size;++code_counter)
    {
        (this->*code_translater[code[code_counter].type])();
    }
}


/*** dump stack ***/


void ExecuteCode::dump_stack()
{
    std::cout<<"*** stack dump start ***\n"<<std::endl;

    if(data_stack.size()==0)
    {
        std::cout<<"stack -> [empty]"<<std::endl;
        std::cout<<"*** stack dump end ***"<<std::endl;
        return;
    }

    for(int stack_counter=1;data_stack.size()!=0;++stack_counter)
    {
        Stack st=data_stack.top();
        data_stack.pop();

        std::cout<<"[stack deep] : "<<stack_counter<<std::endl;

        std::cout<<"+ integer_value : "<<st.i_val<<std::endl;
        std::cout<<"+ float_value : "<<st.f_val<<std::endl;
        std::cout<<"+ string_value : "<<st.s_val<<std::endl;
        std::cout<<"+ boolean_value : "<<st.b_val<<std::endl;

        std::cout<<"\n"<<std::flush;
    }

    std::cout<<"*** stack dump end ***"<<std::endl;
}


/*** Pop Stack ***/


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

void ExecuteCode::add_s()
{
    Stack st;

    st.s_val=pop().s_val+pop().s_val;

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


/*** Compare L_I/L_F/G_I/G_F/LE_I/LE_F/GE_I/GE_F/E_I/E_F/NE_I/NE_F ***/


void ExecuteCode::l_i()
{
    int comp_buf=pop().i_val;

    Stack st;

    st.b_val=pop().i_val<comp_buf;

    data_stack.push(st);
}

void ExecuteCode::l_f()
{
    double comp_buf=pop().f_val;

    Stack st;

    st.b_val=pop().f_val<comp_buf;

    data_stack.push(st);
}

void ExecuteCode::g_i()
{
    int comp_buf=pop().i_val;

    Stack st;

    st.b_val=pop().i_val>comp_buf;

    data_stack.push(st);
}

void ExecuteCode::g_f()
{
    double comp_buf=pop().f_val;

    Stack st;

    st.b_val=pop().f_val>comp_buf;

    data_stack.push(st);
}


void ExecuteCode::le_i()
{
    int comp_buf=pop().i_val;

    Stack st;

    st.b_val=pop().i_val<=comp_buf;

    data_stack.push(st);
}

void ExecuteCode::le_f()
{
    double comp_buf=pop().f_val;

    Stack st;

    st.b_val=pop().f_val<=comp_buf;

    data_stack.push(st);
}

void ExecuteCode::ge_i()
{
    int comp_buf=pop().i_val;

    Stack st;

    st.b_val=pop().i_val>=comp_buf;

    data_stack.push(st);
}

void ExecuteCode::ge_f()
{
    double comp_buf=pop().f_val;

    Stack st;

    st.b_val=pop().f_val>=comp_buf;

    data_stack.push(st);
}

void ExecuteCode::e_i()
{
    int comp_buf=pop().i_val;

    Stack st;

    st.b_val=pop().i_val==comp_buf;

    data_stack.push(st);
}

void ExecuteCode::e_f()
{
    double comp_buf=pop().f_val;

    Stack st;

    st.b_val=pop().f_val==comp_buf;

    data_stack.push(st);
}

void ExecuteCode::ne_i()
{
    int comp_buf=pop().i_val;

    Stack st;

    st.b_val=pop().i_val!=comp_buf;

    data_stack.push(st);
}

void ExecuteCode::ne_f()
{
    double comp_buf=pop().f_val;

    Stack st;

    st.b_val=pop().f_val!=comp_buf;

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


void ExecuteCode::jump()
{
    code_counter=code[code_counter].opr_i;
}

void ExecuteCode::jump_true()
{
    if(pop().b_val)
    {
        code_counter=code[code_counter].opr_i;
    }
}

void ExecuteCode::jump_false()
{
    if(!pop().b_val)
    {
        code_counter=code[code_counter].opr_i;
    }
}


/*** Global Store/Load (Static Memory) ***/


void ExecuteCode::g_store_i()
{
    static_memory[code[code_counter].opr_i].i_val=pop().i_val;
}

void ExecuteCode::g_store_f()
{
    static_memory[code[code_counter].opr_i].f_val=pop().f_val;
}

void ExecuteCode::g_store_s()
{
    static_memory[code[code_counter].opr_i].s_val=pop().s_val;
}

void ExecuteCode::g_store_b()
{
    static_memory[code[code_counter].opr_i].b_val=pop().b_val;
}

void ExecuteCode::g_load_i()
{
    Stack st;

    st.i_val=static_memory[code[code_counter].opr_i].i_val;

    data_stack.push(st);
}

void ExecuteCode::g_load_f()
{
    Stack st;

    st.f_val=static_memory[code[code_counter].opr_i].f_val;

    data_stack.push(st);
}

void ExecuteCode::g_load_s()
{
    Stack st;

    st.s_val=static_memory[code[code_counter].opr_i].s_val;

    data_stack.push(st);
}

void ExecuteCode::g_load_b()
{
    Stack st;

    st.b_val=static_memory[code[code_counter].opr_i].b_val;

    data_stack.push(st);
}