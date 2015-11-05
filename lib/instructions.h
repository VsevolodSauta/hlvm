/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#ifndef __instructions_h_
#define __instructions_h_

#include <inttypes.h>

#define INSTRUCTION_S(op, reg_flag, arg1, arg2) \
  { .two_op =                                   \
    {                                           \
      .opcode = op,                             \
      .register_flag = reg_flag,                \
      .lower_argument = arg1,                   \
      .upper_argument = arg2                    \
    }                                           \
  }
#define INSTRUCTION_L(op, reg_flag, arg)        \
  { .long_instruction =                         \
    {                                           \
      .opcode = op,                             \
      .register_flag = reg_flag,                \
      .argument = arg                           \
    }                                           \
  }
#define INSTRUCTION_LN(op, reg_flag) {.value = ((op << 27) + (reg_flag << 26))}
#define INSTRUCTION_LA(arg) {.value = (arg)}

extern const char * instruction_names[];

enum opcode_t {
  ADD,     /* Add */
  SUB,     /* Subtract */
  DIV,     /* Divide */
  MUL,     /* Multiply */
  AND,     /* Bitwise AND */
  OR,      /* Bitwise OR */
  XOR,     /* Bitwise XOR */

  LDC,     /* Load Constant */
  MOV,     /* Move register */

  BRNE,    /* Branch Relative if Not Equal */
  BRE,     /* Branch Relative if Equal */

  BT,      /* Branch absolute if True */
  BF,      /* Branch absolute if False */
  BU,      /* Branch unconditional */

  JMP,     /* Absolute Jump */

  LDW,     /* Load word */
  STW,     /* Store word */
  LDA,     /* Load address */
  STA,     /* Store address */

  RET,     /* Return from function */
  ENTSP,   /* Enter function and move the stack pointer down */
  PUSH,    /* Push all registers onto the stack */
  POP,     /* Pop all registers from the stack */
  EXIT     /* Print the contents of a register and exit the program */
};

enum register_t {
  /* General purpose registers */
  R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11,

  /* Other registers */
  PC, SP, RETSP, LR, STATUS,

  REGISTER_FILE_SIZE
};

typedef struct status_register_t {
  uint32_t carry : 1;          /* Carry flag */
  uint32_t zero : 1;           /* Zero flag */
  uint32_t negative : 1;       /* Negative flag */
  uint32_t overflow : 1;       /* Overflow flag */
  uint32_t reserved : 28;      /* Unused */
} status_register_t;

typedef union instruction {
  uint32_t value;

  struct {
    uint32_t lower_argument : 13;
    uint32_t upper_argument : 13;
    uint32_t register_flag : 1;
    uint32_t opcode : 5;
  } two_op  __attribute__ ((__packed__));


  struct {
    int32_t argument : 26;
    uint32_t register_flag : 1;
    uint32_t opcode : 5;
  } long_instruction  __attribute__ ((__packed__));

} instruction_t;

/* Macros to access operands of an instruction */
#define GET_LOWER_WORD(instruction) (instruction.operand.word_16_s.lower_word)
#define GET_UPPER_WORD(instruction) (instruction.operand.word_16_s.upper_word)

#include "arithmetic.h"
#include "branching.h"
#include "memory.h"

#endif
