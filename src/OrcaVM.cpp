#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

void dump_code(std::vector<InstructionCode> code_list)
{
    std::cout<<"*** code dump start ***\n"<<std::endl;

    for(auto code:code_list)
    {
        switch(code.type)
        {
            case InstructionCodeType::Push_I: std::cout<<"[push_i] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Push_F: std::cout<<"[push_f] : "<<code.opr_f<<std::endl; break;
            case InstructionCodeType::Push_S: std::cout<<"[push_s] : "<<code.opr_s<<std::endl; break;
            case InstructionCodeType::Push_B: std::cout<<"[push_b] : "<<code.opr_b<<std::endl; break;
            case InstructionCodeType::Add_I: std::cout<<"[add_i]"<<std::endl; break;
            case InstructionCodeType::Add_F: std::cout<<"[add_f]"<<std::endl; break;
            case InstructionCodeType::Add_S: std::cout<<"[add_s]"<<std::endl; break;
            case InstructionCodeType::Sub_I: std::cout<<"[sub_i]"<<std::endl; break;
            case InstructionCodeType::Sub_F: std::cout<<"[sub_f]"<<std::endl; break;
            case InstructionCodeType::Mul_I: std::cout<<"[mul_i]"<<std::endl; break;
            case InstructionCodeType::Mul_F: std::cout<<"[mul_f]"<<std::endl; break;
            case InstructionCodeType::Div_I: std::cout<<"[div_i]"<<std::endl; break;
            case InstructionCodeType::Div_F: std::cout<<"[div_f]"<<std::endl; break;
            case InstructionCodeType::Mod_I: std::cout<<"[mod_i]"<<std::endl; break;
            case InstructionCodeType::L_I: std::cout<<"[L_I]"<<std::endl; break;
            case InstructionCodeType::L_F: std::cout<<"[L_F]"<<std::endl; break;
            case InstructionCodeType::G_I: std::cout<<"[G_I]"<<std::endl; break;
            case InstructionCodeType::G_F: std::cout<<"[G_F]"<<std::endl; break;
            case InstructionCodeType::LE_I: std::cout<<"[LE_I]"<<std::endl; break;
            case InstructionCodeType::LE_F: std::cout<<"[LE_F]"<<std::endl; break;
            case InstructionCodeType::GE_I: std::cout<<"[GE_I]"<<std::endl; break;
            case InstructionCodeType::GE_F: std::cout<<"[GE_F]"<<std::endl; break;
            case InstructionCodeType::E_I: std::cout<<"[E_I]"<<std::endl; break;
            case InstructionCodeType::E_F: std::cout<<"[E_F]"<<std::endl; break;
            case InstructionCodeType::NE_I: std::cout<<"[NE_I]"<<std::endl; break;
            case InstructionCodeType::NE_F: std::cout<<"[NE_F]"<<std::endl; break;
            case InstructionCodeType::Jump: std::cout<<"[Jump] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Jump_True: std::cout<<"[Jump_True] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Jump_False: std::cout<<"[Jump_False] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::Output: std::cout<<"[Output]"<<std::endl; break;
            case InstructionCodeType::Input: std::cout<<"[Input]"<<std::endl; break;
            case InstructionCodeType::G_Store_I: std::cout<<"[G_Store_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Store_F: std::cout<<"[G_Store_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Store_S: std::cout<<"[G_Store_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Store_B: std::cout<<"[G_Store_B] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_I: std::cout<<"[G_Load_I] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_F: std::cout<<"[G_Load_F] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_S: std::cout<<"[G_Load_S] : "<<code.opr_i<<std::endl; break;
            case InstructionCodeType::G_Load_B: std::cout<<"[G_Load_B] : "<<code.opr_i<<std::endl; break;
            default: std::cerr<<"code dump error"<<std::endl; exit(1);
        }
    }

    std::cout<<"*** code dump end ***\n"<<std::endl;
}

int main(int argc,char **argv)
{
    int opt=0;

    bool dump_stack_flag=false;

    bool dump_code_flag=false;

    bool file_read_flag=false;

    char *filename;

    if(argc>1)
    {
        while((opt=getopt(argc,argv,"dco:"))!=-1) //オプションの解析
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

        if(dump_code_flag)
        {
            dump_code(parser.get_code().get_code());
        }

        ExecuteCode exec(parser.get_code().get_code(),0);

        exec.execute();

        if(dump_stack_flag)exec.dump_stack();
    }

    return 0;
}