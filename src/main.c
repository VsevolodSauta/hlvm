/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "instructions.h"

#define MEMORY_SIZE 100

const char * instruction_names[] = {
  "ADD", "SUB", "DIV", "MUL", "AND", "OR",  "XOR", "LDC", "MOV",
  "BRNE","BRE", "BT",  "BF",  "BU",  "JMP", "LDW", "STW", "LDA",
  "STA", "RET", "ENTSP","PUSH","POP","EXIT"
};

uint32_t memory[MEMORY_SIZE];
instruction_t program[] = {
  INSTRUCTION_L(LDC, 1, R0),
  INSTRUCTION_LA(0x01),

  INSTRUCTION_L(LDC, 1, R1),
  INSTRUCTION_LA(0xF),

  INSTRUCTION_L(LDC, 1, R2),     // prev
  INSTRUCTION_LA(0x00),

  INSTRUCTION_L(LDC, 1, R3),     // curr
  INSTRUCTION_LA(0x01),

  INSTRUCTION_L(LDC, 1, R4),     // tmp
  INSTRUCTION_LA(0x00),

  // Begin loop

  INSTRUCTION_S(MOV, 1, R2, R4), // tmp = prev
  INSTRUCTION_S(MOV, 1, R3, R2), // prev = curr
  INSTRUCTION_S(ADD, 1, R3, R4), // tmp = tmp + curr
  INSTRUCTION_S(MOV, 1, R4, R3), // curr = tmp
  INSTRUCTION_S(SUB, 1, R0, R1), // counter --


  INSTRUCTION_LN(BRNE, 0),
  INSTRUCTION_LA(10),

  INSTRUCTION_S(EXIT, 1, R3, R3)
};

uint32_t register_file[REGISTER_FILE_SIZE];
uint32_t * pc = &register_file[PC];
status_register_t * status_reg = (status_register_t *) &register_file[STATUS];

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

    printf("[%04d] Instruction: %4s. register_flag: %5s. Machine instruction: 0x%08x\n",
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
  memset(register_file, sizeof(register_file), 0);
  memset(memory, sizeof(memory), 0);
  assert(sizeof(program) < sizeof(memory));
  memcpy(memory, program, sizeof(program));
}

void
execute_instruction()
{
  instruction_t * current_inst = (instruction_t*) &memory[register_file[PC]];

  // At 1st we have to assume this is a long instruction
  // TODO: Measure this switch vs an array of function pointers
  switch(current_inst->long_instruction.opcode)
  {
    // Add is a short instruction
    case ADD:
    {
      op_add(register_file, memory);
      break;
    }

    case SUB:
    {
      op_sub(register_file, memory);
      break;
    }

    case AND:
    {
      op_and(register_file, memory);
      break;
    }

    case OR:
    {
      op_or(register_file, memory);
      break;
    }

    case XOR:
    {
      op_xor(register_file, memory);
      break;
    }


    // Load constant is a long instruction
    case LDC:
    {
      op_ldc(register_file, memory);
      break;
    }

    // Copy one register to another. Short instruction
    case MOV:
    {
      op_mov(register_file, memory);
      break;
    }

    // Branch if not equal. Short instruction with registers, long without
    case BRNE:
    {
      op_brne(register_file, memory);
      break;
    }

    case BRE:
    {
      op_bre(register_file, memory);
      break;
    }

    case BT:
    {
      op_bt(register_file, memory);
      break;
    }

    case BF:
    {
      op_bf(register_file, memory);
      break;
    }

    case BU:
    {
      op_bu(register_file, memory);
      break;
    }

    case JMP:
    {
      op_jmp(register_file, memory);
      break;
    }

    case EXIT:
    {
      op_exit(register_file, memory);
      break;
    }
  }

  *pc += 1;
}
