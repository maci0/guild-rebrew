#ifndef CLIENT_TIMER_H
#define CLIENT_TIMER_H

/* Inferred interface and field names; native slots have a 12-byte stride. */
typedef void (__cdecl* TIMER_CALLBACK)(void);

typedef struct {
    TIMER_CALLBACK funktion;
    unsigned int periode;
    int pausiert;
} TIMER_CALLBACK_SLOT;

/* Declarations only; the table's storage owner remains unresolved. */
/* ADDRESS: GOLDTL 0x01052c60 */
/* ADDRESS: GOLD 0x00fe7aa0 */
extern TIMER_CALLBACK_SLOT g_1052c60[32];

int __cdecl fcn_0042de90(TIMER_CALLBACK callback, unsigned int period);
int __cdecl fcn_0042def0(TIMER_CALLBACK callback);
int __cdecl fcn_0042df30(TIMER_CALLBACK callback, int paused);
int __cdecl fcn_0042df70(TIMER_CALLBACK callback);

#endif
