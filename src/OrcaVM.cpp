#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"

int main(int argc,char **argv)
{
    int opt=0;

    bool dump_stack_flag=false;

    bool file_read_flag=false;

    char *filename;

    if(argc>1)
    {
        while((opt=getopt(argc,argv,"do:"))!=-1) //オプションの解析
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

                default:
                    break;
            }
        }
    }

    if(file_read_flag)
    {
        ExecuteCode exec(generator.get_code(),0);

        exec.execute();

        if(dump_stack_flag)exec.dump_stack();
    }

    return 0;
}