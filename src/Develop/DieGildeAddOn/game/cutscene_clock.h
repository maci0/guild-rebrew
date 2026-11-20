#ifndef CUTSCENE_CLOCK_H
#define CUTSCENE_CLOCK_H

/* Inferred declaration home and scalar views; no storage ownership is claimed. */
/* ADDRESS: GOLDTL 0x00772f30 */
/* ADDRESS: GOLD 0x006f0d80 */
extern int cut_CurrentTick;
/* ADDRESS: GOLDTL 0x00772f34 */
/* ADDRESS: GOLD 0x006f0d84 */
extern int cut_ClockDeadline;
/* ADDRESS: GOLDTL 0x00772f38 */
/* ADDRESS: GOLD 0x006f0d88 */
extern int cut_ClockExpired;

void __cdecl cut_UpdateClock(void);

#endif
