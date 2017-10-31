#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

Parser::Parser(std::vector<Token> tk)
{
    this->token_list=tk;
}

CodeGenerator Parser::get_code()
{
    return gen;
}

void Parser::parse()
{
    Token tk=next_token();

    for(;;)
    {
        bool loop_f=false;

        switch(tk.type)
        {
            case TokenType::Push_I:
                tk=next_token();
                gen.AddCode(InstructionCodeType::Push_I,tk.i_val);
                break;
            case TokenType::Push_F:
                tk=next_token();
                gen.AddCode(InstructionCodeType::Push_F,tk.f_val);
                break;
            case TokenType::Push_S:
                tk=next_token();
                gen.AddCode(InstructionCodeType::Push_S,tk.s_val);
                break;
            case TokenType::Push_B:
                tk=next_token();
                gen.AddCode(InstructionCodeType::Push_B,tk.b_val);
                break;
            case TokenType::Add_I:
                gen.AddCode(InstructionCodeType::Add_I);
                break;
            case TokenType::Add_F:
                gen.AddCode(InstructionCodeType::Add_F);
                break;
            case TokenType::End_Token:
                loop_f=true;
                break;
            default:
                std::cout<<"parser error"<<std::endl;
                exit(1);
        }

        tk=next_token();

        if(loop_f)break;
    }
}

inline Token Parser::next_token()
{
    Token tk=token_list[code_count];

    code_count++;
    
    return tk;
}