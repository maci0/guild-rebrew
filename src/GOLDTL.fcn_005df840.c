// FUNCTION: GOLD 0x005d3310
// SIZE: 168
// FUNCTION: GOLDTL 0x005df840
// SIZE: 168

// SIZE 0xf8
typedef struct {
	int h0;
	unsigned char kind;
	char p5[3];
	int owner;
	int entity;
	char p10[0x26];
	unsigned char flag;
	char p37[0x21];
	unsigned char mode;
	unsigned char count;
	char p5a[2];
	float dx;
	float dy;
	int speed;
	char p68[0x90];
} Msg;

void __cdecl fcn_004c5530(Msg*);

int __cdecl fcn_005df840(char* a1)
{
	Msg msg;

	msg.kind = 0x82;
	msg.owner = *(int*) (a1 + 4);
	msg.entity = -1;
	msg.flag = 2;
	msg.mode = 0;
	msg.dx = 1.0f / 6.0f;
	msg.count = 4;
	msg.dy = 1.0f / 6.0f;
	msg.speed = 0x18;
	fcn_004c5530(&msg);
	msg.kind = 0x82;
	msg.owner = *(int*) (a1 + 4);
	msg.entity = -1;
	msg.flag = 2;
	msg.mode = 3;
	msg.dx = -1.0f / 6.0f;
	msg.count = 2;
	msg.dy = -1.0f / 6.0f;
	msg.speed = 0x18;
	fcn_004c5530(&msg);
	return 1;
}
