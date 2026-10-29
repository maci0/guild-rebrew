extern int g_6b8010;
extern float g_665ea0;

void __cdecl fcn_004432d0(int, int);
int __cdecl gm_ResolveEntityById(int*, int, int, int);
void __cdecl fcn_00455350(void*, void*, float*);
void __cdecl fcn_00455140(void*, void*, float*);
float __cdecl fcn_004514d0(float*, float*);
void __cdecl fcn_00412cf0(void*, float*, float*, int, int);

/* Places the camera at the referenced entity's aim point once both the
 * camera chain and the resolved entity expose a view target. The aim vector
 * is rotated by the view direction and sent as a placement message. */
/* ADDRESS: GOLDTL 0x00558b70 */
unsigned int __cdecl fcn_00558b70(char* a0)
{
	float from[3];
	float to[3];
	float aim[3];
	float delta[3];
	float angle;
	int saved;
	char* ent;
	char* view;

	saved = g_6b8010;
	fcn_004432d0(0, 1);
	ent = a0;
	view = *(char**) (a0 + 0xc8);
	if (view == 0) {
		goto fail;
	}
	view = *(char**) (view + 0x1cc);
	if (view == 0) {
		goto fail;
	}
	if (*(int*) (view + 0x318) == 0) {
		goto fail;
	}
	if (gm_ResolveEntityById((int*) &ent, 0, 0, *(int*) (a0 + 0xb4)) == 0) {
		goto fail;
	}
	if (ent == 0) {
		goto fail;
	}
	view = *(char**) (ent + 0x61);
	if (view == 0) {
		goto fail;
	}
	view = *(char**) (view + 0x1cc);
	if (view == 0) {
		goto fail;
	}
	if (*(int*) (view + 0x318) == 0) {
		goto fail;
	}
	fcn_00455350(ent, ent + 0x4c, from);
	to[0] = from[0];
	to[1] = from[1] + *(float*) (*(char**) (*(char**) (*(char**) (ent + 0x61) + 0x1cc) + 0x318) + 0x1d4) + g_665ea0;
	to[2] = from[2];
	fcn_00455350(*(char**) (a0 + 0xc8), *(char**) (a0 + 0xc8) + 0x4c, to);
	delta[0] = from[0] - to[0];
	delta[1] = from[1] - to[1];
	delta[2] = from[2] - to[2];
	fcn_00455140(*(char**) (a0 + 0xc8), (char*) 0x662d40, aim);
	angle = fcn_004514d0(aim, delta);
	view = *(char**) (a0 + 0xc8);
	if (view == 0) {
		goto fail;
	}
	aim[0] = *(float*) (view + 0x84);
	aim[1] = *(float*) (view + 0x88);
	aim[2] = *(float*) (view + 0x8c);
	aim[1] = aim[1] + angle;
	fcn_00412cf0(view, to, aim, 0x78, 8);
	fcn_004432d0(saved, 1);
	return 1;
fail:
	fcn_004432d0(saved, 1);
	return 0;
}
