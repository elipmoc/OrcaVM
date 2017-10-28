#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"

int main(int argc,char **argv)
{
    int opt=0;

    #ifndef Debug

    while((opt=getopt(argc,argv,"o:"))!=1) //オプションの解析
    {
        switch(opt)
        {
            case 'o':
                std::cout<<optarg<<std::endl;
                break;

            default:
                std::cerr<<"不正なオプションです"<<std::endl;
                return -1;
        }
    }

    #endif

    CodeGenerator generator;

    generator.AddCode(InstructionCodeType::Push_I,10);
    generator.AddCode(InstructionCodeType::Push_I,30);
    generator.AddCode(InstructionCodeType::AddI);

    ExecuteCode exec(generator.get_code(),0);

    exec.execute();

    return 0;
}