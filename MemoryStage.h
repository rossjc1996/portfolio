//class to perform the Memory Stage
class MemoryStage: public Stage
{
	private:
		void setWinput(W * wreg, uint64_t stat, 
			uint64_t icode, uint64_t valE, 
			uint64_t dstE, uint64_t dstM, uint64_t valM);
		uint64_t getmemAddr(uint64_t icode, uint64_t valA, uint64_t valE);
		uint64_t mvalM;
	public:
		bool doClockLow(PipeReg ** pregs, Stage ** stages);
		void doClockHigh(PipeReg ** pregs);
		uint64_t getvalM();
};