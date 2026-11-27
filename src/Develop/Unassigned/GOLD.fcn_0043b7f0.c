
// fcn_0043b7f0 — { int x[4]; x[0]=p2; x[1]=p3; x[2]=p4; fcn_0043b790(p1, x); }.

int __cdecl d3_SetNodePosition(int, int*);

void __cdecl d3_SetNodePositionXYZ(int node, int x, int y, int z)
{
	int pos[4];
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	d3_SetNodePosition(node, pos);
}
