/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "instructions.h"

void op_brne(uint32_t * register_file, uint32_t * memory)
{
  uint32_t * pc = &register_file[PC];
  status_register_t * status_reg = (status_register_t *) &register_file[STATUS];
  instruction_t * current_inst = (instruction_t*) &memory[register_file[PC]];

  if(status_reg->zero == 0)
  {
    if(current_inst->two_op.register_flag == 1)
    {
      *pc += current_inst->two_op.upper_argument;
    }
    else
    {
      *pc += 1;
      current_inst = (instruction_t*) &memory[register_file[PC]];
      *pc = current_inst->value;
      return;
    }
  }

  if(current_inst->two_op.register_flag == 0)
    *pc += 1;
}


void op_exit(uint32_t * register_file, uint32_t * memory)
{
  uint32_t * pc = &register_file[PC];
  status_register_t * status_reg = (status_register_t *) &register_file[STATUS];
  instruction_t * current_inst = (instruction_t*) &memory[register_file[PC]];

  if(current_inst->two_op.register_flag == 1)
  {
    printf("Exit.\n  Register 0x%02x = 0x%04x (%d)\n",
      current_inst->two_op.upper_argument,
      register_file[current_inst->two_op.upper_argument],
      register_file[current_inst->two_op.upper_argument]);
    exit(0);
  }
  else
  {
    ILLEGAL_INSTRUCTION_FORMAT();
  }
}
