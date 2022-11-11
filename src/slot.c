#include "slot.h"

static struct Slot new() {
    return (struct Slot) {
        .isMine = false,
        .isRevealed = false,
        .mineCount = 0
    };
}

static char description(struct Slot *this) {
    if (!this->isRevealed) {
        return '*';
    }

    if (this->isMine) {
        return 'X';
    } else if (this->mineCount == 0) {
        return ' ';
    } else {
        return '0' + this->mineCount;
    }
}

const struct SlotClass Slot={.new=&new};
