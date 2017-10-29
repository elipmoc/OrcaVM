#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"

int main(int argc,char **argv)
{
    int opt=0;

    bool dump_stack_flag=false;

    if(argc>1)
    {
        while((opt=getopt(argc,argv,"do:"))!=-1) //オプションの解析
        {
            switch(opt)
            {
                case 'o':
                    std::cout<<optarg<<std::endl;
                    break;

                case 'd':
                    dump_stack_flag=true;
                    break;

                default:
                    break;
            }
        }
    }

    CodeGenerator generator;

    generator.AddCode(InstructionCodeType::Push_I,3);
    generator.AddCode(InstructionCodeType::Push_I,2);
    generator.AddCode(InstructionCodeType::G_I);

    ExecuteCode exec(generator.get_code(),0);

    exec.execute();

    if(dump_stack_flag)exec.dump_stack();

    return 0;
}