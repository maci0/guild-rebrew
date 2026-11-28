#ifndef RENDER_QUAD_H
#define RENDER_QUAD_H

typedef struct {
	float x, y, z, rhw;
	unsigned int color;
	float u, v;
} RENDER_VERTEX;

typedef struct {
	RENDER_VERTEX v[6];
	int tex;
} RENDER_QUAD;
/* SIZE 0xac */

extern RENDER_QUAD d2_QueuedQuads[0x400];

#endif
