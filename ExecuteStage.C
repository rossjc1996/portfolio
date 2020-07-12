#include <string>
#include <cstdint>
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "E.h"
#include "M.h"
#include "Stage.h"
#include "ExecuteStage.h"
#include "Status.h"
#include "Debug.h"
#include "Instructions.h"
#include "ConditionCodes.h"

/*
 * doClockLow:
 * performs the Execute Stage logic that is performed when the clock edge is low
 * @param: pregs - array of the pipeline register sets (F, D, E, M, W instances)
 * @param: stages - array of stages (FetchStage, DecodeStage, ExecuteStage, Memory Stage, WritebackStagfe instances)
 */
bool ExecuteStage::doClockLow(PipeReg ** pregs, Stage ** stages){
	E * ereg = (E *) pregs[EREG];
   	M * mreg = (M *) pregs[MREG];
   
   	uint64_t valE = 0, Cnd = 0;
   
	uint64_t stat = ereg->getstat()->getOutput();
   	uint64_t icode = ereg->geticode()->getOutput();
   	uint64_t valA = ereg->getvalA()->getOutput();
   	uint64_t dstE = ereg->getdstE()->getOutput();
   	uint64_t dstM = ereg->getdstM()->getOutput();

	//HCL for ALU A component

    int64_t alu1 = getalu1(icode, ereg);
	int64_t alu2 = getalu2(icode, ereg);
	uint64_t alufun = getalufun(icode, ereg);
	bool cc = set_cc(icode);
    	
    valE = aluMethod(alufun, alu1, alu2, cc);
    
    Cnd = getCnd(icode, ereg->getifun()->getOutput());

	dstE = getdstE(icode, Cnd, dstE);
	
    edstE = dstE;
    evalE = valE;
    e_Cnd = Cnd;

   	setMinput(mreg, Cnd, valE, stat, icode, valA, dstE, dstM);
   	
	return false;
}

void ExecuteStage::doClockHigh(PipeReg ** pregs){
   	M * mreg = (M *) pregs[MREG];
   
   	mreg->getCnd()->bubble();
   	mreg->getvalE()->bubble();
   	mreg->getstat()->bubble(SAOK);
   	mreg->geticode()->bubble(INOP);
   	mreg->getvalA()->bubble();
   	mreg->getdstE()->bubble(RNONE);
   	mreg->getdstM()->bubble(RNONE);
   
}

void ExecuteStage::setMinput(M * mreg, uint64_t Cnd, 
				uint64_t valE, uint64_t stat, uint64_t icode, 
				uint64_t valA, uint64_t dstE, uint64_t dstM ){
	
	mreg->getstat()->setInput(stat);
	mreg->getCnd()->setInput(Cnd);
	mreg->getvalE()->setInput(valE);
	mreg->getstat()->setInput(stat);
	mreg->geticode()->setInput(icode);
	mreg->getvalA()->setInput(valA);		
	mreg->getdstE()->setInput(dstE);
	mreg->getdstM()->setInput(dstM);		
}

int64_t ExecuteStage::getalu1(uint64_t icode, E * ereg){
	if(icode == IRRMOVQ || icode == IOPQ){
		return ereg->getvalA()->getOutput();
	}
	if(icode == IIRMOVQ || icode == IRMMOVQ || icode == IMRMOVQ){
		return ereg->getvalC()->getOutput();
	}
	if(icode == ICALL || icode == IPUSHQ){
		return -8;
	}
	if(icode == IRET || icode == IPOPQ){
		return 8;
	}
		return 0;
}

int64_t ExecuteStage::getalu2(uint64_t icode, E * ereg){
	if(icode == IRMMOVQ || icode == IMRMOVQ || icode == IOPQ 
		|| icode == ICALL || icode == IPUSHQ || icode == IRET
		|| icode == IPOPQ){
		return ereg->getvalB()->getOutput();
	}
	if(icode == IRRMOVQ || icode == IIRMOVQ){
		return 0;
	}
		return 0;
	
}

uint64_t ExecuteStage::getalufun(uint64_t icode, E * ereg){
	if(icode == IOPQ){
		return ereg->getifun()->getOutput();
	}
	else{
		return ADDQ;
	}
}

bool ExecuteStage::set_cc(uint64_t icode){
    if(e_icode == IOPQ) && (!m_stat){
        return true;
    }
    else{
        return false;
    }
}

uint64_t ExecuteStage::getdstE(uint64_t icode, uint64_t Cnd, uint64_t dstE){
    if(icode == IRRMOVQ && !Cnd){
        return RNONE;
    }
    else{
        return dstE;
    }
}

int64_t ExecuteStage::aluMethod(uint64_t alu, int64_t alu1, int64_t alu2, bool get_cc){
    if(alu == ADDQ){
        int64_t aluVal = alu2 + alu1;
        if(get_cc){
            ccMethod(alu1, alu2, aluVal, ADDQ);
        }
        return aluVal;
    }
    if(alu == SUBQ){
        int64_t aluVal = alu2 - alu1;
        if(get_cc){
            ccMethod(alu1, alu2, aluVal, SUBQ);
        }
        return aluVal;
    }

    if(alu == XORQ){
        int64_t aluVal = alu2 ^ alu1;
        if(get_cc){
            ccMethod(alu1, alu2, aluVal, XORQ);
        }
        return aluVal;
    }
    if(alu == ANDQ){
        int64_t aluVal = alu2 & alu1;
        if(get_cc){
            ccMethod(alu1, alu2, aluVal, ANDQ);
        }
        return aluVal;
    }
    return 0;
}

void ExecuteStage::ccMethod(int64_t alu1, int64_t alu2, int64_t aluVal, uint64_t y86stuff){
    ConditionCodes * cc = ConditionCodes::getInstance();
    bool oops = false;

    if(aluVal == 0){
        cc->setConditionCode(true, ZF, oops);
    }
    else{
        cc->setConditionCode(false, ZF, oops);
    }
    
    cc->setConditionCode(false, SF, oops);

    if(aluVal < 0){
        cc->setConditionCode(true, SF, oops);
    }

    if(((y86stuff == ANDQ || y86stuff == ADDQ) &&
        ((alu1 < 0 && alu2 < 0 && aluVal >= 0) || 
        (alu1 > 0 && alu2 > 0 && aluVal < 0)))){
        cc->setConditionCode(true, OF, oops);
    }
    else if (y86stuff == SUBQ &&
        ((alu1 > 0 && alu2 < 0 && aluVal > 0) ||
        (alu1 < 0 && alu2 > 0 && aluVal < 0))){
        cc->setConditionCode(true, OF, oops);
    }
    else{
        cc->setConditionCode(false, OF, oops);
    }
}

uint64_t ExecuteStage::getevalE(){
    return evalE;
}

uint64_t ExecuteStage::getedstE(){
    return edstE;
}

uint64_t ExecuteStage::getCnd(uint64_t icode,uint64_t ifun){
    ConditionCodes * cc = ConditionCodes::getInstance();

	bool error = false;
	bool sf = cc->getConditionCode(SF, error);
	bool of = cc->getConditionCode(OF, error);
	bool zf = cc->getConditionCode(ZF, error);
	
	if( icode == IJXX || icode == ICMOVXX){
		switch (ifun){
			case UNCOND:
				return 1;
				break;
			case LESSEQ: 
				return (sf != of) || zf;
				break;
			case LESS:
				return sf != of;
				break;
			case EQUAL:
				return zf;
				break;
			case NOTEQUAL:
				return !zf;
				break;
			case GREATEREQ:
				return !(sf != of);
				break;
			case GREATER:
				return !(sf != of) && !zf; 
				break;
			default:
				return 1;
				break;
		}
	}else{
		return 0;
	}
}

uint64_t ExecuteStage::geteCndE(){
	return e_Cnd;
}
