//class to perform the combinational logic of
//the Fetch stage
class FetchStage: public Stage
{
   private:
      void setDInput(D * dreg, uint64_t stat, uint64_t icode, uint64_t ifun, 
                     uint64_t rA, uint64_t rB,
                     uint64_t valC, uint64_t valP);
      uint64_t selectPC(uint64_t M_Cnd, uint64_t M_valA, uint64_t W_valM, uint64_t F_predPC, uint64_t M_icode, uint64_t W_icode);
      bool need_regids(uint64_t f_icode);
      bool need_valC(uint64_t f_icode);
      uint64_t predictPC(uint64_t f_valC, uint64_t f_valP, uint64_t f_icode);
      uint64_t PCincrement(uint64_t f_pc, bool uno, bool dos);
      void getRegIds(uint64_t regs, uint64_t &rA, uint64_t &rB); 
      void buildValC(uint64_t &valC, bool requiresreg, bool &wrong, uint64_t f_pc);

   public:
      bool doClockLow(PipeReg ** pregs, Stage ** stages);
      void doClockHigh(PipeReg ** pregs);
};
