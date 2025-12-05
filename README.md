# Super Tic-Tac-Toe da Juh (Ultimate Tic-Tac-Toe em C)

Este projeto é uma implementação avançada do **Super Jogo da Velha (Ultimate Tic-Tac-Toe)** em **linguagem C**, jogável diretamente no terminal e com interface totalmente colorida via códigos **ANSI**, destacando jogadas, tabuleiros forçados e status de cada tabuleirozinho.

O código é modular, organizado e cheio de comentários para facilitar o entendimento, perfeito para estudo ou para quem quer se aprofundar em jogos baseados em matrizes e lógica de estado.

---

## Funcionalidades

* **Interface Colorida Completa:** `X` em **vermelho** , `O` em **magenta**, Tabuleiro Forçado destacado em **ciano** e Empates exibidos em **amarelo** .

* **Tabuleiro Grande + 9 Tabuleirozinhos:** Exibição organizada com numeração de linhas e colunas.

* **Sistema de Tabuleiro Forçado:** A posição jogada determina onde o próximo jogador é obrigado a jogar.

* **Verificação de vitória modular:** Tanto para os tabuleiros pequenos quanto para o tabuleirão maior.

* **Validação completa de jogada:** Impede jogadas fora do intervalo, em casa ocupada ou em tabuleiro inválido/fechado.

* **Interface limpa e clara:** Fácil de entender mesmo em terminais simples.

---

## Como Compilar e Jogar

Este projeto utiliza o compilador **GCC (GNU Compiler Collection)**.

### 1_ Compilação

No terminal, execute:

```bash
gcc supertictactoe.c -o supertictactoe -std=c11
```

### 2_ Execução

```bash
./supertictactoe
```

----

## Simulação no Terminal


```text
Tabuleiro atual =     1     2    [3]    4     5     6     7     8     9   

      1 2 3   1 2 3   1 2 3  
   +-------+-------+-------+
 1 | X . . | X O X | . O . |
 2 | O O O | O X X | . O . |
 3 | . . . | O X O | . X O |
   +-------+-------+-------+
 1 | X X X | X O X | X X X |
 2 | . . . | O X . | . O . |
 3 | . . . | X . . | . . . |
   +-------+-------+-------+
 1 | O X O | . . . | X . . |
 2 | O O O | O O . | . . . |
 3 | X . . | . . . | X . . |
   +-------+-------+-------+

(Player 1 = X, Player 2 = O, Empate = D, . = Disponível)

      O    D   [.]
      X    X    X  
      O    .    .  
```

### Jogada obrigatória

```text
Vez do player X
Você deve jogar no tabuleiro [3]. Informe a LINHA (1 a 3) e a COLUNA (1 a 3):
```

###  Fim de jogo

```text
Player X venceu o SUPER TICTACTOE DA JUH! <3

Fim de jogo! Obrigada por jogar!! <3
```


---


## Estrutura do Código

| Função                  | Tipo   | Função                                                                   |
| ----------------------- | ------ | ------------------------------------------------------------------------ |
| `main()`                | `int`  | Controla o fluxo do jogo, entradas, trocas de turno e tabuleiro forçado. |
| `print_board()`         | `void` | Exibe o tabuleiro grande + 9 tabuleiros pequenos com cores e destaques.  |
| `check_win_grid()`      | `int`  | Checa vitórias nos tabuleiros 3×3 individuais.                           |
| `check_big_win()`       | `char` | Checa vitória no tabuleirozão (3×3 de smallStatus).                      |
| `valid_move()`          | `int`  | Verifica se a jogada é válida.                                           |
| `update_small_status()` | `void` | Marca X/O/D nos tabuleirozinhos vencidos.                                |

---

## Destaques Técnicos

Uso de cores ANSI para destaque visual:

```c
#define C_RED   "\[31m" // Vermelho
#define C_MAG   "\[35m" // Magenta
#define C_CYAN  "\[36m" // Ciano
#define C_YEL   "\[33m" // Amarelo
#define C_RESET "\[0m"  // Reset
```

Uso típico durante a impressão:

```c
printf("%sX%s", C_RED, C_RESET);
```

Isso garante que apenas o símbolo seja colorido sem afetar o restante da interface.

---

## Melhorias futuras planejadas

- [ ] Modo jogador vs CPU

- [ ] Interface gráfica com SDL2 ou ncurses

- [ ] Opção de salvamento e carregamento de partida

- [ ] Animações no terminal

- [ ] Versão online multiplayer

 ---

## Conclusão

Este projeto demonstra o uso de:

* matrizes 3D
* condicionais
* modularização de funções
* manipulação de entrada
* lógica avançada de estado (tabuleiro forçado)
* formatação ANSI


---

Se você gostou do projeto, deixe uma estrelinha ⭐ no repositório! <3

Feito com 🖤 por [@0xjuL14](https://github.com/0xjuL14)
