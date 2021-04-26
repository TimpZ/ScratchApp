#include <math.h>
#include "app.h"

inline int32 FloorFloat32ToInt32(float32 Float32)
{
	int32 Result = (int32)floorf(Float32);
	return Result;
}

inline int32 RoundFloat32ToInt32(float32 Float32)
{
	int32 Result = (int32)roundf(Float32);
	return Result;
}

inline uint32 RoundFloat32ToUInt32(float32 Float32)
{
	int32 Int32 = RoundFloat32ToInt32(Float32);
	Assert(Int32 >= 0);
	uint32 Result = (uint32)Int32;
	return Result;
}

inline float32 RootFloat32(float32 Float32)
{
	float32 Result = sqrtf(Float32);
	return Result;
}
