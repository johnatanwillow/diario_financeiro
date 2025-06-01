# 💰 Diário Financeiro Pessoal

## 🏆 Sobre o Projeto

O **Diário Financeiro Pessoal** é um gerenciador de finanças pessoais desenvolvido em **C** por um personagem fictício chamado **Filipe**, criado especialmente para este projeto. Seu objetivo é ajudar usuários a controlarem suas receitas e despesas, acompanharem o saldo atual e gerarem relatórios financeiros detalhados.  

Com suporte a múltiplos idiomas (Português, Inglês e Francês - Canadá), o sistema oferece uma interface simples, eficiente e prática para facilitar o controle das finanças pessoais.

---

## 🎯 Objetivos do Projeto

- Criar uma ferramenta leve e acessível para acompanhar ganhos e gastos.
- Atender a qualquer pessoa que deseje melhorar sua organização financeira.
- Proporcionar uma experiência intuitiva e multilíngue.

---

## 🛠 Funcionalidades Principais

- **Cadastro de receitas e despesas**: Informe descrição, valor, data e categoria.
- **Consulta de saldo atualizado**: Veja rapidamente seu saldo total.
- **Geração de relatórios**:
  - **Geral**: Lista todas as transações registradas.
  - **Diário**: Filtra transações por dia específico.
  - **Mensal**: Mostra as transações de um mês e ano escolhidos.
  - **Gráfico de Fluxo de Caixa (ASCII)**: Visualização gráfica do fluxo financeiro.
- **Definição de metas financeiras**: Estabeleça objetivos e acompanhe o progresso com uma barra indicadora.
- **Remoção de transações**: Exclua registros com base na descrição.
- **Suporte a múltiplos idiomas**: Português 🇧🇷, Inglês 🇨🇦 e Francês 🇨🇦.
- **Persistência de dados**: As informações são salvas automaticamente em um arquivo binário `.bin`, mantendo tudo seguro entre execuções.

---

## 📜 Fluxo de Funcionamento

Ao iniciar o programa, você verá o seguinte menu principal:

[1] Cadastrar Receita 🟢  
[2] Cadastrar Despesa 🔴  
[3] Consultar Saldo 💰  
[4] Gerar Relatório 📊  
[5] Alterar Idioma 🌍  
[6] Remover Movimentação 🗑️  
[7] Sair 🚪  
---
![image](https://github.com/user-attachments/assets/4a6489c8-f66a-4617-bdac-ee3ff53538aa)
---
### 📌 Exemplo Simplificado do Fluxo

Início  
  ↓  
Exibir Menu Principal  
  ↓  
Usuário escolhe uma opção  
  ↓  
Executa a ação escolhida  
  ↓  
Retorna ao menu ou finaliza o programa  

---
    A[Início do Programa] --> B{Carregar Movimentações e Meta (df.bin)};
    B --> C{Exibir Boas-vindas};

    C --> D{Loop Principal do Menu};

    D --> E{Exibir Menu Principal};
    E --> F{Usuário Insere Opção};

    F --> G{Leitura Válida?};
    G -- Não --> H[Opção Inválida];
    H --> D;

    G -- Sim --> I{Qual a Opção?};

    I -- Opção 1: Cadastrar Receita --> J[Gerenciar Cadastro de Movimentação ('R')];
    I -- Opção 2: Cadastrar Despesa --> K[Gerenciar Cadastro de Movimentação ('D')];
    J --> L{Sucesso no Cadastro?};
    K --> L;
    L -- Sim --> M[Inserir Movimentação];
    L -- Não --> D;
    M --> N{Continuar Cadastrando?};
    N -- Sim --> J;
    N -- Não --> D;

    I -- Opção 3: Consultar Saldo --> O[Gerenciar Saldo e Meta];
    O --> D;

    I -- Opção 4: Gerar Relatório --> P[Menu de Relatórios];
    P --> Q{Usuário Escolhe Tipo de Relatório};
    Q -- Geral --> R[Imprimir Movimentações (Geral)];
    Q -- Diário --> S[Ler Data com Validação (dia/mês/ano)];
    Q -- Mensal --> T[Ler Data com Validação (mês/ano)];
    Q -- Gráfico Fluxo de Caixa --> U[Imprimir Gráfico de Fluxo de Caixa];

    R --> V[Pausar Execução];
    S --> W{Data Válida?};
    W -- Sim --> X[Imprimir Movimentações (Diária)];
    W -- Não --> V;
    X --> V;

    T --> Y{Data Válida?};
    Y -- Sim --> Z[Imprimir Movimentações (Mensal)];
    Y -- Não --> V;
    Z --> V;

    U --> V;
    V --> P;
    Q -- Voltar ao Menu Principal --> D;

    I -- Opção 5: Alterar Idioma --> AA[Alterar Idioma];
    AA --> AB{Idioma FR ou EN?};
    AB -- Sim --> AC{Exibir Menu Consentimento Dados?};
    AC -- Sim --> AD{Consentimento Dado?};
    AD -- Não --> AE[Sair do Programa];
    AD -- Sim --> AF[Solicitar Novo Nome de Usuário];
    AF --> D;
    AB -- Não --> D;
    AC -- Não --> D;
    AE --> GGG;


    I -- Opção 6: Remover Movimentação --> AG[Gerenciar Remoção de Movimentação];
    AG --> D;

    I -- Opção 7: Sair --> GGG[Salvar Todas Movimentações];
    GGG --> FIM[Fim do Programa];
    ---

## 🚀 Como Usar

### 1. Baixe o código-fonte do projeto em sua máquina.

### 2. Compile o código com um compilador C (ex: GCC):

gcc -o diario_financeiro main.c -Wall

### No Linux/macOS:
./diario_financeiro

---
## ⚙️ Tecnologias Utilizadas
Linguagem: C

Compilador: GCC

Armazenamento de dados: Arquivo binário .bin

💡 Melhorias Futuras
Suporte a banco de dados.

Desenvolvimento de interface gráfica.

Relatórios e gráficos financeiros avançados.

Exportação de relatórios para CSV.

## 📜 Licença
**Este projeto é de código aberto e pode ser usado, estudado e modificado livremente para fins educacionais e pessoais.

## 👨‍💻 Desenvolvido por
**Alunos do curso de Introdução à Programação – 2025 🚀
