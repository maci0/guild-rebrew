#include <string.h>
int __cdecl __ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_DeallocEntity(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float fColorScale;
extern int DAT_10030b6c;
extern char DAT_10035439;
extern float DAT_100256cc;
extern float DAT_100256a0;
extern char s__ahm_AllocAhmInfo_1002a0f7[];
extern double dScaleFactor;
extern int DAT_1002c050[];
int* __cdecl ahm_LookupEntityInTable(int);
extern dispatch_fn PTR_LAB_1002c5a0[];

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
typedef struct {
	char hdr[8];
	int key;
	char pad[4];
	int val;
} SRC;

// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */

// FUNCTION: SERVER 0x1000c710
// GetCommandPayloadSize

int GetCommandPayloadSize(unsigned char* param_1)

{
	int entry_size;
	unsigned char* cursor;
	int total_size;
	int count;

	// switch table (103 cases) at 0x1000c864
	switch (*param_1) {
	case 3:
	case 0x13:
	case 0x1a:
	case 0x25:
	case 0x2b:
	case 0x34:
	case 0x36:
	case 0x38:
	case 0x47:
	case 0x52:
	case 0x54:
	case 0x5b:
	case 0x5d:
		return 0x1c;
	case 4:
		return 0x11;
	default:
		return 0x91;
	case 8:
	case 0x1c:
	case 0x28:
	case 0x31:
	case 0x3b:
	case 0x42:
	case 0x43:
	case 0x4a:
	case 0x4d:
	case 0x57:
	case 0x58:
	case 0x69:
		return 0x14;
	case 10:
		return 0x50;
	case 0xb:
		return 0x2a;
	case 0xc:
		return 0x49;
	case 0xd:
	case 0x21:
	case 0x23:
	case 0x24:
	case 0x26:
	case 0x27:
	case 0x29:
	case 0x2a:
	case 0x33:
	case 0x39:
	case 0x3a:
	case 0x5a:
	case 0x66:
	case 0x68:
		return 0x18;
	case 0xf:
	case 0x2c:
		return 0x21;
	case 0x11:
	case 0x3d:
		return 0x27;
	case 0x12:
	case 0x1e:
		return 0x1e;
	case 0x14:
		return 0x16;
	case 0x15:
		return 0x39;
	case 0x16:
	case 0x17:
		cursor = param_1 + (*param_1 == 0x16 ? 0x15 : 0x15);
		total_size = 0x15;
		break;
	case 0x18:
		return param_1[0x14] * 5 + 0x15;
	case 0x19:
	case 0x53:
		return 0x24;
	case 0x1b:
	case 100:
		return 0x28;
	case 0x1d:
		return 0x5f;
	case 0x20:
		return (-(param_1[0x10] != '\x0e') & 0x7c) + 0x11;
	case 0x22:
		return 0x3d;
	case 0x2d:
	case 0x45:
		return 0x1f;
	case 0x2e:
	case 0x3c:
		return 0x20;
	case 0x2f:
	case 0x30:
		return 0x3c;
	case 0x32:
	case 0x3e:
	case 0x4f:
	case 0x5e:
	case 99:
		return 0x34;
	case 0x35:
		return 0x5d;
	case 0x37:
		return 0x45;
	case 0x40:
	case 0x60:
		return 0x2f;
	case 0x41:
		return 0x4a;
	case 0x44:
		return 0x17;
	case 0x46:
		return 0x19;
	case 0x48:
		return 0x15;
	case 0x49:
		return 0x36;
	case 0x4b:
	case 0x67:
		return 0x90;
	case 0x4c:
		return 0x35;
	case 0x4e:
		return 0x40;
	case 0x50:
	case 0x51:
		return 0x44;
	case 0x55:
		return 0x61;
	case 0x56:
		return 0x38;
	case 0x5c:
		return 0x1a;
	case 0x5f:
		return 0x80;
	case 0x61:
	case 0x62:
		return 0x29;
	}
	for (count = param_1[0x14]; count > 0; count = count - 1) {
		entry_size = cursor[1] * *cursor + 4;
		total_size = total_size + entry_size;
		cursor = cursor + entry_size;
	}
	return total_size;
}

/* Processes an alchemy entity chain. Iterates linked alchemy
 * entities and applies processing steps (mixing, timing,
 * completion checks). */
