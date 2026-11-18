#ifndef D2_TRAINING_ROWS_H
#define D2_TRAINING_ROWS_H

typedef struct D2_TRAINING_ITEM {
    int button;
    int objekt_id;
} D2_TRAINING_ITEM;

typedef struct D2_TRAINING_ROW {
    int entity;
    int portrait_element;
    int row_element;
    int window;
    D2_TRAINING_ITEM item[6];
} D2_TRAINING_ROW;
/* SIZE 0x40 */

extern D2_TRAINING_ROW g_7774a0[32];

#endif
