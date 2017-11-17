#include "OrcaVM.hpp"
#include "Execute.hpp"

ExecuteCode::ExecuteCode(const std::vector<InstructionCode>& code,const int entry_point=0)
{
    this->code_counter=entry_point;
    this->code=code;
    this->init_code_translater();

    static_memory=new Memory*[Static_Memory_Size];
    static_base=new Memory[Static_Memory_Size];
    call_base=new Memory[Call_Stack_Size];
    call_stack=new Memory*[Call_Stack_Size];

    call_stack_size.push(0);

    stack_ptr=call_stack;

    for(int i=0;i<Static_Memory_Size;++i)
    {
        static_memory[i]=static_base+i;
    }

    for(int i=0;i<Static_Memory_Size;++i)
    {
        call_stack[i]=call_base+i;
    }
}

ExecuteCode::~ExecuteCode()
{
    delete[] static_memory;
    delete[] static_base;
    delete[] call_base;
    delete[] call_stack;
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
    code_translater[InstructionCodeType::E_S]=&ExecuteCode::e_s;
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
    code_translater[InstructionCodeType::G_Store_A]=&ExecuteCode::g_store_a;
    code_translater[InstructionCodeType::G_Load_I]=&ExecuteCode::g_load_i;
    code_translater[InstructionCodeType::G_Load_F]=&ExecuteCode::g_load_f;
    code_translater[InstructionCodeType::G_Load_S]=&ExecuteCode::g_load_s;
    code_translater[InstructionCodeType::G_Load_B]=&ExecuteCode::g_load_b;
    code_translater[InstructionCodeType::G_Load_A]=&ExecuteCode::g_load_a;
    code_translater[InstructionCodeType::Store_I]=&ExecuteCode::store_i;
    code_translater[InstructionCodeType::Store_F]=&ExecuteCode::store_f;
    code_translater[InstructionCodeType::Store_S]=&ExecuteCode::store_s;
    code_translater[InstructionCodeType::Store_B]=&ExecuteCode::store_b;
    code_translater[InstructionCodeType::Store_A]=&ExecuteCode::store_a;
    code_translater[InstructionCodeType::Load_I]=&ExecuteCode::load_i;
    code_translater[InstructionCodeType::Load_F]=&ExecuteCode::load_f;
    code_translater[InstructionCodeType::Load_S]=&ExecuteCode::load_s;
    code_translater[InstructionCodeType::Load_B]=&ExecuteCode::load_b;
    code_translater[InstructionCodeType::Load_A]=&ExecuteCode::load_a;
    code_translater[InstructionCodeType::G_AStore_I]=&ExecuteCode::g_astore_i;
    code_translater[InstructionCodeType::G_AStore_F]=&ExecuteCode::g_astore_f;
    code_translater[InstructionCodeType::G_AStore_S]=&ExecuteCode::g_astore_s;
    code_translater[InstructionCodeType::G_AStore_B]=&ExecuteCode::g_astore_b;
    code_translater[InstructionCodeType::G_AStore_A]=&ExecuteCode::g_astore_a;
    code_translater[InstructionCodeType::G_ALoad_I]=&ExecuteCode::g_aload_i;
    code_translater[InstructionCodeType::G_ALoad_F]=&ExecuteCode::g_aload_f;
    code_translater[InstructionCodeType::G_ALoad_S]=&ExecuteCode::g_aload_s;
    code_translater[InstructionCodeType::G_ALoad_B]=&ExecuteCode::g_aload_b;
    code_translater[InstructionCodeType::G_ALoad_A]=&ExecuteCode::g_aload_a;
    code_translater[InstructionCodeType::AStore_I]=&ExecuteCode::astore_i;
    code_translater[InstructionCodeType::AStore_F]=&ExecuteCode::astore_f;
    code_translater[InstructionCodeType::AStore_S]=&ExecuteCode::astore_s;
    code_translater[InstructionCodeType::AStore_B]=&ExecuteCode::astore_b;
    code_translater[InstructionCodeType::AStore_A]=&ExecuteCode::astore_a;
    code_translater[InstructionCodeType::ALoad_I]=&ExecuteCode::aload_i;
    code_translater[InstructionCodeType::ALoad_F]=&ExecuteCode::aload_f;
    code_translater[InstructionCodeType::ALoad_S]=&ExecuteCode::aload_s;
    code_translater[InstructionCodeType::ALoad_B]=&ExecuteCode::aload_b;
    code_translater[InstructionCodeType::ALoad_A]=&ExecuteCode::aload_a;
    code_translater[InstructionCodeType::Or]=&ExecuteCode::Or;
    code_translater[InstructionCodeType::And]=&ExecuteCode::And;
    code_translater[InstructionCodeType::ItoF]=&ExecuteCode::itof;
    code_translater[InstructionCodeType::ItoS]=&ExecuteCode::itos;
    code_translater[InstructionCodeType::FtoI]=&ExecuteCode::ftoi;
    code_translater[InstructionCodeType::FtoS]=&ExecuteCode::ftos;
    code_translater[InstructionCodeType::StoI]=&ExecuteCode::stoi;
    code_translater[InstructionCodeType::StoF]=&ExecuteCode::stof;
    code_translater[InstructionCodeType::CtoI]=&ExecuteCode::ctoi;
    code_translater[InstructionCodeType::ItoC]=&ExecuteCode::itoc;
    code_translater[InstructionCodeType::Return]=&ExecuteCode::return_;
    code_translater[InstructionCodeType::Set_Stack_Size]=&ExecuteCode::set_call_stack_size;
    code_translater[InstructionCodeType::Invoke]=&ExecuteCode::invoke;
    code_translater[InstructionCodeType::Exit]=&ExecuteCode::exit_;
    code_translater[InstructionCodeType::Push_Return_Stack]=&ExecuteCode::push_return_stack;
}


/*** Execute ***/


void ExecuteCode::execute()
{
    for(;;++code_counter)
    {
        #ifdef Debug

        std::cout<<"execute : "<<code_counter<<std::endl;

        #endif

        if(exit_flag)break;

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
        std::cout<<"+ reference_value : "<<st.ref<<std::endl;

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


/*** Compare L_I/L_F/G_I/G_F/LE_I/LE_F/GE_I/GE_F/E_I/E_F/E_S/NE_I/NE_F/And/Or ***/


void ExecuteCode::And()
{
    Stack st;

    bool b1=pop().b_val;
    bool b2=pop().b_val;

    st.b_val=b1==true && b2==true?true :false;

    data_stack.push(st);
}

void ExecuteCode::Or()
{
    Stack st;

    bool b1=pop().b_val;
    bool b2=pop().b_val;

    st.b_val=b1==true || b2==true ? true : false;

    data_stack.push(st);
}

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

void ExecuteCode::e_s()
{
    Stack st;

    st.b_val=pop().s_val==pop().s_val;

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
    static_memory[code[code_counter].opr_i]->i_val=pop().i_val;
}

void ExecuteCode::g_store_f()
{
    static_memory[code[code_counter].opr_i]->f_val=pop().f_val;
}

void ExecuteCode::g_store_s()
{
    static_memory[code[code_counter].opr_i]->s_val=pop().s_val;
}

void ExecuteCode::g_store_b()
{
    static_memory[code[code_counter].opr_i]->b_val=pop().b_val;
}

void ExecuteCode::g_load_i()
{
    Stack st;

    st.i_val=static_memory[code[code_counter].opr_i]->i_val;

    data_stack.push(st);
}

void ExecuteCode::g_load_f()
{
    Stack st;

    st.f_val=static_memory[code[code_counter].opr_i]->f_val;

    data_stack.push(st);
}

void ExecuteCode::g_load_s()
{
    Stack st;

    st.s_val=static_memory[code[code_counter].opr_i]->s_val;

    data_stack.push(st);
}

void ExecuteCode::g_load_b()
{
    Stack st;

    st.b_val=static_memory[code[code_counter].opr_i]->b_val;

    data_stack.push(st);
}

void ExecuteCode::g_store_a()
{
    static_memory[code[code_counter].opr_i]=pop().ref;
}

void ExecuteCode::g_load_a()
{
    Stack st;

    st.ref=static_memory[code[code_counter].opr_i];

    data_stack.push(st);
}


/*** store/load ***/


void ExecuteCode::store_i()
{
    (*(stack_ptr+code[code_counter].opr_i))->i_val=pop().i_val;
}

void ExecuteCode::store_f()
{
    (*(stack_ptr+code[code_counter].opr_i))->f_val=pop().f_val;
}

void ExecuteCode::store_s()
{
    (*(stack_ptr+code[code_counter].opr_i))->s_val=pop().s_val;
}

void ExecuteCode::store_b()
{
    (*(stack_ptr+code[code_counter].opr_i))->b_val=pop().b_val;
}

void ExecuteCode::load_i()
{
    Stack st;

    st.i_val=(*(stack_ptr+code[code_counter].opr_i))->i_val;

    data_stack.push(st);
}

void ExecuteCode::load_f()
{
    Stack st;

    st.f_val=(*(stack_ptr+code[code_counter].opr_i))->f_val;

    data_stack.push(st);
}


void ExecuteCode::load_s()
{
    Stack st;

    st.s_val=(*(stack_ptr+code[code_counter].opr_i))->s_val;

    data_stack.push(st);
}


void ExecuteCode::load_b()
{
    Stack st;

    st.b_val=(*(stack_ptr+code[code_counter].opr_i))->b_val;

    data_stack.push(st);
}

void ExecuteCode::store_a()
{
    *(stack_ptr+code[code_counter].opr_i)=pop().ref;
}

void ExecuteCode::load_a()
{
    Stack st;

    st.ref=(*stack_ptr+code[code_counter].opr_i);

    data_stack.push(st);
}


/*** array ***/


void ExecuteCode::g_aload_i()
{
    Stack st;

    st.i_val=static_memory[code[code_counter].opr_i+pop().i_val]->i_val;

    data_stack.push(st);
}

void ExecuteCode::g_aload_f()
{
    Stack st;

    st.f_val=static_memory[code[code_counter].opr_i+pop().i_val]->f_val;

    data_stack.push(st);
}

void ExecuteCode::g_aload_s()
{
    Stack st;

    st.s_val=static_memory[code[code_counter].opr_i+pop().i_val]->s_val;

    data_stack.push(st);
}

void ExecuteCode::g_aload_b()
{
    Stack st;

    st.b_val=static_memory[code[code_counter].opr_i+pop().i_val]->b_val;

    data_stack.push(st);
}

void ExecuteCode::g_aload_a()
{
    Stack st;

    st.ref=static_memory[code[code_counter].opr_i+pop().i_val];

    data_stack.push(st);
}

void ExecuteCode::g_astore_i()
{
    int addr=pop().i_val;
    int i_val=pop().i_val;

    static_memory[code[code_counter].opr_i+addr]->i_val=i_val;
}

void ExecuteCode::g_astore_f()
{
    int addr=pop().i_val;
    double f_val=pop().f_val;

    static_memory[code[code_counter].opr_i+addr]->f_val=f_val;
}

void ExecuteCode::g_astore_s()
{
    int addr=pop().i_val;
    std::string s_val=pop().s_val;

    static_memory[code[code_counter].opr_i+addr]->s_val=s_val;
}

void ExecuteCode::g_astore_b()
{
    int addr=pop().i_val;
    bool b_val=pop().b_val;

    static_memory[code[code_counter].opr_i+addr]->b_val=b_val;
}

void ExecuteCode::g_astore_a()
{
    int addr=pop().i_val;
    Memory *ref=pop().ref;

    static_memory[code[code_counter].opr_i+addr]=ref;
}

void ExecuteCode::aload_i()
{
    Stack st;

    st.i_val=(*stack_ptr+code[code_counter].opr_i+pop().i_val)->i_val;

    data_stack.push(st);
}

void ExecuteCode::aload_f()
{
    Stack st;

    st.f_val=(*stack_ptr+code[code_counter].opr_i+pop().i_val)->f_val;

    data_stack.push(st);
}

void ExecuteCode::aload_s()
{
    Stack st;

    st.s_val=(*stack_ptr+code[code_counter].opr_i+pop().i_val)->s_val;

    data_stack.push(st);
}

void ExecuteCode::aload_b()
{
    Stack st;

    st.b_val=(*stack_ptr+code[code_counter].opr_i+pop().i_val)->b_val;

    data_stack.push(st);
}

void ExecuteCode::aload_a()
{
    Stack st;

    st.ref=(*stack_ptr+code[code_counter].opr_i+pop().i_val);

    data_stack.push(st);
}

void ExecuteCode::astore_i()
{
    int addr=pop().i_val;
    int i_val=pop().i_val;

    (*(stack_ptr+code[code_counter].opr_i+addr))->i_val=i_val;
}

void ExecuteCode::astore_f()
{
    int addr=pop().i_val;
    double f_val=pop().f_val;

    (*stack_ptr+code[code_counter].opr_i+addr)->f_val=f_val;
}

void ExecuteCode::astore_s()
{
    int addr=pop().i_val;
    std::string s_val=pop().s_val;

    (*(stack_ptr+code[code_counter].opr_i+addr))->s_val=s_val;
}

void ExecuteCode::astore_b()
{
    int addr=pop().i_val;
    bool b_val=pop().b_val;

    (*(stack_ptr+code[code_counter].opr_i+addr))->b_val=b_val;
}

void ExecuteCode::astore_a()
{
    int addr=pop().i_val;
    Memory *ref=pop().ref;

    (*(stack_ptr+code[code_counter].opr_i+addr))=ref;
}


/*** cast itof/itos/ftoi/ftos/stoi/stof ***/


void ExecuteCode::itof()
{
    Stack st;

    st.f_val=(double)pop().i_val;

    data_stack.push(st);
}

void ExecuteCode::itos()
{
    Stack st;

    st.s_val=std::to_string(pop().i_val);

    data_stack.push(st);
}

void ExecuteCode::ftoi()
{
    Stack st;

    st.i_val=(int)pop().f_val;

    data_stack.push(st);
}

void ExecuteCode::ftos()
{
    Stack st;

    st.s_val=std::to_string(pop().f_val);

    data_stack.push(st);
}

void ExecuteCode::stoi()
{
    Stack st;

    st.i_val=std::stoi(pop().s_val);

    data_stack.push(st);
}

void ExecuteCode::stof()
{
    Stack st;

    st.f_val=std::stod(pop().s_val);

    data_stack.push(st);
}

void ExecuteCode::itoc()
{
    Stack st;

    st.s_val=(char)pop().i_val;

    data_stack.push(st);
}

void ExecuteCode::ctoi()
{
    Stack st;

    st.i_val=(int)pop().s_val[0];

    data_stack.push(st);
}


/*** return ***/


void ExecuteCode::return_()
{
    code_counter=return_stack.top();
    return_stack.pop();

    call_stack_size.pop();

    stack_ptr=stack_ptr-call_stack_size.top();
}

void ExecuteCode::invoke()
{
    code_counter=code[code_counter].opr_i;

    stack_ptr=(stack_ptr+call_stack_size.top());
}

void ExecuteCode::set_call_stack_size()
{
    call_stack_size.push(code[code_counter].opr_i);
}


void ExecuteCode::push_return_stack()
{
    return_stack.push(code[code_counter].opr_i);
}


/*** exit ***/

void ExecuteCode::exit_()
{
    exit_flag=true;
}