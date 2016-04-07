#include <stdbool.h>

typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT
} InstructionSet;

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  HLT
};

bool running = true;
int ip = 0;

int fetch() {
  return program[ip];
}

void eval(int instr) {
  switch (instr) {
    case HLT:
      running = false;
      break;
  }
}

int main() {
  while (running) {
    eval(fetch());
    ip++;
  }
  return 0;
}
