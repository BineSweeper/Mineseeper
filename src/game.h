#ifndef MINESEEPER_GAME_H
#define MINESEEPER_GAME_H

#include "slot.h"
#include <time.h>

struct Game {
    int width;
    int height;
    int mineCount;
    struct Slot ***slots;
    bool isLost;
    bool isWon;
    time_t start;

    void (*checkWin)(struct Game *this);

    void (*reveal)(struct Game *this, int x, int y);

    void (*printBoard)(struct Game *this);

    void (*delete)(struct Game *this);
};

extern const struct GameClass {
    struct Game (*new)(int width, int height, int mineCount);
} Game;

#endif //MINESEEPER_GAME_H
