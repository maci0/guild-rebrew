#ifndef GOLD_WINDOW_H
#define GOLD_WINDOW_H

typedef struct {
    char unk_000[4];
    short x;
    short y;
    short width;
    short height;
    char unk_00c[0x0c];
    int* list;
    short count;
    char unk_01e[0x0a];
    int unk_028;
    char unk_02c[0x218];
    int limit;
    int scroll;
    char unk_24c[0x18];
    int step;
    char unk_268[4];
    int id;
    char unk_270[0x0c];
    short font;
    char unk_27e[2];
    int active;
    char unk_284[0x114];
    int margin[4];
    int child[3];
    char unk_3b4[4];
    int control[3];
} GOLD_GUI_WINDOW;
/* SIZE 0x3c4 */

extern GOLD_GUI_WINDOW g_f8f120[];

#endif
