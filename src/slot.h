//
// Created by Shrish Deshpande on 11/11/22.
//

#ifndef MINESEEPER_SLOT_H
#define MINESEEPER_SLOT_H

#include <stdbool.h>

struct SlotStruct {
    bool isMine;
    bool isRevealed;
    int mineCount;
};

extern const struct SlotClass {
    struct SlotStruct (*new)(bool isMine, int mineCount);
} SlotStruct;

#endif //MINESEEPER_SLOT_H
