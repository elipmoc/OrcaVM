#include "OrcaVM.hpp"
#include "Lexer.hpp"
#include "JIT.hpp"

JIT::JIT(const std::vector<Token>& token_list)
{
    this->token_list=token_list;
}

void JIT::parse()
{
    bool loop_f=false;

    static Token tk;

    for(;;)
    {
        tk=next_token();

        switch(tk.type)
        {
            case TokenType::Push_I:

                tk=next_token();

                gen.push_i(std::to_string(tk.i_val));

                break;

            case TokenType::Push_F:

                tk=next_token();

                gen.push_f(std::to_string(tk.f_val));

                break;

            case TokenType::Push_S:

                tk=next_token();

                gen.push_s(tk.s_val);

                break;

            case TokenType::Push_B:

                tk=next_token();

                gen.push_b(tk.b_val ? std::to_string(1) : std::to_string(0));

                break;

            case TokenType::Add_I:

                gen.add_i();

                break;

            case TokenType::Output:

                gen.output();

                break;

            case TokenType::Func_Start:

                tk=next_token();

                if(tk.s_val!="main")
                {
                    gen.def_func(tk.s_val);
                }
                else gen.def_main();

                parse();

                gen.end_func();

                break;

            case TokenType::Func_End: return;

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

inline Token JIT::next_token()
{
    Token tk=token_list[code_counter];

    code_counter++;
    
    return tk;
}

void JIT::execute()
{
    write_code(gen.get_code());

    system("gcc -o temp/bin temp/temp.c");
    system("./temp/bin");
}

void JIT::write_code(std::string s)
{
    std::ofstream o("temp/temp.c");
    o<<s;
    o.close();
}

std::string JITCodeGenerator::get_code()
{
    return code;
}

JITCodeGenerator::JITCodeGenerator()
{
    code += "#include <stdio.h>\n";
    code += "#include <string.h>\n";
    code += "typedef struct{\n";
    code += "int i_val;\n";
    code += "double f_val;\n";
    code += "char s_val[100];\n";
    code += "int b_val;\n";
    code += "}Stack;\n";
    code += "Stack st[100000];\n";
    code += "Stack s;\n";
    code += "int i;\n";
    code += "int counter = 0;\n";
    code += "Stack pop(){\ncounter--;\nStack t = st[counter];\nreturn t;\n}\n";
    code += "void push(Stack stk)\n{\nst[counter]=stk;\ncounter++;\n}\n";
}

void JITCodeGenerator::def_func(std::string name)
{
    code += "void ";
    code += name;
    code += "(){\n";
}

void JITCodeGenerator::end_func()
{
    code += "}\n";
}

void JITCodeGenerator::def_main()
{
    code += "void main(){\n";

    main_f=true;
}

void JITCodeGenerator::push_i(std::string i_val)
{
    code += "s.i_val ="+i_val+";\n";
    code += "push(s);\n";
}

void JITCodeGenerator::push_f(std::string f_val)
{
    code += "s.f_val ="+f_val+";\n";
    code += "push(s);\n";
}

void JITCodeGenerator::push_s(std::string s_val)
{
    std::string o_code;

    for(size_t i=0;i<s_val.length();i++)
    {
        if(s_val[i]=='\n')
        {
            o_code+="\\n";
        }
        else
        {
            o_code+=s_val[i];
        }
    }

    code += "strcpy(s.s_val,\"" + o_code + "\");\n";
    code += "push(s);\n";
}

void JITCodeGenerator::push_b(std::string b_val)
{
    code += "s.b_val="+b_val+";\n";
    code += "push(s);\n";
}

void JITCodeGenerator::add_i()
{
    code += "i = pop().i_val + pop().i_val;\n";
    code += "s.i_val = i;\npush(s);\n";
}

void JITCodeGenerator::output()
{
    code += "s = pop();\n";
    code += "printf(\"%s\",s.s_val);\n";
}