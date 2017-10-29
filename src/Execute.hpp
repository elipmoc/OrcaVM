#ifndef EXECUTE_HPP
#define EXECUTE_HPP

struct Stack
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

        inline Stack pop();

        void push_i();
        void push_f();
        void push_s();
        void push_b();

        void add_i();
        void add_f();
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
        void ne_i();
        void ne_f();

        void output();

        void input();

        void jump();
        void jump_true();
        void jump_false();
        
        void init_code_translater();

    public:

        ExecuteCode(const std::vector<InstructionCode>&,const int);

        void execute();

        void dump_stack();
};

#endif