#ifndef ORCAVM_HPP
#define ORCAVM_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <array>
#include <ctype.h>

//#define Debug

#define Static_Memory_Size 100000

#define Call_Stack_Size 100000

#define Return_Stack_Size 100000

enum class InstructionCodeType //命令コードの種類
{
    Push_I,Push_F,Push_S,Push_B,

    Add_I,Add_F,Add_S,

    Sub_I,Sub_F,

    Mul_I,Mul_F,

    Div_I,Div_F,

    Mod_I,

    Output,Input,

    Jump,Jump_True,Jump_False,

    L_I,L_F,
    
    LE_I,LE_F,

    G_I,G_F,
    
    GE_I,GE_F,

    E_I,E_F,E_S,

    NE_I,NE_F,

    ItoF,ItoS,

    FtoI,FtoS,

    StoI,StoF,

    Or,And,

    G_Store_I,G_Store_F,G_Store_S,G_Store_B,

    G_Load_I,G_Load_F,G_Load_S,G_Load_B,

    Store_I,Store_F,Store_S,Store_B,

    Load_I,Load_F,Load_S,Load_B,

    Return,

    Invoke,

    Push_Return_Stack,

    Set_Stack_Size,
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