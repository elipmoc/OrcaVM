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

        int code_counter;
        
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
        
        void init_code_translater();

    public:

        ExecuteCode(const std::vector<InstructionCode>&,const int);

        void execute();
};

#endif