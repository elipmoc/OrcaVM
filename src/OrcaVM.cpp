#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

void dump_code(std::vector<InstructionCode> code_list)
{
    std::cout<<"*** code dump start ***\n"<<std::endl;

    unsigned int code_cnt=0;

    for(auto code:code_list)
    {
        switch(code.type)
        {
            case InstructionCodeType::Push_I: std::cout<<code_cnt<<" : [push_i] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Push_F: std::cout<<code_cnt<<" : [push_f] : "<<code.opr_f<<std::endl; break;
            case InstructionCodeType::Push_S: std::cout<<code_cnt<<" : [push_s] : "<<code.opr_s<<std::endl; break;
            case InstructionCodeType::Push_B: std::cout<<code_cnt<<" : [push_b] : "<<code.opr_b<<std::endl; break;
            case InstructionCodeType::Add_I: std::cout<<code_cnt<<" : [add_i]"<<std::endl; break;
            case InstructionCodeType::Add_F: std::cout<<code_cnt<<" : [add_f]"<<std::endl; break;
            case InstructionCodeType::Add_S: std::cout<<code_cnt<<" : [add_s]"<<std::endl; break;
            case InstructionCodeType::Sub_I: std::cout<<code_cnt<<" : [sub_i]"<<std::endl; break;
            case InstructionCodeType::Sub_F: std::cout<<code_cnt<<" : [sub_f]"<<std::endl; break;
            case InstructionCodeType::Mul_I: std::cout<<code_cnt<<" : [mul_i]"<<std::endl; break;
            case InstructionCodeType::Mul_F: std::cout<<code_cnt<<" : [mul_f]"<<std::endl; break;
            case InstructionCodeType::Div_I: std::cout<<code_cnt<<" : [div_i]"<<std::endl; break;
            case InstructionCodeType::Div_F: std::cout<<code_cnt<<" : [div_f]"<<std::endl; break;
            case InstructionCodeType::Mod_I: std::cout<<code_cnt<<" : [mod_i]"<<std::endl; break;
            case InstructionCodeType::L_I: std::cout<<code_cnt<<" : [L_I]"<<std::endl; break;
            case InstructionCodeType::L_F: std::cout<<code_cnt<<" : [L_F]"<<std::endl; break;
            case InstructionCodeType::G_I: std::cout<<code_cnt<<" : [G_I]"<<std::endl; break;
            case InstructionCodeType::G_F: std::cout<<code_cnt<<" : [G_F]"<<std::endl; break;
            case InstructionCodeType::LE_I: std::cout<<code_cnt<<" : [LE_I]"<<std::endl; break;
            case InstructionCodeType::LE_F: std::cout<<code_cnt<<" : [LE_F]"<<std::endl; break;
            case InstructionCodeType::GE_I: std::cout<<code_cnt<<" : [GE_I]"<<std::endl; break;
            case InstructionCodeType::GE_F: std::cout<<code_cnt<<" : [GE_F]"<<std::endl; break;
            case InstructionCodeType::E_I: std::cout<<code_cnt<<" : [E_I]"<<std::endl; break;
            case InstructionCodeType::E_F: std::cout<<code_cnt<<" : [E_F]"<<std::endl; break;
            case InstructionCodeType::E_S: std::cout<<code_cnt<<" : [E_S]"<<std::endl; break;
            case InstructionCodeType::NE_I: std::cout<<code_cnt<<" : [NE_I]"<<std::endl; break;
            case InstructionCodeType::NE_F: std::cout<<code_cnt<<" : [NE_F]"<<std::endl; break;
            case InstructionCodeType::Or: std::cout<<code_cnt<<" : [OR]"<<std::endl; break;
            case InstructionCodeType::And: std::cout<<code_cnt<<" : [AND]"<<std::endl; break;
            case InstructionCodeType::Jump: std::cout<<code_cnt<<" : [Jump] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Jump_True: std::cout<<code_cnt<<" : [Jump_True] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Jump_False: std::cout<<code_cnt<<" : [Jump_False] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Output: std::cout<<code_cnt<<" : [Output]"<<std::endl; break;
            case InstructionCodeType::Input: std::cout<<code_cnt<<" : [Input]"<<std::endl; break;
            case InstructionCodeType::G_Store_I: std::cout<<code_cnt<<" : [G_Store_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Store_F: std::cout<<code_cnt<<" : [G_Store_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Store_S: std::cout<<code_cnt<<" : [G_Store_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Store_B: std::cout<<code_cnt<<" : [G_Store_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_I: std::cout<<code_cnt<<" : [G_Load_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_F: std::cout<<code_cnt<<" : [G_Load_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_S: std::cout<<code_cnt<<" : [G_Load_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_B: std::cout<<code_cnt<<" : [G_Load_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Store_I: std::cout<<code_cnt<<" : [Store_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Store_F: std::cout<<code_cnt<<" : [Store_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Store_S: std::cout<<code_cnt<<" : [Store_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Store_B: std::cout<<code_cnt<<" : [Store_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Load_I: std::cout<<code_cnt<<" : [Load_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Load_F: std::cout<<code_cnt<<" : [Load_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Load_S: std::cout<<code_cnt<<" : [Load_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Load_B: std::cout<<code_cnt<<" : [Load_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_AStore_I: std::cout<<code_cnt<<" : [G_AStore_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_AStore_F: std::cout<<code_cnt<<" : [G_AStore_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_AStore_S: std::cout<<code_cnt<<" : [G_AStore_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_AStore_B: std::cout<<code_cnt<<" : [G_AStore_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_ALoad_I: std::cout<<code_cnt<<" : [G_ALoad_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_ALoad_F: std::cout<<code_cnt<<" : [G_ALoad_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_ALoad_S: std::cout<<code_cnt<<" : [G_ALoad_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_ALoad_B: std::cout<<code_cnt<<" : [G_ALoad_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::AStore_I: std::cout<<code_cnt<<" : [AStore_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::AStore_F: std::cout<<code_cnt<<" : [AStore_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::AStore_S: std::cout<<code_cnt<<" : [AStore_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::AStore_B: std::cout<<code_cnt<<" : [AStore_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::ALoad_I: std::cout<<code_cnt<<" : [ALoad_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::ALoad_F: std::cout<<code_cnt<<" : [ALoad_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::ALoad_S: std::cout<<code_cnt<<" : [ALoad_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::ALoad_B: std::cout<<code_cnt<<" : [ALoad_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::ItoF: std::cout<<code_cnt<<" : [ItoF]"<<std::endl; break;
            case InstructionCodeType::ItoS: std::cout<<code_cnt<<" : [ItoS]"<<std::endl; break;
            case InstructionCodeType::FtoI: std::cout<<code_cnt<<" : [FtoI]"<<std::endl; break;
            case InstructionCodeType::FtoS: std::cout<<code_cnt<<" : [FtoS]"<<std::endl; break;
            case InstructionCodeType::StoI: std::cout<<code_cnt<<" : [StoI]"<<std::endl; break;
            case InstructionCodeType::StoF: std::cout<<code_cnt<<" : [StoF]"<<std::endl; break;
            case InstructionCodeType::Invoke: std::cout<<code_cnt<<" : [Invoke] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Return: std::cout<<code_cnt<<" : [Return]"<<std::endl; break;
            case InstructionCodeType::Push_Return_Stack: std::cout<<code_cnt<<" : [Push_Return_Stack] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Set_Stack_Size: std::cout<<code_cnt<<" : [Set_Stack_Size] : "<<code.opr_i<<std::endl; break;
            default: std::cerr<<"code dump error"<<std::endl; exit(1);
        }

        code_cnt++;
    }

    std::cout<<"*** code dump end ***\n"<<std::endl;
}

int main(int argc,char **argv)
{
    int opt=0;

    bool dump_stack_flag=false;

    bool dump_code_flag=false;

    bool entry_point_flag=false;

    bool file_read_flag=false;

    char *filename;

    if(argc>1)
    {
        while((opt=getopt(argc,argv,"dceo:"))!=-1) //オプションの解析
        {
            switch(opt)
            {
                case 'o':
                    filename=optarg;
                    file_read_flag=true;
                    break;

                case 'd':
                    dump_stack_flag=true;
                    break;

                case 'c':
                    dump_code_flag=true;
                    break;

                case 'e':
                    entry_point_flag=true;
                    break;

                default:
                    break;
            }
        }
    }

    if(file_read_flag)
    {
        FILE *fp=fopen(filename,"r");
        char data[100];
        std::string file_code;

        if(fp==NULL)
        {
            std::cerr<<"\'"<<filename<<"\' ファイルをオープンできません"<<std::endl;
            return -1;
        }

        while(fgets(data,100,fp))
        {
            file_code+=std::string(data);
        }

        Lexer lexer(file_code);

        lexer.start();

        Parser parser(lexer.get_token());

        parser.parse();

        if(entry_point_flag)
        {
            std::cout<<"entry_point : "<<parser.entry_point+1<<std::endl;
        }

        if(dump_code_flag)
        {
            dump_code(parser.get_code().get_code());
        }

        ExecuteCode exec(parser.get_code().get_code(),parser.entry_point+1);

        exec.execute();

        if(dump_stack_flag)exec.dump_stack();
    }

    return 0;
}