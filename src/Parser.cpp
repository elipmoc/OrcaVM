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
    static Token tk;

    static int nest_cnt=0;
    static int loop_nest_cnt=0;

    static std::stack<std::vector<int>> loop_end_addr;

    int if_b_patch,else_b_patch;

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
            case TokenType::Or:
                gen.AddCode(InstructionCodeType::Or);
                break;
            case TokenType::And:
                gen.AddCode(InstructionCodeType::And);
                break;
            case TokenType::ItoF:
                gen.AddCode(InstructionCodeType::ItoF);
                break;
            case TokenType::ItoS:
                gen.AddCode(InstructionCodeType::ItoS);
                break;
            case TokenType::FtoI:
                gen.AddCode(InstructionCodeType::FtoI);
                break;
            case TokenType::FtoS:
                gen.AddCode(InstructionCodeType::FtoS);
                break;
            case TokenType::StoI:
                gen.AddCode(InstructionCodeType::StoI);
                break;
            case TokenType::StoF:
                gen.AddCode(InstructionCodeType::StoF);
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
            case TokenType::Jump:
                tk=next_token();
                if(label_place.count(tk.s_val)==0)
                {
                    gen.AddCode(InstructionCodeType::Jump,-1);
                    backpatch_label[tk.s_val].push_back(gen.now_count());
                }
                else gen.AddCode(InstructionCodeType::Jump,label_place[tk.s_val]);
                break;
            case TokenType::Jump_True:
                tk=next_token();
                if(label_place.count(tk.s_val)==0)
                {
                    gen.AddCode(InstructionCodeType::Jump_True,-1);
                    backpatch_label[tk.s_val].push_back(gen.now_count());
                }
                else gen.AddCode(InstructionCodeType::Jump_True,label_place[tk.s_val]);
                break;
            case TokenType::Jump_False:
                tk=next_token();
                if(label_place.count(tk.s_val)==0)
                {
                    gen.AddCode(InstructionCodeType::Jump_False,-1);
                    backpatch_label[tk.s_val].push_back(gen.now_count());
                }
                else gen.AddCode(InstructionCodeType::Jump_False,label_place[tk.s_val]);
                break;
            case TokenType::Def_Label:
                tk=next_token();
                label_place[tk.s_val]=gen.now_count();
                backpatch_l(tk.s_val,gen.now_count());
                break;
            case TokenType::Output:
                gen.AddCode(InstructionCodeType::Output);
                break;
            case TokenType::Input:
                gen.AddCode(InstructionCodeType::Input);
                break;
            case TokenType::If:
                nest_cnt++;
                gen.AddCode(InstructionCodeType::Jump_False,-1);
                if_b_patch=gen.now_count();
                parse();
                nest_cnt--;
                if(tk.type==TokenType::Else)
                {
                    gen.AddCode(InstructionCodeType::Jump,-1);
                    gen.backpatch_addr(if_b_patch,gen.now_count());
                    else_b_patch=gen.now_count();
                    nest_cnt++;
                    parse();
                    nest_cnt--;
                    gen.backpatch_addr(else_b_patch,gen.now_count());
                }
                else if(tk.type==TokenType::EndIf)
                {
                    gen.backpatch_addr(if_b_patch,gen.now_count());
                }
                break;
            case TokenType::Else:
                if(nest_cnt==0)
                {
                    std::cerr<<"syntax error"<<std::endl;
                    exit(1);
                }
                return;
            case TokenType::EndIf:
                if(nest_cnt==0)
                {
                    std::cerr<<"syntax error"<<std::endl;
                    exit(1);
                }
                return;
            case TokenType::Loop_Start:
            {   
                loop_nest_cnt++;
                std::vector<int> v;
                loop_end_addr.push(v);
                int loop_addr=gen.now_count();
                parse();

                gen.AddCode(InstructionCodeType::Jump,loop_addr);
                
                for(auto addr:loop_end_addr.top())
                {
                    gen.backpatch_addr(addr,gen.now_count());
                }

                loop_end_addr.pop();
                
                break;
            }
            case TokenType::Loop_End:
                if(loop_nest_cnt==0)
                {
                    std::cerr<<"syntax error"<<std::endl;
                    exit(1);
                }
                return;
            case TokenType::Break:
                gen.AddCode(InstructionCodeType::Jump,-1);
                loop_end_addr.top().push_back(gen.now_count());
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

void Parser::backpatch_l(std::string name,int addr)
{
    for(auto place:backpatch_label[name])
    {
        gen.backpatch_addr(place,addr);
    }
}

inline Token Parser::next_token()
{
    Token tk=token_list[code_count];

    code_count++;
    
    return tk;
}