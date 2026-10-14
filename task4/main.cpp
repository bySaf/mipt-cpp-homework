#include <algorithm>
#include <cstring>
#include <iostream>

// идея программы - редактор чанков в майнкрафте
// int*** нужен для трехмерного массива блоков
// applyToArea обходит выбранную область и вызывает action для каждого блока
// через void* в action передаются данные: новое состояние или пара id

using Action = void (*)(int&, void*);

struct ReplaceData {
  int old_id;
  int new_id;
};

void setState(int& block, void* data) {
  int state = *static_cast<int*>(data);
  int id = block / 17;
  block = id * 17 + state;
}

void replaceId(int& block, void* data) {
  ReplaceData* ids = static_cast<ReplaceData*>(data);
  int id = block / 17;
  int state = block % 17;

  if (id == ids->old_id) {
    block = ids->new_id * 17 + state;
  }
}

bool applyToArea(int*** chunk, int width, int height, int depth, int x1, int y1,
                 int z1, int x2, int y2, int z2, Action action, void* data) {
  if (x1 < 0 || y1 < 0 || z1 < 0 || x2 >= width || y2 >= height ||
      z2 >= depth || x1 > x2 || y1 > y2 || z1 > z2) {
    return false;
  }

  for (int y = y1; y <= y2; ++y) {
    for (int z = z1; z <= z2; ++z) {
      for (int x = x1; x <= x2; ++x) {
        action(chunk[y][z][x], data);
      }
    }
  }
  return true;
}

int main() {
  int width;
  int height;
  int depth;
  std::cin >> width >> height >> depth;

  int*** chunk = new int**[height];
  for (int y = 0; y < height; ++y) {
    chunk[y] = new int*[depth];
    for (int z = 0; z < depth; ++z) {
      chunk[y][z] = new int[width];
      for (int x = 0; x < width; ++x) {
        int id;
        int state;
        std::cin >> id >> state;
        chunk[y][z][x] = id * 17 + state;
      }
    }
  }

  int x1, y1, z1;
  int x2, y2, z2;
  std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

  char command[16];
  std::cin >> command;

  Action action = nullptr;
  void* data = nullptr;
  int new_state;
  ReplaceData ids;

  if (std::strcmp(command, "state") == 0) {
    std::cin >> new_state;
    if (new_state >= 0 && new_state <= 16) {
      action = setState;
      data = &new_state;
    }
  } else if (std::strcmp(command, "replace") == 0) {
    std::cin >> ids.old_id >> ids.new_id;
    if (ids.old_id >= 0 && ids.new_id >= 0) {
      action = replaceId;
      data = &ids;
    }
  }

  if (action == nullptr || !applyToArea(chunk, width, height, depth, x1, y1, z1,
                                        x2, y2, z2, action, data)) {
    std::cout << "error" << "\n";
  } else {
    for (int y = 0; y < height; ++y) {
      for (int z = 0; z < depth; ++z) {
        for (int x = 0; x < width; ++x) {
          int id = chunk[y][z][x] / 17;
          int state = chunk[y][z][x] % 17;
          std::cout << id << ':' << state << ' ';
        }
        std::cout << '\n';
      }
      std::cout << '\n';
    }
  }

  for (int y = 0; y < height; ++y) {
    for (int z = 0; z < depth; ++z) {
      delete[] chunk[y][z];
    }
    delete[] chunk[y];
  }
  delete[] chunk;

  return 0;
}

// урааа дз все
