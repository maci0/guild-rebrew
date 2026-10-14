/* Canonical types of client globals whose declaring files view them
 * through different local structs.  Each global has one declaration,
 * typed here; a file with another view reads it through a cast at the
 * use site. */
#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

/* g_100b0c0 */
typedef struct Seg {
	int id;
	int next;
	int owner;
	char padc[8];
	int want;
	char pad18[0xc];
	int busy;
	int stock;
	int cap;
	char pad30[0xc];
	int flags;
} Seg;

/* g_100dc20 */
typedef struct {
	char* owner;
	char pad4[0x14];
	int count;
	char pad1c[0x2e4];
	Seg lights[4];
} LightState;

/* g_1007ce0 */
typedef struct {
	int rank;
	int suit;
	int count;
	int owner;
} Card_1007ce0;

/* g_1007ce8 */
typedef struct {
	int state;
	int flag;
	int c;
	int d;
} slot_1007ce8;

/* g_100d0c0 */
typedef struct {
	int f0;
	char pad4[0x38];
	int f3c;
	char pad40[0x14];
	unsigned char flags;
	char pad55[0x3];
} entry_100d0c0;

/* g_100e7a0 */
typedef struct {
	char* seq;
	char frame;
	char pad5[7];
	char running;
	char padd[7];
} Anim_100e7a0;

/* DisplayCounters */
typedef struct {
	int key;
	int val;
	unsigned char unknown_08[4];
} DISPLAY_COUNTER;

extern DISPLAY_COUNTER DisplayCounters[6];
void __cdecl ResetDisplayCounters(void);
int __cdecl CountDisplayCounters(void);

/* g_1015f40 */
typedef struct {
	char pad0[0xc];
	int xc;
	char pad10[0x248];
	int x258;
	char pad25c[0x18];
	int x274;
	char pad278[0x3cc - 0x278];
} Win_1015f40;

/* g_1015f4c */
typedef struct {
	char pad[0x270];
	int f270;
	char pad2[0x158];
} s_1015f4c;

/* g_102cbc4 */
typedef struct {
	int count;
	int sel;
	int ids[33];
} Group_102cbc4;

/* g_102cbc8 */
typedef struct {
	int n;
	char pad4[0x88];
} List8c_102cbc8;

/* g_102d140 */
typedef struct {
	int idx;
	int x;
	int y;
	int pad0c;
	int w;
	int h;
	int max;
	int f1c;
	int pad20;
	unsigned char digits;
	char pad25[3];
	int flags;
	char pad2c[0x12c - 0x2c];
	int f12c;
	int used;
	int ent;
	int font;
	int def;
	int f140;
	char pad144[0x160 - 0x144];
} Fld_102d140;

/* g_102d278 */
typedef struct {
	int i[0x160 / 4];
} Tex_102d278;

/* g_1038140 */
typedef struct {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x1a4 - 0x194];
	void* fx[2];
	void* h[2];
	char pad1b4[0x2bc - 0x1b4];
} Obj_1038140;

/* g_1038144 */
typedef struct {
	int i[175];
} Page_1038144;

/* g_1041d20 */
typedef struct {
	int color;
	float f4;
	float f8;
} Pal_1041d20;

/* g_1043340 */
typedef struct {
	int used;
	char pad4[0x3d8];
} Slot_1043340;

/* g_14cbbe0 */
typedef struct {
	int h;
	char* sample;
	int prio;
	int loop;
	int time;
	int flags;
	int f18;
	int f1c;
	int f20;
	int vol;
	int pan;
	int f2c;
} Voice_14cbbe0;

/* g_14cc460 */
typedef struct Chan_14cc460 {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char b105;
	unsigned char bAmbient;
	unsigned char b107;
	int f108;
	int f10c;
	int f110;
	int f114;
	unsigned int f118;
	int f11c;
	int f120;
	struct Chan_14cc460* next;
} Chan_14cc460;

/* g_14d0c40 */
typedef struct {
	int handler;
	unsigned char kind;
	char name[0x43];
	int param;
} Entry_14d0c40;

/* g_67bbdc, g_6b86c4 */
typedef struct {
	float x;
	float y;
	float z;
} VECTOR3;

/* Three-float view; complete allocation and storage owner remain unresolved. */
extern VECTOR3 g_67bbdc;

/* g_68da68, g_9a9220 */
typedef struct {
	unsigned char id;
	char pad1[3];
	int x4;
	unsigned char type;
	char pad9[3];
	int xc;
	unsigned char x10;
	char pad11[7];
} Rec18_68da68;

/* g_68ff80 */
typedef struct {
	int v;
	char pad4[0x20];
} Slot_68ff80;

/* g_699058 */
#pragma pack(push, 1)
typedef struct {
	unsigned char k;
	unsigned short ids[10];
} Rec15_699058;
#pragma pack()

/* g_7731b8 */
typedef struct {
	int id;
	char pad[0x158];
	int h[3];
	char tail[8];
} Slot170_7731b8;

/* g_776c60 */
typedef struct {
	int btn;
	char* item;
} Btn_776c60;

/* g_7774a0 */
typedef struct {
	int x0;
	int x4;
	int btn;
	char padc[0x34];
} Loot_7774a0;

/* g_778da0, g_7796e0 */
typedef struct {
	int x0;
	int x4;
	int x8;
	int xc;
	int x10;
	int x14;
	int x18;
	int x1c;
	int x20;
	int x24;
	int x28;
	int x2c;
	int x30;
	int x34;
} Slot_778da0;

/* g_779d00 */
typedef struct {
	int a;
	int b;
	int c;
} Slot_779d00;

/* g_77e8c0 */
typedef struct {
	char* p;
	int h;
	int x8;
} s_77e8c0;

/* g_77e980 */
typedef struct {
	unsigned char kind;
	char pad1[7];
	unsigned short house;
	char pada[0x66];
	int target;
	char pad74[0xd8];
} unit_77e980;

/* g_7e2ac0 */
typedef struct {
	int key;
	int pad[5];
	int v;
	int w;
} s_7e2ac0;

/* g_7e43a8 */
typedef struct {
	int a[24];
	int b[24];
	int pad[2];
	int c[24];
	int d[24];
} Tabs_7e43a8;

/* g_7e46c0 */
typedef struct {
	char* e;
	char pad[0x44];
	char name[0x80];
} s_7e46c0;

/* g_7f3f00 */
typedef struct {
	int x0;
	int x4;
	int x8;
	unsigned short xc;
	char pad[0x26];
} Rec34_7f3f00;

/* g_7f4c00 */
#pragma pack(2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} pos14_7f4c00;
#pragma pack()

/* g_868080 */
typedef struct {
	char pad[0x2f4];
} trade_868080;

/* g_99ec20 */
typedef struct {
	float a;
	float b;
	float c;
	float d;
	float e;
} Sample_99ec20;

/* g_99ec2c */
typedef struct {
	float f;
	int v;
	float pad[3];
} Pt5d36_99ec2c;

/* g_99ef80 */
typedef struct {
	short demand;
	short supply;
	char pad4[0x18 - 4];
} Cell_99ef80;

/* g_99f5a0 */
typedef struct {
	int head;
	int rest[8];
} Rec24_99f5a0;

/* g_99f800 */
typedef struct {
	int owner;
	int key;
} Pair_99f800;

/* g_9a3800 */
#pragma pack(push, 1)
typedef struct {
	int id;
	char p4[0xe];
	int x12;
	int x16;
	char p1a[2];
	unsigned char x1c;
	char p1d[8];
	unsigned int x25;
	char p29[4];
} Rec2d_9a3800;
#pragma pack()

/* g_aed340 */
typedef struct {
	int f0;
	unsigned char type;
	char pad5[3];
	int who;
	char padc[0x2a];
	unsigned char flags;
	char pad37[0x21];
	int f58;
	char pad5c[0x9c];
} Msg_aed340;

/* g_f8f110 */
typedef struct {
	char pad0[0x27c];
	int panel;
	char pad280[0x3c4 - 0x280];
} Slot_f8f110;

/* g_f8f120 */
typedef struct {
	char pad0[0x398];
	int x398;
	int x39c;
	int x3a0;
	int x3a4;
	char pad3a8[0x3c4 - 0x3a8];
} Win_f8f120;

/* g_fb5760 */
#pragma pack(1)
typedef struct {
	char f0;
	char f1;
	int f2;
	int f6;
} cell10_fb5760;
#pragma pack()

#endif
