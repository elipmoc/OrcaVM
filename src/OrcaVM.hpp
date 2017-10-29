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

    Add_I,Add_F,

    Sub_I,Sub_F,

    Mul_I,Mul_F,

    Div_I,Div_F,

    Mod_I,

    Output,Input,

    Jump,Jump_True,Jump_False,
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