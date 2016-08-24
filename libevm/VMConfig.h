///////////////////////////////////////////////////////////////////////////////
//
// interpreter configuration macros

//#define EVM_USE_CONSTANT_POOL
//#define EVM_REPLACE_CONST_JUMP

#define EVM_SWITCH_DISPATCH
//#define EVM_JUMP_DISPATCH

#if defined(EVM_SWITCH_DISPATCH)

	// build a simple loop-and-switch interpreter

	#define DO_CASES for(;;) { fetchInstruction(); switch(INST) {
	#define CASE_BEGIN(name) case Instruction::name:
	#define CASE_END break;
	#define CASE_RETURN return;
	#define CASE_DEFAULT default:
	#define END_CASES } }

#elif defined(EVM_JUMP_DISPATCH)

	// build an indirect-threaded interpreter using a jump table of
	// label addresses (a gcc extension)

	#define DO_CASES fetchInstruction(); goto *VMJumpTable[(byte)INST];
	#define CASE_BEGIN(label) label:
	#define CASE_END fetchInstruction(); goto *VMJumpTable[m_code[PC]];
	#define CASE_RETURN return;
	#define CASE_DEFAULT INVALID:
	#define END_CASES
	
	static const void * const VMJumpTable[256] = 
	{
		&&STOP,          // 00
		&&ADD,
		&&MUL,
		&&SUB,
		&&DIV,
		&&SDIV,
		&&MOD,
		&&SMOD,
		&&ADDMOD,
		&&MULMOD,
		&&EXP,
		&&SIGNEXTEND,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&LT,            // 10
		&&GT,
		&&SLT,
		&&SGT,
		&&EQ,
		&&ISZERO,
		&&AND,
		&&OR,
		&&XOR,
		&&NOT,
		&&BYTE,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&SHA3,          // 20
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&ADDRESS,       // 30
		&&BALANCE,
		&&ORIGIN,
		&&CALLER,
		&&CALLVALUE,
		&&CALLDATALOAD,
		&&CALLDATASIZE,
		&&CALLDATACOPY,
		&&CODESIZE,
		&&CODECOPY,
		&&GASPRICE,
		&&EXTCODESIZE,
		&&EXTCODECOPY,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&BLOCKHASH,     // 40
		&&COINBASE,
		&&TIMESTAMP,
		&&NUMBER,
		&&DIFFICULTY,
		&&GASLIMIT,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&POP,           // 50
		&&MLOAD,
		&&MSTORE,
		&&MSTORE8,
		&&SLOAD,
		&&SSTORE,
		&&JUMP,
		&&JUMPI,
		&&PC,
		&&MSIZE,
		&&GAS,
		&&JUMPDEST,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&PUSH1,         // 60
		&&PUSH2,
		&&PUSH3,
		&&PUSH4,
		&&PUSH5,
		&&PUSH6,
		&&PUSH7,
		&&PUSH8,
		&&PUSH9,
		&&PUSH10,
		&&PUSH11,
		&&PUSH12,
		&&PUSH13,
		&&PUSH14,
		&&PUSH15,
		&&PUSH16,
		&&PUSH17,         // 70
		&&PUSH18,
		&&PUSH19,
		&&PUSH20,
		&&PUSH21,
		&&PUSH22,
		&&PUSH23,
		&&PUSH24,
		&&PUSH25,
		&&PUSH26,
		&&PUSH27,
		&&PUSH28,
		&&PUSH29,
		&&PUSH30,
		&&PUSH31,
		&&PUSH32,
		&&DUP1,          // 80
		&&DUP2,
		&&DUP3,
		&&DUP4,
		&&DUP5,
		&&DUP6,
		&&DUP7,
		&&DUP8,
		&&DUP9,
		&&DUP10,
		&&DUP11,
		&&DUP12,
		&&DUP13,
		&&DUP14,
		&&DUP15,
		&&DUP16,
		&&SWAP1,         // 90
		&&SWAP2,
		&&SWAP3,
		&&SWAP4,
		&&SWAP5,
		&&SWAP6,
		&&SWAP7,
		&&SWAP8,
		&&SWAP9,
		&&SWAP10,
		&&SWAP11,
		&&SWAP12,
		&&SWAP13,
		&&SWAP14,
		&&SWAP15,
		&&SWAP16,
		&&LOG0,          // A0
		&&LOG1,
		&&LOG2,
		&&LOG3,
		&&LOG4,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&PUSHC,
		&&JUMPV,
		&&JUMPVI,
		&&INVALID,       // B0
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,       // C0
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,       // D0
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,       // E0
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&CREATE,        // F0
		&&CALL,
		&&CALLCODE,
		&&RETURN,
		&&DELEGATECALL,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&INVALID,
		&&SUICIDE
	};

#endif