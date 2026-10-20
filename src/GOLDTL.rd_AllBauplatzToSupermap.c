#include "client_scene_transform.h"

char* __cdecl fcn_004bdf40(char* name);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
void __cdecl rd_FillSupermapQuad(char** context, float* points, unsigned char byte_value, int record_value);

/* ADDRESS: GOLDTL 0x004bdda0 */
void __cdecl rd_AllBauplatzToSupermap(char** context, char* object)
{
	char msg[0x40];
	float corner[4];
	float points[8];
	float* box;
	float t;

	box = (float*) fcn_004bdf40(object);
	if (box == 0) {
		fcn_0064d41a(msg, "rd_AllBauplatzToSupermap(): Unbekannter Bauplatz '%s'", object);
		return;
	}
	t = box[0x10];
	corner[0] = t;
	t = box[0x11];
	corner[1] = t;
	t = box[0x12];
	corner[2] = t;
	fcn_004bdfb0(&points[0], &points[1], corner, object, context);
	t = box[0x14];
	corner[0] = t;
	t = box[0x11];
	corner[1] = t;
	t = box[0x12];
	corner[2] = t;
	fcn_004bdfb0(&points[2], &points[3], corner, object, context);
	t = box[0x14];
	corner[0] = t;
	t = box[0x11];
	corner[1] = t;
	t = box[0x16];
	corner[2] = t;
	fcn_004bdfb0(&points[4], &points[5], corner, object, context);
	t = box[0x10];
	corner[0] = t;
	t = box[0x11];
	corner[1] = t;
	t = box[0x16];
	corner[2] = t;
	fcn_004bdfb0(&points[6], &points[7], corner, object, context);
	rd_FillSupermapQuad(context, points, 0xff, 0);
}
