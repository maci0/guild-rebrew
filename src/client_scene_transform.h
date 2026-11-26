#ifndef CLIENT_SCENE_TRANSFORM_H
#define CLIENT_SCENE_TRANSFORM_H

/* Inferred declaration home; object pointers are byte-access views. */
void __cdecl d3_TransformToObjectSpace(char* object, float* position, float* result);
void __cdecl d3_GetObjectWorldPosition(float* result, char* object);
void __cdecl fcn_004bdfb0(float* x, float* y, float* position, char* object, char** context);

int __cdecl CompareVector3WithinTolerance(float* a, float* b, float range);

#endif
