/******************************************************************************
DIARIO FINANCEIRO PESSOAL (PROJETO 9)
Data de criação: 27 mar 2025.
REPOSITÓRIO DO CÓDIGO: https://github.com/johnatanwillow/diario_financeiro
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 - Estrutura do Fluxograma
1️⃣ Início
2️⃣ Exibir Menu Principal

[1] Cadastrar Receita
[2] Cadastrar Despesa
[3] Exibir Saldo Atual
[4] Gerar Relatórios
[5] Alterar Idioma
[6] Salvar & Sair

3️⃣ Processamento das Opções

Se [1] ou [2]: Solicitar informações da transação por categoria diária e mensalmente 
{data, tipo, valor, descrição, categoria} (  ) e armazenar no arquivo/binário/BD (  ). 
Se [3]: Calcular saldo total (Receitas versus Despesas diaria e mensalmente) (  ) e projetar uma META FINANCEIRA (  ).
Se [4]: Exibir lista de transações {listando por dia específico e/ou mês específico} e gerar gráficos ASCII ou arquivos CSV (  ).
Se [5]: Invoca os menus em francês ou inglês conforme escolha do usuário ( X ).
4️⃣ Retornar ao menu ou sair do programa
Se [6]: Salva {com persistência de dados} e sai do programa com delay programado de 3s (  ).
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 - Persistência de Dados
○ Todas as transações financeiras registradas devem ser armazenadas em um arquivo binário,
garantindo que os dados sejam preservados após o encerramento do programa. (  )
○ O sistema deve carregar automaticamente os dados do arquivo ao ser iniciado, 
permitindo a continuidade do controle financeiro. (  )
 - Requisitos Técnicos
● O sistema deve ser implementado em C. ( X )
● O uso de structs ( ), vetores ( ), arquivos binários ( ) e ponteiros ( X ) é obrigatório. 
● O código deve ser modularizado, com funções bem definidas para cada operação do sistema. ( X )
● O sistema deve interagir com o usuário via entrada e saída de texto no console. ( X )
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

enum Idioma {
    PORTUGUES,  
    FRANCES,    
    INGLES      
};
// Rol de funções (consultar declaração de cada uma delas no rodapé): 
void limparTela();
void exibirMenu(const char* titulo, const char* opcoes[], int num_opcoes);
int entradaSaida(const char* titulo, const char* opcoes[], int num_opcoes);
int lerValor(const char* tipo, enum Idioma idioma);
void exibirTransacao(int* total, const char* tipo, enum Idioma idioma);
void exibirSaldo(int receita_total, int despesa_total);
void exibirRelatorio(int receita_total, int despesa_total);
int lerEscolha(enum Idioma idioma);
void french();
void english();

int categoria = 0, option = 0, opcao = 0, transacao = 0, receita_total = 0, despesa_total = 0;
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
        // Solicita a escolha do usuário
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
        case 1:
                /*O sistema deve permitir o registro de transações financeiras, com as seguintes informações:
                ■ Data da transação (dia, mês, ano)
                ■ Tipo de transação (receita ou despesa)
                ■ Valor da transação
                ■ Descrição (opcional, para detalhar a transação)
                ■ Categorias*/
                // Cadastrar Receita
                subOpcao = 1;
            opcao = 0;
            while (subOpcao != 2) {
                limparTela();
                printf("+_+== CARTEIRA DIGITAL ==+_+_\n");
                // Título da categoria de despesas
                const char* titulo = "E qual eh a categoria da receita? \n";
                
                // Opções de categoria
                const char* option [] = {
                    "BOLSA DE ESTUDOS",
                    "ESTAGIO EM STARTUP",
                    "MESADA DA MAMAE (ja convertido em CAD)",
                    "FREELANCE",
                    "OUTROS"
                };
                int num_opcoes = 6; // Número de categorias
                // Registrar a transação de despesa
                exibirTransacao(&receita_total, "RECEITA", PORTUGUES);
                // Ler a categoria de despesa
                categoria = entradaSaida(titulo, option, num_opcoes);  
                // Verificar se a categoria é válida e exibir saldo da despesa
                if (categoria >= 1 && categoria <= 6) {
                    printf("\nSua conta atual possui X RECEITA no montante de %i.%02i CAD \ncadastradas na categoria %i\n", receita_total / 100, receita_total % 100, categoria);
                    printf("  \n");
                } else {
                    printf("Opcao invalida!\n");
                }
        
                // Pergunta ao usuário se ele quer continuar ou sair
                printf("Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: ");
                scanf("%i", &subOpcao);
            }
            break;
        case 2:
            /*O sistema deve permitir o registro de transações financeiras, com as seguintes informações:
            ■ Data da transação (dia, mês, ano)
            ■ Tipo de transação (receita ou despesa)
            ■ Valor da transação
            ■ Descrição (opcional, para detalhar a transação)
            ■ Categorias*/
            subOpcao = 1;
            opcao = 0;
            while (subOpcao != 2) {
                limparTela();
                printf("+_+== CARTEIRA DIGITAL ==+_+_\n");
                // Título da categoria de despesas
                const char* titulo = "E qual eh a categoria da despesa? \n";
                // Opções de categoria
                const char* option [] = {
                    "ALIMENTACAO RESTAURANT FRANCES",
                    "TRANSPORTE DE UBER",
                    "ALUGUEL DO FLAT",
                    "ACADEMIA DO FLAT",
                    "BOATE",
                    "OUTROS", 
                    "NENHUM E RETORNAR"   
                };
                int num_opcoes = 7; // Número de categorias
                // Registrar a transação de despesa
                exibirTransacao(&receita_total, "DESPESA", PORTUGUES);
                // Ler a categoria de despesa
                categoria = entradaSaida(titulo, option, num_opcoes);  
                // Verificar se a categoria é válida e exibir saldo da despesa
                if (categoria >= 1 && categoria <= num_opcoes) {
                    printf("\nSua conta atual possui X DESPESAS no montante de %i.%02i CAD \ncadastradas na categoria %i\n", despesa_total / 100, despesa_total % 100, categoria);
                    printf("  \n");
                } else {
                    printf("Opcao invalida!\n");
                }
                 // Pergunta ao usuário se ele quer continuar ou sair
                subOpcao = lerEscolha(PORTUGUES);
                
            }
            break;
    
        case 3:
            /*O sistema deve calcular o saldo atualizado a partir das transações registradas:
            ■ O saldo inicial pode ser zero ou definido pelo usuário.
            ■ As receitas aumentam o saldo e as despesas diminuem.
            ○ O sistema deve permitir ao usuário cadastrar uma meta financeira mensal.*/
            limparTela();
            exibirSaldo(receita_total, despesa_total);                                   
            
            printf("Deseja cadastrar uma meta financeira?\n");
            printf("Digite [ 1 ] para SIM || Digite [ 2 ] para Sair: ");
            scanf("%d", &subOpcao);
            if (subOpcao == 1) {
                char nome_meta[100];
                int valor_meta;
                printf("Qual eh o nome da meta?: ");
                scanf(" %[^\n]", nome_meta);  // lê string com espaço
                printf("\nE qual eh o valor da meta financeira (Ex: digite 190000 para $1900.00 CAD: ");
                scanf("%d", &valor_meta);
                printf("Meta '%s' cadastrada com valor de $%i.%02i CAD.\n", nome_meta, valor_meta / 100, valor_meta % 100);
            }
            printf("  \n");
            printf("\n+_+_+_+_+_+_+_+_+ == META FINANCEIRA == +_+_+_+_+_+_+_+_+_+_+_\n"); 
            printf("  \n");
            printf("\nPressione Enter para continuar...\n");
            getchar();  // Limpar buffer
            getchar();  // Esperar Enter do usuário
            break;
        case 4:
            /*O sistema deve gerar relatórios que permitem visualizar:
            ■ Movimentação diária: lista de todas as transações de um dia específico.
            ■ Movimentação mensal: lista de todas as transações de um mês específico.
            ○ O sistema deve exibir gráficos de fluxo de caixa usando caracteres ASCII no console.*/
            while (subOpcao != 2) {
                limparTela();
                exibirRelatorio(receita_total, despesa_total);
                printf("Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: ");
                scanf("%d", &subOpcao);
            }
            break;
             
        case 5:        
            limparTela();
            printf("    [ 1 ] Francais\n");
            printf("    [ 2 ] English\n");
            printf("Choisissez/Choose: ");
            scanf("%d", &option);    
            
            if(option == 1) { french(); break;}  // Chama diretamente a função french() para exibir o menu em francês
            else if(option == 2){ english(); break;} // Chama diretamente a função english() para exibir o menu em inglês
        case 6:
            limparTela();
            printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nAguarde...\n");
            sleep(3);
            printf("\nAte mais! Obrigado por interagir. Volte sempre!\n");
            printf("\nA bientot ! Merci d'avoir interagi. Reviens quand tu veux.\n");
            printf("\nSee you soon! Thanks for interacting. Come back anytime.\n");
            break;
        default:
            limparTela();
            printf("OPCAO INVALIDA!\a");
        }
    
    }while (opcao != 6);
    return 0;
}
// Função que limpa a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Para Windows
    #else
        system("clear");  // Para Linux/Mac
    #endif
}
// Função para exibir o menu
void exibirMenu(const char* titulo, const char* opcoes[], int num_opcoes) {
    limparTela();
    printf("_+_+== CARTEIRA DIGITAL ==+_+_\n");
    printf(" \n");
    printf("%s\n", titulo);
    for (int i = 0; i < num_opcoes; i++) {
        printf(" [ %d ] %s\n", i + 1, opcoes[i]);
    }
}
// Função para ler a categoria de despesa e receita
int entradaSaida(const char* titulo, const char* opcoes[], int num_opcoes) {
    int categoria;
    printf("%s\n", titulo);
    for (int i = 0; i < num_opcoes; i++) {
        printf(" [ %d ] %s\n", i + 1, opcoes[i]);
    }
    while (1) {
        printf("Sua escolha: ");
        scanf("%d", &categoria);
        if (categoria >= 1 && categoria <= num_opcoes) return categoria;
        else printf("Opção invalida! Tente novamente.\n");        
    }
}
// Função para registrar transações
void exibirTransacao(int* total, const char* tipo, enum Idioma idioma){
    int transacao = lerValor(tipo, idioma);
    *total += transacao;

    if (idioma == PORTUGUES){
        printf("Sua %s total eh de $%i.%02i CAD \n", tipo, *total / 100, *total % 100);
    } else if (idioma == FRANCES){
        printf("Votre %s total est de $%i.%02i CAD \n", tipo, *total / 100, *total % 100);
    } else if (idioma == INGLES) {
        printf("Your total %s is $%i.%02i CAD \n", tipo, *total / 100, *total % 100);
    }     
}
// Função para exibir o saldo
void exibirSaldo(int receita_total, int despesa_total) {
    int saldo = receita_total - despesa_total;
    printf("+_+== CARTEIRA DIGITAL ==+_+_\n");
    printf("+---------------------------+\n");
    printf("|       SALDO ATUAL         |\n");
    printf("+---------------------------+\n");
    printf("| Receitas Totais: $%i.%02i CAD |\n", receita_total / 100, receita_total % 100);
    printf("| Despesas Totais: $%i.%02i CAD |\n", despesa_total / 100, despesa_total % 100);
    printf("|---------------------------|\n");
    printf("| Saldo Final: $%s%i.%02i CAD  |\n", saldo < 0 ? "-" : " ", abs(saldo) / 100, abs(saldo) % 100);
    printf("+---------------------------+\n");

    if (saldo > 0) printf("\nPARABENS! Voce esta no positivo!\n");
    else if (saldo < 0) printf("\nATENCAO! Voce esta no vermelho!\n");
    else printf("\nSeu saldo esta zerado.\n");
}
// Função para exibir relatório
void exibirRelatorio(int receita_total, int despesa_total) {
    int saldo = receita_total - despesa_total;
    printf("_+_+== CARTEIRA DIGITAL ==+_+_\n");
    printf("_+_+== RELAT0RIO FINANCEIRO ==+_+\n");
    printf("Total de Receitas: $%i.%02i CAD\n", receita_total / 100, receita_total % 100);
    printf("Total de Despesas: $%i.%02i CAD\n", despesa_total / 100, despesa_total % 100);
    printf("Saldo Final: $%i.%02i CAD\n", saldo / 100, saldo % 100);
}
// Função para ler o valor de uma transação
int lerValor(const char* tipo, enum Idioma idioma) {
    int valor;
    while (1) { // Loop até o valor ser válido
        // Mostra mensagem de acordo com o idioma
        if (idioma == PORTUGUES) {
            printf("Digite o valor da %s (ex: 750 para $7.50 CAD): ", tipo);
        } else if (idioma == FRANCES) {
            printf("Digitez la valeur de la %s (ex: 750 pour $7.50 CAD): ", tipo);
        } else if (idioma == INGLES) {
            printf("Write the value of %s (ex: 750 to $7.50 CAD): ", tipo);
        }

        // Lê a entrada
        if (scanf("%d", &valor) != 1) {
            // Caso a leitura não seja um número inteiro
            while (getchar() != '\n'); // Limpa o buffer
            if (idioma == PORTUGUES) {
                printf("Erro! Digite apenas valores numéricos.\n");
            } else if (idioma == FRANCES) {
                printf("Erreur! Veuillez entrer uniquement des valeurs numériques.\n");
            } else if (idioma == INGLES) {
                printf("Error! Please enter only numeric values.\n");
            }
        } else {
            return valor; // Se o valor for válido, retorna
        }
    }
}
int lerEscolha(enum Idioma idioma) {
    int subOpcao = 0, leitura = 0;

    while (1) {
        // Mostra mensagem de acordo com o idioma
        if (idioma == PORTUGUES) {
            printf("Digite [ 1 ] para Continuar || Digite [ 2 ] para Sair: ");
        } else if (idioma == FRANCES) {
            printf("Entrez [ 1 ] pour Continuer || Entrez [ 2 ] pour Quitter: ");
        } else if (idioma == INGLES) {
            printf("Press [ 1 ] to Continue || Press [ 2 ] to Exit: ");
        }

        leitura = scanf("%i", &subOpcao);

        // Validação
        if (leitura != 1 || (subOpcao != 1 && subOpcao != 2)) {
            if (idioma == PORTUGUES) printf("Opcao invalida. Tente novamente.\n");
            else if (idioma == FRANCES) printf("Option invalide. Veuillez rEessayer.\n");
            else if (idioma == INGLES) printf("Invalid option. Please try again.\n");
            while (getchar() != '\n'); // limpa o buffer
        } else {
            break; // entrada válida
        }
    }
    return subOpcao;
}
void french() {

    const char* titulo = "Bienvenue dans votre CARTE DIGITALE en Dollar Canadien.\nMenu Principal\nChoisissez l'option souhaitée:";
    const char* opcoes[] = {
        "Enregistrer un revenu",
        "Enregistrer une dEpense",
        "Afficher le solde",
        "GEnErer un rapport",
        "Changer de langue",
        "Sauvegarder & Quitter"
    };
    int num_opcoes = 6;
    int opcao = 0;
    while (opcao != 6) {
        exibirMenu(titulo, opcoes, num_opcoes);  // Chama a função exibirMenu com as opções em francês
        printf("\a");// Solicita a escolha do usuário
        printf("\nChoisissez une option: ");
        scanf("%d", &opcao);

        switch(opcao) {
        case 1:
            // Cadastrar Receita em francês
            limparTela();          
            break;
        case 2:
            // Enregistrer une dépense en français
            subOpcao = 1;
        while (subOpcao != 2) {
            limparTela();
            printf("+_+== PORTEFEUILLE NUMÉRIQUE ==+_+_\n");
            const char* titre = "Quelle est la catégorie de la dépense? \n";
            const char* options[] = {
                "RESTAURANT 'LE BOIS DU BOIS'",
                "TRANSPORT UBER",
                "LOYER DU FLAT",
                "SALLE DE SPORT",
                "BOÎTE DE NUIT",
                "AUTRES"
            };
            int num_options = 6;
    
            exibirTransacao(&despesa_total, "DEPENSE", FRANCES);
            categoria = entradaSaida(titre, options, num_options);
    
            if (categoria >= 1 && categoria <= num_options) {
                printf("\nVotre compte contient actuellement X DÉPENSES d’un montant de %i.%02i CAD \nenregistrées dans la catégorie %i\n", despesa_total / 100, despesa_total % 100, categoria);
                printf("  \n");
            } else {
                printf("Option invalide!\n\a");
            }
    
            subOpcao = lerEscolha(FRANCES);
        }
            break;
        case 3:
            // Exibir Saldo em francês
            break;
        case 4:
            // Gerar Relatório em francês
            break;
        case 5:
            // Alterar Idioma
            break;
        case 6:
            limparTela();
            printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nAttendez...\n");
            sleep(3);
            printf("\nA bientot ! Merci d'avoir interagi. Reviens quand tu veux.\n");
            printf("\nSee you soon! Thanks for interacting. Come back anytime.\n");
            printf("\nAte mais! Obrigado por interagir. Volte sempre!\n");
            break;
        default:
            printf("Option invalide!\n\a");
            
        }
    }
}
void english() {
    const char* titulo = "Welcome to your DIGITAL WALLET in Canadian Dollar.\nMain Menu\nChoose the desired option:";
    const char* opcoes[] = {
        "Register Income",
        "Register Expense",
        "Display Balance",
        "Generate Report",
        "Change Language",
        "Save & Exit"
    };
    int num_opcoes = 6;
    
    int opcao = 0;
    while (opcao != 6) {
        exibirMenu(titulo, opcoes, num_opcoes);  // Chama a função exibirMenu com as opções em inglês
        // Solicita a escolha do usuário
        printf("\nWhat is your choice: ");
        scanf("%d", &opcao);

        // Aqui você pode manter o mesmo switch que está no seu código original para gerenciar as opções
        switch(opcao) {
        case 1:
            // Register Income (implemente a lógica para cadastrar receita)
            limparTela();
            break;
        case 2:
            // Register Expense (implemente a lógica para cadastrar despesa)
            break;
        case 3:
            // Display Balance (implemente a lógica para exibir saldo)
            break;
        case 4:
            // Generate Report (implemente a lógica para gerar relatório)
            break;
        case 5:
            // Change Language (implemente a lógica para alterar idioma)
            break;
        case 6:
            limparTela();
            printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=\nWait...\n");
            sleep(3);
            printf("\nA bientot ! Merci d'avoir interagi. Reviens quand tu veux.\n");
            printf("\nSee you soon! Thanks for interacting. Come back anytime.\n");
            printf("\nAte mais! Obrigado por interagir. Volte sempre!\n");
            break;
        default:
            printf("Invalid option!\n\a");                   
        }
    }
}
