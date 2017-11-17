#ifndef JIT_HPP
#define JIT_HPP

class JITCodeGenerator
{
    private:

        std::string code;

        bool main_f=false;

    public:

        std::string get_code();

        void def_func(std::string);
        void end_func();
        void def_main();
        void push_i(std::string);
        void push_f(std::string);
        void push_s(std::string);
        void push_b(std::string);
        void add_i();
        void output();

        JITCodeGenerator();
};

class JIT
{
    private:

        std::vector<Token> token_list;

        std::string output_code;

        JITCodeGenerator gen;

        int code_counter = 0;

        void write_code(std::string);

        inline Token next_token();

    public:

        JIT(const std::vector<Token>&);

        void parse();
        void execute();
};

#endif