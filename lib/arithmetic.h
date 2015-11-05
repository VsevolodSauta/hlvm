/*
 * (C) The University of Kent and Simon Cooksey 2015.
 */

#ifndef __arithmetic_h_
#define __arithmetic_h_

void op_add(uint32_t * register_file, uint32_t * memory);
void op_sub(uint32_t * register_file, uint32_t * memory);

void op_and(uint32_t * register_file, uint32_t * memory);
void op_or(uint32_t * register_file, uint32_t * memory);
void op_xor(uint32_t * register_file, uint32_t * memory);



#endif // __arithmetic_h_
