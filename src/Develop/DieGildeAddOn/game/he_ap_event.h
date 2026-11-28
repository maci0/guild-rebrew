#ifndef HE_AP_EVENT_H
#define HE_AP_EVENT_H

/* SIZE 0x50 */
typedef struct HE_AP_EVENT {
    signed char lifetime;
    char unk_01[3];
    int subject_id;
    int value_08;
    int value_0c;
    char name[0x40];
} HE_AP_EVENT;

extern HE_AP_EVENT he_ApEvents[256];

#endif
