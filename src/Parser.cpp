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
    Token tk;

    for(;;)
    {
        bool loop_f=false;

        tk=next_token();

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
            case TokenType::Add_S:
                gen.AddCode(InstructionCodeType::Add_S);
                break;
            case TokenType::Sub_I:
                gen.AddCode(InstructionCodeType::Sub_I);
                break;
            case TokenType::Sub_F:
                gen.AddCode(InstructionCodeType::Sub_F);
                break;
            case TokenType::Mul_I:
                gen.AddCode(InstructionCodeType::Mul_I);
                break;
            case TokenType::Mul_F:
                gen.AddCode(InstructionCodeType::Mul_F);
                break;
            case TokenType::Div_I:
                gen.AddCode(InstructionCodeType::Div_I);
                break;
            case TokenType::Mod_I:
                gen.AddCode(InstructionCodeType::Mod_I);
                break;
            case TokenType::L_I:
                gen.AddCode(InstructionCodeType::L_I);
                break;
            case TokenType::L_F:
                gen.AddCode(InstructionCodeType::L_F);
                break;
            case TokenType::Le_I:
                gen.AddCode(InstructionCodeType::LE_I);
                break;
            case TokenType::Le_F:
                gen.AddCode(InstructionCodeType::LE_F);
                break;
            case TokenType::G_I:
                gen.AddCode(InstructionCodeType::G_I);
                break;
            case TokenType::G_F:
                gen.AddCode(InstructionCodeType::G_F);
                break;
            case TokenType::Ge_I:
                gen.AddCode(InstructionCodeType::GE_I);
                break;
            case TokenType::Ge_F:
                gen.AddCode(InstructionCodeType::GE_F);
                break;
            case TokenType::E_I:
                gen.AddCode(InstructionCodeType::E_I);
                break;
            case TokenType::E_F:
                gen.AddCode(InstructionCodeType::E_F);
                break;
            case TokenType::Ne_I:
                gen.AddCode(InstructionCodeType::NE_I);
                break;
            case TokenType::Ne_F:
                gen.AddCode(InstructionCodeType::NE_F);
                break;
            case TokenType::G_Load_I:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Load_I,tk.i_val);
                break;
            case TokenType::G_Load_F:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Load_F,tk.i_val);
                break;
            case TokenType::G_Load_S:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Load_S,tk.i_val);
                break;
            case TokenType::G_Load_B:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Load_B,tk.i_val);
                break;
            case TokenType::G_Store_I:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Store_I,tk.i_val);
                break;
            case TokenType::G_Store_F:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Store_F,tk.i_val);
                break;
            case TokenType::G_Store_S:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Store_S,tk.i_val);
                break;
            case TokenType::G_Store_B:
                tk=next_token();
                gen.AddCode(InstructionCodeType::G_Store_B,tk.i_val);
                break;
            case TokenType::Output:
                gen.AddCode(InstructionCodeType::Output);
                break;
            case TokenType::Input:
                gen.AddCode(InstructionCodeType::Input);
                break;
            case TokenType::End_Token:
                loop_f=true;
                break;
            default:
                std::cout<<tk.s_val<<std::endl;
                std::cout<<"parser error"<<std::endl;
                exit(1);
        }

        if(loop_f)break;
    }
}

inline Token Parser::next_token()
{
    Token tk=token_list[code_count];

    code_count++;
    
    return tk;
}