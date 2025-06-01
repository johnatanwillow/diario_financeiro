#📌 README – Diário Financeiro Pessoal
##🏆 Sobre o Projeto:
O Diário Financeiro Pessoal é um gerenciador de finanças desenvolvido em C que permite controlar receitas e despesas, visualizar o saldo atual e gerar relatórios detalhados. Com suporte a múltiplos idiomas (Português, Inglês e Francês), ele oferece uma interface simples e eficiente para facilitar o controle financeiro.

🔹 Objetivo: Criar um sistema prático e rápido para acompanhar ganhos e gastos.
🔹 Público-Alvo: Qualquer pessoa que deseja melhorar sua organização financeira.
🛠 Funcionalidades Principais
Cadastro de receitas e despesas – Registre suas transações facilmente com descrição, valor, data e categoria.
Exibição de saldo atualizado – Veja o total de receitas menos despesas.
Geração de relatórios – Exporte suas transações em relatórios detalhados (geral, diário, mensal) ou visualize um gráfico de fluxo de caixa em ASCII.
Modo multilíngue – Alterne entre Português, Inglês (Canadá) e Francês (Canadá).
Interface intuitiva – Menu interativo e fácil de usar no console.
Persistência de dados – Todos os registros e a meta financeira são armazenados em um arquivo binário, garantindo que seus dados sejam preservados e carregados automaticamente em futuras sessões.
Definição de meta financeira – Estabeleça um objetivo financeiro e acompanhe seu progresso com uma barra indicadora.
📜 Fluxo de Funcionamento
Início – O programa é carregado e o usuário é saudado com uma mensagem de boas-vindas.

##Exibição do Menu Principal:

[1] Cadastrar Receita 🟢
[2] Cadastrar Despesa 🔴
[3] Consultar Saldo 💰
[4] Gerar Relatório 📊
[5] Alterar Idioma 🌍
[6] Remover Movimentação 🗑️
[7] Sair 🚪
![image](https://github.com/user-attachments/assets/b816dc4a-39f6-4628-9605-854fd4028769)

##Processamento das Opções:

Cadastrar Receita/Despesa: Solicita detalhes da transação (data, tipo, valor, descrição, categoria) e a registra.
Consultar Saldo: Calcula e exibe o saldo total, além de permitir a definição ou visualização de uma meta financeira com barra de progresso.
Gerar Relatório: Oferece opções para visualizar relatórios gerais, diários, mensais ou um gráfico de fluxo de caixa.
Alterar Idioma: Permite mudar o idioma da interface.
Remover Movimentação: Remove uma transação específica com base na sua descrição.
Sair: Salva todas as movimentações e metas em um arquivo binário e encerra o programa.
Retorno ao menu ou finalização do programa: Após cada operação, o usuário pode escolher continuar no menu ou sair.

🚀 Como Usar
Baixe o código-fonte do projeto em seu computador.

Compile o código utilizando um compilador C (como GCC) no terminal:

Bash

gcc -o diario_financeiro main.c -Wall
(Certifique-se de que o nome do arquivo .c esteja correto, se for diferente de main.c.)

Execute o programa no terminal:

No Windows:
Bash

.\diario_financeiro.exe
No Linux/macOS:
Bash

./diario_financeiro
🔧 Tecnologias Utilizadas
Linguagem: C
Compilador: GCC
Formato de armazenamento: Arquivo binário (.bin)
🎨 Melhorias Futuras
Suporte para armazenamento em banco de dados para maior escalabilidade.
Implementação de interface gráfica para uma experiência de usuário mais rica.
Estatísticas financeiras detalhadas com gráficos interativos e análise de tendências.
Funcionalidade de exportação de relatórios para CSV.
📜 Licença
Este projeto é de código aberto e pode ser utilizado livremente para fins educacionais e pessoais.

👨‍💻 Desenvolvido por alunos do curso de Intro. Programação – 2025 🚀

Ainda tem alguma dúvida sobre como usar ou melhorar o Diário Financeiro Pessoal? Sinta-se à vontade para perguntar!








 
