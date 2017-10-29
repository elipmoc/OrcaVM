#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"

int main(int argc,char **argv)
{
    int opt=0;

    if(argc>1)
    {
        while((opt=getopt(argc,argv,"o:"))!=1) //オプションの解析
        {
            switch(opt)
            {
                case 'o':
                    std::cout<<optarg<<std::endl;
                    break;

                default:
                    std::cout<<"invalid option"<<std::endl;
                    opterr=1;
                    break;
            }
        }
    }

    CodeGenerator generator;

    generator.AddCode(InstructionCodeType::Input);
    generator.AddCode(InstructionCodeType::Output);

    ExecuteCode exec(generator.get_code(),0);

    exec.execute();

    return 0;
}