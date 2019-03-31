#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace{
  struct OpcodeCounter : public FunctionPass{
    static char ID;
	OpcodeCounter() : FunctionPass(ID){}

	bool runOnFunction(Function &F) override {
		std::map<std::string, int>opcode_map;
		errs() << "函数名：";
		errs() << F.getName() << '\n';

		for(Function::iterator bb = F.begin(), e = F.end(); bb!=e ; bb++)
		{
			for(BasicBlock::iterator i = bb->begin(),i2 = bb->end(); i!=i2; i++)
			{
				if(opcode_map.find(i->getOpcodeName()) == opcode_map.end())
					opcode_map[i->getOpcodeName()] = 1;
				else
					opcode_map[i->getOpcodeName()] +=1;
			}
		}

		std::map<std::string, int> :: iterator p_start = opcode_map.begin();
		std::map<std::string, int> :: iterator p_final = opcode_map.end();

		while(p_start != p_final)
		{
			outs()<< p_start->first <<":::"<<p_start->second<<"\n";
			p_start++;
		}
		opcode_map.clear();
		return false;
	}
  };
}
char OpcodeCounter::ID = 0;
static RegisterPass<OpcodeCounter> X("OpcodeCounter","count the number of opcode for every type!");
