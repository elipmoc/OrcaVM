#include "OrcaVM.hpp"
#include "Gencode.hpp"
#include "Execute.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

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

        ExecuteCode exec(parser.get_code().get_code(),0);

        exec.execute();

        if(dump_stack_flag)exec.dump_stack();
    }

    return 0;
}