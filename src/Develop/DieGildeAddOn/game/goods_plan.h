#ifndef GOODS_PLAN_H
#define GOODS_PLAN_H

typedef struct GOODS_PLAN_ENTRY {
    int goods_id;
    int parent_index;
    char *supplier;
    int unk_0c;
    int unk_10;
    int requested;
    int unk_18;
    float price;
    int unk_20;
    int allocated;
    int stock;
    int capacity;
    int state_30;
    int unk_34;
    int unk_38;
    int flags;
} GOODS_PLAN_ENTRY;
// SIZE 0x40

extern GOODS_PLAN_ENTRY g_100b0c0[];

#endif
