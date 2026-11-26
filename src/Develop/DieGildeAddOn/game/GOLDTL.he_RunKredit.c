/* Run the credit window state machine: validate the open request, refresh the
 * slot message and record the activity time stamp. */

int __cdecl cm_GetCommandStatus(int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_AccumulateTyped2(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_004c5620(int, int);
int __cdecl fcn_005c4ec0(int, int, int, char*);
#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl fcn_64d41a(char*, char*, int);
void __cdecl he_FreeAction(int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x00564b90 */
void __cdecl he_RunKredit(int loanEvent)
{
	char info[0x80];
	char buf[0x400];
	char msg[0x800];
	char* slot;
	float f;
	int obj;
	int n;
	int time;

	if (*(int*) (loanEvent + 0x84) != -1 && !cm_GetCommandStatus(*(int*) (loanEvent + 0x84))) {
		return;
	}
	n = *(int*) (loanEvent + 0x70);
	*(int*) (loanEvent + 0x84) = -1;
	if (n < -2) {
		return;
	}
	if (n >= 0) {
		if (n != 0) {
			return;
		}
		if (*(unsigned char*) (loanEvent + 0x78) & 2) {
			obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (loanEvent + 0xac));
			if (obj) {
			n = gm_LookupEntityRecordById(*(int*) (loanEvent + 0xb0));
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			if (!n) {
				io_FormatTextBuffer(buf, 0x18e7, *(int*) (loanEvent + 0xb4));
				fcn_00545d40(*(int*) (slot + 4), -1, buf, 0, 0x5ff, 0);
				*(int*) (loanEvent + 0x84) = fcn_004c5620(-1, loanEvent);
				return;
			}
			f = (float) (*(int*) (loanEvent + 0xb4) *
			             (*(int*) (loanEvent + 0xc0) * g_6640e8));
			time = gm_AccumulateTyped2(n);
			if ((float) time < f) {
				time = (int) f;
				io_FormatTextBuffer(msg, 0x18e8, time);
				n = fcn_005c4ec0(*(int*) ((char*) obj + 1), n, time, msg);
				*(int*) ((char*) obj + 0x55) += n;
				if (*(unsigned char*) (slot + 2) == 6 ||
				    *(unsigned char*) (slot + 2) == 7) {
					fcn_00545d40(*(int*) (loanEvent + 0xb0), -1, msg, 0, 0x5ff, 0);
				}
			} else {
				cm_RequestTransferCurrencyNoKill(*(int*) ((char*) obj + 1), *(int*) (loanEvent + 0xb0),
				           g_773d75, (int) f);
				*(int*) ((char*) obj + 0x55) = (int) (*(int*) ((char*) obj + 0x55) + f);
			}
			} else {
				fcn_64d41a(info, (char*) 0x6a6620, *(int*) (loanEvent + 0xac));
				he_FreeAction(loanEvent);
				return;
			}
		}
		n = *(int*) (loanEvent + 0xbc) - 1;
		*(int*) (loanEvent + 0xbc) = n;
		if (n >= 0) {
			return;
		}
		obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (loanEvent + 0xac));
		if (obj) {
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			n = gm_LookupEntityRecordById(*(int*) (loanEvent + 0xb0));
			if (*(unsigned char*) (loanEvent + 0x78) & 2) {
				time = gm_AccumulateTyped2(n);
				if (time < *(int*) (loanEvent + 0xb4))
					io_FormatTextBuffer(buf, 0x18ea, *(int*) (loanEvent + 0xb4));
				else
					io_FormatTextBuffer(buf, 0x18e9, *(int*) (loanEvent + 0xb4));
				fcn_005c4ec0(*(int*) ((char*) obj + 1), n,
				           *(int*) (loanEvent + 0xb4), buf);
				if (time < *(int*) (loanEvent + 0xb4))
					fcn_00545d40(*(int*) (loanEvent + 0xb0), -1, buf, 0, 0x5ff, (char*) 0x699a88);
				else
					fcn_00545d40(*(int*) (loanEvent + 0xb0), -1, buf, 0, 0x5ff, (char*) 0x6b5c60);
				if (*(unsigned char*) (slot + 2) == 6 ||
				    *(unsigned char*) (slot + 2) == 7) {
					io_FormatTextBuffer(msg, 0x18d8, *(unsigned short*) n, obj,
					           *(int*) (loanEvent + 0xb4));
					fcn_00545d40(*(int*) (slot + 4), -1, msg, 0, 0x5ff, 0);
				}
			}
		}
	} else {
		obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (loanEvent + 0xac));
		if (obj) {
			n = gm_LookupEntityRecordById(*(int*) (loanEvent + 0xb0));
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			if (!n) {
				io_FormatTextBuffer(msg, 0x18e7, *(int*) (loanEvent + 0xb4));
				fcn_00545d40(*(int*) (slot + 4), -1, msg, 0, 0x5ff, 0);
			}
		}
	}
	he_FreeAction(loanEvent);
}
