#ifndef PARSER_HPP
#define PARSER_HPP

class Parser
{
    private:

        std::vector<Token> token_list;

        std::unordered_map<std::string,int> label_place;
        std::unordered_map<std::string,std::vector<int>> backpatch_label;
        std::unordered_map<std::string,std::vector<int>> backpatch_func;
        std::unordered_map<std::string,int> func_addr;
        std::stack<std::unordered_map<std::string,int>> local_var_addr;
        std::unordered_map<std::string,int> global_var_addr;

        int get_addr_stack();
        int get_addr_static();

        bool *static_memory_sim;

        std::stack<std::array<bool,Call_Stack_Size>> stack_memory_sim;

        void backpatch_l(std::string,int);
        void backpatch_f(std::string,int);
        
        CodeGenerator gen;

        unsigned int code_count=0;

        inline Token next_token();

        void statement();

    public:

        Parser(std::vector<Token>);
        ~Parser();

        CodeGenerator get_code();

        void parse();

        int entry_point=0;
};

#endif