//
// Created by manjaro on 6/2/23.
//

#include <unistd.h>
#include "snake_game.h"
#include "linked_list.h"
#include "pthread.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include "color_prints.h"

#define WIDTH 20
#define HEIGHT 20

//This function is from online resources
//https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

void setUp(int _level);

void update();

void draw();

void newFruit();


lst tail, tail_end;
int gameOver = 0;
int fruit, free_cells_left = HEIGHT * WIDTH - 1, headX, headY, score = 0;
int dir[] = {0, 0};
uint speed;
int lvl_;
const char HEAD[] = "\u263a";
const char LOST_HEAD[] = "\u2639";

char *to_char(int n, char inp[]) {
    int i = 0;
    char ret[6];
    while (n) {
        ret[i] = '0' + (n % 10);
        i++;
        n /= 10;
    }
    if (!i) {
        ret[0] = '0';
        i++;
    }
    ret[i] = 0;
    inp[i] = 0;
    int j = 0;
    i--;
    while (i + 1) {
        inp[j] = ret[i];
        j++;
        i--;
    }

    return inp;
}

void setUp(int level_) {
    gameOver = 0;
    score = 0;
    free_cells_left = HEIGHT * WIDTH - 1;
    lvl_ = level_;
    srand(time(NULL));
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    tail = create_list(-2);
    tail_end = tail;
    speed = 500000 / level_;
    newFruit();
    draw();
}

int prev_val;

void tail_move(lst node) {
    int tmp = get_val(node);
    set_val(node, prev_val);
    prev_val = tmp;
}

void update() {
    if (!dir[0] && !dir[1]) return;
    headX += dir[0];
    headY += dir[1];
    if (headX == WIDTH) {
        headX = 0;
    } else if (headX == -1) {
        headX = WIDTH - 1;
    } else if (headY == HEIGHT) {
        headY = 0;
    } else if (headY == -1) {
        headY = HEIGHT - 1;
    }
    int tmp = headY * WIDTH + headX;
    if (find(tail, tmp) || free_cells_left == 0) {
        gameOver = 1;
        draw();
        return;
    }
    prev_val = tmp;
    for_each_node(tail, tail_move);
    if (tmp == fruit) {
        score += lvl_;
        newFruit();
        free_cells_left--;
        push_after(tail_end, prev_val);
        tail_end = get_tail(tail_end);
    }
    draw();
}

void newFruit() {
    int r = rand() % free_cells_left;
    int i = 0;
    while (r) {
        if (!find(tail, i))
            r--;
        i++;
    }
    i--;
    fruit = i;
}

void draw() {
    system("clear");
    fflush(stdout);
    print_green("Score: ");
    char ret[6];
    print_purple(to_char( score, ret));
    printf("\n");
    int tmp;
    for (int i = 0; i < WIDTH; i++) {
        print_blue("--");
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {

        for (int j = 0; j < WIDTH; j++) {
            tmp = j + i * WIDTH;
            if (i == headY && j == headX) {
                print_purple(" ");
                if(!gameOver)
                    print_purple(HEAD);
                else
                    print_red(LOST_HEAD);
            } else if (find(tail, tmp)) {
                print_green(" o");
            } else if (tmp == fruit) {
                print_blue(" F");
            } else
                printf("  ");
        }
        print_blue("\n");
    }
    for (int i = 0; i < WIDTH; i++) {
        print_blue("--");
    }
    printf("\n");
    if(gameOver){
        print_red("\nPress any key");
    }
    fflush(stdout);
}

void game_over() {
    system("clear");
    delete_list(tail);
    print_red("GAME OVER\nYOUR SCORE IS: ");
    char ret[6];
    print_red(to_char(score, ret));
    printf("\n");
}


void *get_key() {
    char temp;
    while (!gameOver) {
        temp = getch();
        if (temp == 'a') {
            if (dir[0] != 1) {
                usleep(speed + speed / 2);
                dir[0] = -1;
                dir[1] = 0;
            }
        } else if (temp == 'd') {
            if (dir[0] != -1) {
                usleep(speed + speed / 2);
                dir[0] = 1;
                dir[1] = 0;
            }
        } else if (temp == 'w') {
            if (dir[1] != 1) {
                usleep(speed + speed / 2);
                dir[0] = 0;
                dir[1] = -1;
            }
        } else if (temp == 's') {
            if (dir[1] != -1) {
                usleep(speed + speed / 2);
                dir[0] = 0;
                dir[1] = 1;
            }
        }
    }
    fflush(stdin);
}

void run(int level_) {
    setUp(level_);
    pthread_t th;

    pthread_create(&th, NULL, get_key, "X");
    while (!gameOver) {
        update();
        usleep(speed);
    }

    pthread_join(th,NULL);
    game_over();
    print_green("");
}
