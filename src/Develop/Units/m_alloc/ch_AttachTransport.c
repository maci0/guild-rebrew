// SIZE 0x218
struct node_403ce0 {
	char pad0[0x214];
	unsigned char pad214 : 7;
	unsigned char shown : 1;
	unsigned char pad215;
	unsigned char attached : 1;
	unsigned char detached : 1;
	unsigned char pad216 : 6;
	unsigned char moving : 1;
};

// SIZE 0x18
struct link_403ce0 {
	struct node_403ce0* node;
	char pad[0x10];
	int next;
};

extern float flt_0_0;
extern float g_6628b8;

struct link_403ce0* __cdecl m_alloc(int size, const char* tag);
void __cdecl d3_SetNodePosition(struct node_403ce0*, float*);
void __cdecl d3_SetObjectRotation(struct node_403ce0*, char*);


/* Attaches a transport node to an object at the object's anchor point. */
/* ADDRESS: GOLDTL 0x00403ce0 */
/* ADDRESS: GOLDDE 0x00403210 */
struct link_403ce0* __cdecl ch_AttachTransport(char* obj, struct node_403ce0* node)
{
	struct link_403ce0* link;
	char* n;
	float pos[4];

	link = m_alloc(0x18, "ch:ch_AttachTransport");
	n = *(char**) (obj + 0x34);
	pos[0] = (*(float*) (n + 0x19c) + *(float*) (n + 0x18c)) * flt_0_0 - *(float*) (n + 0x1ac) * 70.0f + *(float*) (n + 0x1bc);
	pos[1] = (*(float*) (n + 0x1a0) + *(float*) (n + 0x190)) * flt_0_0 - *(float*) (n + 0x1b0) * 70.0f + *(float*) (n + 0x1c0);
	pos[2] = (*(float*) (n + 0x1a4) + *(float*) (n + 0x194)) * flt_0_0 - *(float*) (n + 0x1b4) * 70.0f + *(float*) (n + 0x1c4);
	d3_SetNodePosition(node, pos);
	d3_SetObjectRotation(node, *(char**) (obj + 0x34) + 0x84);
	node->moving = 0;
	node->attached = 1;
	node->detached = 0;
	node->shown = 0;
	*(struct link_403ce0**) (obj + 0x124) = link;
	link->next = 0;
	link->node = node;
	return link;
}
