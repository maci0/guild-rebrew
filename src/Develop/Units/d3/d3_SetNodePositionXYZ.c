int __cdecl d3_SetNodePosition(int, int*);

/* ADDRESS: GOLD 0x0043b7f0 */
/* ADDRESS: GOLDTL 0x00438ba0 */
/* ADDRESS: GOLDDE 0x00431d80 */
void __cdecl d3_SetNodePositionXYZ(int node, int x, int y, int z)
{
	int pos[4];
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	d3_SetNodePosition(node, pos);
}
