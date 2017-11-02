#ifndef LEXER_HPP
#define LEXER_HPP

enum class TokenType
{
    Num,
    Rnum,
    String,
    Bool,
    Ident,
    Push_I,
    Push_F,
    Push_S,
    Push_B,
    Add_I,
    Add_F,
    Add_S,
    Sub_I,
    Sub_F,
    Mul_I,
    Mul_F,
    Div_I,
    Div_F,
    Mod_I,
    L_I,
    L_F,
    Le_I,
    Le_F,
    G_I,
    G_F,
    Ge_I,
    Ge_F,
    E_I,
    E_F,
    Ne_I,
    Ne_F,
    Or,
    And,
    G_Load_I,
    G_Load_F,
    G_Load_S,
    G_Load_B,
    G_Store_I,
    G_Store_F,
    G_Store_S,
    G_Store_B,
    Output,
    Input,
    Jump,
    Jump_True,
    Jump_False,
    Label,
    Def_Label,
    If,
    Else,
    EndIf,
    Func_Start,
    Func_End,
    Loop_Start,
    Loop_End,
    End_Token,
};

struct Token
{
    TokenType type;

    int i_val;
    double f_val;
    std::string s_val;
    bool b_val;
};

class Lexer
{
    private:

        unsigned int code_cnt=0;

        std::string code;

        std::vector<Token> token_list;

        std::unordered_map<std::string,TokenType> token_map;

        inline char next_char();

        void skip_space();

        inline bool check_size();

        void init_token_map();

        void error(std::string);

    public:

        Lexer(std::string);

        std::vector<Token> get_token();

        void start();
};

#endif