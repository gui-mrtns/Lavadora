# Lavadora
Este projeto consiste na simulação de uma máquina lavadora na placa PIC18F4520 da PICGenios. Realizou-se o projeto no segundo semestre de 2020 como parte da avaliação da disciplina de "Laboratório de Programação Embarcada" do curso de Engenharia de Computação da Universidade Federal de Itajubá (UNIFEI - _campus_ Itajubá).

## Ferramentas
* Ambiente de desenvolvimento: MPLAB X IDE v5.35
* Compilador: MPLAB XC8 C Compiler v2.10
* Simulador: PICSimLab v0.7.5
* Microcontrolador: PIC18F4520 – PICGenios
* Conhecimento em linguagem C
* Conhecimento em sistemas embarcados

## Como executar?
### Primeiro passo
Primeiramente, devemos compilar o projeto no IDE, em “File” selecionar “New Project”, na janela aberta em “Categories” selecionar “Microchip Embedded”, em “Projects” selecionar “Standalone Project” e clicar em “Next >”. Na nova janela em “Device” digitar “PIC18F4520” e clicar em “Next >”. Na nova janela, em “Other Tools” selecionar “Picsimlab” e clicar em “Next > “. Na nova janela, em “XC8” selecionar “XC8 (v2.10)” e clicar em “Next >”. Por fim, dar o nome ao projeto de “Lavadora” e clicar em “Finish”. Em “Source files” clicar em “Add Existing Item...”, navegar até a pasta dos arquivos, selecionar todos eles, selecionar também a checkbox “Copy” e clicar em “Select”. Feito isso, abra o arquivo main.c e compile-o acessando “Production” e clicando em “Clean and Build Project” ou apertando F11. Bem-sucedido o processo prossiga para o próximo passo.

### Segundo passo
Preparando o ambiente, no PICSimLab, em “Board” devemos selecionar “4 PICGenios”, em “Microcontroller” selecionar “PIC18F4520” e ao lado da placa, em “LCD” selecionar o display “hd44780 16x4”. Feito isso, é preciso carregar o arquivo em hexadecimal do projeto indo em “File\Load hex” e navegando até a pasta gerada pelo IDE “\Lavadora.X\dist\default\production\Lavadora.X.production.hex”. Se tudo ocorrer corretamente, o projeto se iniciará.

### Terceiro passo
O projeto se inicia em uma tela de inicialização e aguarda a resposta do usuário. Depois, o usuário deve configurar como ele deseja que a lavagem seja realizada, selecionando algumas informações que o LCD pedir.

## Vídeo apresentação
* [Projeto Lavadora (PIC18F4520) - ECOP14 | UNIFEI](https://youtu.be/QW69CpfIx9U?si=WZdYoFyGj_QKQYMZ)
