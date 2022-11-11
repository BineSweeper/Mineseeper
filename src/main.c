#include <stdio.h>
#include "game.h"
#include <string.h>

int main() {
    while (true) {
        printf("\033[2J\033[1;1H");
        printf("Welcome to Mineswifter!\n");
        printf("If you want to exit, type 'exit' at any point of time.\n");
        printf("Please enter the level (default is easy): (easy, medium, hard, custom)\n");
        printf("  Easy   - 9x9 board with 10 mines\n");
        printf("  Medium - 16x16 board with 40 mines\n");
        printf("  Hard   - 30x16 board with 99 mines\n");
        printf("  Custom - You specify the board size and mine count\n");
        char *level = "easy";
        scanf("%s", level);

        if (strcmp(level, "exit") == 0) {
            break;
        }

        int width = 9;
        int height = 9;
        int mineCount = 10;

        if (strcmp(level, "medium") == 0) {
            width = 16;
            height = 16;
            mineCount = 40;
        } else if (strcmp(level, "hard") == 0) {
            width = 30;
            height = 16;
            mineCount = 99;
        } else if (strcmp(level, "custom") == 0) {
            printf("Enter the width of the board:\n");
            scanf("%d", &width);
            printf("Enter the height of the board:\n");
            scanf("%d", &height);
            printf("Enter the number of mines:\n");
            scanf("%d", &mineCount);
        }

        struct Game game = Game.new(width, height, mineCount);

        while (!(game.isLost || game.isWon)) {
            printf("\033[2J\033[1;1H");
            printf("Mineceeper\n");
            game.printBoard(&game);
            printf("Enter the coordinates of the slot you want to reveal: ");
            int x;
            int y;
            scanf("%d %d", &y, &x);
            game.reveal(&game, x, y);
            game.checkWin(&game);

            if (game.isLost || game.isWon) {
                printf("\033[2J\033[1;1H");
                printf("Mineceeper\n");
                game.printBoard(&game);
                if (game.isLost) {
                    printf("You lost!\n");
                } else {
                    printf("You won!\n");
                }
                printf("Press enter to continue...\n");
                getchar();
            }
        }

        game.delete(&game);
    }
    return 0;
}
