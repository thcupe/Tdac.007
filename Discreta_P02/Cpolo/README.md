
# Calculadora Polonesa com Pilhas

## Introdução

 * Este programa simula uma calculadora Polonesa.

 O usuário deve digitar uma expressão na notação polonesa.
 

 À medida que a expressão é digitada, o programa exibe o valor da expressão atual
                                  (como se fosse a tela de uma calculadora comum).
 
 Cada linha digitada deve conter um número, um operador (+, -, ., /), ou um dos
 seguintes comandos :

   * Q (Quit):   Sair do programa
   * C (Clear):  Limpar a calculadora
   * S (Stack):  Exibir o contéudo da pilha

 * Restrição : Cada linha deve ter no máximo 100 caracteres.


# Simulação da calculadora polonesa :

##  Polish Calculator Simulation

  > 2
  > 1
  > +
  3
  > 9
  > *
  27
  > 3
  > -
  24
  > 8
  > /
  3
  > s

  Stack : 3.000000

  > 4
  > 7
  > +
  11
  > s
 
  Stack : 3.000000, 11.000000

  > +
  14
  > s

  Stack : 14.000000

  > c
  > s

  Stack : Empty !

  > 2
  > 6
  > 4
  > -
  2
  > s

  Stack : 2.000000, 2.000000

  > +
  4
  > 3
  > -
  1
  > 4
  > /
  0.25
  > q


### Explicação 

 O programa armazena os resultados intermediários em uma pilha de números do tipo double.
 Essa estrutura está sujeita a duas operações :

 * Push Empilhar/Acrescentar um novo elemento no topo da pilha
 * Pop retirar um elemento do topo da pilha
 
  A pilha estrá no vetor stk[0..stkcount-1],
  sendo stkcount - 1 o índice do tipo da pilha

###  Outras funções

  * void ApplyOperator(char op)
      Aplica o operador op aos dois operandos que estão no topo da pilha.
   
  * void DisplayStack(void)
      Imprime o conteúdo da pilha.
   
  * string getLine(void)
      Lê a linha digitada pelo usuário e a devolve na forma de uma string.

### Integrantes do grupo Hermes
    
 * Guilherme Rodrigues Chaves Do Nascimento 
 * Thiago De Azevedo Cavendish 
    
### Orientação

* Autor: Prof. Dr. Ruben Carlo Benante
* Email: rcb@upe.br
* Data: 2021-11-14
* Licensa: GNU/GPL v2.0

