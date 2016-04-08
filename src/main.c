#include <stdbool.h>
#include <stdio.h>

typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  MOV,
  PRT,
  HLT = -999
} InstructionSet;

typedef enum {
  A, B, C, D, E, F, IP, SP,
  NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  SET, B, 10,
  MOV, B, A,
  PRT,
  HLT
};

bool running    =   true;
int stack[256];

int fetch() {
  return program[registers[IP]];
}

void eval(int instr) {
  switch (instr) {
    case HLT: {
      running = false;
      break;
    }
    case PSH: {
      registers[SP]++;
      stack[registers[SP]] = program[++registers[IP]];
      break;
    }
    case POP: {
      int val_popped = stack[registers[SP]--];
      printf("popped %d\n", val_popped);
      break;
    }
    case ADD: {
      int b = stack[registers[SP]--];
      int a = stack[registers[SP]--];

      stack[++registers[SP]] = a + b;
      
      break;
    }
    case SET: {
      int regid = program[++registers[IP]];
      int val   = program[++registers[IP]];
      registers[regid] = val;
      break;
    }
    case MOV: {
      int regid1 = program[++registers[IP]];
      int regid2 = program[++registers[IP]];
      registers[regid2] = registers[regid1];
      break;
    }
    case PRT: {
      printf("A -> %d\n", registers[A]);
      break;
    }
  }
}

int main() {

  registers[IP] = 0;
  registers[SP] = -1;

  printf("Running program...\n");
  while (running) {
    eval(fetch());
    registers[IP]++;
  }

  printf("\nProgram that was run:\n");
  registers[IP] = 0;
  while (program[registers[IP]] != HLT)
    printf("%4d: %4d\n", ++registers[IP], program[registers[IP]]);

  return 0;
}
