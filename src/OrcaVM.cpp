#include "OrcaVM.hpp"

int main(int argc,char **argv)
{
    int opt=0;

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

    return 0;
}