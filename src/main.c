#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "instructions.h"

#define MEMORY_SIZE 100

uint32_t memory[MEMORY_SIZE];
instruction_t program[] = {
  INSTRUCTION_L(LDC, 1, R0),
  INSTRUCTION_LA(0x10),
  INSTRUCTION_S(ADD, 1, R0, R0),

  INSTRUCTION_L(LDC, 1, R1),
  INSTRUCTION_LA(0x0c),
  INSTRUCTION_S(SUB, 1, R1, R0),

  INSTRUCTION_S(EXIT, 1, R0, R0)
};

uint32_t register_file[REGISTER_FILE_SIZE];
uint32_t * pc = &register_file[PC];

void initialise_machine();
void execute_instruction();

int
main(int argc, char * argv[])
{
  // Set all the registers to a default value
  initialise_machine();

  while(1)
  {
    if(*pc >= MEMORY_SIZE)
    {
      printf("Error.\n  Illegal Program Counter value of %d.\n", *pc);
      exit(2);
    }

    printf("[%04d] Instruction: % 4s. register_flag: %s. Machine instruction: 0x%08x\n",
      *pc,
      instruction_names[((instruction_t)memory[*pc]).long_instruction.opcode],
      ((instruction_t)memory[*pc]).long_instruction.register_flag == 1 ? "true" : "false",
      ((instruction_t)memory[*pc]).value);

    execute_instruction();
  }
}

void
initialise_machine()
{
  memset(&register_file, sizeof(register_file), 0);
  assert(sizeof(program) < sizeof(memory));
  memcpy(memory, program, sizeof(program));
}

void
execute_instruction()
{
  instruction_t * current_inst = (instruction_t*) &memory[register_file[PC]];

  // At 1st we have to assume this is a long instruction
  switch(current_inst->long_instruction.opcode)
  {
    // Add is a short instruction
    case ADD:
    {
      if(current_inst->two_op.register_flag == 1)
      {
        register_file[current_inst->two_op.upper_argument] += register_file[current_inst->two_op.lower_argument];
      }
      else
      {
        ILLEGAL_INSTRUCTION_FORMAT();
      }
      break;
    }

    case SUB:
    {
      if(current_inst->two_op.register_flag == 1)
      {
        register_file[current_inst->two_op.upper_argument] -= register_file[current_inst->two_op.lower_argument];
      }
      else
      {
        ILLEGAL_INSTRUCTION_FORMAT();
      }
      break;
    }

    // Load constant is a long instruction
    case LDC:
    {
      if(current_inst->long_instruction.register_flag == 1)
      {
        register_file[current_inst->long_instruction.argument] = memory[*pc + 1];
        *pc +=1;
      }
      else
      {
        ILLEGAL_INSTRUCTION_FORMAT();
      }

      break;
    }

    case EXIT:
    {
      if(current_inst->two_op.register_flag == 1)
      {
        printf("Exit.\n  Register 0x%02x = 0x%04x (%d)",
          current_inst->two_op.upper_argument,
          register_file[current_inst->two_op.upper_argument],
          register_file[current_inst->two_op.upper_argument]);
        exit(0);
      }
      else
      {
        ILLEGAL_INSTRUCTION_FORMAT();
      }

      break;
    }
  }

  *pc += 1;
}
