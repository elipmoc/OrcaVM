#ifndef LEXER_HPP
#define LEXER_HPP

enum class TokenType
{
    Num,
    Rnum,
    String,
    Bool,
    Push_I,
    Push_F,
    Push_S,
    Push_B,
    Add_I,
    Add_F,
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
    G_Load_I,
    G_Load_F,
    G_Load_S,
    G_Load_B,
    G_Store_I,
    G_Store_F,
    G_Store_S,
    G_Store_B,
    If_Start,
    If_End,
    Else,
    Func_Start,
    Func_End,
    Loop_Start,
    Loop_End,
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

        int code_cnt=0;

        std::string code;

    public:

        Lexer(std::string);

        Token get_token();
};

#endif