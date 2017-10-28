#include "OrcaVM.hpp"
#include "Execute.hpp"

ExecuteCode::ExecuteCode(const std::vector<InstructionCode>& code,const int entry_point)
{
    this->code_counter=entry_point;
    this->code=code;
}

void ExecuteCode::execute()
{
    
}