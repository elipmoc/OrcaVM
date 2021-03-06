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
        else if(isalpha(c) || c=='.')
        {
            std::string ident_str;
            Token tk;

            for(;isalpha(c) || c=='_' || isdigit(c) || c==':' || c=='.';c=next_char())
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
        else if(c=='@')
        {
            std::string label_str;

            for(c=next_char();isdigit(c) || isalpha(c);c=next_char())
            {
                label_str+=c;
            }

            Token tk;

            tk.type=TokenType::Label;
            tk.s_val=label_str;

            token_list.push_back(tk);
        }
        else if(c=='$')
        {
            std::string var_str;

            for(c=next_char();isdigit(c) || isalpha(c) || c=='_';c=next_char())var_str+=c;

            Token tk;

            tk.type=TokenType::VarName;
            tk.s_val=var_str;

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
    token_map["e_s"]=TokenType::E_S;
    token_map["ne_i"]=TokenType::Ne_I;
    token_map["ne_f"]=TokenType::Ne_F;
    token_map["or"]=TokenType::Or;
    token_map["and"]=TokenType::And;
    token_map["g_load_i"]=TokenType::G_Load_I;
    token_map["g_load_f"]=TokenType::G_Load_F;
    token_map["g_load_s"]=TokenType::G_Load_S;
    token_map["g_load_b"]=TokenType::G_Load_B;
    token_map["g_load_a"]=TokenType::G_Load_A;
    token_map["g_store_i"]=TokenType::G_Store_I;
    token_map["g_store_f"]=TokenType::G_Store_F;
    token_map["g_store_s"]=TokenType::G_Store_S;
    token_map["g_store_b"]=TokenType::G_Store_B;
    token_map["g_store_a"]=TokenType::G_Store_A;
    token_map["load_i"]=TokenType::Load_I;
    token_map["load_f"]=TokenType::Load_F;
    token_map["load_s"]=TokenType::Load_S;
    token_map["load_b"]=TokenType::Load_B;
    token_map["load_a"]=TokenType::Load_A;
    token_map["store_i"]=TokenType::Store_I;
    token_map["store_f"]=TokenType::Store_F;
    token_map["store_s"]=TokenType::Store_S;
    token_map["store_b"]=TokenType::Store_B;
    token_map["store_a"]=TokenType::Store_A;
    token_map["g_aload_i"]=TokenType::G_ALoad_I;
    token_map["g_aload_f"]=TokenType::G_ALoad_F;
    token_map["g_aload_s"]=TokenType::G_ALoad_S;
    token_map["g_aload_b"]=TokenType::G_ALoad_B;
    token_map["g_aload_a"]=TokenType::G_ALoad_A;
    token_map["g_astore_i"]=TokenType::G_AStore_I;
    token_map["g_astore_f"]=TokenType::G_AStore_F;
    token_map["g_astore_s"]=TokenType::G_AStore_S;
    token_map["g_astore_b"]=TokenType::G_AStore_B;
    token_map["g_astore_a"]=TokenType::G_AStore_A;
    token_map["aload_i"]=TokenType::ALoad_I;
    token_map["aload_f"]=TokenType::ALoad_F;
    token_map["aload_s"]=TokenType::ALoad_S;
    token_map["aload_b"]=TokenType::ALoad_B;
    token_map["aload_a"]=TokenType::ALoad_A;
    token_map["astore_i"]=TokenType::AStore_I;
    token_map["astore_f"]=TokenType::AStore_F;
    token_map["astore_s"]=TokenType::AStore_S;
    token_map["astore_b"]=TokenType::AStore_B;
    token_map["astore_a"]=TokenType::AStore_A;
    token_map["output"]=TokenType::Output;
    token_map["input"]=TokenType::Input;
    token_map["jump"]=TokenType::Jump;
    token_map["jump_true"]=TokenType::Jump_True;
    token_map["jump_false"]=TokenType::Jump_False;
    token_map["label:"]=TokenType::Def_Label;
    token_map[".if"]=TokenType::If;
    token_map[".else"]=TokenType::Else;
    token_map[".endif"]=TokenType::EndIf;
    token_map["itof"]=TokenType::ItoF;
    token_map["itos"]=TokenType::ItoS;
    token_map["ftoi"]=TokenType::FtoI;
    token_map["ftos"]=TokenType::FtoS;
    token_map["stoi"]=TokenType::StoI;
    token_map["stof"]=TokenType::StoF;
    token_map["itoc"]=TokenType::ItoC;
    token_map["ctoi"]=TokenType::CtoI;
    token_map[".loop"]=TokenType::Loop_Start;
    token_map[".loop_end"]=TokenType::Loop_End;
    token_map[".break"]=TokenType::Break;
    token_map[".func"]=TokenType::Func_Start;
    token_map[".func_end"]=TokenType::Func_End;
    token_map["return"]=TokenType::Return;
    token_map["invoke"]=TokenType::Invoke;
    token_map[".stack_size"]=TokenType::Stack_Size;
    token_map[".entry_point"]=TokenType::Entry_Point;
    token_map["def"]=TokenType::DefVar;
    token_map[".exit"]=TokenType::Exit;
}

void Lexer::skip_space()
{
    char c=code[code_cnt];

    if(c=='\n' || c=='\t')
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