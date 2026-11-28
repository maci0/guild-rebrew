#ifndef HEAD_SET_H
#define HEAD_SET_H

typedef struct {
    int key;
    char name[0x30];
    int head[4];
} HEAD_SET;
/* SIZE 0x44 */

extern HEAD_SET gm_FemaleHeadSets[];

#endif
