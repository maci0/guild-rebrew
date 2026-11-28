

typedef struct {
	unsigned char mode;
	unsigned char pad0[3];
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} Out495a80;

int __cdecl ai_SelectBestMethod(int, int, int, Out495a80*, Out495a80*);
int __cdecl gm_CheckPrivilege(int, char*, int*);
int __cdecl gm_GetCitySkillAverage(int); /* 0x4fbd20, metadata name is stale */
int __cdecl gm_QueryEntities(int, int, int, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00495a80 */
int __cdecl ai_StartBildung(int unused, char* actorEntity, int mode, char* out1, char* out2)
{
	int left;
	int i;
	int k;
	int r;
	int keep[5];
	int used[5];
	unsigned int weight[5];
	int buf[0x88];
	union { Out495a80 msg; float ratios[5]; } extra;
	union { Out495a80 msg; unsigned int count[5]; } action;

	(void) unused;
	left = 5;
	keep[0] = 0x3a;
	keep[1] = 0x1a;
	keep[2] = 0x17;
	keep[3] = 0x18;
	keep[4] = 0x19;
	if (mode != 0) {
		return 0;
	}
	if (*(int*) (actorEntity + 0x170) == 0 && *(char*) (actorEntity + 2) != 3) {
		action.msg.mode = 0;
		action.msg.f1 = 0;
		action.msg.f2 = 0;
		extra.msg.mode = 0;
		extra.msg.f1 = 0;
		extra.msg.f2 = 0;
		extra.msg.f5 = 0x3f28f5c3;
		r = ai_SelectBestMethod(4, *(unsigned short*) actorEntity, 1, &extra.msg, &action.msg);
		if (r != 0) {
			*(Out495a80*) out1 = extra.msg;
			*(Out495a80*) out2 = action.msg;
		}
		return r;
	}
	if (he_StartHandlungSearch(2, 2, *(unsigned short*) actorEntity, 0, 0x60) != 0) {
		return 0;
	}
	if (*(char*) out1 == 0x0e) {
		int slot;
		float f;

		i = *(int*) (out1 + 4);
		for (k = 0; k < 0x88; k++) {
			buf[k] = 0;
		}
		buf[0] = 1;
		r = gm_CheckPrivilege(keep[i], actorEntity, buf);
		f = (r & 2) ? (-1.0f) : 0.0f;
		if (*(unsigned char*) (actorEntity + i + 0x80) < 0x2a) {
			slot = 1;
		} else if (*(unsigned char*) (actorEntity + i + 0x80) < 0x54) {
			slot = 2;
		} else if (*(unsigned char*) (actorEntity + i + 0x80) < 0x7e) {
			slot = 4;
		} else if (*(unsigned char*) (actorEntity + i + 0x80) < 0xa8) {
			slot = 6;
		} else if (*(unsigned char*) (actorEntity + i + 0x80) < 0xd2) {
			slot = 9;
		} else {
			slot = 12;
		}
		/* native: fild; fadd; call _ftol (0x64d228) */
		slot = (int) ((float) slot + f);
		if (slot < *(int*) (actorEntity + 0x194)) {
			return 0;
		}
		if ((float) *(unsigned char*) (actorEntity + i + 0x80) == 252.0f) {
			return 0;
		}
		*(int*) (out1 + 0x10) = slot;
		return 4;
	}
	for (i = 0; (unsigned int) i < 5; i++) {
		float f;

		for (k = 0; k < 0x88; k++) {
			buf[k] = 0;
		}
		buf[0] = 1;
		used[i] = 1;
		action.count[i] = gm_GetCitySkillAverage(i) & 0xff;
		if (action.count[i] == 0) {
			action.count[i] = 0xfc;
		}
		r = gm_CheckPrivilege(keep[i], actorEntity, buf);
		f = (r & 2) ? (-1.0f) : 0.0f;
		if (*(unsigned char*) (actorEntity + 0x80 + i) < 0x2a) {
			weight[i] = 1;
		} else if (*(unsigned char*) (actorEntity + 0x80 + i) < 0x54) {
			weight[i] = 2;
		} else if (*(unsigned char*) (actorEntity + 0x80 + i) < 0x7e) {
			weight[i] = 4;
		} else if (*(unsigned char*) (actorEntity + 0x80 + i) < 0xa8) {
			weight[i] = 6;
		} else if (*(unsigned char*) (actorEntity + 0x80 + i) < 0xd2) {
			weight[i] = 9;
		} else {
			weight[i] = 12;
		}
		/* native: fild qword; fadd; call _ftol (0x64d228) */
		weight[i] = (unsigned int) ((float) weight[i] + f);
		if (weight[i] > *(unsigned int*) (actorEntity + 0x194)) {
			used[i] = 0;
			left--;
		} else if ((float) *(unsigned char*) (actorEntity + 0x80 + i) == 252.0f) {
			used[i] = 0;
			left--;
		} else {
			extra.ratios[i] = (float) *(unsigned char*) (actorEntity + 0x80 + i) / (float) action.count[i];
		}
	}
	if (left == 0) {
		return 0;
	}
	i = (unsigned short) gm_RandomMod(5);
	while (used[i] == 0) {
		i = (i + 1) % 5;
	}
	if (*(char*) (actorEntity + 2) == 3) {
		if (i == 4) {
			if ((*(unsigned char*) (actorEntity + 0x1e8) & 4) == 0) {
				return 0;
			}
		} else if (i == 3) {
			if ((*(unsigned char*) (actorEntity + 0x1e8) & 8) == 0) {
				return 0;
			}
		} else if (i == 2) {
			if ((*(unsigned char*) (actorEntity + 0x1e8) & 2) == 0) {
				return 0;
			}
		}
		goto fill;
	}
	if (i > 1) {
		int slot;

		if (i == 4) {
			slot = 0x15;
		} else {
			slot = (i == 3) ? 0x17 : 0x14;
		}
		if (gm_QueryEntities(*(int*) (*(char**) (actorEntity + 0x170) + 0x5d), 1, 0, slot) == 0) {
			extra.msg.mode = 2;
			extra.msg.f1 = slot;
			extra.msg.f2 = 1;
			extra.msg.f5 = 0x3ee147ae;
			action.msg.mode = 4;
			action.msg.f1 = *(int*) (*(char**) (actorEntity + 0x170) + 1);
			action.msg.f2 = 1;
			r = ai_SelectBestMethod(4, *(unsigned short*) actorEntity, 1, &extra.msg, &action.msg);
			if (r != 0) {
				*(Out495a80*) out1 = extra.msg;
				*(Out495a80*) out2 = action.msg;
			}
			return r;
		}
	}
fill:
	*(unsigned char*) out1 = 0x0e;
	*(int*) (out1 + 4) = i;
	*(int*) (out1 + 0x10) = (int) weight[i];
	return 4;
}
