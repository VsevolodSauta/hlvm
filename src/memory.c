/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#include <stdio.h>

#include "errors.h"
#include "instructions.h"

void op_ldc(uint32_t * register_file, uint32_t * memory)
{
  uint32_t * pc = &register_file[PC];
  status_register_t * status_reg = (status_register_t *) &register_file[STATUS];
  instruction_t * current_inst = (instruction_t*) &memory[register_file[PC]];

  if(current_inst->long_instruction.register_flag == 1)
  {
    register_file[current_inst->long_instruction.argument] = memory[*pc + 1];
    *pc +=1;
  }
  else
  {
    ILLEGAL_INSTRUCTION_FORMAT();
  }
}

void op_mov(uint32_t * register_file, uint32_t * memory)
{
  uint32_t * pc = &register_file[PC];
  status_register_t * status_reg = (status_register_t *) &register_file[STATUS];
  instruction_t * current_inst = (instruction_t*) &memory[register_file[PC]];

  if(current_inst->two_op.register_flag == 1)
  {
    register_file[current_inst->two_op.upper_argument] = register_file[current_inst->two_op.lower_argument];
  }
  else
  {
    ILLEGAL_INSTRUCTION_FORMAT();
  }
}
