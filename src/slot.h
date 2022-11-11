#ifndef MINESEEPER_SLOT_H
#define MINESEEPER_SLOT_H

#include <stdbool.h>

struct SlotStruct {
    bool isMine;
    bool isRevealed;
    int mineCount;
};

extern const struct SlotClass {
    struct SlotStruct (*new)();
} SlotStruct;

#endif //MINESEEPER_SLOT_H
