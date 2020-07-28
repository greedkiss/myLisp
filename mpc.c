#include "mpc.h"

static mpc_state_t mpc_state_invalid(void){
  mpc_state_t s;
  s.pos = -1;
  s.row = -1;
  s.col = -1;
  s.term = 0;
  return s;
}

static mpc_state_t mpc_state_new(void){
  mpc_state_t s;
  s.pos = 0;
  s.row = 0;
  s.col = 0;
  s.term = 0;
  return s;
}


enum {
  MPC_INPUT_STRING = 0,
  MPC_INPUT_FILE = 1,
  MPC_INPUT_PIPE = 2
};

enum {
  MPC_INPUT_MARKS_MIN = 32
};

enum{
  MPC_INPUT_MEM_NUM = 512
};

typedef struct{
  char mem[64]
}mpc_mem_t;

typedef struct {
  int type;
  char* filename;
  mpc_state_t state;

  char* string;
  char* buffer;
  FILE* file;

  int suppress;
  int backtrack;
  int marks_slots;
  int marks_num;
  mpc_state_t * marks;

  char * lasts;
  char last;

  size_t mem_index;
  char mem_full[MPC_INPUT_MEM_NUM];
  mpc_mem_t mem[MPC_INPUT_MEM_NUM];
}mpc_input_t;


static mpc_input_t * mpc_input_new_string(const char * filename, const char * string){
  mpc_input_t *i = malloc(sizeof(mpc_input_t));

  i->filename = malloc(strlen(filename) + 1);
  strcpy(i->filename, filename);
  i->type = MPC_INPUT_STRING;

  i->state = mpc_state_new();

  i->string = malloc(strlen(string)+1);
  strcpy(i->string, string);
  i->buffer = NULL;
  i->file = NULL;

  i->suppress = 0;
  i->backtrack = 1;
  i->marks_num = 0;
  i->marks_slots = MPC_INPUT_MARKS_MIN;
  i->marks = malloc(sizeof(mpc_state_t) * i->marks_slots);
  i->lasts = malloc(sizeof(char) * i->marks_slots);
  i->last = '\0';

  i->mem_index = 0;
  memset(i->mem_full, 0, sizeof(char)* MPC_INPUT_MEM_NUM);

  return i;
} 

static mpc_input_t * mpc_input_new_nstring(const char * filename, const char * string, size_t length){
  mpc_input_t * i = malloc(sizeof(mpc_input_t));

  i->filename = malloc(strlen(filename) + 1);
  strcpy(i->filename, filename);
  i->type = MPC_INPUT_STRING;

  i->state = mpc_state_new();

  


}