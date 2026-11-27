extern char* g_772eb4; extern int g_772f2c; extern unsigned short* g_772e9c; extern int g_67a370;
char* __cdecl fcn_004cef30(int id);
unsigned short __cdecl fcn_0042e410(int code);
char* __cdecl gm_FindOrCreateEntitySlot(int a, char* s);
int __cdecl cut_FindCombatTarget(char* s);
char* __cdecl d3_FindNearestEscapeNode(char* s);
int __cdecl d3_TransformPoint(char* a, char* b, void* c);
char __cdecl d3sm_SampleHeight(int a, void* b, void* c, void* d, void* e);
int __cdecl cm_SendUpdateCutsceneEntitySlot(int a, void* b);
double __cdecl gm_GetEntityHealthRatio(char* s);
int __cdecl fcn_0064d228(float v);
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x004d7fa0 */
int __cdecl cut_UpdateCombatTeamAI(int ctx, int teamPtr)
{
	int level;
	int count80;
	int countC0;
	int i;
	char* base;
	char* list;
	char* s;
	char* slotPtr;
	char* targetPtr;
	char* found;
	int tmp[11];
	float point[3];
	int map_x;
	int entityId;
	int status;
	double ratio;
	double val;

	level = g_772f2c;
	if (level < 1) {
		return level;
	}
	list = g_772eb4;
	if (teamPtr == (int) g_772e9c) {
		base = list + 0xc0;
	} else {
		base = list + 0x80;
	}
	count80 = 0;
	for (i = 0; i < 0x10; i++) {
		entityId = *(int*) (list + 0x80 + i * 4);
		if (entityId != -1) {
			s = fcn_004cef30(entityId);
			if (s[8] != 0 && s[8] != 4) {
				count80++;
			}
		}
	}
	countC0 = 0;
	for (i = 0; i < 0x10; i++) {
		entityId = *(int*) (list + 0xc0 + i * 4);
		if (entityId != -1) {
			s = fcn_004cef30(entityId);
			if (s[8] != 0 && s[8] != 4) {
				countC0++;
			}
		}
	}
	if (teamPtr == (int) g_772e9c) {
		ratio = (double) countC0 / (double) count80;
	} else {
		ratio = (double) count80 / (double) countC0;
	}
	if (ratio <= 0.5 && fcn_0042e410(0x64) > 0x14) {
		found = 0;
		i = 0;
		while (i < 0x10 && found == 0) {
			entityId = *(int*) (base + i * 4);
			if (entityId != -1) {
				found = fcn_004cef30(entityId);
			}
			i++;
		}
		if (found == 0) {
			return 0;
		}
		slotPtr = (char*) gm_FindOrCreateEntitySlot(ctx, found);
		*(int*) slotPtr = *(int*) (found + 4);
		*(int*) (slotPtr + 4) = 5;
		return (int) slotPtr;
	}
	for (i = 0; i < 0x10; i++) {
		entityId = *(int*) (base + i * 4);
		if (entityId == -1) {
			continue;
		}
		s = fcn_004cef30(entityId);
		slotPtr = (char*) gm_FindOrCreateEntitySlot(ctx, s);
		memcpy(tmp, slotPtr, 0x2c);
		val = gm_GetEntityHealthRatio(s) * 100.0;
		status = (int) val;
		if (status >= 0x14 || fcn_0042e410(0x64) <= 0x1e) {
			status = cut_FindCombatTarget(s);
			if (status == 0) {
				continue;
			}
			targetPtr = (char*) status;
			*(int*) (tmp + 0) = *(int*) (s + 4);
			*(int*) (tmp + 1) = 2;
			*(int*) (tmp + 5) = *(int*) (targetPtr + 4);
			cm_SendUpdateCutsceneEntitySlot(*(int*) (ctx + 0x10), tmp);
		} else {
			float height;
			targetPtr = (char*) d3_FindNearestEscapeNode(s);
			d3_TransformPoint(targetPtr, targetPtr + 0x4c, point);
			map_x = ctx;
			status = d3sm_SampleHeight(*(int*) (g_67a370 + 0xb0),
			    point, &map_x, &countC0, &height);
			if (status != 0) {
				continue;
			}
			*(int*) (tmp + 0) = *(int*) (s + 4);
			*(int*) (tmp + 1) = 3;
			*(int*) (tmp + 4) = map_x;
			*(int*) (tmp + 5) = countC0;
			cm_SendUpdateCutsceneEntitySlot(*(int*) (ctx + 0x10), tmp);
		}
	}
	return 0;
}
