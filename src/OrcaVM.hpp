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

    ItoC,CtoI,

    Or,And,

    G_Store_I,G_Store_F,G_Store_S,G_Store_B,G_Store_A,

    G_Load_I,G_Load_F,G_Load_S,G_Load_B,G_Load_A,

    Store_I,Store_F,Store_S,Store_B,Store_A,

    Load_I,Load_F,Load_S,Load_B,Load_A,

    G_AStore_I,G_AStore_F,G_AStore_S,G_AStore_B,G_AStore_A,

    G_ALoad_I,G_ALoad_F,G_ALoad_S,G_ALoad_B,G_ALoad_A,

    AStore_I,AStore_F,AStore_S,AStore_B,AStore_A,

    ALoad_I,ALoad_F,ALoad_S,ALoad_B,ALoad_A,

    Return,

    Invoke,

    Push_Return_Stack,

    Set_Stack_Size,

    Exit,
};

struct InstructionCode //命令コード
{
        InstructionCodeType type;

        int opr_i=0;
        double opr_f=0.0;
        std::string opr_s="";
        bool opr_b=false;
};

#endif