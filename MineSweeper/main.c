#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

HANDLE COUT = 0;
HANDLE CIN = 0;

typedef struct {
    int x;
    int y;
    int mine;
    int dif;
    int cheat;
    int status; // -1 : game over, 0 : playing, 1 : success
    int** player;
    int** map;
} MineSweeper;

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcolor(int num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

void clear(int y,int height) {
    gotoxy(0, y);
    for (int i = 0; i < height; i++) printf("                                                                                                                      \n");
    gotoxy(0, y);
}

void show_map(int** map, int x, int y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            //printf("%d", map[i][j]);
            switch (map[i][j]) {
                case -1: setcolor(8); printf("■"); break;
                case 0: setcolor(6); printf("○"); break;
                case 1: setcolor(6); printf("①"); break;
                case 2: setcolor(6); printf("②"); break;
                case 3: setcolor(6); printf("③"); break;
                case 4: setcolor(6); printf("④"); break;
                case 5: setcolor(6); printf("⑤"); break;
                case 6: setcolor(6); printf("⑥"); break;
                case 7: setcolor(6); printf("⑦"); break;
                case 8: setcolor(6); printf("⑧"); break;
                case 9: setcolor(12); printf("※"); break;
            }
        }
        printf("\n");
        setcolor(15);
    }
}

int be_input() {
    INPUT_RECORD input_record;
    DWORD input_count;
    PeekConsoleInput(CIN, &input_record, 1, &input_count);
    return input_count;
}

int get_input(WORD* vkey, COORD* pos) {
    INPUT_RECORD input_record;
    DWORD input_count;
    ReadConsoleInput(CIN, &input_record, 1, &input_count);
    switch (input_record.EventType) {
    case MOUSE_EVENT:
        if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(COUT, &csbi);
            *pos = input_record.Event.MouseEvent.dwMousePosition;
            pos->X -= csbi.srWindow.Left;
            pos->Y -= csbi.srWindow.Top;
            return MOUSE_EVENT;
        }
        break;
    }
    return 0;
}

int select_map(int x, int y, MineSweeper *data) {
    if (data->map[y][x] == 9) {
        data->player[y][x] = 9;
        data->status = -1;
        return -1;
    }
    else {
        data->player[y][x] = data->map[y][x];
        int isMine = 0;
        for (int tx = x - 1; tx < x + 2; tx++) for (int ty = y - 1; ty < y + 2; ty++) {
            if (tx < 0 || ty < 0 || tx >= data->x || ty >= data->y || (x == tx && y == ty) || data->player[ty][tx] != -1) continue;
            if (data->map[ty][tx] == 9) isMine = 1;
        }
        if (!isMine) for (int tx = x - 1; tx < x + 2; tx++) for (int ty = y - 1; ty < y + 2; ty++) {
            if (tx < 0 || ty < 0 || tx >= data->x || ty >= data->y || (x == tx && y == ty) || data->player[ty][tx] != -1) continue;
            select_map(tx, ty, data);
        }
    }
    for (int i = 0; i < data->y; i++) for (int j = 0; j < data->x; j++) if (data->map[i][j] != 9 && data->map[i][j] != data->player[i][j]) {
        data->status = 0;
        return 0;
    }
    data->status = 1;
    return 1;
}

void main() {

    MineSweeper data;
    data.cheat = 0;
    srand(time(NULL));

    system("title MineSweeper");
    system("mode con cols=175 lines=50");

    DWORD mode;
    WORD key;
    COORD pos;
    int event, x, y;
    CIN = GetStdHandle(STD_INPUT_HANDLE);
    COUT = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(CIN, &mode);
    SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);

    //while(1) if(be_input()) if(get_input(&key, &pos) != 0) {
    //    MOUSE_EVENT;
    //    x = pos.X, y = pos.Y;
    //}

    restart:
    clear(0, 150);

    data.x = data.y = data.dif = data.mine = data.cheat = -1;

    gotoxy(71, 17);
    printf("지뢰찾기 레벨을 선택해주세요.");
    gotoxy(73, 18);
    printf("┌──────┬────────┬──────┐");
    gotoxy(73, 19);
    printf("│ Easy │ Normal │ Hard │");
    gotoxy(73, 20);
    printf("└──────┴────────┴──────┘");
    gotoxy(52, 21);
    printf("클릭이 안된다면 설정 - 속성에서 '빠른 편집 모드'와 '삽입모드'를 꺼주세요.");
    gotoxy(0, 0);

    while(1) if(be_input()) if(get_input(&key, &pos) != 0) {
        MOUSE_EVENT;
        x = pos.X, y = pos.Y;
        //printf("x : %d, y : %d\n", x, y);
        if (x == 0 && y == 0) {
            gotoxy(0, 0);
            data.cheat = 1;
            printf("Wow! You Fount Cheat!");
        } else if (74 <= x && x <= 96 && 18 <= y && y <= 20) {
            if (74 <= x && x <= 80) data.dif = 1;
            else if (81 <= x && x <= 89) data.dif = 2;
            else data.dif = 3;
            data.x = data.dif == 1 ? 9 : data.dif == 2 ? 16 : 30;
            data.y = data.dif == 1 ? 9 : 16;
            data.mine = data.dif == 1 ? 10 : data.dif == 2 ? 40 : 99;
            break;
        }
    }

    //Generate MineSweeper Map
    data.map = (int**)malloc(sizeof(int*) * data.y);
    for (int i = 0; i < data.y; i++) data.map[i] = (int*)malloc(sizeof(int) * data.x);
    for (int i = 0; i < data.y; i++) for (int j = 0; j < data.x; j++) data.map[i][j] = 0;
    for (int i = 0; i < data.mine; i++) {
        int rx = rand() % data.x;
        int ry = rand() % data.y;
        if (data.map[ry][rx] == 9) i--;
        else {
            data.map[ry][rx] = 9;
            for (int tx = -1; tx < 2; tx++) for (int ty = -1; ty < 2; ty++) if (0 <= rx + tx && rx + tx < data.x && 0 <= ry + ty && ry + ty < data.y && data.map[ry + ty][rx + tx] != 9) {
                data.map[ry + ty][rx + tx]++;
            }
        }
    }

    //Generate Player's Map
    data.player = (int**)malloc(sizeof(int*) * data.y);
    for (int i = 0; i < data.y; i++) data.player[i] = (int*)malloc(sizeof(int) * data.x);
    for (int i = 0; i < data.y; i++) for (int j = 0; j < data.x; j++) data.player[i][j] = -1;

    clear(0, 150);

    show_map(data.player, data.x, data.y);
    printf("블럭을 클릭해주세요."); 
    if (data.cheat == 1) { //Show MineSweeper Map
        gotoxy(0, data.y + 2);
        show_map(data.map, data.x, data.y);
    }

    while(1) if(be_input()) if(get_input(&key, &pos) != 0) {
        MOUSE_EVENT;
        x = pos.X, y = pos.Y;
        if (0 <= x && x < data.x*2 && 0 <= y && y < data.y) {
            x = (x + 1) % 2 == 0 ? (x + 1) / 2 - 1 : (x + 1) / 2;
            int res = select_map(x, y, &data);
            if (res == 0) {
                clear(0, data.y + 2);
                show_map(data.player, data.x, data.y);
                printf("블럭을 클릭해주세요.");
                if (data.cheat == 1) { //Show MineSweeper Map
                    gotoxy(0, data.y + 2);
                    show_map(data.map, data.x, data.y);
                }
            } else if (res == -1) { // Game Over
                clear(0, data.y * 3);
                printf("        Game Over!");
                gotoxy(0, 5);
                show_map(data.player, data.x, data.y);
                if (data.cheat == 1) { //Show MineSweeper Map
                    gotoxy(0, data.y + 7);
                    show_map(data.map, data.x, data.y);
                }
                break;
            } else { // Success
                clear(0, data.y*3);
                printf("         Sucess!");
                gotoxy(0, 5);
                show_map(data.player, data.x, data.y);
                if (data.cheat == 1) { //Show MineSweeper Map
                    gotoxy(0, data.y + 7);
                    show_map(data.map, data.x, data.y);
                }
                break;
            }
        }
    }

    gotoxy(0, 1);
    printf("다시 플레이 하시겠습니까? \n");
    printf("    ┌───────┬──────┐ \n");
    printf("    │  Yes  │  No  │ \n");
    printf("    └───────┴──────┘ \n");
    gotoxy(0,0);

    while(1) if(be_input()) if(get_input(&key, &pos) != 0) {
        MOUSE_EVENT;
        x = pos.X, y = pos.Y;
        //printf("x : %d, y : %d\n", x, y);
        if (5 <= x && x <= 19 && 2 <= y && y <= 4) {
            if (5 <= x && x <= 12) goto restart;
            else break;
        }
    }

}