Diário Financeiro Pessoal
🏆 Sobre o Projeto
O Diário Financeiro Pessoal é um gerenciador de finanças desenvolvido em C que te ajuda a controlar receitas e despesas, ver seu saldo atual e gerar relatórios detalhados. Com suporte a múltiplos idiomas (Português, Inglês e Francês - Canadá), ele oferece uma interface simples e eficiente para facilitar o seu controle financeiro.

🎯 Objetivos do Projeto
Criar um sistema prático e rápido para você acompanhar seus ganhos e gastos.
Atingir o público-alvo: Qualquer pessoa que queira melhorar sua organização financeira.
🛠 Funcionalidades Principais
Cadastro de receitas e despesas: Registre suas transações financeiras de forma simples, incluindo descrição, valor, data e categoria.
Consulta de saldo atualizado: Saiba rapidamente qual é o seu saldo total, resultado da diferença entre suas receitas e despesas.
Geração de relatórios:
Relatório Geral: Visualize todas as suas transações registradas.
Relatório Diário: Consulte as transações de um dia específico.
Relatório Mensal: Veja as transações de um mês e ano específicos.
Gráfico de Fluxo de Caixa: Tenha uma representação visual do seu fluxo financeiro em um gráfico ASCII.
Definição de metas financeiras: Estabeleça um objetivo de economia ou gasto e acompanhe seu progresso com uma barra indicadora.
Remoção de transações: Exclua movimentações específicas usando a descrição.
Suporte a múltiplos idiomas: Alterne a interface entre Português, Francês (Canadá) e Inglês (Canadá).
Persistência de dados: Todas as suas transações e metas são salvas automaticamente em um arquivo binário, garantindo que nada se perca ao fechar o programa e que os dados sejam carregados na próxima vez que você usar o diário.
📜 Fluxo de Funcionamento
Início: Ao executar o programa, você será saudado e o menu principal será exibido.

Menu Principal:

[1] Cadastrar Receita 🟢
[2] Cadastrar Despesa 🔴
[3] Consultar Saldo 💰
[4] Gerar Relatório 📊
[5] Alterar Idioma 🌍
[6] Remover Movimentação 🗑️
[7] Sair 🚪
Exemplo visual do fluxograma (representação simplificada):

Início
  |
  V
Exibir Menu Principal
  |
  V
Processar Opção Escolhida
  |   [1] Cadastrar Receita (data, valor, descrição, categoria)
  |   [2] Cadastrar Despesa (data, valor, descrição, categoria)
  |   [3] Consultar Saldo (saldo atual, meta financeira)
  |   [4] Gerar Relatório (geral, diário, mensal, gráfico)
  |   [5] Alterar Idioma (PT/FR/EN)
  |   [6] Remover Movimentação (por descrição)
  |
  V
Se [7] Sair: Salvar Dados -> Encerrar
Senão: Voltar ao Menu Principal
![image](https://github.com/user-attachments/assets/6007c7b4-c7a7-437c-b98f-f5db6184bf3a)

Processamento da Escolha do Usuário: O programa executa a ação correspondente à opção selecionada.

Retorno ao Menu ou Finalização: Após a conclusão de uma operação, você pode optar por continuar no menu principal ou sair do programa.

🚀 Como Usar
Baixe o código-fonte do projeto em seu computador.

Compile o código usando um compilador C (como o GCC) no seu terminal. Certifique-se de estar no diretório do projeto:

Bash

gcc -o diario_financeiro main.c -Wall
(Se o seu arquivo principal tiver um nome diferente de main.c, substitua-o no comando.)

Execute o programa no terminal:

No Windows:
Bash

.\diario_financeiro.exe
No Linux/macOS:
Bash

./diario_financeiro
⚙️ Tecnologias Utilizadas
Linguagem: C
Compilador: GCC
Formato de armazenamento: Arquivo binário (.bin)
💡 Melhorias Futuras
Suporte a banco de dados: Para um armazenamento mais robusto e escalável.
Interface gráfica: Uma interface visual para facilitar ainda mais o uso.
Estatísticas financeiras avançadas: Gráficos e análises interativas para uma visão mais profunda das suas finanças.
Exportação de relatórios para CSV: Para facilitar a manipulação dos dados em outras ferramentas.
📜 Licença
Este projeto é de código aberto e pode ser utilizado, estudado e modificado livremente para fins educacionais e pessoais.

👨‍💻 Desenvolvido por alunos do curso de Intro. Programação – 2025 🚀








 
