#include <cstring>
#include <iostream>

const int ROWS = 5;
const int COLS = 10;

bool fits(int x, int y, int len) {
  return x >= 0 && y >= 0 && y < ROWS && x + len <= COLS;
}

void clear(char board[ROWS][COLS]) {
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool put(char board[ROWS][COLS], int x, int y, char c) {
  if (!fits(x, y, 1)) {
    return false;
  }
  board[y][x] = c;
  return true;
}

bool text(char board[ROWS][COLS], int x, int y, const char* word) {
  int len = std::strlen(word);
  if (!fits(x, y, len)) {
    return false;
  }
  for (int i = 0; i < len; ++i) {
    put(board, x + i, y, word[i]);
  }
  return true;
}

void print(const char board[ROWS][COLS]) {
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  char board[ROWS][COLS];
  clear(board);

  char command[16];
  while (std::cin >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }

    if (std::strcmp(command, "clear") == 0) {
      clear(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x;
      int y;
      char c;
      std::cin >> x >> y >> c;
      if (!put(board, x, y, c)) {
        std::cout << "error" << "\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x;
      int y;
      char word[11];
      std::cin >> x >> y >> word;
      if (!text(board, x, y, word)) {
        std::cout << "error" << "\n";
      }
    } else if (std::strcmp(command, "print") == 0) {
      print(board);
    } else {
      std::cout << "error" << "\n";
    }
  }

  return 0;
}
