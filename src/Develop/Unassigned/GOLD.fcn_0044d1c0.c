int __cdecl d3_RecalculateObjectBounds(int);
int __cdecl d3_CalculateMeshNormals(int);

void __cdecl d3_RecalculateAndSmoothMesh(int a, char b)
{
	d3_RecalculateObjectBounds(a);
	if (b != 0) {
		d3_CalculateMeshNormals(a);
	}
}
