#ifndef MINESEEPER_SLOT_H
#define MINESEEPER_SLOT_H

#include <stdbool.h>

struct Slot {
    bool isMine;
    bool isRevealed;
    int mineCount;

    char (*description)(struct Slot *this);
};

extern const struct SlotClass {
    struct Slot (*new)();
} Slot;

#endif //MINESEEPER_SLOT_H
