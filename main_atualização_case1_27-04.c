#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "pointer_lib.h"   // Biblioteca de ponteiros para case 1

enum Idioma {
    PORTUGUES,
    FRANCES,
    INGLES
};

// Protótipos das demais funções
void exibirMenu(const char* titulo, const char* opcoes[], int num_opcoes);
void exibirTransacao(int* total, const char* tipo, enum Idioma idioma);
void exibirSaldo(int receita_total, int despesa_total);
void exibirRelatorio(int receita_total, int despesa_total);
int lerEscolha(enum Idioma idioma);
void french();
void english();

// Variáveis globais
int categoria = 0, option = 0, opcao = 0;
int receita_total = 0, despesa_total = 0;
int num_opcoes = 6;
int subOpcao = 1;

int main() {
    const char* titulo = "Bem-vindo a sua CARTEIRA DIGITAL em Canadian Dollar.\nMenu Principal\nEscolha a opcao desejada:";
    const char* opcoes[] = {
        "Cadastrar Receita",
        "Cadastrar Despesa",
        "Exibir Saldo",
        "Gerar Relatorio",
        "Alterar Idioma",
        "Salvar & Sair"
    };

    do {
        exibirMenu(titulo, opcoes, num_opcoes);
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
        case 1:
            subOpcao = 1;
            opcao = 0;
            while (subOpcao != 2) {
                // Limpa tela via ponteiro
                limparTela_p();
                printf("+_+== CARTEIRA DIGITAL ==+_+_\n");

                // Solicita valor da receita via ponteiro
                int valor = lerValor_p("RECEITA", PORTUGUES);
                if (valor < 0) {
                    // Retorna ao menu principal
                    break;
                }
                receita_total += valor;
                printf("Sua RECEITA total eh de $%i.%02i CAD \n", receita_total/100, receita_total%100);

                // Categoria da receita via ponteiro
                const char* titulo_categoria = "E qual eh a categoria da receita? \n";
                const char* categorias[] = {
                    "BOLSA DE ESTUDOS",
                    "ESTAGIO EM STARTUP",
                    "MESADA DA MAMAE (ja convertido em CAD)",
                    "FREELANCE",
                    "OUTROS",
                    "VOLTAR"
                };
                int num_cat = 6;

                categoria = entradaSaida_p(titulo_categoria, categorias, num_cat);
                if (categoria == num_cat) {
                    // Retorna ao menu principal
                    break;
                }
                printf("\nSua conta atual possui X RECEITA no montante de %i.%02i CAD \
cadastradas na categoria %i\n",
                       receita_total/100, receita_total%100, categoria);

                printf("Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: ");
                scanf("%i", &subOpcao);
            }
            break;

        case 2:
            // ... restante do código inalterado para outros cases ...
            break;

        case 6:
            limparTela_p();  // pode usar ponteiro ou direto
            printf("\nAguarde...\n");
            sleep(3);
            printf("\nAte mais! Volte sempre!\n");
            break;

        default:
            limparTela_p();
            printf("OPCAO INVALIDA!\a");
        }

    } while (opcao != 6);
    return 0;
}

// Implementações das demais funções permanecem conforme o original, sem alterações.
