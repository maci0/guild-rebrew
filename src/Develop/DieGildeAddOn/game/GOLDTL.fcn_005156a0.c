#include <string.h>

extern char* g_6b8014;
extern char* lpObjektePROT;
extern unsigned char* lpGebaeudePROT;
extern unsigned char* g_7746c8;
extern unsigned short g_774970;
extern unsigned char g_773dd4;

extern void* __cdecl fcn_00502cd0(int list, int a, int b, ...);
extern void* __cdecl gm_NextEntityQueryMatch(void);
extern int __cdecl fcn_005014d0(unsigned short handle);
extern int __cdecl fcn_00501490(char* key);
extern int __cdecl fcn_00506380(int a, void* table, void* record, int mode);
extern void __cdecl fcn_00442d50(char* record, int mode);
extern int __cdecl fcn_00413680(char* record, char* scene, char* out, int* value);
extern void* __cdecl fcn_00426fd0(char* name);
extern void __cdecl fcn_00428340(void* handle, int a, int b);
extern void __cdecl SelectTextureSet(char* record, int target, char mode, int flag);

/* ADDRESS: GOLDTL 0x005156a0 */
void __cdecl fcn_005156a0(char* record)
{
	char* list;
	char* base;
	char* entry;
	char* slot;
	char* item;
	char* table;
	unsigned int id;
	unsigned int v22;
	int idx;
	int kind;
	int i;
	int n;
	int count;
	int a;
	int b;
	int rc;
	unsigned short v1;
	unsigned short v2;
	unsigned short v12;
	char buf[16];
	int value;
	void* handle;

	base = record;
	slot = 0;
	list = 0;
	id = *(unsigned int*) (record + 0x48) & 0xffffff;
	if (*(int*) 0x7f3b24 != 0)
		list = (char*) *(int*) (*(int*) 0x7f3b24 + 0x14);
	else
		list = *(char**) (0x7f3ee0 + 0x5d);
	if (record[0x4b] != 1)
		goto tail;
	idx = (int) (id * 0x41);
	entry = lpObjektePROT + idx;
	kind = *(unsigned char*) entry;
	if (kind == 2)
		goto label_59eb;
	if (kind == 0x1d)
		goto label_5a7a;
	if (kind != 0x21 && kind != 6) {
		slot = (char*) fcn_00502cd0((int) list, 1, 0, (int) id);
		if (slot == 0)
			goto label_59eb;
		*(unsigned int*) (slot + 0x30) = 0;
		*(unsigned int*) (slot + 0x34) = 0;
		table = *(char**) (record + 0x1fc);
		if (table != 0) {
			if (table[0x4b] != 1) {
				fcn_00442d50(record, 1);
				*(char**) (record + 0x204) = slot;
				*(unsigned int*) (record + 0x224) = 0;
				*(char**) (slot + 0x30) = record;
				if (fcn_005014d0(*(unsigned short*) slot) != 0) {
					item = (char*) fcn_00502cd0((int) list, 1, 4, *(unsigned char*) entry);
					while (item != 0) {
						if (*(unsigned short*) slot < *(unsigned short*) item)
							fcn_00442d50(record, 0);
						item = (char*) gm_NextEntityQueryMatch();
					}
				}
			} else {
				char* other;
				other = (char*) fcn_00502cd0((int) list, 1, 0,
					*(unsigned int*) (table + 0x48) & 0xffffff);
				if (other != 0) {
					fcn_00442d50(record, 1);
					*(char**) (record + 0x204) = slot;
					*(unsigned int*) (record + 0x224) = 0;
					*(char**) (slot + 0x30) = record;
					if (fcn_005014d0(*(unsigned short*) slot) != 0) {
						item = (char*) fcn_00502cd0((int) list, 1, 4, *(unsigned char*) entry);
						while (item != 0) {
							v1 = *(unsigned short*) item;
							v2 = *(unsigned short*) slot;
							if (v1 != v2) {
								int best;
								int second;
								char* row;
								row = (char*) lpGebaeudePROT
									+ *(unsigned char*) 0x7f3ee0 * 0x24d;
								best = -1;
								second = -1;
								count = *(unsigned char*) (row + 0x22);
								if (count != 0) {
									char* p;
									p = row + 0x23;
									for (i = 0; i < count; i++) {
										v12 = *(unsigned short*) p & 0x7fff;
										if (v12 != 0) {
											if (v1 != v12) {
												if (v2 == v12)
													second = i;
											} else {
												best = i;
											}
										}
										p += 2;
									}
									if (best != -1 && second < best)
										fcn_00442d50(record, 0);
								}
							}
							item = (char*) gm_NextEntityQueryMatch();
						}
					}
					(void) other;
					table = lpObjektePROT + *(unsigned int*) other * 0x41;
					slot = (char*) other;
					if (fcn_005014d0(*(unsigned short*) slot) != 0) {
						int* q;
						q = (int*) fcn_00502cd0((int) list, 1, 4, *(unsigned char*) table);
						while (q != 0) {
							if (*(unsigned short*) slot < *(unsigned short*) q)
								fcn_00442d50(record, 0);
							q = (int*) gm_NextEntityQueryMatch();
						}
					}
				} else {
					fcn_00442d50(record, 0);
					*(unsigned int*) (record + 0x204) = 0;
				}
			}
		} else {
			entry = lpObjektePROT + idx;
			fcn_00442d50(record, 1);
			*(char**) (record + 0x204) = slot;
			if (*entry != 0x1d)
				*(unsigned int*) (record + 0x224) = 0;
			*(char**) (slot + 0x30) = record;
			if (fcn_005014d0(*(unsigned short*) slot) != 0) {
				item = (char*) fcn_00502cd0((int) list, 1, 4, *(unsigned char*) entry);
				while (item != 0) {
					if (*(unsigned short*) slot < *(unsigned short*) item)
						fcn_00442d50(record, 0);
					item = (char*) gm_NextEntityQueryMatch();
				}
			}
		}
	} else {
label_59eb:
		if (entry[0] == 0x1d)
			goto label_5a7a;
		slot = (char*) fcn_00502cd0((int) *(void**) (0x7f3ee0 + 0x5d), 2, 6,
			0, (int) id);
		if (slot == 0)
			goto label_5a7a;
		fcn_00442d50(record, 1);
		*(char**) (record + 0x204) = slot;
		if ((entry[0] == 6 || entry[0] == 2) && g_7746c8 != 0) {
			v22 = fcn_00506380(g_774970, (void*) 0x7f3ee0, slot, 0);
			if ((v22 & 0x4000) != 0) {
				*(unsigned int*) (record + 0x224) = 1;
				*(char**) (slot + 0x30) = record;
				goto label_5aab;
			}
		} else {
			*(unsigned int*) (record + 0x224) = 0;
		}
		*(char**) (slot + 0x30) = record;
		goto label_5aab;
label_5a7a:
		if (lpObjektePROT[idx] != 0x1d && lpObjektePROT[idx] != 0x21
			&& *(int*) (record + 0x218) != 1)
			fcn_00442d50(record, 0);
	}
label_5aab:
	if (slot != 0 && (*(unsigned char*) (slot + 0x13) & 0xa0) != 0) {
		if (*(int*) (record + 0x1ec) != 0) {
			rc = fcn_00413680(record, g_6b8014, buf, &value);
			if (rc != 0) {
				handle = fcn_00426fd0((char*) 0x6a1f3c);
				if (handle != 0)
					fcn_00428340(handle, 6, value);
			}
		}
		*(unsigned char*) (slot + 0x13) = *(unsigned char*) (slot + 0x13) & 0x5f;
	}
tail:
	if (strncmp(record, (char*) 0x6a1f38, 3) != 0) {
		if (strncmp(record, (char*) 0x68d6fc, 4) == 0
			&& strncmp(record, (char*) 0x68d6f8, 3) == 0)
			return;
		if (*(int*) (record + 0x1cc) == 0) {
			SelectTextureSet(record, *(int*) (record + 0x1ec) + 0xf4,
				(char) g_773dd4, 1);
			return;
		}
		SelectTextureSet(record, *(int*) (record + 0x1cc), (char) g_773dd4, 1);
		return;
	}
	idx = fcn_00501490(record + 6);
	if (idx == -1)
		return;
	if (lpObjektePROT[idx * 0x41] != 2)
		list = base;
	else
		list = *(char**) (0x7f3ee0 + 0x5d);
	if (fcn_00502cd0((int) list, 1, 0, idx) != 0) {
		fcn_00442d50(record, 0);
		return;
	}
	fcn_00442d50(record, 1);
}
