#include "OrcaVM.hpp"
#include "Gencode.hpp"

int CodeGenerator::now_count()
{
    return code.size()-1;
}

void CodeGenerator::backpatch_addr(int addr,int val)
{
    code[addr].opr_i=val;
}

void CodeGenerator::AddCode(InstructionCodeType type)
{
    InstructionCode add_code;

    add_code.type=type;

    code.push_back(add_code);
}

void CodeGenerator::AddCode(InstructionCodeType type,const int i_val)
{
    InstructionCode add_code;

    add_code.type=type;
    add_code.opr_i=i_val;

    code.push_back(add_code);
}

void CodeGenerator::AddCode(InstructionCodeType type,const double f_val)
{
    InstructionCode add_code;

    add_code.type=type;
    add_code.opr_f=f_val;

    code.push_back(add_code);
}

void CodeGenerator::AddCode(InstructionCodeType type,const std::string s_val)
{
    InstructionCode add_code;

    add_code.type=type;
    add_code.opr_s=s_val;

    code.push_back(add_code);
}

void CodeGenerator::AddCode(InstructionCodeType type,const bool b_val)
{
    InstructionCode add_code;

    add_code.type=type;
    add_code.opr_b=b_val;

    code.push_back(add_code);
}

std::vector<InstructionCode>& CodeGenerator::get_code()
{
    return code;
}