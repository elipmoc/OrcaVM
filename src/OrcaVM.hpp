#ifndef ORCAVM_HPP
#define ORCAVM_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

#define Debug

enum class InstructionCodeType //命令コードの種類
{
    Push_I,Push_F,Push_S,Push_B,
    AddI,AddF,
};

struct InstructionCode //命令コード
{
        InstructionCodeType type;

        int opr_i;
        double opr_f;
        std::string opr_s;
        bool opr_b;
};

#endif