#include "stdio.h"
#include "snake_game.h"


int main() {
    int lvl;
    char play_again = 'y';
    while (play_again == 'y' || play_again == 'Y') {
        printf("Choose the lvl 1-10\n");
        scanf("%d", &lvl);
        if (lvl > 10) lvl = 10;
        if (lvl < 1) lvl = 1;
        run(lvl);
        play_again = 0;
        fflush(stdin);
        while(play_again != 'y' && play_again != 'Y' && play_again != 'n' && play_again != 'N') {
            printf("\nPress y if you want to try again\npress N otherwise");
            printf("\n");
            scanf("%c", &play_again);
            scanf("%c", &play_again);
        }
    }
    return 0;
}
