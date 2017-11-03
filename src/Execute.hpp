#ifndef EXECUTE_HPP
#define EXECUTE_HPP

struct Stack
{
    int i_val;
    double f_val;
    std::string s_val;
    bool b_val;
};

struct Memory
{
    int i_val;
    double f_val;
    std::string s_val;
    bool b_val;
};

class ExecuteCode
{
    private:

        unsigned int code_counter;
        
        std::vector<InstructionCode> code;

        std::unordered_map<InstructionCodeType,void (ExecuteCode::*)()> code_translater;

        std::stack<Stack> data_stack;

        std::stack<int> return_stack;

        std::stack<int> call_stack_size;

        Memory *static_memory;

        Memory *call_stack;

        Memory *stack_ptr;

        inline Stack pop();

        void push_i();
        void push_f();
        void push_s();
        void push_b();

        void add_i();
        void add_f();
        void add_s();
        void sub_i();
        void sub_f();
        void mul_i();
        void mul_f();
        void div_i();
        void div_f();
        void mod_i();

        void l_i();
        void l_f();
        void g_i();
        void g_f();
        void le_i();
        void le_f();
        void ge_i();
        void ge_f();
        void e_i();
        void e_f();
        void e_s();
        void ne_i();
        void ne_f();

        void itof();
        void itos();
        void ftoi();
        void ftos();
        void stoi();
        void stof();
        
        void And();
        void Or();

        void output();

        void input();

        void jump();
        void jump_true();
        void jump_false();
        
        void g_store_i();
        void g_store_f();
        void g_store_s();
        void g_store_b();

        void g_load_i();
        void g_load_f();
        void g_load_s();
        void g_load_b();

        void store_i();
        void store_f();
        void store_s();
        void store_b();

        void load_i();
        void load_f();
        void load_s();
        void load_b();

        void return_();

        void invoke();

        void push_return_stack();

        void set_call_stack_size();

        void init_code_translater();

    public:

        ExecuteCode(const std::vector<InstructionCode>&,const int);
        ~ExecuteCode();

        void execute();

        void dump_stack();
};

#endif