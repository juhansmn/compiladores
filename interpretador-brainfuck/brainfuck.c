#include <stdio.h>

#define OP_FINALIZAR            0
#define OP_INC_POS              1
#define OP_DEC_POS              2
#define OP_INC_VAL              3
#define OP_DEC_VAL              4
#define OP_SAIDA                5
#define OP_ENTRADA              6
#define OP_AVANCAR              7
#define OP_RETROCEDER           8

#define SUCESSO                 0
#define FALHA                   1

#define TAMANHO_PROGRAMA        4096
#define TAMANHO_PILHA           512
#define TAMANHO_DATA            65535

#define PILHA_EMPILHAR(A)   (PILHA[SP++] = A)
#define PILHA_DESEMPILHAR()     (PILHA[--SP])
#define PILHA_VAZIA()   (SP == 0)
#define PILHA_CHEIA()    (SP == TAMANHO_PILHA)

struct instrucao {
    unsigned short operador;
    unsigned short operando;
};

static struct instrucao PROGRAM[TAMANHO_PROGRAMA];
static unsigned short PILHA[TAMANHO_PILHA];
static unsigned int SP = 0;

int compilar_brainfuck(FILE* fp) {
    unsigned short pc = 0, jmp_pc;
    int c;
    while ((c = getc(fp)) != EOF && pc < TAMANHO_PROGRAMA) {
        switch (c) {
            case '>': PROGRAM[pc].operador = OP_INC_POS; break;
            case '<': PROGRAM[pc].operador = OP_DEC_POS; break;
            case '+': PROGRAM[pc].operador = OP_INC_VAL; break;
            case '-': PROGRAM[pc].operador = OP_DEC_VAL; break;
            case '.': PROGRAM[pc].operador = OP_SAIDA; break;
            case ',': PROGRAM[pc].operador = OP_ENTRADA; break;
            case '[':
                PROGRAM[pc].operador = OP_AVANCAR;
                if (PILHA_CHEIA()) {
                    return FALHA;
                }
                PILHA_EMPILHAR(pc);
                break;
            case ']':
                if (PILHA_VAZIA()) {
                    return FALHA;
                }
                jmp_pc = PILHA_DESEMPILHAR();
                PROGRAM[pc].operador =  OP_RETROCEDER;
                PROGRAM[pc].operando = jmp_pc;
                PROGRAM[jmp_pc].operando = pc;
                break;
            default: pc--; break;
        }
        pc++;
    }
    if (!PILHA_VAZIA() || pc == TAMANHO_PROGRAMA) {
        return FALHA;
    }
    PROGRAM[pc].operador = OP_FINALIZAR;
    
    return SUCESSO;
}

int executar_brainfuck() {
    unsigned short data[TAMANHO_DATA], pc = 0;
    unsigned int ptr = TAMANHO_DATA;
    
    while (--ptr) { data[ptr] = 0; }
    
    while (PROGRAM[pc].operador != OP_FINALIZAR && ptr < TAMANHO_DATA) {
        switch (PROGRAM[pc].operador) {
            case OP_INC_POS: 
                ptr++; 
            break;
            case OP_DEC_POS: 
                ptr--; 
            break;
            case OP_INC_VAL: 
                data[ptr]++; 
            break;
            case OP_DEC_VAL: 
                data[ptr]--; 
            break;
            case OP_SAIDA: 
                putchar(data[ptr]); 
            break;
            case OP_ENTRADA: 
                data[ptr] = (unsigned int)getchar(); 
            break;
            case OP_AVANCAR: 
                if(!data[ptr]) { 
                    pc = PROGRAM[pc].operando; 
                } 
            break;
            case OP_RETROCEDER: 
                if(data[ptr]) { 
                    pc = PROGRAM[pc].operando; 
                } 
            break;
            default: 
                return FALHA;
        }
        pc++;
    }
    
    return ptr != TAMANHO_DATA ? SUCESSO : FALHA;
}

int main(int argc, const char * argv[])
{
    int status;
    FILE *fp;
    
    if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "USO: %s ARQUIVO\n", argv[0]);
        return FALHA;
    }

    status = compilar_brainfuck(fp);
    fclose(fp);

    if (status == SUCESSO) {
        status = executar_brainfuck();
    }
    if (status == FALHA) {
        fprintf(stderr, "FALHA!\n");
    }
    
    return status;
}
