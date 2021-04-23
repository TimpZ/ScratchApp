#ifndef APP_H

#define internal static
#define global static
#define local_persist static

#if BUILD_SLOW
#define Assert(Expression) if(!(Expression)) {*(int*)0 = 0;}
#else
#define Assert(Expression)
#endif

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)
#define Petabytes(Value) (Terabytes(Value)*1024LL)

#include <stdint.h>

typedef int32_t bool32;

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int32_t int32;
typedef int64_t int64;

typedef float float32;
typedef double float64;

struct offscreen_buffer
{
	void *Memory;
	int32 Width;
	int32 Height;
	int32 Pitch;
	int32 BytesPerPixel;
};

struct app_button_state
{
	int32 HeldDownCount;
	bool32 IsDown;
};

struct keyboard_input
{
	union
	{
		app_button_state Buttons[2];
		struct
		{
			app_button_state ExitApp;
			app_button_state W;
		};
	};
	
};

#define APP_H
#endif