#ifndef EXECUTE_HPP
#define EXECUTE_HPP

class ExecuteCode
{
    private:

        int code_counter;
        
        std::vector<InstructionCode> code;

    public:

        ExecuteCode(const std::vector<InstructionCode>&,const int);

        void execute();
};

#endif