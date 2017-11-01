#ifndef PARSER_HPP
#define PARSER_HPP

class Parser
{
    private:

        std::vector<Token> token_list;

        std::unordered_map<std::string,int> label_place;
        std::unordered_map<std::string,std::vector<int>> backpatch_label;

        void backpatch_l(std::string,int);
        
        CodeGenerator gen;

        unsigned int code_count=0;

        inline Token next_token();

        void statement();

    public:

        Parser(std::vector<Token>);

        CodeGenerator get_code();

        void parse();
};

#endif