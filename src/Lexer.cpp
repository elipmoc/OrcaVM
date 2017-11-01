#include "OrcaVM.hpp"
#include "Lexer.hpp"

Lexer::Lexer(std::string code)
{
    this->code=code;

    init_token_map();
}

std::vector<Token> Lexer::get_token()
{
    return this->token_list;
}

void Lexer::start()
{
    for(;;)
    {
        skip_space();

        char c=next_char();

        if(isdigit(c))
        {
            std::string str_num;
            bool p_flag=false;

            for(;isdigit(c) || c=='.';c=next_char())
            {
                str_num+=c;

                if(c=='.')
                {
                    if(p_flag)
                    {
                        error("lexer error");
                    }

                    p_flag=true;
                }
            }

            Token tk;

            if(p_flag)
            {
                tk.type=TokenType::Rnum;
                tk.f_val=std::stof(str_num);
            }
            else
            {
                tk.type=TokenType::Num;
                tk.i_val=std::stoi(str_num);
            }

            token_list.push_back(tk);
        }
        else if(isalpha(c))
        {
            std::string ident_str;
            Token tk;

            for(;isalpha(c) || c=='_' || isdigit(c);c=next_char())
            {
                ident_str+=c;
            }

            if(token_map.count(ident_str)>0)
            {
                tk.type=token_map[ident_str];
            }
            else
            {
                tk.s_val=ident_str;
                tk.type=TokenType::Ident;
            }

            token_list.push_back(tk);
        }
        else if(c=='\"')
        {
            std::string str;

            for(c=next_char();c!='\"';c=next_char())
            {
                if(c=='\\')
                {
                    c=next_char();

                    if(c=='n')
                    {
                        str+="\n";
                    }
                }
                else str+=c;
            }

            Token tk;

            tk.type=TokenType::String;
            tk.s_val=str;

            code_cnt++;

            token_list.push_back(tk);
        }

        if(check_size())
        {
            break;
        }
    }

    Token end;

    end.type=TokenType::End_Token;

    token_list.push_back(end);
}

inline bool Lexer::check_size()
{
    if(code_cnt<=code.size())return false;
    else return true;
}

inline char Lexer::next_char()
{
    char c=code[code_cnt];

    code_cnt++;

    return c;
}

void Lexer::init_token_map()
{
    token_map["push_i"]=TokenType::Push_I;
    token_map["push_f"]=TokenType::Push_F;
    token_map["push_s"]=TokenType::Push_S;
    token_map["push_b"]=TokenType::Push_B;
    token_map["add_i"]=TokenType::Add_I;
    token_map["add_f"]=TokenType::Add_F;
    token_map["add_s"]=TokenType::Add_S;
    token_map["sub_i"]=TokenType::Sub_I;
    token_map["sub_f"]=TokenType::Sub_F;
    token_map["mul_i"]=TokenType::Mul_I;
    token_map["mul_f"]=TokenType::Mul_F;
    token_map["div_i"]=TokenType::Div_I;
    token_map["div_f"]=TokenType::Div_F;
    token_map["mod_i"]=TokenType::Mod_I;
    token_map["l_i"]=TokenType::L_I;
    token_map["l_f"]=TokenType::L_F;
    token_map["le_i"]=TokenType::Le_I;
    token_map["le_f"]=TokenType::Le_F;
    token_map["g_i"]=TokenType::G_I;
    token_map["g_f"]=TokenType::G_F;
    token_map["ge_i"]=TokenType::Ge_I;
    token_map["ge_f"]=TokenType::Ge_F;
    token_map["e_i"]=TokenType::E_I;
    token_map["e_f"]=TokenType::E_F;
    token_map["ne_i"]=TokenType::Ne_I;
    token_map["ne_f"]=TokenType::Ne_F;
    token_map["g_load_i"]=TokenType::G_Load_I;
    token_map["g_load_f"]=TokenType::G_Load_F;
    token_map["g_load_s"]=TokenType::G_Load_S;
    token_map["g_load_b"]=TokenType::G_Load_B;
    token_map["g_store_i"]=TokenType::G_Store_I;
    token_map["g_store_f"]=TokenType::G_Store_F;
    token_map["g_store_s"]=TokenType::G_Store_S;
    token_map["g_store_b"]=TokenType::G_Store_B;
    token_map["output"]=TokenType::Output;
    token_map["input"]=TokenType::Input;
}

void Lexer::skip_space()
{
    char c=code[code_cnt];

    if(c=='\n')
    {
        code_cnt++;
    }
    else
    {
        while(isspace(c))
        {
            c=next_char();
        }
    }
}

void Lexer::error(std::string msg)
{
    std::cerr<<msg<<std::endl;
    exit(1);
}