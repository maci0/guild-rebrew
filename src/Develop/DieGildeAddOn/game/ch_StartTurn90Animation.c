/* Starts the 90 degree turn animation toward a heading, as the sibling handler
 * ch_ExecuteTurn90 does for queued tasks. Inferred from the native body at 0x004092d0
 * (485 bytes); the option block and the 2 x 0x58 frame pair are the same aggregates
 * StartObjectTransformAnimation hands to d3_CreateObjectAnimation. */

typedef struct {
	unsigned char unbekannt_000;
	unsigned char bit_1_0 : 1;
	unsigned char bit_1_1 : 1;
	unsigned char bit_1_2 : 1;
	unsigned char bit_1_3 : 1;
	unsigned char bit_1_4 : 1;
	unsigned char unbekannt_1_rest : 3;
	unsigned char unbekannt_002[6];
	unsigned char bit_8_0 : 1;
	unsigned char bit_8_1 : 1;
	unsigned char unbekannt_8_rest : 6;
	unsigned char unbekannt_009[3];
} D3_OBJ_ANIM_FLAGS;

typedef struct {
	int unbekannt_000;
	float position[3];
	char unbekannt_010[4];
	float drehung[3];
	char unbekannt_020[0x58 - 0x20];
} D3_OBJ_ANIM_FRAME;

typedef struct {
	float v[4];
} VEC4_4092d0;

extern double g_6628f0;

char* __cdecl ch_AttachAni(char*, char*, unsigned char);
int __cdecl d3_CreateObjectAnimation(char*, D3_OBJ_ANIM_FLAGS, int, D3_OBJ_ANIM_FRAME*);

/* ADDRESS: GOLDTL 0x004092d0 */
int __cdecl ch_StartTurn90Animation(char* owner, float angle)
{
	D3_OBJ_ANIM_FRAME frames[2];
	int type;
	VEC4_4092d0 dir;
	D3_OBJ_ANIM_FLAGS flags;
	char* stream;
	char* frame;

	if (!(angle >= g_6628f0)) {
		if (angle < *(double*) 0x6628e8) {
			*(char**) (owner + 0x70) = ch_AttachAni(owner, "bewegung/dreh_90_rechts", 1);
		}
	} else {
		*(char**) (owner + 0x70) = ch_AttachAni(owner, "bewegung/dreh_90_links", 1);
	}
	if (*(char**) (owner + 0x70) != 0) {
		stream = *(char**) (*(char**) (owner + 0x70) + 0x68);
		frame = *(char**) (stream + 0x15c) + *(int*) (stream + 0x148) * 0xc0;
		dir.v[2] = *(float*) (frame - 0x8c);
		dir.v[1] = *(float*) (frame - 0x90);
		dir.v[0] = *(float*) (frame - 0x94);
		*(int*) &flags = 0;
		type = *(int*) (frame - 0xc0) - 0x1e;
		frames[0].unbekannt_000 = type;
		*(int*) ((char*) &flags + 8) = 0;
		flags.bit_1_2 = 1;
		flags.bit_1_4 = 1;
		frames[1].drehung[0] = -dir.v[0];
		frames[1].drehung[1] = angle - dir.v[1];
		flags.bit_1_3 = 1;
		frames[1].drehung[2] = -dir.v[2];
		flags.bit_8_1 = 1;
		frames[0].position[0] = 0.0f;
		frames[0].position[1] = 0.0f;
		frames[0].position[2] = 0.0f;
		frames[0].drehung[0] = 0.0f;
		frames[0].drehung[1] = 0.0f;
		frames[0].drehung[2] = 0.0f;
		frames[1].position[0] = 0.0f;
		frames[1].position[1] = 0.0f;
		frames[1].position[2] = 0.0f;
		*(int*) (owner + 0x78) = d3_CreateObjectAnimation(*(char**) (owner + 0x34), flags, 2, frames);
		return 1;
	}
	frames[0].unbekannt_000 = 8;
	*(int*) &flags = 0;
	*(int*) ((char*) &flags + 8) = 0;
	flags.bit_1_2 = 1;
	flags.bit_1_4 = 1;
	flags.bit_1_3 = 1;
	frames[1].drehung[1] = angle;
	flags.bit_8_1 = 1;
	frames[0].drehung[0] = 0.0f;
	frames[0].drehung[1] = 0.0f;
	frames[0].drehung[2] = 0.0f;
	frames[0].position[0] = 0.0f;
	frames[0].position[1] = 0.0f;
	frames[0].position[2] = 0.0f;
	frames[1].drehung[0] = 0.0f;
	frames[1].drehung[2] = 0.0f;
	frames[1].position[0] = 0.0f;
	frames[1].position[1] = 0.0f;
	frames[1].position[2] = 0.0f;
	*(int*) (owner + 0x78) = d3_CreateObjectAnimation(*(char**) (owner + 0x34), flags, 2, frames);
	return 1;
}
