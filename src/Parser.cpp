#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

Parser::Parser(std::vector<Token> tk)
{
    this->token_list=tk;

    static_memory_sim=new bool[Static_Memory_Size];
}

Parser::~Parser()
{
    delete[] static_memory_sim;
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

    static int in_func=0;

    static std::stack<std::vector<int>> loop_end_addr;

    static std::stack<std::string> now_func;

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
            case TokenType::E_S:
                gen.AddCode(InstructionCodeType::E_S);
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

                break;

            case TokenType::G_Load_I:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Load_I,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Load_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Load_F,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Load_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Load_S,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Load_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Load_B,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Load_A:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Load_A,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Store_I:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Store_I,global_var_addr[tk.s_val]);
                
                break;

            case TokenType::G_Store_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Store_F,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Store_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Store_S,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Store_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Store_B,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_Store_A:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_Store_A,global_var_addr[tk.s_val]);

                break;

            case TokenType::Load_I:
                
                tk=next_token();
                
                gen.AddCode(InstructionCodeType::Load_I,local_var_addr.top()[tk.s_val]);

                break;
                
            case TokenType::Load_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Load_F,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Load_S:
                
                tk=next_token();
                
                gen.AddCode(InstructionCodeType::Load_S,local_var_addr.top()[tk.s_val]);
                
                break;

            case TokenType::Load_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Load_B,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Load_A:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Load_A,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Store_I:
                
                tk=next_token();
                
                gen.AddCode(InstructionCodeType::Store_I,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Store_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Store_F,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Store_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Store_S,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Store_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Store_B,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::Store_A:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Store_A,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::G_ALoad_I:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_ALoad_I,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_ALoad_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_ALoad_F,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_ALoad_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_ALoad_S,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_ALoad_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_ALoad_B,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_AStore_I:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_AStore_I,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_AStore_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_AStore_F,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_AStore_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_AStore_S,global_var_addr[tk.s_val]);

                break;

            case TokenType::G_AStore_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::G_AStore_B,global_var_addr[tk.s_val]);

                break;

            case TokenType::AStore_I:

                tk=next_token();

                gen.AddCode(InstructionCodeType::AStore_I,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::AStore_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::AStore_F,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::AStore_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::AStore_S,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::AStore_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::AStore_B,local_var_addr.top()[tk.s_val]);

                break;

            case TokenType::ALoad_I:

                tk=next_token();

                gen.AddCode(InstructionCodeType::ALoad_I,local_var_addr.top()[tk.s_val]);
                
                break;

            case TokenType::ALoad_F:

                tk=next_token();

                gen.AddCode(InstructionCodeType::ALoad_F,local_var_addr.top()[tk.s_val]);
                
                break;

            case TokenType::ALoad_S:

                tk=next_token();

                gen.AddCode(InstructionCodeType::ALoad_S,local_var_addr.top()[tk.s_val]);
                
                break;

            case TokenType::ALoad_B:

                tk=next_token();

                gen.AddCode(InstructionCodeType::ALoad_B,local_var_addr.top()[tk.s_val]);
                
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

            case TokenType::DefVar:
            {
                tk=next_token();

                std::string var_name=tk.s_val;

                tk=next_token();

                if(in_func==0)
                {
                    global_var_addr[var_name]=get_addr_static();

                    for(int i=0;i<tk.i_val;++i)static_memory_sim[global_var_addr[var_name]+i]=true;
                }
                else
                {
                    local_var_addr.top()[var_name]=get_addr_stack();

                    for(int i=0;i<tk.i_val;++i)stack_memory_sim.top()[local_var_addr.top()[var_name]+i]=true;
                }

                break;
            }

            case TokenType::If:
            {
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
            }

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

            case TokenType::Func_Start:
            {
                
                tk=next_token();

                func_addr[tk.s_val]=gen.now_count();

                backpatch_f(tk.s_val,func_addr[tk.s_val]);
                
                in_func++;
                
                std::array<bool,Call_Stack_Size> sim;
                std::unordered_map<std::string,int> new_local;

                stack_memory_sim.push(sim);

                local_var_addr.push(new_local);

                parse();

                local_var_addr.pop();

                stack_memory_sim.pop();

                in_func--;

                gen.AddCode(InstructionCodeType::Return);

                break;
            }

            case TokenType::Func_End:
                return;

            case TokenType::Exit:

                gen.AddCode(InstructionCodeType::Exit);

                break;

            case TokenType::Invoke:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Push_Return_Stack,gen.now_count()+2);

                if(func_addr.count(tk.s_val)==0)
                {
                    gen.AddCode(InstructionCodeType::Invoke,-1);
                    backpatch_func[tk.s_val].push_back(gen.now_count());
                }
                else gen.AddCode(InstructionCodeType::Invoke,func_addr[tk.s_val]);

                break;

            case TokenType::Stack_Size:

                tk=next_token();

                gen.AddCode(InstructionCodeType::Set_Stack_Size,tk.i_val);

                break;

            case TokenType::Return:

                gen.AddCode(InstructionCodeType::Return);

                break;

            case TokenType::Break:

                gen.AddCode(InstructionCodeType::Jump,-1);

                loop_end_addr.top().push_back(gen.now_count());

                break;

            case TokenType::End_Token:

                loop_f=true;

                break;

            case TokenType::Entry_Point:

                entry_point=gen.now_count();

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

void Parser::backpatch_f(std::string name,int addr)
{
    for(auto place:backpatch_func[name])
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

int Parser::get_addr_stack()
{
    for(int i=0;i<Call_Stack_Size;++i)
    {
        if(stack_memory_sim.top()[i]==false)
        {
            return i;
        }
    }

    return 0;
}

int Parser::get_addr_static()
{
    for(int i=0;i<Static_Memory_Size;++i)
    {
        if(static_memory_sim[i]==false)
        {
            return i;
        }
    }

    return 0;
}