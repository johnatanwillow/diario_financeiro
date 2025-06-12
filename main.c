/*******************************************************************************
 * PROJETO FINAL: DIÁRIO FINANCEIRO PESSOAL (MVP)
 *
 * DESCRIÇÃO:
 * Uma aplicação de console desenvolvida em C para o gerenciamento de finanças
 * pessoais, permitindo registro de receitas/despesas, consulta de saldo,
 * geração de relatórios e definição de metas. O sistema é projetado para
 * ser robusto, modular e aderente a boas práticas de programação.
 *
 * DESENVOLVEDORES:
 * GABRIEL DE MELO
 * JOHNATAN WILLOW DIAS DE ANDRADE
 * MATHEUS GOMES RODRIGUES
 * NICOLE DOS SANTOS CASSIANO
 *
 * DISCIPLINA: Introdução à Programação – 2025/1
 * INSTITUIÇÃO: Universidade Federal de Goiás (UFG) - Instituto de Informática (INF)
 * PROFESSOR: Hugo Marciano de Melo (marciano@ufg.br)
 *
 * DATA DE CRIAÇÃO: 27 de março de 2025
 * ÚLTIMA ATUALIZAÇÃO: 10 de junho de 2025
 * REPOSITÓRIO DO CÓDIGO: https://github.com/johnatanwillow/diario_financeiro
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * - ESTRUTURA E FUNCIONALIDADES PRINCIPAIS (FLUXO)
 * 1️⃣ INÍCIO: Carregamento automático de dados financeiros persistidos.
 *
 * 2️⃣ MENU PRINCIPAL: O usuário é guiado pelas seguintes opções:
 * [1] Cadastrar Receita
 * [2] Cadastrar Despesa
 * [3] Consultar Saldo
 * [4] Gerar Relatório
 * [5] Alterar Idioma
 * [6] Remover Movimentação
 * [7] Sair
 *
 * 3️⃣ PROCESSAMENTO DAS OPÇÕES:
 * - [1] ou [2] ➜ Solicita e registra transações (data, tipo, valor, descrição, categoria)
 * - [3] ➜ Calcula e exibe o saldo financeiro, além de gerenciar/exibir metas financeiras.
 * - [4] ➜ Oferece relatórios (geral, diário, mensal) e um gráfico de fluxo de caixa em ASCII.
 * - [5] ➜ Permite alternar entre Português, Francês Canadense e Inglês Canadense;
 * inclui lógica para solicitar consentimento de dados anônimos e novo nome de usuário
 * (especialmente para idiomas canadenses, conforme legislação local).
 * - [6] ➜ Remove uma movimentação específica baseada em sua descrição.
 *
 * 4️⃣ ENCERRAMENTO:
 * - [7] ➜ Salva todos os dados em arquivo binário e encerra o programa após um breve delay (1 segundo).
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * - DESTAQUES DE DESIGN E CONFORMIDADE
 *
 * ● PERSISTÊNCIA DE DADOS: Todas as transações e metas são salvas em arquivo binário (df.bin)
 * e carregadas automaticamente, garantindo a integridade dos dados. (✓)
 * ● REQUISITOS TÉCNICOS: Implementado em C, com uso obrigatório de structs, vetores,
 * arquivos binários e ponteiros. O código é modularizado e interage via console. (✓)
 * ● PRIMAZIA DO IDIOMA FRANCÊS (CANADÁ): Prioridade ao francês canadense na interface
 * e lógicas específicas, em conformidade com a Lei 101 de Quebec.
 * ● CONFORMIDADE COM LEI DE PROTEÇÃO DE DADOS (PIPEDA): Simulação de consentimento
 * para dados anônimos, refletindo a Lei de Proteção de Informações Pessoais e Documentos Eletrônicos.
 * ● USO DE INTEIROS PARA VALORES FINANCEIROS: Todos os valores monetários são
 * armazenados em centavos (int), evitando erros de precisão de ponto flutuante.
 * ● ADOÇÃO DO PADRÃO DE DATA ISO 8601 (YYYY-MM-DD): Garante clareza e interoperabilidade,
 * alinhado às práticas do Governo do Canadá.
 * ● REUTILIZAÇÃO DE CÓDIGO: Uso de funções auxiliares e macros para otimizar o desenvolvimento.
 * ● CRIATIVIDADE E USABILIDADE: Suporte multilíngue, efeito de "digitação" de mensagens,
 * gerenciamento de meta financeira com barra de progresso visual e gráficos ASCII.
 *
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

// --- DEFINIÇÕES DE MACROS ---
#define T(index) textos[idiomaAtual][index] // Macro para acessar o texto do dicionário
#define PRINT_MSG(index) printf("%s", T(index))// Macro para imprimir uma mensagem do dicionário (sem digitação letra por letra)
#define TYPE_MSG(index) digitar(T(index), 25) // Macro para "digitar" uma mensagem do dicionário (letra por letra)
#define MAX(a, b) ((a) > (b) ? (a) : (b)) // Macro auxiliar para obter o maior valor (para garantir pelo menos 1 barra)

#ifdef _WIN32
    #include <windows.h> // Para Sleep() no Windows
#else
    #include <unistd.h> // Para usleep() em sistemas Unix-like (Linux, macOS)
#endif
// --- Definições de Categorias ---
typedef enum {
    CAT_ALIMENTACAO,
    CAT_TRANSPORTE,
    CAT_MORADIA,
    CAT_EDUCACAO,
    CAT_SAUDE,
    CAT_LAZER,
    CAT_CONTAS,
    CAT_RENDA, 
    CAT_INVESTIMENTO,
    CAT_PRESENTE,    
    NUM_CATEGORIAS   // Usado para contar o numero total de categorias
} CategoriaValida;

typedef struct {
    CategoriaValida tipoCategoria;
} Categoria;
// --- Estrutura de Movimentação ---
typedef struct {
    int valorCentavos;
    char descricao[100];
    int dia, mes, ano; 
    char tipo; // 'R' para Receita, 'D' para Despesa
    Categoria categoriaMovimentacao; 
} Movimentacao;
// --- Variáveis Globais ---
Movimentacao *lista = NULL;
int capacidade = 0, total = 0;
char nomeUsuario[50] = "Filipe"; // Nome inicial padrão
char metaFinanceiraNome[100] = "";
int metaFinanceiraValorCentavos = 0;
int metaFinanceiraCadastrada = 0; // 0 = false, 1 = true

// --- Enumeração e Dicionários para Idiomas e Textos ---
typedef enum {
    PT, 
    FR, 
    EN   
} Idioma;
Idioma idiomaAtual = PT;

const char *nomesCategorias[NUM_CATEGORIAS][3] = {
    // PT          FR          EN
    {"Alimentacao", "Alimentation", "Food"},             // CAT_ALIMENTACAO
    {"Transporte", "Transport", "Transportation"},      // CAT_TRANSPORTE
    {"Moradia", "Logement", "Housing"},                  // CAT_MORADIA
    {"Educacao", "Education", "Education"},              // CAT_EDUCACAO
    {"Saude", "Sante", "Health"},                        // CAT_SAUDE
    {"Lazer", "Loisirs", "Leisure"},                     // CAT_LAZER
    {"Contas", "Factures", "Bills"},                     // CAT_CONTAS
    {"Renda", "Revenu", "Income"},                       // CAT_RENDA
    {"Investimento", "Investissement", "Investment"},    // CAT_INVESTIMENTO
    {"Presente", "Cadeau", "Gift"}                       // CAT_PRESENTE
};
const char *textos[][59] = { /*===================================[ DICIONARIO ]===================================*/
    { // PT - Portugues Brasileiro (indice 0)
        "Bem-vindo, %s\nEu sou Alef e este eh o seu DIARIO FINANCEIRO PESSOAL em Canadian Dollar.\n \t \t Escolha a opcao desejada abaixo\n \t MENU PRINCIPAL", // (0) Boas-vindas
        "[1] Cadastrar Receita",                              // (1) Menu - Receita
        "[2] Cadastrar Despesa",                              // (2) Menu - Despesa
        "[3] Consultar Saldo",                                // (3) Menu - Consultar saldo
        "[4] Gerar Relatorio",                                // (4) Menu - Gerar relatorio
        "[5] Alterar Idioma",                                 // (5) Menu - Alterar idioma
        "[6] Remover Movimentacao",                           // (6) Menu - Remover movimentacao
        "[7] Sair",                                           // (7) Menu - Sair
        "\n+== DIARIO FINANCEIRO PESSOAL==+\n\n",             // (8) Cabecalho - Titulo
        "Descricao da transacao: ",                           // (9) Entrada - Descricao
        "Valor da transacao (ex: 120099 para 1200.99 CAD ) || ZERO OU -1 para cancelar: ", // (10) Entrada - Valor
        "Data da Transacao (aaaa-mm-dd): ",                   // (11) Data da Transacao
        "Receita registrada com sucesso!\n",                  // (12) Confirmacao - Receita registrada
        "Despesa registrada com sucesso!\n",                  // (13) Confirmacao - Despesa registrada
        "Gostaria de definir uma meta financeira mensal?\n",  // (14) Pergunta - Meta financeira
        "Digite [ 1 ] para SIM || Digite [ 2 ] para Sair: ",  // (15) Opcao - Meta financeira
        "Pressione ENTER para continuar...",                  // (16) Prompt - Continuar
        "Informe a descricao do que deseja remover ou ZERO para sair:\n", // (17) Entrada - Remocao descricao
        "Movimentacao removida com sucesso.\n",               // (18) Confirmacao - Remocao
        "Nenhum registro com essa descricao encontrado.\n",   // (19) Erro - Nao encontrada
        "Opcao invalida.\n",                                  // (20) Erro - Opcao invalida
        "Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: ", // (21) Confirmacao - Continuidade
        "Idioma alterado para: %s\n",                         // (22) Confirmacao - Idioma alterado
        "Novo idioma (PT/FR/EN): ",                           // (23) Entrada - Novo idioma
        "Operacao cancelada. Retornando ao menu...\n",        // (24) Aviso - Operacao cancelada
        "\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nAguarde...\n",         // (25) Aguarde
        "Sua Escolha: ",                                      // (26) Prompt - Escolha do menu
        "Escolha uma categoria:\n",                           // (27) Novo: Prompt para escolher categoria
        "Opcao de categoria invalida. Tente novamente.\n",    // (28) Novo: Erro de categoria invalida
        "Categoria: ",                                        // (29) NOVO: Label "Categoria" para exibicao
        "Escolha o tipo de relatorio:\n[1] Geral\n[2] Diario\n[3] Mensal\n[4] Grafico de Fluxo de Caixa\n[5] Voltar ao menu principal\nSua escolha: ", // (30) Tipo de relatorio e sub-menu de relatorios
        "Digite a data no padrao ISO 8601 (aaaa-mm-dd): ",           // (31) Digite a data
        "Digite o ano e mes no padrao ISO 8601 (aaaa-mm): ",        // (32) Digite o ano e mês
        "Nao ha transacoes para este periodo.\n",             // (33) Nao ha transacoes
        "Relatorio Diario para %04d-%02d-%02d\n",       // (34) Titulo Relatorio Diario (ANO-MES-DIA) ISO 8601
        "Relatorio Mensal para %04d-%02d\n",            // (35) Titulo Relatorio Mensal (ANO-MES)
        "Erro na leitura da data. Formato esperado (aaaa-mm-dd).\n", //(36) Erro de leitura
        "Erro de alocacao de memoria ao ler movimentacao!\n",     //(37)Erro de memoria
        "Valor invalido! Por favor, insira um numero inteiro valido ou ZERO/NEGATIVO para cancelar.\n", // (38) Erro - Valor inválido
        "Data invalida! Por favor, insira uma data valida (aaaa-mm-dd).\n", // (39) Erro - Data inválida
        "Receitas: ",                                         // (40) Receitas Grafico
        "\nDespesas: ",                                       // (41) Despesas Grafico
        "\nSaldo: ",                                          // (42) Saldo
        "Gostariamos de coletar dados anonimos de uso para melhorar o aplicativo. Voce concorda com o compartilhamento de dados?\n", // (43) Pergunta de Consentimento (PT)
        "--- RELATORIO FINANCEIRO GERAL ---\n",               // (44) Título Relatório Geral
        "Nenhuma movimentacao registrada ainda.\n",           // (45) Nenhuma movimentação (Relatório Geral)
        "\n--- GRAFICO DE FLUXO DE CAIXA ---\n",              // (46) Título Gráfico de Fluxo de Caixa
        "\n+_+_+_+_+_+_+_+_+ == META FINANCEIRA == +_+_+_+_+_+_+_+_+_+_+_\n", // (47) Título da Meta Financeira
        "Digite o nome da sua meta financeira: ",             // (48) Pergunta pelo nome da meta
        "E qual seria o valor da meta (ex: 120099 para 1200.99 CAD): ", // (49) Pergunta pelo valor da meta
        "\nMeta: %s\n",                                       // (50) Exibe o nome da meta
        "Valor da Meta: ",                                    // (51) Exibe o valor da meta
        " CAD\n",                                             // (52) Moeda CAD
        "Parabens! Voce ja atingiu sua meta financeira!\n",   // (53) Mensagem de parabéns
        "Saldo atual: ",                                      // (54) Exibe o saldo atual
        "Faltam: ",                                           // (55) Exibe o valor restante para a meta
        "\n\n\tProgresso:\n\t[",                              // (56) Título da barra de progresso
        "] %.0f%%\n",                                         // (57) Final da barra de progresso e porcentagem
        "Obrigado! Seus dados nos ajudarao a melhorar o aplicativo.\n" // (58) Agradecimento de consentimento PT
    },
    { // FR - Quebecois (pas d'accent) (indice 1)
        "Salut, %s\nJe suis Alef et voici votre JOURNAL FINANCIER PERSONNEL en dollar canadien.\n \t \t Veuillez choisir une option ci-dessous\n \t MENU PRINCIPAL", // (0) Bienvenue
        "[1] Enregistrer un revenu",                            // (1) Menu - Revenu
        "[2] Enregistrer une depense",                          // (2) Menu - Depense
        "[3] Consulter le solde",                               // (3) Menu - Solde
        "[4] Generer un rapport",                               // (4) Menu - Rapport
        "[5] Changer la langue",                                // (5) Menu - Langue
        "[6] Supprimer une transaction",                        // (6) Menu - Supprimer
        "[7] Quitter",                                          // (7) Menu - Quitter
        "\n+== JOURNAL FINANCIER PERSONNEL ==+\n\n",             // (8) Titre - Journal
        "Description de la transaction : ",                     // (9) Entree - Description
        "Montant de la transaction (ex : 120099 pour 1200.99 CAD) || ZERO ou -1 pour annuler : ", // (10) Entree - Montant
        "Date de la transaction (aaaa-mm-jj): ",               // (11) Date
        "Revenu enregistre avec succes !\n",                    // (12) Confirmation - Revenu
        "Depense enregistree avec succes !\n",                  // (13) Confirmation - Depense
        "Souhaitez-vous vous fixer un objectif financier mensuel ?\n", // (14) Question a propos de l'Objectif
        "Appuyez sur [ 1 ] pour OUI || Appuyez sur [ 2 ] pour Quitter : ", // (15) Opcao - Objectif
        "Appuyez sur ENTREE pour continuer...",                 // (16) Invite - Continuer
        "Entrez la description a supprimer ou 0 pour quitter :\n", // (17) Entree - Suppression
        "Transaction supprimee avec succes.\n",                 // (18) Confirmation - Suppression
        "Transaction non trouvee.\n",                           // (19) Erreur - Non trouvee
        "Option invalide.\n",                                  // (20) Erreur - Invalide
        "Appuyez sur [ 1 ] pour Continuer || Appuyez sur [ 2 ] pour Quitter : ", // (21) Confirmation - Continuer
        "Langue changee pour : %s\n",                           // (22) Confirmation - Langue
        "Nouvelle langue (PT/FR/EN) : ",                        // (23) Entree - Langue
        "Operation annulee. Retour au menu...\n",               // (24) Avis - Annulation
        "\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nVeuillez patienter...\n",  // (25) Attente
        " Votre choix : ",                                      // (26) Invite - Choix menu
        "Choisissez une categorie:\n",                          // (27) Prompt para escolher categoria
        "Option de categorie invalide. Veuillez reessayer.\n",    // (28) Erro de categoria invalida
        "Categorie : ",                                         // (29) "Categorie" para exibicao
        "Choisissez le type de rapport:\n[1] General\n[2] Quotidien\n[3] Mensuel\n[4] Graphique de Flux de Tresorerie\n[5] Retour au menu principal\nVotre choix: ", // (30) Tipo de relatorio
        "Entrez la date au format ISO 8601 (aaaa-mm-jj): ",  // (31) Entrez le jour
        "Entrez l'annee et le mois au format ISO 8601 (aaaa-mm): ", // (32) Entrez l'annee et le mois
        "Aucune transaction pour cette periode.\n",             // (33) Aucune transaction
        "Rapport quotidien pour %04d-%02d-%02d\n",              // (34) Titulo Relatorio Diario (ANNEE-MOIS-JOUR)
        "Rapport mensuel pour %04d-%02d\n",                     // (35) Titulo Relatorio Mensal (ANNEE-MOIS)
        "Erreur lors de la lecture de la date. Format attendu aaaa-mm-jj (ISO 8601).\n", //Erreur de la lecture de la date
        "Erreur d'allocation de memoire lors de la lecture du mouvement !\n", // Erreur de memoire
        "Montant invalide ! Veuillez saisir un nombre entier valide ou ZERO/NEGATIF pour annuler.\n", // (38) Erro - Montant invalide
        "Date invalide ! Veuillez saisir une date valide (aaaa-mm-jj).\n", // (39) Erro - Date invalide
        "Revenus: ",                                          // (40) Revenus Graphique
        "\nDepenses: ",                                       // (41) Depenses Graphique
        "\nSolde: ",                                          // (42) Saldo
        "Nous aimerions collecter des donnees d'utilisation anonymes pour ameliorer l'application. \nAcceptez-vous le partage de donnees ?\n",            // (43) Pergunta de Consentimento (FR)
        "--- RAPPORT FINANCIER GENERAL ---\n",                  // (44) Título Relatório Geral
        "Aucune transaction enregistree pour le moment.\n",      // (45) Nenhuma movimentação (Relatório Geral)
        "\n--- GRAPHIQUE DES FLUX DE TRESORERIE ---\n",          // (46) Título Gráfico de Fluxo de Caixa
        "\n+_+_+_+_+_+_+_+_+ == OBJECTIF FINANCIER == +_+_+_+_+_+_+_+_+_+_+_\n", // (47) Título da Meta Financeira
        "Veuillez entrer le nom de votre objectif financier : ",  // (48) Pergunta pelo nome da meta
        "Quel serait le montant de votre objectif (ex : 120099 pour 1200.99 $ CAD) : ", // (49) Pergunta pelo valor da meta
        "\nObjectif : %s\n",                                    // (50) Exibe o nome da meta
        "Montant de l'objectif : ",                             // (51) Exibe o valor da meta
        " CAD\n",                                               // (52) Moeda CAD
        "Felicitations ! Vous avez atteint votre objectif financier !\n", // (53) Mensagem de parabéns
        "Solde actuel : ",                                      // (54) Exibe o saldo atual
        "Il manque : ",                                         // (55) Exibe o valor restante para a meta
        "\n\n\tProgression :\n\t[",                              // (56) Título da barra de progresso
        "] %.0f%%\n",                                           // (57) Final da barra de progresso e porcentagem
        "Merci beaucoup! Vos donnees nous aiderons a ameliorar l'application.\n" // (58) Agradecimento de consentimento FR
    },
    { // EN - Canadian English (indice 2)
        "Hello, %s\nI am Alef and this is your PERSONAL FINANCIAL JOURNAL in Canadian Dollars.\n \t \t Please choose an option below\n \t MAIN MENU", // (0) Welcome
        "[1] Register Income",                                  // (1) Menu - Income
        "[2] Register Expense",                                 // (2) Menu - Expense
        "[3] Check Balance",                                    // (3) Menu - Check balance
        "[4] Generate Report",                                  // (4) Menu - Generate report
        "[5] Change Language",                                  // (5) Menu - Change language
        "[6] Remove Transaction",                               // (6) Menu - Remove transaction
        "[7] Exit",                                             // (7) Menu - Exit
        "\n+== PERSONAL FINANCIAL JOURNAL ==+\n\n",              // (8) Header - Title
        "Transaction description: ",                            // (9) Input - Description
        "Transaction amount (e.g., 120099 for 1200.99 CAD) || ZERO or -1 to cancel: ", // (10) Input - Amount
        "Transaction date (yyyy-mm-dd):",                      // (11) Date
        "Income successfully recorded!\n",                      // (12) Confirmation - Income
        "Expense successfully recorded!\n",                     // (13) Confirmation - Expense
        "Would you like to set a monthly financial goal?\n",    // (14) Question - Goal
        "Press [ 1 ] for YES || Press [ 2 ] to Exit: ",         // (15) Option - Goal
        "Press ENTER to continue...",                           // (16) Prompt - Continue
        "Please enter the description to remove, or type 0 to exit:\n", // (17) Input - Remove description
        "Transaction successfully removed.\n",                  // (18) Confirmation - Removed
        "Transaction not found.\n",                             // (19) Error - Not found
        "Invalid option.\n",                                   // (20) Error - Invalid option
        "Press [ 1 ] to Continue || Press [ 2 ] to Exit: ",     // (21) Confirmation - Continue
        "Language changed to: %s\n",                            // (22) Confirmation - Language changed
        "New language (PT/FR/EN): ",                           // (23) Input - New language
        "Operation canceled. Returning to menu...\n",           // (24) Notice - Operation canceled
        "\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nPlease wait...\n",       // (25) Wait
        "Your Choice: ",                                        // (26) Prompt - Menu choice
        "Choose a category:\n",                                 // (27) Prompt para escolher categoria
        "Invalid category option. Please try again.\n",         // (28) Erro de categoria invalida
        "Category: ",                                           // (29) Label "Category" para exibicao
        "Choose report type:\n[1] General\n[2] Daily\n[3] Monthly\n[4] Cash Flow Chart\n[5] Back to main menu\nYour choice: ", // (30) Tipo de relatorio
        "Enter date in ISO 8601 format (yyyy-mm-dd): ",         // (31) Enter day
        "Enter year and month in ISO 8601 format (yyyy-mm): ",  // (32) Enter year and month
        "No transactions for this period.\n",                   // (33) No transactions
        "Daily Report for %04d-%02d-%02d\n",                   // (34) Titulo Relatorio Diario (YEAR-MONTH-DAY)
        "Monthly Report for %04d-%02d\n",                          // (35) Titulo Relatorio Mensal (YEAR-MONTH)
        "Error reading date. Expected format: yyyy-mm-dd. (ISO 8601)\n",     //(36) Error reading date
        "Memory allocation error when reading movement!\n",       // (37) Memory
        "Invalid amount! Please enter a valid integer or ZERO/NEGATIVE to cancel.\n", // (38) Error - Invalid amount
        "Invalid date! Please enter a valid date (yyyy-mm-dd).\n", // (39) Error - Invalid date
        "Income: ",                                             // (40) Income Chart
        "\nExpenses: ",                                         // (41) Expenses Chart
        "\nCurrent balance:",                                   // (42) Saldo
        "We would like to collect anonymous usage data to improve the application. \nDo you agree to data sharing?\n", // (43) Pergunta de Consentimento (EN)
        "--- GENERAL FINANCIAL REPORT ---\n",                   // (44) Título Relatório Geral
        "No transactions recorded yet.\n",                      // (45) Nenhuma movimentação (Relatório Geral)
        "\n--- CASH FLOW CHART ---\n",                          // (46) Título Gráfico de Fluxo de Caixa
        "\n+_+_+_+_+_+_+_+_+ == FINANCIAL GOAL == +_+_+_+_+_+_+_+_+_+_+_\n", // (47) Título da Meta Financeira
        "Please enter the name of your financial goal: ",       // (48) Pergunta pelo nome da meta
        "What would be the target amount (e.g., 120099 for $1200.99 CAD): ", // (49) Pergunta pelo valor da meta
        "\nGoal: %s\n",                                         // (50) Exibe o nome da meta
        "Goal Amount: ",                                        // (51) Exibe o valor da meta
        " CAD\n",                                               // (52) Moeda CAD
        "Congratulations! You have already reached your financial goal!\n",// (53) Mensagem de parabéns
        "Current balance: ",                                    // (54) Exibe o saldo atual
        "Remaining: ",                                          // (55) Exibe o valor restante para a meta
        "\n\n\tProgresso:\n\t[",                                 // (56) Título da barra de progresso
        "] %.0f%%\n",                                           // (57) Final da barra de progresso e porcentagem
        "Thank you! Your data will help us improve the application.\n" // (58) Agradecimento de consentimento EN
    }
};

// --- Protótipos das Funções ---
void gerenciarIdioma();
void bufferLimpo();
void beep();
void carregarMovimentacoes(const char *nomeArquivo);
void consultarSaldo();
int dataValida(int dia, int mes, int ano); // Reintroduzida
void despedida();
void digitar(const char *mensagem, unsigned int atraso_ms);
void expandirLista();
int exibirMenuConsentimentoDados();
void exibirMenuPrincipal();
void exibirMetaFinanceira();
void gerenciarCadastroMovimentacao(char tipoMovimentacao);
void gerenciarRemocaoMovimentacao();
void gerenciarSaldoEMeta();
void imprimirMovimentacoes(int tipoRelatorio, int dia, int mes, int ano);
void imprimirGraficoFluxoCaixa();
void gerenciarMenuRelatorios();
void imprimirValor(int centavos);
void inserirMovimentacao(Movimentacao m);
int lerEscolha();
int lerValorInteiro(int mensagem_prompt_key_index, int mensagem_erro_key_index, int pode_cancelar);
int lerDataComValidacao(int *dia, int *mes, int *ano, int tipo_leitura);
void lerStringSimples(char *buffer, int tamanho);
void limparTela();
Movimentacao *lerMovimentacao(char tipo);
void pausarExecucao();
void projetarMetaFinanceira(); 
int removerMovimentacao(char desc[]);
void salvarTodasMovimentacoes(const char *nomeArquivo);
void solicitarNovoNomeUsuario();
void tratarOpcaoInvalida();

int main() {/*******************************************[ INICIO DO MAIN ]*****************************************/
    int opcao;
    limparTela();
    carregarMovimentacoes("df.bin"); 
    char mensagemBoasVindasInicial[200];
    sprintf(mensagemBoasVindasInicial, T(0), nomeUsuario);
    digitar(mensagemBoasVindasInicial, 25);

    do {
        exibirMenuPrincipal();
        int leitura_opcao = scanf("%i", &opcao);
        bufferLimpo(); 

        if (leitura_opcao != 1) opcao = -1; // Define uma opção inválida para acionar o default
        switch (opcao) {
            case 1: /*_______________________________________(Cadastrar Receita )_______________________________________*/
                gerenciarCadastroMovimentacao('R');
                break;
            case 2: /*_______________________________________(Cadastrar Despesa)_______________________________________*/
                gerenciarCadastroMovimentacao('D');
                break;
            case 3: /*_______________________________________(Consultar Saldo)_______________________________________*/
                gerenciarSaldoEMeta();
                break;
            case 4: /*_______________________________________(Gerar Relatorio)_______________________________________*/
                limparTela();
                gerenciarMenuRelatorios();
                pausarExecucao();
                break;
            case 5: /*_______________________________________(Alterar Idiomas)_______________________________________*/
                limparTela();
                gerenciarIdioma();
                break;
            case 6: /*_____________________________________(Remover Movimentacao)_______________________________________*/
                gerenciarRemocaoMovimentacao();
                pausarExecucao();
                break;
            case 7: /*___________________________________________( Sair )_______________________________________*/
                salvarTodasMovimentacoes("df.bin"); 
                limparTela();
                despedida();
                break;
            default:
                tratarOpcaoInvalida();
        }
    } while (opcao != 7);
    free(lista);    // Liberar memória alocada dinamicamente
    lista = NULL;   // Medida de segurança 
    return 0;
}/*******************************************************[ FIM DO MAIN ] *****************************************/
/*CATEGORIZAÇÃO DE FUNÇÕES 

Funções Finais (Ligadas ao Menu Principal)

(Funções diretamente acessadas através de um item do menu principal no main, orquestrando operações para o usuário.)
•	main(): A função principal do programa. É o ponto de entrada e o orquestrador principal, gerenciando o ciclo de vida da aplicação: inicialização (carregamento de dados), loop principal (exibição de menu e processamento de opções) e encerramento (salvamento de dados e liberação de memória). (Corresponde ao controle geral do programa e à opção [7] Sair que encerra o loop).
•	gerenciarIdioma(): Permite ao usuário selecionar um novo idioma para a interface do programa. Inclui lógica para solicitar consentimento de dados e um novo nome de usuário caso o idioma seja alterado para Francês ou Inglês. (Corresponde à opção [5] Alterar Idioma do menu ).
•	gerenciarCadastroMovimentacao(char tipoMovimentacao): Controla o fluxo de cadastro de novas movimentações (receitas ou despesas). Solicita ao usuário todas as informações necessárias e valida as entradas. (Corresponde às opções [1] Cadastrar Receita e [2] Cadastrar Despesa do menu).
•	gerenciarMenuRelatorios(): Apresenta um submenu ao usuário para que ele possa escolher o tipo de relatório financeiro que deseja gerar (geral, diário, mensal, ou gráfico de fluxo de caixa). (Corresponde à opção [4] Gerar Relatório do menu).
•	gerenciarRemocaoMovimentacao(): Permite ao usuário remover uma movimentação existente. O usuário insere a descrição da movimentação a ser removida, e a função realiza a busca e remoção. (Corresponde à opção [6] Remover Movimentação do menu).
•	gerenciarSaldoEMeta(): Agrupa as funcionalidades de consulta de saldo e exibição/definição de metas financeiras, oferecendo um submenu para o usuário interagir com essas opções. (Corresponde à opção [3] Consultar Saldo do menu).

Funções Intermediárias

(Funções que realizam algum tipo de trabalho para as funções finais, geralmente agrupando operações básicas ou realizando cálculos e manipulações de dados mais complexas.)
•	carregarMovimentacoes(const char *nomeArquivo): Carrega todas as movimentações financeiras previamente salvas e os dados da meta financeira de um arquivo binário especificado. Implementa tratamento de erro para falhas na leitura.
•	consultarSaldo(): Calcula o saldo total, o total de receitas e o total de despesas a partir das movimentações registradas e os exibe no console.
•	despedida(): Exibe mensagens de despedida em todos os idiomas suportados e introduz um pequeno atraso antes que o programa seja encerrado, proporcionando uma transição suave.
•	exibirMenuConsentimentoDados(): Apresenta uma tela de consentimento ao usuário, perguntando se ele concorda em compartilhar dados de uso anônimos. Esta funcionalidade é ativada apenas quando o idioma é Francês ou Inglês. Retorna a escolha do usuário.
•	exibirMetaFinanceira(): Exibe os detalhes da meta financeira cadastrada, incluindo seu nome, valor e o progresso atual em relação ao saldo, acompanhado de uma barra de progresso visual.
•	expandirLista(): Função utilitária que dobra a capacidade alocada para o vetor dinâmico lista de movimentações. É chamada quando o número de movimentações atinge a capacidade atual.
•	imprimirGraficoFluxoCaixa(): Gera um gráfico de fluxo de caixa simplificado utilizando caracteres ASCII no console, mostrando visualmente as proporções de receitas, despesas e saldo total.
•	imprimirMovimentacoes(int tipoRelatorio, int diaFiltro, int mesFiltro, int anoFiltro): Imprime as movimentações financeiras com base no tipo de relatório (geral, diário ou mensal) e filtros de data.
•	inserirMovimentacao(Movimentacao m): Adiciona uma nova movimentação ao vetor dinâmico lista, expandindo-o se necessário.
•	lerMovimentacao(char tipo): Aloca memória dinamicamente para uma nova movimentação, solicita e lê todos os detalhes da transação (valor, descrição, categoria, data) e retorna um ponteiro para a estrutura preenchida.
•	projetarMetaFinanceira(): Permite ao usuário definir ou atualizar sua meta financeira. Após a definição, exibe o nome da meta, o valor e o progresso em relação ao saldo atual.
•	removerMovimentacao(char desc[]): Procura e remove uma movimentação específica da lista com base na descrição fornecida.
•	salvarTodasMovimentacoes(const char *nomeArquivo): Salva todas as movimentações financeiras, o nome do usuário e os dados da meta financeira em um arquivo binário para persistência.
•	solicitarNovoNomeUsuario(): Solicita ao usuário que digite e armazene um novo nome para ser usado nas saudações do sistema.

Funções Básicas

(Funções compartilhadas com diversas outras funções de forma recursiva e recorrente no código. Geralmente lidam com operações de baixo nível, utilitários ou validações fundamentais.)
•	beep(): Emite um bipe sonoro através do console usado para alertar o usuário sobre erros.
•	bufferLimpo(): Limpa o buffer de entrada do teclado.
•	dataValida(int dia, int mes, int ano): Uma função de validação que verifica se uma data fornecida (dia, mês, ano) é logicamente válida, incluindo a consideração de anos bissextos.
•	digitar(const char *mensagem, unsigned int atraso_ms): Imprime uma mensagem caractere por caractere, simulando o efeito de digitação.
•	imprimirValor(int centavos): Formata e imprime um valor inteiro em centavos para o formato monetário canadense (CAD), exibindo-o com duas casas decimais.
•	lerEscolha(): Solicita e valida a escolha do usuário para continuar ou sair de uma operação.
•	lerDataComValidacao(int *dia, int *mes, int *ano, int tipo_leitura): Lê uma data do usuário, validando o formato e a validade da data. Suporta leitura completa (dd/mm/aaaa) ou apenas mês e ano (mm/aaaa).
•	lerValorInteiro(int mensagem_prompt_key_index, int mensagem_erro_key_index, int pode_cancelar): Lê um valor inteiro do usuário, exibe mensagens de prompt e erro conforme o dicionário, e oferece a opção de cancelar a entrada.
•	lerStringSimples(char *buffer, int tamanho): Lê uma linha de texto do console para um buffer de caracteres, removendo o caractere de nova linha que fgets inclui.
•	limparTela(): Executa um comando do sistema operacional (cls para Windows, clear para Unix-like) para limpar a tela do console.
•	pausarExecucao(): Exibe uma mensagem solicitando que o usuário pressione ENTER para continuar e aguarda a entrada, mantendo a interface do console estável.
•	tratarOpcaoInvalida(): Exibe uma mensagem de erro genérica para quando o usuário insere uma opção inválida em menus, acompanhada de um bipe.
*/
// --- Implementações das Funções (em ordem alfabética para organização) ---
void beep() {
    printf("\a");
}

void bufferLimpo() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void carregarMovimentacoes(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo) return; 
    if (lista != NULL) {
        free(lista);
        lista = NULL;
    }
    capacidade = 0;
    total = 0; // Resetar total também, para começar limpo
    
    if (fread(nomeUsuario, sizeof(nomeUsuario), 1, arquivo) != 1) { 
        strcpy(nomeUsuario, "Filipe"); // Se falhar a leitura do nome, assume padrão
    }
    if (fread(metaFinanceiraNome, sizeof(metaFinanceiraNome), 1, arquivo) != 1 ||
        fread(&metaFinanceiraValorCentavos, sizeof(metaFinanceiraValorCentavos), 1, arquivo) != 1 ||
        fread(&metaFinanceiraCadastrada, sizeof(metaFinanceiraCadastrada), 1, arquivo) != 1) {
        // Se falhar a leitura da meta, assume que não há meta cadastrada
        strcpy(metaFinanceiraNome, "");
        metaFinanceiraValorCentavos = 0;
        metaFinanceiraCadastrada = 0;
    }
    
    // Tenta ler 'total' de movimentações
    if (fread(&total, sizeof(total), 1, arquivo) != 1) {
        total = 0; // Se falhar a leitura do total, assume 0
    }
    const int MAX_MOVIMENTACOES_PERMITIDAS_LOCAL = 100000; 

    if (total > 0 && total <= MAX_MOVIMENTACOES_PERMITIDAS_LOCAL) {
        capacidade = total; // Ajusta a capacidade para o total carregado
        lista = (Movimentacao*) malloc(capacidade * sizeof(Movimentacao)); 
        if (!lista) {
            printf("%s", textos[idiomaAtual][37]); // (37) Erro de alocacao de memoria ao ler movimentacao!
            exit(1);
        }
        if (fread(lista, sizeof(Movimentacao), (size_t)total, arquivo) != (size_t)total) {
            free(lista);
            lista = NULL;
            total = 0;
            capacidade = 0;
        }
    } else {        
        if (lista) { 
            free(lista);
            lista = NULL;
        }
        total = 0;
        capacidade = 0;
    } 
    
    fclose(arquivo);
}
void consultarSaldo() {
    int r = 0, d = 0;
    for (int willow = 0; willow < total; willow++) { 
        if (lista[willow].tipo == 'R') r += lista[willow].valorCentavos;
        else if (lista[willow].tipo == 'D') d += lista[willow].valorCentavos;
    }
    int saldo = r - d;    
    printf("\n--- $$$$$$ ---\n");
    PRINT_MSG(40); printf("..............."); imprimirValor(r); printf("\n"); // (40) "Receitas: "
    PRINT_MSG(41); printf("..............."); imprimirValor(d); printf("\n"); // (41) "Despesas: "
    PRINT_MSG(42); printf(".................."); imprimirValor(saldo); printf("\n\n"); // (42) "Saldo: "
}

int dataValida(int dia, int mes, int ano) {
    if (ano < 2000 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Índice 0 não utilizado 
    // Verifica ano bissexto para fevereiro
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[2] = 29;
    }
    if (dia < 1 || dia > diasNoMes[mes]) return 0;
    return 1;
}
void despedida() {
    PRINT_MSG(25); // (25) Aguarde
#ifdef _WIN32
    Sleep(1000); // 1 segundo para Windows 
#else
    usleep(1000 * 1000); // 1 segundo para Unix-like (usleep em microssegundos) 
#endif
    digitar("\n \t Ate mais! Obrigado por interagir. Volte sempre!", 25);
    digitar("\n \t \t A bientot ! Merci d'avoir interagi. Reviens quand tu veux.", 25);
    digitar("\n \t \t \t See you soon! Thanks for interacting. Come back anytime.\n", 25);
}
void digitar(const char *mensagem, unsigned int atraso_ms) {
    for (int willow = 0; mensagem[willow] != '\0'; willow++) { 
        putchar(mensagem[willow]);
        fflush(stdout); // Garante que o caractere seja exibido imediatamente 
#ifdef _WIN32
        Sleep(atraso_ms); // Para Windows
#else
        usleep(atraso_ms * 1000); // Para Unix-like (usleep em microssegundos) 
#endif
    }
}

int exibirMenuConsentimentoDados() {
    int escolhaConsentimento;
    if (idiomaAtual == FR || idiomaAtual == EN) {
        TYPE_MSG(43); // (43) Pergunta de Consentimento
        PRINT_MSG(15); // (15) "Digite [ 1 ] para SIM || Digite [ 2 ] para Sair: "

        while (1) {
            if (scanf("%d", &escolhaConsentimento) != 1) {
                bufferLimpo();
                tratarOpcaoInvalida();
                PRINT_MSG(15); // (15) "Digite [ 1 ] para SIM || Digite [ 2 ] para Sair: "
                continue; // Volta para o início do loop. 
            }
            bufferLimpo();
            if (escolhaConsentimento == 1 || escolhaConsentimento == 2) {
                break; // Entrada válida, sai do loop 
            } else {
                tratarOpcaoInvalida();
                PRINT_MSG(15); // (15) "Digite [ 1 ] para SIM || Digite [ 2 ] para Sair: "
            }
        }
        if (escolhaConsentimento == 1) { // Se o usuário concordar 
            printf("\n");
            TYPE_MSG(58); // (58) Agradecimento de consentimento
            return 1; // Retorna 1 para indicar que o programa pode continuar 
        } else return 0; // Retorna 0 para indicar que o programa deve sair 
    }
    return 1;
}

void exibirMenuPrincipal() {
    limparTela();
    printf(T(0), nomeUsuario); // Reutiliza a mensagem de boas-vindas com o nome do usuário
    PRINT_MSG(8); // (8) Cabeçalho - Título
    for (int willow = 1; willow <= 7; willow++) { // Alterado 'i' para 'willow'
        printf("%s\n", T(willow)); // Textos de 1 a 7 do menu
    }
    PRINT_MSG(26); // (26) Sua Escolha:
}

void exibirMetaFinanceira() {
    PRINT_MSG(47); // Título da Meta Financeira
    if (metaFinanceiraCadastrada) {
        int r = 0, d = 0;
        for (int willow = 0; willow < total; willow++) {
            if (lista[willow].tipo == 'R') r += lista[willow].valorCentavos;
            else d += lista[willow].valorCentavos;
        }
        int saldo = r - d;

        printf(T(50), metaFinanceiraNome); // Exibe o nome da meta
        PRINT_MSG(51); // "Valor da Meta: "
        imprimirValor(metaFinanceiraValorCentavos);
        PRINT_MSG(52); // " CAD\n"

        if (saldo >= metaFinanceiraValorCentavos) {
            PRINT_MSG(53); // "Parabens! Voce ja atingiu sua meta financeira!\n"
            PRINT_MSG(54); // "Saldo atual: "
            imprimirValor(saldo);
            PRINT_MSG(52); // " CAD\n"
        } else {
            PRINT_MSG(54); // "Saldo atual: "
            imprimirValor(saldo);
            PRINT_MSG(52); // " CAD\n"
            PRINT_MSG(55); // "Faltam: "
            imprimirValor(metaFinanceiraValorCentavos - saldo);
            PRINT_MSG(52); // " CAD\n"

            // BARRA DE PROGRESO FINANCEIRA
            float progresso = (float)saldo / (float)metaFinanceiraValorCentavos;
            if (progresso > 1.0) progresso = 1.0;
            int largura = 50;
            int preenchido = (int)(progresso * largura);

            PRINT_MSG(56); // Título da barra de progresso
            for (int willow = 0; willow < largura; willow++) {
                if (willow < preenchido)
                    printf("$");
                else
                    printf(" ");
            }
            printf(T(57), progresso * 100); // Final da barra e porcentagem
        }
    } else {
        printf("\n%s\n", idiomaAtual == PT ? "Nenhuma meta financeira cadastrada ainda." :
                          idiomaAtual == FR ? "Aucun objectif financier defini pour le moment." :
                          "No financial goal set yet.");
    }
}

void expandirLista() {
    capacidade = (capacidade == 0) ? 10 : capacidade * 2; 
    Movimentacao *novaLista = realloc(lista, capacidade * sizeof(Movimentacao));
    if (!novaLista) {
        TYPE_MSG(37); // (37) Error Memory
        exit(1);
    }
    lista = novaLista;
}

void gerenciarCadastroMovimentacao(char tipoMovimentacao) {
    int subOpcao = 1; 
    char mensagemConfirmacao[50]; 

    if (tipoMovimentacao == 'R') {
        strcpy(mensagemConfirmacao, T(12)); // (12) "Receita registrada com sucesso!"
    } else { 
        strcpy(mensagemConfirmacao, T(13)); // (13) "Despesa registrada com sucesso!"
    }

    while (subOpcao != 2) {
        limparTela(); 
        Movimentacao *m_ptr = lerMovimentacao(tipoMovimentacao); // lerMovimentacao já aloca a memória
        if (m_ptr == NULL) { // lerMovimentacao retorna NULL se a operação foi cancelada ou falhou
            TYPE_MSG(24); // (24) "Operacao cancelada. Retornando ao menu..."
            break;
        }

        digitar(mensagemConfirmacao, 25); 

        inserirMovimentacao(*m_ptr); 

        PRINT_MSG(9); // (9) "Descricao da transacao: "
        printf("%s\n", m_ptr->descricao); 
        imprimirValor(m_ptr->valorCentavos); 
        printf("\n%s%04i-%02i-%02i\n", T(11), m_ptr->ano, m_ptr->mes, m_ptr->dia);
        printf("%s%s\n", T(29), nomesCategorias[m_ptr->categoriaMovimentacao.tipoCategoria][idiomaAtual]);
        free(m_ptr); 
        subOpcao = lerEscolha(); 
    }
}

void gerenciarIdioma() {
    char idioma[20];
    PRINT_MSG(23); // (23) Entrada - Novo idioma
    int leitura = scanf("%s", idioma);
    bufferLimpo();
    Idioma idiomaAnterior = idiomaAtual;
    int resultadoConsentimento = 1; // 1 = pode continuar, 0 = deve sair

    if (leitura != 1) {
        tratarOpcaoInvalida();
        return;
    }
    if (strcmp(idioma, "FR") == 0 || strcmp(idioma, "fr") == 0) idiomaAtual = FR;
    else if (strcmp(idioma, "EN") == 0 || strcmp(idioma, "en") == 0) idiomaAtual = EN;
    else if (strcmp(idioma, "PT") == 0 || strcmp(idioma, "pt") == 0) idiomaAtual = PT;
    else {
        tratarOpcaoInvalida();
        return;
    }
    printf(T(22), idioma); // (22) Confirmacao - Idioma alterado

    int solicitar_dados_e_nome = 0;
    if (idiomaAtual == FR || idiomaAtual == EN) { // Verifica se o idioma atual é FR ou EN E se houve uma mudança de idioma
        if (idiomaAnterior != idiomaAtual ||
            (idiomaAnterior == FR && idiomaAtual == FR) ||
            (idiomaAnterior == EN && idiomaAtual == EN)) {
            solicitar_dados_e_nome = 1;
        }
    }

    if (solicitar_dados_e_nome) {
        resultadoConsentimento = exibirMenuConsentimentoDados();
        if (resultadoConsentimento == 0) {
            salvarTodasMovimentacoes("df.bin");
            limparTela();
            despedida();
            exit(0);
        }
        solicitarNovoNomeUsuario(); // Esta linha só será alcançada se o consentimento for dado
    }
    
    if (resultadoConsentimento == 0) {
        salvarTodasMovimentacoes("df.bin");
        limparTela();
        despedida();
        exit(0);
    }
}

void gerenciarMenuRelatorios() {
    int subOpcao;
    int dia = 0, mes = 0, ano = 0; 

    do {
        limparTela();
        printf("%s", textos[idiomaAtual][30]); // (30) Tipo de relatorio e sub-menu
        scanf("%d", &subOpcao); 
        bufferLimpo();
        switch (subOpcao) {
            case 1: // Geral 
                limparTela();
                imprimirMovimentacoes(0, 0, 0, 0); // Tipo 0 para geral 
                break;
            case 2: // Diario 
                limparTela();
                if (!lerDataComValidacao(&dia, &mes, &ano, 1)) { 
                    digitar(textos[idiomaAtual][24], 25); // (24) Operação cancelada.
                    break;
                }
                imprimirMovimentacoes(1, dia, mes, ano); 
                break;
            case 3: // Mensal 
                limparTela();
                if (!lerDataComValidacao(&dia, &mes, &ano, 2)) { 
                    digitar(textos[idiomaAtual][24], 25); // (24) Operação cancelada.
                    break;
                }
                imprimirMovimentacoes(2, 0, mes, ano); 
                break;
            case 4: // Gráfico de Fluxo de Caixa 
                limparTela();
                imprimirGraficoFluxoCaixa();
                break;
            case 5: 
                digitar(textos[idiomaAtual][24], 25); // (24) Operação cancelada.
                break;
            default:
                tratarOpcaoInvalida();
                break;
        }
        if (subOpcao != 5) { 
            pausarExecucao();
        }
    } while (subOpcao != 5);
}

void gerenciarRemocaoMovimentacao() {
    char desc_para_remover[100]; 
    while (1) {
        limparTela(); 
        TYPE_MSG(17); // (17) "Informe a descricao do que deseja remover ou ZERO para sair:"
        lerStringSimples(desc_para_remover, sizeof(desc_para_remover)); 

        if (strcmp(desc_para_remover, "0") == 0) { 
            TYPE_MSG(24); // (24) "Operacao cancelada. Retornando ao menu..."
            break;
        }
        if (strlen(desc_para_remover) == 0) 
            continue;

        if (removerMovimentacao(desc_para_remover)) 
            TYPE_MSG(18); // (18) "Movimentacao removida com sucesso."
        else
            PRINT_MSG(19); // (19) "Nenhum registro com essa descricao encontrado."

        pausarExecucao();
    }
}

void gerenciarSaldoEMeta() {
    int subOpcao; 
    limparTela(); 
    consultarSaldo(); 
    exibirMetaFinanceira(); 
    printf("\n%s\n", idiomaAtual == PT ? "Opcoes de Meta Financeira:" :
                      idiomaAtual == FR ? "Options d'objectif financier:" :
                      "Financial Goal Options:");
    printf("[1] %s\n", idiomaAtual == PT ? "Definir/Atualizar Meta" :
                        idiomaAtual == FR ? "Definir/Mettre a jour l'objectif" :
                        "Set/Update Goal");
    printf("[2] %s\n", idiomaAtual == PT ? "Voltar ao Menu Principal" :
                        idiomaAtual == FR ? "Retour au menu principal" :
                        "Back to Main Menu");
    
    PRINT_MSG(26); //(26) "Sua Escolha: "
    scanf("%d", &subOpcao); 
    bufferLimpo(); 

    if (subOpcao == 1) {
        projetarMetaFinanceira(); 
    } else if (subOpcao == 2) { 
        TYPE_MSG(24); // (24) "Operacao cancelada. Retornando ao menu..."
    } else {
        tratarOpcaoInvalida();
    }
    pausarExecucao(); 
}

void imprimirGraficoFluxoCaixa() {
    int receita_total = 0, despesa_total = 0;
    for (int willow = 0; willow < total; willow++) { 
        if (lista[willow].tipo == 'R') receita_total += lista[willow].valorCentavos;
        else if (lista[willow].tipo == 'D') despesa_total += lista[willow].valorCentavos;
    }
    int saldo_atual = receita_total - despesa_total; // Calcula o saldo antes de determinar o valor máximo
    
    int largura_max_barras = 50; 
        int max_valor_para_proporcao = MAX(abs(receita_total), abs(despesa_total));
    max_valor_para_proporcao = MAX(max_valor_para_proporcao, abs(saldo_atual));

    int receita_barras = (receita_total > 0 && max_valor_para_proporcao > 0) ? (int)((float)receita_total / max_valor_para_proporcao * largura_max_barras) : 0;
    int despesa_barras = (despesa_total > 0 && max_valor_para_proporcao > 0) ? (int)((float)despesa_total / max_valor_para_proporcao * largura_max_barras) : 0;
    int saldo_barras = (saldo_atual != 0 && max_valor_para_proporcao > 0) ? (int)((float)abs(saldo_atual) / max_valor_para_proporcao * largura_max_barras) : 0;

    if (receita_total > 0 && receita_barras == 0) receita_barras = 1;
    if (despesa_total > 0 && despesa_barras == 0) despesa_barras = 1;
    if (saldo_atual != 0 && saldo_barras == 0) saldo_barras = 1;

    PRINT_MSG(46); // (46) Título Gráfico de Fluxo de Caixa
    PRINT_MSG(40); // (40) "Receitas: "
    for (int willow = 0; willow < receita_barras; willow++) printf("$");
    printf(" ("); imprimirValor(receita_total); printf(")\n"); 

    PRINT_MSG(41); // (41) "Despesas: "
    for (int willow = 0; willow < despesa_barras; willow++) printf("$"); 
    printf(" ("); imprimirValor(despesa_total); printf(")\n"); 
    
    PRINT_MSG(42); // (42) "Saldo: "
    for (int willow = 0; willow < saldo_barras; willow++) printf("$"); 
    printf(" ("); imprimirValor(saldo_atual); printf(")\n\n");     
}

// tipoRelatorio: 0 para Geral, 1 para Diário, 2 para Mensal 
void imprimirMovimentacoes(int tipoRelatorio, int diaFiltro, int mesFiltro, int anoFiltro) {
    printf("\n"); 
    if (tipoRelatorio == 0) { 
        PRINT_MSG(44); // (44) Título Relatório Geral
    } else if (tipoRelatorio == 1) { 
        printf(T(34), anoFiltro, mesFiltro, diaFiltro); 
    } else if (tipoRelatorio == 2) { 
        printf(T(35), anoFiltro, mesFiltro);
    }
    printf("---------------------------\n"); 
    if (total == 0 && tipoRelatorio == 0) { 
        PRINT_MSG(45); // (45) "Nenhuma movimentacao registrada ainda.\n"
        return;
    }

    int transacoesEncontradas = 0;
    for (int willow = 0; willow < total; willow++) { 
        int imprimir = 0;
        if (tipoRelatorio == 0) { 
            imprimir = 1;
        } else if (tipoRelatorio == 1) { 
            if (lista[willow].dia == diaFiltro && lista[willow].mes == mesFiltro && lista[willow].ano == anoFiltro) {
                imprimir = 1;
            }
        } else if (tipoRelatorio == 2) { 
            if (lista[willow].mes == mesFiltro && lista[willow].ano == anoFiltro) {
                imprimir = 1;
            }
        }

        if (imprimir) {
            if (tipoRelatorio != 0) { 
                printf("[%02d] ", lista[willow].dia);
            }
            printf("[%c] %s - %s - ", 
                   lista[willow].tipo,
                   lista[willow].descricao,
                   nomesCategorias[lista[willow].categoriaMovimentacao.tipoCategoria][idiomaAtual]);
            imprimirValor(lista[willow].valorCentavos);
            printf(" CAD - Data: %02d/%02d/%04d\n", 
                   lista[willow].dia, lista[willow].mes, lista[willow].ano);
            transacoesEncontradas++;
        }
    }

    if (transacoesEncontradas == 0 && tipoRelatorio != 0) { 
        PRINT_MSG(33); // (33) "Nao ha transacoes para este periodo."
    }
    printf("\n"); 
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
    int escolha = 0;
    int leitura;
    while (1) {
        PRINT_MSG(21); // (21) "Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: "
        leitura = scanf("%i", &escolha);
        bufferLimpo();

        if (leitura != 1 || (escolha != 1 && escolha != 2)) {
            tratarOpcaoInvalida();
        } else {
            return escolha;
        }
    }
}

int lerDataComValidacao(int *dia, int *mes, int *ano, int tipo_leitura) {
    char linha_data[20];
    int d_temp, m_temp, a_temp;
    int sucesso_leitura;

    do {
        if (tipo_leitura == 1 || tipo_leitura == 0) { // Relatório diário ou cadastro de movimentação (aaaa-mm-dd)
            PRINT_MSG(31); // (31)"Digite a data (aaaa-mm-dd): " (ou 11)
            if (fgets(linha_data, sizeof(linha_data), stdin) == NULL) {
                return 0;
            }
            // *** ALTERAÇÃO AQUI ***
            sucesso_leitura = sscanf(linha_data, "%d-%d-%d", &a_temp, &m_temp, &d_temp);

            if (sucesso_leitura == 3 && dataValida(d_temp, m_temp, a_temp)) {
                *dia = d_temp;
                *mes = m_temp;
                *ano = a_temp;
                return 1;
            }
        } else if (tipo_leitura == 2) { // Relatório mensal (aaaa-mm)
            PRINT_MSG(32); //(32) "Digite o mes e ano (aaaa-mm): "
            if (fgets(linha_data, sizeof(linha_data), stdin) == NULL) {
                return 0;
            }
            sucesso_leitura = sscanf(linha_data, "%d-%d", &a_temp, &m_temp);

            if (sucesso_leitura == 2 && dataValida(1, m_temp, a_temp)) { // Dia é 1 para validação mensal
                *dia = 1;
                *mes = m_temp;
                *ano = a_temp;
                return 1;
            }
        }

        PRINT_MSG(39); // "Data invalida! Por favor, insira uma data valida (aaaa-mm-dd)."
        beep();

    } while (1);
}

int lerValorInteiro(int mensagem_prompt_key_index, int mensagem_erro_key_index, int pode_cancelar) {
    int valor;
    int leitura;
    char linha[50]; // Buffer para ler a linha inteira

    do {
        PRINT_MSG(mensagem_prompt_key_index);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return -999999; // Erro de leitura, considera como cancelamento
        }        
        // Tenta converter a linha para um inteiro
        leitura = sscanf(linha, "%i", &valor);

        if (leitura != 1) { // Não conseguiu ler um número inteiro
            PRINT_MSG(mensagem_erro_key_index);
            beep();
        } else if (pode_cancelar && (valor == 0 || valor == -1)) {
            return -999999; // Retorna um valor específico para indicar cancelamento
        } else {
            return valor;
        }
    } while (1);
}
void lerStringSimples(char *buffer, int tamanho) { // fgets já lê o \n, strcspn o remove
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
Movimentacao *lerMovimentacao(char tipo) {
    Movimentacao *m = (Movimentacao *)malloc(sizeof(Movimentacao));
    if (m == NULL) {
        PRINT_MSG(37);
        return NULL;
    }

    m->valorCentavos = lerValorInteiro(10, 38, 1);
    if (m->valorCentavos == -999999) {
        free(m);
        return NULL;
    }

    PRINT_MSG(9);
    lerStringSimples(m->descricao, sizeof(m->descricao));

    int escolhaCategoriaNum = -1;
    int leitura_categoria; 
    do {
        PRINT_MSG(27);
        for (int willow = 0; willow < NUM_CATEGORIAS; willow++) { 
            printf("[%d] %s\n", willow + 1, nomesCategorias[willow][idiomaAtual]);
        }
        PRINT_MSG(26);
        char linha_categoria[10];
        if (fgets(linha_categoria, sizeof(linha_categoria), stdin) == NULL) {
             free(m);
             return NULL;
        }
        leitura_categoria = sscanf(linha_categoria, "%i", &escolhaCategoriaNum);

        if (leitura_categoria != 1 || escolhaCategoriaNum < 1 || escolhaCategoriaNum > NUM_CATEGORIAS) {
            PRINT_MSG(28);
            beep();
        } else {
            m->categoriaMovimentacao.tipoCategoria = (CategoriaValida)(escolhaCategoriaNum - 1);
            break;
        }
    } while (1);
    if (!lerDataComValidacao(&m->dia, &m->mes, &m->ano, 0)) {
        free(m);
        return NULL;
    }
    m->tipo = tipo;
    return m;
}

void pausarExecucao() {
    TYPE_MSG(16);
    getchar();
}

void projetarMetaFinanceira() {
    int r = 0, d = 0;
    char tempNomeMeta[100];
    int tempMetaValor;

    PRINT_MSG(47);
    PRINT_MSG(48);
    lerStringSimples(tempNomeMeta, sizeof(tempNomeMeta)); 

    for (int willow = 0; willow < total; willow++) { 
        if (lista[willow].tipo == 'R') r += lista[willow].valorCentavos;
        else d += lista[willow].valorCentavos;
    }
    int saldo = r - d;

    tempMetaValor = lerValorInteiro(49, 38, 0);
    strcpy(metaFinanceiraNome, tempNomeMeta);
    metaFinanceiraValorCentavos = tempMetaValor;
    metaFinanceiraCadastrada = 1; 
    printf(T(50), metaFinanceiraNome);
    PRINT_MSG(51);
    imprimirValor(metaFinanceiraValorCentavos);
    PRINT_MSG(52);

    if (saldo >= metaFinanceiraValorCentavos) {
        PRINT_MSG(53);
        PRINT_MSG(54);
        imprimirValor(saldo);
        PRINT_MSG(52);
    } else {
        PRINT_MSG(54);
        imprimirValor(saldo);
        PRINT_MSG(52);
        PRINT_MSG(55);
        imprimirValor(metaFinanceiraValorCentavos - saldo);
        PRINT_MSG(52);

        // BARRA DE PROGRESO FINANCEIRA 
        float progresso = (float)saldo / (float)metaFinanceiraValorCentavos;
        if (progresso > 1.0) progresso = 1.0;
        int largura = 50;
        int preenchido = (int)(progresso * largura);

        PRINT_MSG(56);
        for (int willow = 0; willow < largura; willow++) { 
            if (willow < preenchido) 
                printf("$");
            else 
                printf(" "); 
        }
        printf(T(57), progresso * 100);
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
void salvarTodasMovimentacoes(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb"); 
    if (arquivo == NULL) {
        perror("Error to open the file to save"); 
        return;
    }
    fwrite(nomeUsuario, sizeof(nomeUsuario), 1, arquivo);
    fwrite(metaFinanceiraNome, sizeof(metaFinanceiraNome), 1, arquivo);
    fwrite(&metaFinanceiraValorCentavos, sizeof(metaFinanceiraValorCentavos), 1, arquivo);
    fwrite(&metaFinanceiraCadastrada, sizeof(metaFinanceiraCadastrada), 1, arquivo);
    fwrite(&total, sizeof(total), 1, arquivo); // Salva o total de itens
    if (total > 0) {
        fwrite(lista, sizeof(Movimentacao), total, arquivo);
    }
    fclose(arquivo); 
}

void solicitarNovoNomeUsuario() {
    printf("\n"); 
    if (idiomaAtual == FR) { 
        digitar("Veuillez entrer votre nom: ", 25); 
    } else { 
        digitar("Please enter your name: ", 25); 
    }
    lerStringSimples(nomeUsuario, sizeof(nomeUsuario)); 
}
void tratarOpcaoInvalida() {
    PRINT_MSG(20);
    beep();
}
//atualização 10/junho/2025