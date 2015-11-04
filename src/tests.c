instruction_t test1[] = {
  INSTRUCTION_L(LDC, 1, R0),
  INSTRUCTION_LA(15),

  INSTRUCTION_L(LDC, 1, R1),
  INSTRUCTION_LA(4),

  INSTRUCTION_S(ADD, 1, R1, R0),
  INSTRUCTION_S(ADD, 1, R1, R0),
  INSTRUCTION_S(ADD, 1, R0, R1),

  INSTRUCTION_S(EXIT, 1, R1, R1)
};
// Expected output: 27

instruction_t test2[] = {
  INSTRUCTION_L(LDC, 1, R0),
  INSTRUCTION_LA(100),

  INSTRUCTION_L(LDC, 1, R1),
  INSTRUCTION_LA(44),

  INSTRUCTION_S(SUB, 1, R1, R0),
  INSTRUCTION_S(SUB, 1, R1, R0),
  INSTRUCTION_S(SUB, 1, R0, R1),

  INSTRUCTION_S(EXIT, 1, R1, R1)
};
// Expected output: 32
