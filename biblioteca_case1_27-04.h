// pointer_lib.h
#ifndef POINTER_LIB_H
#define POINTER_LIB_H

#include <stdio.h>
#include <stdlib.h>

// Enum Idioma utilizado nas funções
enum Idioma {
    PORTUGUES,
    FRANCES,
    INGLES
};

// Protótipos das funções originais (do main_updated.c)
void limparTela();
int  lerValor(const char* tipo, enum Idioma idioma);
int  entradaSaida(const char* titulo, const char* opcoes[], int num_opcoes);

// Ponteiros para as funções usadas no case 1
extern void (*limparTela_p)();
extern int  (*lerValor_p)(const char* tipo, enum Idioma idioma);
extern int  (*entradaSaida_p)(const char* titulo, const char* opcoes[], int num_opcoes);

// Inicializa os ponteiros antes de main()
__attribute__((constructor))
void init_pointer_lib();

#endif // POINTER_LIB_H
