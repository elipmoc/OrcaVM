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

        std::vector<InstructionCode>& get_code();
};

#endif