#ifndef GENCODE_HPP
#define GENCODE_HPP

class CodeGenerator
{
    private:

        std::vector<InstructionCode> code;

    public:

        void AddCode(InstructionCodeType);
        void AddCode(InstructionCodeType,const int);
        void AddCode(InstructionCodeType,const double);
        void AddCode(InstructionCodeType,const std::string);
        void AddCode(InstructionCodeType,const bool);

        int now_count();

        void backpatch_addr(int,int);

        std::vector<InstructionCode>& get_code();
};

#endif