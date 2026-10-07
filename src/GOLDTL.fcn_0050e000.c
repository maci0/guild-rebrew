// FUNCTION: GOLD 0x0050ab80
// FUNCTION: GOLDTL 0x0050e000

/* The T&L build of fcn_0050e000 (SERVER 0x10019d30): a missing entity
 * returns 0 without the LogMessageInternal call. */

#include <stddef.h>

extern char* g_99ec10;

void* __cdecl gm_EntityAccumulate(void* pkt);
int __cdecl fcn_00504bd0(int type);
int __cdecl fcn_0050dfd0(char* pkt, int item_id);
void* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl gm_GetMsgField(char* pkt, char* q);
void* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl gm_eval_SlotVoll(char* obj, int item_id, int requested)
{
	char* pkt;
	char* ent;
	char* record;
	int is_cat2;
	int is_producer;
	int size;
	int count;
	int msg_field;
	void* query_result;
	int q_id;

	pkt = obj;
	ent = (char*) gm_EntityAccumulate((void*) pkt);
	if (ent == NULL) {
		return 0;
	}
	is_cat2 = (fcn_00504bd0((unsigned char) *ent) == 2);
	size = fcn_0050dfd0(pkt, item_id);
	query_result = fcn_00502cd0(*(int*) (pkt + 0x14), 1, 0, item_id);
	if (query_result != NULL) {
		msg_field = gm_GetMsgField(pkt, (char*) query_result);
		if (size - msg_field > requested) {
			return requested;
		}
		return size - msg_field;
	}
	record = g_99ec10 + item_id * 0x41;
	if (is_cat2) {
		is_producer = (*record == 0x17);
	} else {
		if (*record == 0x17 || *record == 0x25) {
			is_producer = 1;
		} else {
			is_producer = 0;
		}
	}
	if (*(unsigned short*) pkt == 0x2a) {
		count = 0;
		query_result = fcn_00502cd0(*(int*) (pkt + 0x14), 1, 5);
		if (query_result != NULL) {
			do {
				q_id = *(unsigned short*) query_result;
				record = g_99ec10 + q_id * 0x41;
				if (is_cat2) {
					if (is_producer) {
						if (*record == 0x17) {
							count++;
						}
					} else {
						if (*record != 0x17) {
							count++;
						}
					}
				} else {
					if (is_producer) {
						if (*record == 0x17 || *record == 0x25) {
							count++;
						}
					} else {
						if (*record != 0x17 && *record != 0x25) {
							count++;
						}
					}
				}
				query_result = gm_NextEntityQueryMatch();
			} while (query_result != NULL);
		}
		if (is_producer) {
			if (count >= *(unsigned char*) (pkt + 0x1c)) {
				return 0;
			}
			goto limited;
		}
		if (count >= *(unsigned char*) (pkt + 0x1d)) {
			return 0;
		}
		goto limited;
	}
	count = 0;
	query_result = fcn_00502cd0(*(int*) (pkt + 0x14), 1, 5);
	if (query_result != NULL) {
		do {
			count++;
			query_result = gm_NextEntityQueryMatch();
		} while (query_result != NULL);
	}
	if (count >= *(unsigned char*) (pkt + 0x1c)) {
		return 0;
	}
limited:
	return size < requested ? size : requested;
}
