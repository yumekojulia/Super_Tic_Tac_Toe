//
// Created by juh on 11/22/25 on CLion
//


#include <stdio.h>
#include <stdlib.h>

#define N_BOARDS 9 // número total de tabuleirozinhos (3x3 = 9)
#define N 3 // dimensão de cada tabuleirozinho (3 linhas x 3 colunas)

#define C_RESET  "\x1b[0m" // volta ao estilo padrão
#define C_RED    "\x1b[31m" // X = vermelho
#define C_MAG    "\x1b[35m" // O = magenta
#define C_CYAN   "\x1b[36m" // destacar o tabuleiro que o jogador é forçado a jogar = ciano
#define C_YEL    "\x1b[33m" // D (empate) = amarelo
#define C_BOLD   "\x1b[1m" // negrito

char board[N_BOARDS][N][N]; // array 3D = para cada um dos 9 tabuleirozinhos (N_BOARDS), guardamos uma grade N x N (3x3) de char
char smallStatus[N_BOARDS]; // smallStatus = guarda o status de cada tabuleirozinho: ' ' (ainda em jogo), 'X' e 'O' (jogadores) ou 'D' (empate).

void init_game() { // função que inicializa o jogo
    for (int b = 0; b < N_BOARDS; ++b) { // percorre cada tabuleirozinho (índices 0..8)
        for (int r = 0; r < N; ++r) // percorre cada linha do tabuleirozinho
            for (int c = 0; c < N; ++c) // percorre cada coluna do tabuleirozinho
                board[b][r][c] = ' '; // marca a célula como vazia (espaço)
        smallStatus[b] = ' '; // marca o status do tabuleirozinho como vazio, pois ainda está em jogo
    }
}

void print_token(char t) { // função para imprimir cada cor correspondente
    if (t == 'X') { // imprime X em vermelho e então reseta a cor
        printf("%sX%s", C_RED, C_RESET);
    } else if (t == 'O') { // imprime O em magenta e reseta a cor
        printf("%sO%s", C_MAG, C_RESET);
    } else { // imprime um '.' para célula vazia
        printf(".");
    }
}

void print_board(int forced) { // função responsável pela exibição bonitinha do tabuleiro inteiro
    printf("\n%s=== SUPER TIC-TAC-TOE DA JUH! ===%s\n\n", C_BOLD, C_RESET); // título do jogo em negrito
    printf("Tabuleiro atual =   "); // header com índices dos tabuleirozinhos (1..9) e realce do tabuleirozinho forçado
    for (int bc = 0; bc < 3; ++bc) { // bc: big column (0..2), sb: small block dentro da coluna (0..2)
        for (int sb = 0; sb < 3; ++sb) {
            int idx = bc*3 + sb + 1; // calcula o número do tabuleirozinho (1..9) com base nas posições bc (big column) e sb (small board).
            if (forced == idx-1) { // se o forced for igual ao índice calculado, coloca colchetes coloridos em ciano
                printf(" %s[%d]%s  ", C_CYAN, idx, C_RESET);
            } else {
                printf("  %d   ", idx); // caso contrário, imprimimos normal
            }
        }
    }
    printf("\n\n");

    printf("\t"); // tab mostrando colunas locais (1 a 3) repetidas para cada tabuleirozinho
    for (int bc = 0; bc < 3; ++bc) {
        printf(" 1 2 3  ");
    }
    printf("\n");
    for (int bigRow = 0; bigRow < 3; ++bigRow) { // agora imprimimos cada "bigRow" ( são as 3 grandes linhas dos tabuleirozinhos)
        printf("   +-------+-------+-------+\n"); // separador horizontal entre blocos
        for (int row = 0; row < 3; ++row) { // cada bigRow tem 3 linhas locais (row = 0,1,2)
            printf(" %d |", row+1); // imprimimos um rótulo de linha local (1..3) para facilitar
            for (int bigCol = 0; bigCol < 3; ++bigCol) { // percorremos as 3 colunas grandes (cada uma com um tabuleirozinho)
                int b = bigRow * 3 + bigCol; // transforma coordenadas 2D do grande tabuleiro em um índice b (0..8).
                for (int col = 0; col < 3; ++col) { // percorremos as 3 colunas do tabuleirozinho
                    char t = board[b][row][col]; // atribui t com 'X', 'O' ou ' '
                    if (forced == b) printf(" %s", C_CYAN); // se esse tabuleirozinho for o forçado, imprime um espaço colorido
                    else printf(" ");
                    if (t == 'X') printf("%sX%s", C_RED, (forced == b ? C_CYAN : C_RESET)); // X vermelho
                    else if (t == 'O') printf("%sO%s", C_MAG, (forced == b ? C_CYAN : C_RESET)); // O magenta
                    else printf("%s.%s", (forced == b ? C_CYAN : ""), C_RESET); // o '.' vazio
                    if (forced == b) printf("%s", C_RESET); // se coloriu a borda, reseta a cor
                }
                printf(" |"); // final do pequeno tabuleiro atual
            }
            printf("\n");
        }
    }
    printf("   +-------+-------+-------+\n\n");

    printf("(Player 1 = %sX%s, Player 2 = %sO%s, Empate = %sD%s, . = Disponível)\n", // smallStatus = quem venceu cada tabuleirinho ou '.' se está aberto
           C_RED, C_RESET, C_MAG, C_RESET, C_YEL, C_RESET);

    for (int r = 0; r < 3; ++r) { // imprimimos os 9 smallStatus em formato 3x3, destacando o tabuleirinho forçado com colchetes
        printf("   ");
        for (int c = 0; c < 3; ++c) {
            int b = r*3 + c; // índice do smallStatus
            char s = smallStatus[b];
            if (b == forced) printf(" [");
            else printf("  ");
            if (s == 'X') printf("%sX%s", C_RED, C_RESET);
            else if (s == 'O') printf("%sO%s", C_MAG, C_RESET);
            else if (s == 'D') printf("%sD%s", C_YEL, C_RESET);
            else printf(".");
            if (b == forced) printf("] ");
            else printf("  ");
        }
        printf("\n");
    }
    printf("\n");
}

int check_win_grid(char g[3][3], char p) { // checa se o jogador 'p' venceu numa grade 3x3 passada em g
    for (int i = 0; i < 3; ++i) { // checa linhas e colunas
        if (g[i][0] == p && g[i][1] == p && g[i][2] == p) return 1;
        if (g[0][i] == p && g[1][i] == p && g[2][i] == p) return 1;
    } // checa diagonais
    if (g[0][0] == p && g[1][1] == p && g[2][2] == p) return 1;
    if (g[0][2] == p && g[1][1] == p && g[2][0] == p) return 1;
    return 0; // se nada bate, retorna 0 = não venceu :(
}

int is_full_small(int b) { // cerifica se um tabuleirozinho (índice b) está cheio, sem espaços vazios
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[b][r][c] == ' ') return 0; // ainda existe um espaço vazio
    return 1; // está cheio
}

void update_small_status(int b) { // smallStatus[b] = atualizado após uma jogada naquele tabuleirozinho. É chamada sempre que uma nova peça é colocada num tabuleirozinho
    if (smallStatus[b] != ' ') return; // se já estiver decidido (smallStatus[b] != ' '), não faz nada
    if (check_win_grid(board[b], 'X')) { smallStatus[b] = 'X'; return; } // se 'X' venceu nesse tabuleirozinho, 'X' nele
    if (check_win_grid(board[b], 'O')) { smallStatus[b] = 'O'; return; } // se 'O' venceu nesse tabuleirozinho, 'O' nele
    if (is_full_small(b)) smallStatus[b] = 'D'; // se estiver cheio e ninguém venceu, D de draw
}

char check_big_win() { // vê se há um vencedor no tabuleiro grande. Cada smallStatus vira uma célula do tabuleirozão
    char g[3][3]; // converte o array linear smallStatus[0..8] para g[3][3]
    for (int i = 0; i < 9; ++i) g[i/3][i%3] = smallStatus[i];

    char players[2] = {'X', 'O'}; // checa os jogadores
    for (int pi = 0; pi < 2; ++pi) {
        char p = players[pi];
        for (int i = 0; i < 3; ++i)
            if (g[i][0] == p && g[i][1] == p && g[i][2] == p) return p; // linha i
        for (int i = 0; i < 3; ++i)
            if (g[0][i] == p && g[1][i] == p && g[2][i] == p) return p; // coluna i
        if (g[0][0] == p && g[1][1] == p && g[2][2] == p) return p; // diagonal
        if (g[0][2] == p && g[1][1] == p && g[2][0] == p) return p; // outra diagonal
    }
    return ' '; // sem vencedor
}

int valid_move(int b, int r, int c, int nextBoard) { // função que valida se uma jogada é válida (b = indice tabuleirozinho, r = linha local, c = coluna local, nextBoard = índice do tabuleiro forçado (-1 = livre))
    if (b < 0 || b >= 9) return 0; // tabuleiro fora do intervalo
    if (r < 0 || r >= 3) return 0; // linha fora do intervalo
    if (c < 0 || c >= 3) return 0; // coluna fora do intervalo
    if (nextBoard != -1 && b != nextBoard) return 0; // se há tabuleiro forçado, b deve ser o nextBoard
    if (smallStatus[b] != ' ') return 0; // tabuleiro já decidido
    if (board[b][r][c] != ' ') return 0; // célula ocupada
    return 1; // passou por todas as checagens = valida
}

int moves_exist_for(int nextBoard) { // função que verifica se tem algum movimento possível respeitando o nextBoard forçado
    for (int b = 0; b < 9; ++b) {
        if (smallStatus[b] != ' ') continue; // pular tabuleiros já decididos
        if (nextBoard != -1 && b != nextBoard) continue; // se forçado e não for o tabuleiro, pular
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (board[b][r][c] == ' ') return 1; // encontrou célula vazia = existe movimento ainda :D
    }
    return 0; // retorna 0 se não encontrou movimentos possíveis
}

int main() { // controla o fluxo do jogo (entrada, validação, atualização e alternância de jogador
    init_game(); // inicializa estruturas
    char player = 'X'; // player atual X
    int nextBoard = -1; // -1 significa que o jogador pode escolher qualquer tabuleiro = não tem restrição

    printf("%sRegras:%s\n", C_BOLD, C_RESET); // autoexplicativo XD
    printf("- Se o próximo tabuleiro estiver obrigatório, você digita apenas a LINHA (1 a 3) e a COLUNA (1 a 3).\n");
    printf("- Caso contrário, digite o TABULEIRO (1 a 9), a LINHA (1 a 3) e a COLUNA (1 a 3).\n");
    printf("- Tabuleirozinhos: numerados de 1 a 9 (de cima para baixo, da esquerda para a direita).\n\n");

    while (1) { // loop do jogo é infinito até alguém vencer ou der empate
        print_board(nextBoard); // imprime a situação atual do tabuleiro e se algum tabuleirozinho está forçado

        char bigWinner = check_big_win(); // checa se já temos um vencedor no tabuleirozão :D
        if (bigWinner != ' ') {
            printf("%sPlayer %s%c%s venceu o SUPER TICTACTOE DA JUH!%s\n", // se houver vencedor mostra uma mensagem colorida e sai do loop
                   C_BOLD, (bigWinner=='X'?C_RED:C_MAG), bigWinner, C_RESET, C_RESET);
            break; // encerra o loop principal
        }

        if (!moves_exist_for(nextBoard)) { // checa se existem movimentos válidos com a restrição de nextBoard, se não houver, declara empate e sai
            printf("%sNão há mais movimentos legais. Empate! :( %s\n", C_BOLD, C_RESET);
            break; // encerra jogo por empate
        }

        printf("Vez do player %s%c%s\n", (player=='X'?C_RED:C_MAG), player, C_RESET); // informa de quem é a vez

        int b_in = -1, r_in = -1, c_in = -1; // variáveis para receber a entrada do jogador

        if (nextBoard != -1 && smallStatus[nextBoard] == ' ') {  // se nextBoard não for -1 e esse tabuleiro ainda estiver aberto, o jogador só digita linha e coluna, porque o tabuleiro é forçado
            printf("Você deve jogar no tabuleiro %s%d%s. Informe a LINHA (1 a 3) e a COLUNA (1 a 3): ", // mostramos qual tabuleiro está forçado (1-based para o jogador)
                   C_CYAN, nextBoard+1, C_RESET);
            if (scanf("%d %d", &r_in, &c_in) != 2) { // le a linha e coluna
                while (getchar() != '\n'); // limpeza do buffer de entrada caso o usuário tenha digitado algo inválido X_X
                printf("Entrada inválida. Tente novamente :P \n");
                continue; // volta para o início do loop
            }
            r_in--; c_in--; // subtraí 1 (r_in--; c_in--;) p/ converter da entrada do jogador (1..3) para índices 0-based (0..2) usados pelo array
            b_in = nextBoard; // o tabuleirozinho onde vamos jogar é o forçado

            if (!valid_move(b_in, r_in, c_in, nextBoard)) { // checa se a jogada é válida
                printf("Movimento inválido: espaço ocupada, fora do intervalo ou tabuleiro indisponível :P\n");
                continue; // volta ao loop sem mudar jogador
            }
        } else { // se o jogador puder escolher o tabuleirozinho se pede o tabuleiro + linha + coluna
            printf("Informe o TABULEIRO (1 a 9), a LINHA (1 a 3) e a COLUNA (1 a 3): ");
            if (scanf("%d %d %d", &b_in, &r_in, &c_in) != 3) { // verifica de novo se a jogada é válida
                while (getchar() != '\n');
                printf("Entrada inválida. Tente novamente :P\n");
                continue;
            }
            b_in--; r_in--; c_in--; // converte de novo a entrada digitada para o índice
            if (!valid_move(b_in, r_in, c_in, nextBoard)) { // valida a jogada
                printf("Movimento inválido: espaço ocupado, fora do intervalo ou tabuleiro indisponível :P\n");
                continue;
            }
        }

        board[b_in][r_in][c_in] = player; // coloca 'X' ou 'O' no espaço escolhido do tabuleiro b_in
        update_small_status(b_in); // atualiza o status do tabuleirinho, se passou a ter vencedor ou empate

        // determina o próximo tabuleiro forçado usando a posição local (r_in, c_in)
        // regra: a posição local dentro do tabuleirozinho aponta para qual smallBoard o oponente deve jogar
        int forced = r_in * 3 + c_in; // mapeamento 2D->1D, transforma a coordenada local (r_in, c_in) em índice 0 a8 do tabuleirozinho
        if (forced < 0 || forced >= 9 || smallStatus[forced] != ' ') // se o smallStatus do forced já estiver decidido (X/O/D) ou for inválido, libera poder de escolha
            nextBoard = -1; // livre pra escolher
        else
            nextBoard = forced; // forçado a obedecer

        player = (player == 'X') ? 'O' : 'X'; // alterna a vez do jogador
    }

    print_board(-1); // imprimimos o tabuleiro final (sem forçar nada) e saímos
    printf("Fim de jogo! Obrigada por jogar!! <3\n");
    return 0; // GG! <3
}
