#include "game.h"
#include <stdlib.h>
#include <stdio.h>

static struct Game new(int width, int height, int mineCount) {
    struct Game this = {
            .width = width,
            .height = height,
            .mineCount = mineCount,
            .slots = malloc(sizeof(struct Slot **) * height),
            .isLost = false,
            .isWon = false,
            .start = time(NULL)
    };

    for (int y = 0; y < height; y++) {
        this.slots[y] = malloc(sizeof(struct Slot *) * width);
        for (int x = 0; x < width; x++) {
            struct Slot thing = Slot.new();
            this.slots[y][x] = &thing;
        }
    }

    int placedMines = 0;
    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;
        if (!this.slots[y][x]->isMine) {
            this.slots[y][x]->isMine = true;
            placedMines++;
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int surroundMineCount = 0;
            for (int y2 = y - 1; y2 <= y + 1; y2++) {
                for (int x2 = x - 1; x2 <= x + 1; x2++) {
                    if (y2 >= 0 && y2 < height && x2 >= 0 && x2 < width && this.slots[y2][x2]->isMine) {
                        surroundMineCount++;
                    }
                }
            }
            this.slots[y][x]->mineCount = surroundMineCount;
        }
    }

    return this;
}

static void checkWin(struct Game *this) {
    int unrevealedCount = 0;
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            if (!this->slots[y][x]->isRevealed) {
                unrevealedCount++;
            }
        }
    }
    if (unrevealedCount == this->mineCount) {
        this->isWon = true;
    }
}

static void reveal(struct Game *this, int x, int y) {
    if (this->isWon || this->isLost) {
        return;
    }

    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return;
    }

    if (this->slots[y][x]->isRevealed) {
        return;
    }

    this->slots[y][x]->isRevealed = true;

    if (this->slots[y][x]->isMine) {
        this->isLost = true;
        for (int y2 = 0; y2 < this->height; y2++) {
            for (int x2 = 0; x2 < this->width; x2++) {
                if (this->slots[y2][x2]->isMine) {
                    this->slots[y2][x2]->isRevealed = true;
                }
            }
        }
        return;
    }

    if (this->slots[y][x]->mineCount == 0) {
        for (int y2 = y - 1; y2 <= y + 1; y2++) {
            for (int x2 = x - 1; x2 <= x + 1; x2++) {
                reveal(this, x2, y2);
            }
        }
    }
}

static void printBoard(struct Game *this) {
    printf("  ");
    for (int x = 0; x < this->width; x++) {
        printf("%d ", x);
        if (x < 10 && this->width >= 10) {
            printf(" ");
        }
    }
    printf("\n");
    for (int y = 0; y < this->height; y++) {
        printf("%d ", y);
        if (y < 10 && this->height >= 10) {
            printf(" ");
        }
        for (int x = 0; x < this->width; x++) {
            printf("%c ", this->slots[y][x]->description(this->slots[y][x]));
            if (this->width >= 10) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

static void delete(struct Game *this) {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            free(this->slots[y][x]);
        }
        free(this->slots[y]);
    }
    free(this->slots);
}
