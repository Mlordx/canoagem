#define PROB_OBST 0.3
#define VAR_MARG 1
#define FLUXO_DEFAULT 1
#define TAM_MIN_DEFAULT 30
#define TAM_MIN_BARREIRA 3


typedef struct rio *Rio;

void atualizaRio(Rio);

void rioInit(Rio);

void desenhaRio();

Rio alocaRio(int lin, int col, float fluxo, int tamMin);


