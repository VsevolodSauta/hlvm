#ifndef __errors_h_
#define __errors_h_

#define ILLEGAL_INSTRUCTION_FORMAT() do{ printf("Error.\n  Illegal instruction format @ PC = 0x%04x.\n", *pc); } while(0)

#endif // __errors_h_
