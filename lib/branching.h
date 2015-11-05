/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#ifndef __branching_h_
#define __branching_h_

void op_brne(uint32_t * register_file, uint32_t * memory);
void op_bre(uint32_t * register_file, uint32_t * memory);

void op_bt(uint32_t * register_file, uint32_t * memory);
void op_bf(uint32_t * register_file, uint32_t * memory);

void op_bu(uint32_t * register_file, uint32_t * memory);
void op_jmp(uint32_t * register_file, uint32_t * memory);

void op_exit(uint32_t * register_file, uint32_t * memory);

#endif // __branching_h_
