#include <iostream>
using namespace std;

struct chess_pisces {
  int id;
  int color;
};

chess_pisces board[8][8];
string white_symbols[6] = {"♟", "♞", "♝", "♜", "♛", "♚"};
string black_symbols[6] = {"♙", "♘", "♗", "♖", "♕", "♔"};

bool check_for_king(int color) {
  for (int i = 0 ; i < 8 ; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j].id == 6 and board[i][j].color == color) {
        return true;
      }
    }
  }
  return false;
}

void set_board() {

  //Pawns
  for (int i = 0; i < 8; i++) {
    board[i][6].id = 1;
    board[i][6].color = 0;
  }
  for (int i = 0; i < 8; i++) {
    board[i][1].id = 1;
    board[i][1].color = 1;
  }
  board[0][0].id = 4;
  board[0][0].color = 1;
  board[7][0].id = 4;
  board[7][0].color = 1;
  board[0][7].id = 4;
  board[0][7].color = 0;
  board[7][7].id = 4;
  board[7][7].color = 0;
  board[1][0].id = 2;
  board[1][0].color = 1;
  board[6][0].id = 2;
  board[6][0].color = 1;
  board[2][0].id = 3;
  board[2][0].color = 1;
  board[5][0].id = 3;
  board[5][0].color = 1;
  board[3][0].id = 5;
  board[3][0].color = 1;
  board[4][0].id = 6;
  board[4][0].color = 1;

  // White
  board[1][7].id = 2;
  board[1][7].color = 0;
  board[6][7].id = 2;
  board[6][7].color = 0;
  board[2][7].id = 3;
  board[2][7].color = 0;
  board[5][7].id = 3;
  board[5][7].color = 0;
  board[3][7].id = 5;
  board[3][7].color = 0;
  board[4][7].id = 6;
  board[4][7].color = 0;
}

void draw_board() {
  char x = 'A';
  for (int i = 0; i < 8; i++) {
    cout << i + 1 << " ";
    for (int j = 0; j < 8; j++) {
      if (board[j][i].id != 0) {
        if (board[j][i].color == 0) {
          cout << white_symbols[board[j][i].id - 1];
        } else {
          cout << black_symbols[board[j][i].id - 1];
        }
      } else {
        cout << " ";
      }
      cout << " ";
    }

    cout << endl;
  }
  cout << " ";
  cout << " ";
  for (int i = 0; i < 8; i++) {
    cout << x << " ";
    x += 1;
  }
}

int main() {
  set_board();
  draw_board();
  int turn = 0;
  // Move Pieces
  string color[2] = {"white","black"};
  while (check_for_king(0) and check_for_king(1)) {
    int x, y ,x1 ,y1;
    char count, count1;
    cout << endl;
    cout << "Please choose a piece: ";
    cin >> x >> count;
    x = x - 1;
    y = count - 65;
    if (board[y][x].id == 0) {
      cout << "No piece is on that position.";
    } else {
      if (board[y][x].color == turn) {
        cout << endl;
        cout << "Please choose a position: ";
        cin >> x1 >> count1;
        x1 = x1 - 1;
        y1 = count1 - 65;

        //Check if move is legal
        bool legal = false;
        bool can_castle = true;

        // Pawn
        if (board[y][x].id == 1) {
          cout << "Its a pawn!" << endl;
          if (x1 == x + 2 or x1 == x - 2) {
            if (board[y][x].color == 0 and x == 6 and x1 == x - 2) {
              if (board[y][x-1].id == 0 and board[y][x-2].id == 0) {
                legal = true;
              }
            } else if (board[y][x].color == 1 and x == 1 and x1 == x + 2) {
              if (board[y][x+1].id == 0 and board[y][x+2].id == 0) {
                legal = true;
              }
            }
          }
          if (y1 == y and x1 == x - 1 and board[y][x1].id == 0) {
            legal = true;
          }
          if (y1 == y + 1 or y1 == y - 1) {
            if (board[y][x].color == 0) {
              if (x1 == x - 1 and board[y1][x1].id != 0 and board[y1][x1].color != 0) {
                legal = true;
              }
            } else if (board[y][x].color == 1) {
              if (x1 == x + 1 and board[y1][x1].id != 0 and board[y1][x1].color != 1) {
                legal = true;
              }
            }
          }
        }

        //Horse

        if (legal) {
          board[y1][x1].id = board[y][x].id;
          board[y1][x1].color = board[y][x].color;
          board[y][x].id = 0;
          board[y][x].color = 0;
          draw_board();
          if (turn == 0) {
            turn = 1;
          }else {
            turn = 0;
          }
        } else {
          cout << "Illegal move.";
        }
      } else {
        cout << "Its " << color[turn] << "'s turn, please choose a " << color[turn] << " piece.";
      }
    }
  }

  if (check_for_king(0)) {
    cout << "White wins!";
  } else {
    cout << "Black wins!";
  }
  return 0;
}
