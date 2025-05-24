/******************************************************************************
DIARIO FINANCEIRO PESSOAL (PROJETO 9)
Data de criação: 27 mar 2025.
REPOSITÓRIO DO CÓDIGO: https://github.com/johnatanwillow/diario_financeiro
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 - Estrutura do Fluxograma
 LOGIN XXXX -- Se o programa for executado com dois argumentos int main(admin e 1234), ele faz o login automaticamente.
 PASSWORD XXXX -- Se a autenticação falhar, o programa termina com erro (return 1).
1️⃣ Início
2️⃣ Exibir Menu Principal
"[1] Cadastrar Receita",                               
"[2] Cadastrar Despesa",                                
"[3] Consultar Saldo",                                 
"[4] Gerar Relatorio",                         
"[5] Alterar Idioma",                       
"[6] Remover Movimentacao",                         
"[7] Sair", 

3️⃣ Processamento das Opções
[1] ou [2] ➜ Solicita e registra transações (data, tipo, valor, descrição, categoria)  
- [3] ➜ Calcula saldo diário/mensal e sugere meta financeira  
- [4] ➜ Lista transações por dia ou mês e gera gráficos ASCII ou CSV  
- [5] ➜ Alterna idioma para francês ou inglês (CANADA)
- [6] ➜ Remove movimentação especificada  
4️⃣ Encerramento:
- [7] ➜ Salva dados e encerra com delay de 3 segundos
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 - PERSISTÊNCIA DE DADOS
○ Todas as transações financeiras registradas devem ser armazenadas em um arquivo binário,
garantindo que os dados sejam preservados após o encerramento do programa. (  )
○ O sistema deve carregar automaticamente os dados do arquivo ao ser iniciado, permitindo a continuidade do controle financeiro. (  )
 - REQUISITOS TECNICOS
● O sistema deve ser implementado em C LANGUAGE. ( X )
● O uso de structs (X), vetores (X), arquivos binários ( ) e ponteiros ( X ) é obrigatório. 
● O código deve ser modularizado, com funções bem definidas para cada operação do sistema. ( X )
● O sistema deve interagir com o usuário via entrada e saída de texto no console. ( X )
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char descricao[100];
    int valorCentavos;
    char tipo;
    int dia, mes, ano;
} Movimentacao;

Movimentacao *lista = NULL;
int capacidade = 0, total = 0;
#define PT 0
#define EN 1
#define FR 2
int idiomaAtual = PT; // idioma inicial

const char *textos[][30] = {
    { // PT - Português
        "Bem-vindo, Filipe\nEu sou Alef e este eh o seu DIARIO FINANCEIRO PESSOAL em Canadian Dollar.\n \t \t Escolha a opcao desejada abaixo\n \t MENU PRINCIPAL",                            // (0) Boas-vindas
        "[1] Cadastrar Receita",                                // (1) Menu - Receita
        "[2] Cadastrar Despesa",                                // (2) Menu - Despesa
        "[3] Consultar Saldo",                                  // (3) Menu - Consultar saldo
        "[4] Gerar Relatorio",                                  // (4) Menu - Gerar relatório
        "[5] Alterar Idioma",                                   // (5) Menu - Alterar idioma
        "[6] Remover Movimentacao",                             // (6) Menu - Remover movimentação
        "[7] Sair",                                              // (7) Menu - Sair
        "\n+== DIARIO FINANCEIRO PESSOAL==+\n\n",               // (8) Cabeçalho - Título
        "Descricao da transacao: ",                             // (9) Entrada - Descrição
        "Valor da transacao (ex: 120099 para 1200.99 CAD ) ZERO || -1 para cancelar: ", // (10) Entrada - Valor
        "Data da Transacao (dd/mm/aaaa): ",                     // (11) Entrada - Data
        "Receita registrada com sucesso!\n",                    // (12) Confirmação - Receita registrada
        "Despesa registrada com sucesso!\n",                    // (13) Confirmação - Despesa registrada
        "Gostaria de definir uma meta financeira mensal?\n",    // (14) Pergunta - Meta financeira
        "Digite [ 1 ] para SIM || Digite [ 2 ] para Sair: ",    // (15) Opção - Meta financeira
        "Pressione ENTER para continuar...",                    // (16) Prompt - Continuar
        "Descricao da movimentacao a remover: ",                // (17) Entrada - Remoção descrição
        "Movimentacao removida com sucesso.\n",                 // (18) Confirmação - Remoção
        "Movimentacao nao encontrada.\n",                       // (19) Erro - Não encontrada
        "Opcao invalida.\n",                                    // (20) Erro - Opção inválida
        "Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: ", // (21) Confirmação - Continuidade
        "Idioma alterado para: %s\n",                           // (22) Confirmação - Idioma alterado
        "Novo idioma (PT/EN/FR): ",                             // (23) Entrada - Novo idioma
        "Operacao cancelada. Retornando ao menu...",            // (24) Aviso - Operação cancelada
        "\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nAguarde...\n",           // (25) Aguarde
        "+=======> Escolha: "                                   // (26) Prompt - Escolha do menu
    },
    { // EN - English
        "Welcome, Filipe\nI am Alef and this is your PERSONAL FINANCIAL JOURNAL in Canadian Dollar.\n \t \t Choose an option below\n \t MAIN MENU",                                    // (0) Welcome
        "[1] Register Income",                         // (1) Menu - Income
        "[2] Register Expense",                        // (2) Menu - Expense
        "[3] Check Balance",                           // (3) Menu - Check balance
        "[4] Generate Report",                         // (4) Menu - Generate report
        "[5] Change Language",                         // (5) Menu - Change language
        "[6] Remove Transaction",                      // (6) Menu - Remove transaction
        "[7] Exit",                                    // (7) Menu - Exit
        "\n+== PERSONAL FINANCIAL JOURNAL ==+\n\n",    // (8) Header - Title
        "Transaction description: ",                   // (9) Input - Description
        "Transaction amount (e.g., 120099 for 1200.99 CAD) ZERO || -1 to cancel: ", // (10) Input - Amount
        "Transaction date (dd/mm/yyyy): ",             // (11) Input - Date
        "Income successfully recorded!\n",             // (12) Confirmation - Income
        "Expense successfully recorded!\n",            // (13) Confirmation - Expense
        "Would you like to set a monthly financial goal?\n", // (14) Question - Goal
        "Enter [ 1 ] for YES || Enter [ 2 ] to Exit: ", // (15) Option - Goal
        "Press ENTER to continue...",                  // (16) Prompt - Continue
        "Transaction description to remove: ",         // (17) Input - Remove description
        "Transaction successfully removed.\n",         // (18) Confirmation - Removed
        "Transaction not found.\n",                    // (19) Error - Not found
        "Invalid option.\n",                           // (20) Error - Invalid option
        "Enter [ 1 ] to Continue || Enter [ 2 ] to Exit: ", // (21) Confirmation - Continue
        "Language changed to: %s\n",                   // (22) Confirmation - Language changed
        "New language (PT/EN/FR): ",                   // (23) Input - New language
        "Operation canceled. Returning to menu...",    // (24) Notice - Operation canceled
        "\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nPlease wait...\n", // (25) Wait
        "+=======> Choose: "                           // (26) Prompt - Menu choice
    },
    { // FR - Français
        "Bienvenue, Filipe\nJe suis Alef et voici votre JOURNAL FINANCIER PERSONNEL en dollar canadien.\n \t \t Choisissez une option ci-dessous\n \t MENU PRINCIPAL",              // (0) Bienvenue
        "[1] Enregistrer un revenu",                  // (1) Menu - Revenu
        "[2] Enregistrer une dépense",                // (2) Menu - Dépense
        "[3] Consulter le solde",                     // (3) Menu - Solde
        "[4] Générer un rapport",                     // (4) Menu - Rapport
        "[5] Changer la langue",                      // (5) Menu - Langue
        "[6] Supprimer une transaction",              // (6) Menu - Supprimer
        "[7] Quitter",                                // (7) Menu - Quitter
        "\n+== JOURNAL FINANCIER PERSONNEL ==+\n\n",  // (8) Titre - Journal
        "Description de la transaction : ",           // (9) Entrée - Description
        "Montant de la transaction (ex : 120099 pour 1200.99 CAD) ZERO || -1 pour annuler : ", // (10) Entrée - Montant
        "Date de la transaction (jj/mm/aaaa) : ",     // (11) Entrée - Date
        "Revenu enregistré avec succès !\n",          // (12) Confirmation - Revenu
        "Dépense enregistrée avec succès !\n",        // (13) Confirmation - Dépense
        "Souhaitez-vous définir un objectif financier mensuel ?\n", // (14) Question - Objectif
        "Entrez [ 1 ] pour OUI || Entrez [ 2 ] pour Quitter : ", // (15) Option - Objectif
        "Appuyez sur ENTRÉE pour continuer...",       // (16) Invite - Continuer
        "Description de la transaction à supprimer : ", // (17) Entrée - Suppression
        "Transaction supprimée avec succès.\n",       // (18) Confirmation - Suppression
        "Transaction non trouvée.\n",                 // (19) Erreur - Non trouvée
        "Option invalide.\n",                         // (20) Erreur - Invalide
        "Entrez [ 1 ] pour Continuer || Entrez [ 2 ] pour Quitter : ", // (21) Confirmation - Continuer
        "Langue changée pour : %s\n",                 // (22) Confirmation - Langue
        "Nouvelle langue (PT/EN/FR) : ",              // (23) Entrée - Langue
        "Opération annulée. Retour au menu...",       // (24) Avis - Annulation
        "\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nVeuillez patienter...\n", // (25) Attente
        "+=======> Choisissez : "                     // (26) Invite - Choix menu
    }
};
//Rol de funções (prototipos)
void alterarIdioma();
void consultarSaldo();
void despedida();
void digitar(const char *mensagem, unsigned int atraso_ms);
void expandirLista();
void exibirMenuPrincipal();
void imprimirRelatorio();
void imprimirValor(int centavos);
void inserirMovimentacao(Movimentacao m);
void limparTela();
int lerEscolha();
Movimentacao lerMovimentacao(char tipo);
void projetarMetaFinanceira();
int removerMovimentacao(char desc[]);
int main() {  /******************************************************[ INICIO DO MAIN ]************************************************/
    int opcao;
    int subOpcao = 1;
    limparTela();
    digitar(textos[idiomaAtual][0], 20);
    do {
        limparTela();   
        printf(textos[idiomaAtual][0], 20);     
        exibirMenuPrincipal();
        scanf("%i", &opcao);
        Movimentacao m;
        char desc[100];
        switch (opcao) {
            case 1: /*_____________________________________(Cadastrar Receita )_______________________________________*/
                subOpcao = 1;
                while (subOpcao != 2) {
                    limparTela();
                    m = lerMovimentacao('R');
                    digitar(textos[idiomaAtual][12], 50); // (12) Confirmação - Receita registrada
                    inserirMovimentacao(m);
                    printf("%s\n", textos[idiomaAtual][9]); //(9) Descriçao do Transaçao
                    printf("%s\n", m.descricao);
                    imprimirValor(m.valorCentavos);
                    printf("\nData/Date: %02i/%02i/%04i\n", m.dia, m.mes, m.ano);
                    subOpcao = lerEscolha();
                    free(lista);
                }
                break;
            case 2: /*_____________________________________(Cadastrar Despesa)_______________________________________*/
                subOpcao = 1;
                while (subOpcao != 2) {
                    limparTela();
                    m = lerMovimentacao('D');
                    digitar(textos[idiomaAtual][13], 50); // (13) Confirmação - Despesa registrada
                    inserirMovimentacao(m);
                    printf("%s\n", textos[idiomaAtual][9]); //(9) Descriçao do Transaçao
                    printf("%s\n", m.descricao);
                    imprimirValor(m.valorCentavos);
                    printf("\nData/Date: %02i/%02i/%04i\n", m.dia, m.mes, m.ano);
                    subOpcao = lerEscolha();
                }
                break;
            case 3: /*______________________________________(Consultar Saldo)_______________________________________*/
                limparTela();
                consultarSaldo();
                digitar(textos[idiomaAtual][14], 50);
                printf("%s", textos[idiomaAtual][15]);
                scanf("%d", &subOpcao);
                if (subOpcao == 1) {
                    projetarMetaFinanceira();
                }
                digitar(textos[idiomaAtual][16], 50); // (16) Prompt - Continuar
                getchar(); getchar();
                break;
            case 4: /*______________________________________(Gerar Relatório)_______________________________________*/
                limparTela();
                imprimirRelatorio();
                digitar(textos[idiomaAtual][16], 50); // (16) Prompt - Continuar
                getchar(); getchar();
                break;
            case 5: /*_______________________________________(Alterar Idiomas)_______________________________________*/
                limparTela();
                alterarIdioma();
                break;
            case 6: /*_____________________________________(Remover Movimentação)_______________________________________*/
                limparTela();
                getchar();
                digitar("Descricao da movimentacao a remover: ", 50);
                fgets(desc, 100, stdin);
                desc[strcspn(desc, "\n")] = '\0';
                if (removerMovimentacao(desc))
                    digitar("Movimentacao removida com sucesso.\n", 50);
                else
                    printf("Movimentacao nao encontrada.\n");
                break;
            case 7: /*____________________________________________( Sair )_______________________________________*/
                limparTela();
                despedida();
                break;
            default:
                digitar(textos[idiomaAtual][20], 50); // (20) Erro - Opção inválida
        }
    } while (opcao != 7);
    
    free(lista); // liberar memoria
    lista = NULL; // medida de segurança
    return 0;
}  /******************************************************************[ FIM DO MAIN ]************************************************/
// Implementações de funçõe em ordem alfabética
void alterarIdioma() {
    char idioma[20];
    printf("%s", textos[idiomaAtual][23]);  // (23) Entrada - Novo idioma [PT] [EN] [FR]
    scanf("%s", idioma);
    if (strcmp(idioma, "EN") == 0) idiomaAtual = EN;
    else if (strcmp(idioma, "FR") == 0) idiomaAtual = FR;
    else idiomaAtual = PT;
    printf(textos[idiomaAtual][22], idioma); // (22) Confirmação - Idioma alterado
}
void consultarSaldo() {
    int r = 0, d = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].tipo == 'R') r += lista[i].valorCentavos;
        else if (lista[i].tipo == 'D') d += lista[i].valorCentavos;
    }
    int saldo = r - d;
    printf("\n--- SALDO ---\n");
    printf("Receitas:.......$ %i.%02i CAD\n", r / 100, r % 100);
    printf("Despesas:.......$ %i.%02i CAD\n", d / 100, d % 100);
    printf("Saldo:..........$ %i.%02i CAD\n", saldo / 100, abs(saldo % 100));
}
void despedida() {
    digitar(textos[idiomaAtual][25], 20); // (25) Aguarde
    sleep(1);
    digitar("\n \t Ate mais! Obrigado por interagir. Volte sempre!", 50);
    digitar("\n \t \t A bientot ! Merci d'avoir interagi. Reviens quand tu veux.", 50);
    digitar("\n \t \t \t See you soon! Thanks for interacting. Come back anytime.\n", 50);
}
void digitar(const char *mensagem, unsigned int atraso_ms) {
    for (int i = 0; mensagem[i] != '\0'; i++) {
        putchar(mensagem[i]);
        fflush(stdout);
        Sleep(atraso_ms);
    }
}
void exibirMenuPrincipal() {
    printf(textos[idiomaAtual][9]); //DIARIO FINANCEIRO PESSOAL
    for (int willow = 1; willow <= 7; willow++) {
        printf("%s\n", textos[idiomaAtual][willow]);
    }
    printf(textos[idiomaAtual][26]); // (26) Escolha
}
void expandirLista() {
    
    capacidade = (capacidade == 0) ? 10 : capacidade * 2;
    Movimentacao *novaLista = realloc(lista, capacidade * sizeof(Movimentacao));
    if (!novaLista) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    lista = novaLista;
}
void imprimirRelatorio() {
    printf("\n--- RELATORIO FINANCEIRO ---\n");
    for (int willow = 0; willow < total; willow++) {
        int dolar = lista[willow].valorCentavos / 100;
        int centavos = lista[willow].valorCentavos % 100;
        printf("[%c] %s - $ %i.%02i  CAD - Data: %02d/%02d/%04d\n",
               lista[willow].tipo, lista[willow].descricao,
               dolar, centavos,
               lista[willow].dia, lista[willow].mes, lista[willow].ano);
    }
}
void imprimirValor(int centavos) {
    printf("$ %d.%02d CAD", centavos / 100, abs(centavos % 100));
}
void inserirMovimentacao(Movimentacao m) {
    if (total == capacidade) {
        expandirLista();
    }
    lista[total++] = m;
}
int lerEscolha() {
    int subOpcao = 0, leitura = 0;
    while (1) {
        printf(textos[idiomaAtual][21]); // (21) Confirmação - Continuidade
        leitura = scanf("%i", &subOpcao);
        if (leitura != 1 || (subOpcao != 1 && subOpcao != 2)) {
            printf(textos[idiomaAtual][19]); // Opcao Invalida
        } else {
            return subOpcao;
        }
    }
}
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
Movimentacao lerMovimentacao(char tipo) {
    Movimentacao m;
    // Leitura do valor
    printf("Digite o valor da transacao (ex: 120099 para 1200.99 CAD)\nou digite ZERO / NUM NEGATIVO para Voltar: ");
    scanf("%i", &m.valorCentavos);
    // Limpar o buffer do scanf anterior (ENTER deixado para trás)
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // Leitura da descrição (com espaços)
    printf("Descricao da transacao: ");
    fgets(m.descricao, sizeof(m.descricao), stdin);
    m.descricao[strcspn(m.descricao, "\n")] = '\0';  // remove '\n'
    // Leitura da data
    printf("Data da Transacao (dd/mm/aaaa): ");
    scanf("%i/%i/%i", &m.dia, &m.mes, &m.ano);
    m.tipo = tipo;
    return m;
}
void projetarMetaFinanceira() {
    int r = 0, d = 0;
    char nomeMeta[50];
    printf("\n+_+_+_+_+_+_+_+_+ == META FINANCEIRA == +_+_+_+_+_+_+_+_+_+_+_\n");
    printf("Digite o nome da sua meta financeira: ");
    getchar();
    fgets(nomeMeta, sizeof(nomeMeta), stdin);
    nomeMeta[strcspn(nomeMeta, "\n")] = '\0';
    for (int willow = 0; willow < total; willow++) {
        if (lista[willow].tipo == 'R') r += lista[willow].valorCentavos;
        else d += lista[willow].valorCentavos;
    }
    int saldo = r - d;
    int meta;
    printf("E qual seria o valor da meta (ex: 190000 para $ 1900.00 CAD): ");
    scanf("%i", &meta);
    printf("\nMeta: %s\n", nomeMeta);
    printf("Valor da Meta: $%i.%02d CAD\n", meta / 100, meta % 100);
    if (saldo >= meta) {
        printf("Parabéns! Você já atingiu sua meta financeira!\n");
        printf("Saldo atual: $ %i.%02i CAD\n", saldo / 100, saldo % 100);
    } else {
        printf("Faltam: $ %i.%02i CAD para atingir a meta.\n", (meta - saldo) / 100, (meta - saldo) % 100);
        printf("Saldo atual: $ %i.%02i CAD\n", saldo / 100, saldo % 100);
    }
}
int removerMovimentacao(char desc[]) {
    for (int willow = 0; willow < total; willow++) {
        if (strcmp(lista[willow].descricao, desc) == 0) {
            for (int j = willow; j < total - 1; j++) {
                lista[j] = lista[j + 1];
            }
            total--;
            return 1;
        }
    }
    return 0;
}