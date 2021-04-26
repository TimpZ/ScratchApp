#include "app.h"
#include "app_math.cpp"

internal void ProcessInput(keyboard_input *Input)
{
	if(Input->ExitApp.IsDown != false)
	{
		GlobalRunning = false;
	}
}

internal void DrawRectangle
(
	offscreen_buffer *Buffer, 
	float32 XOffset, float32 YOffset, 
	float32 XSize, float32 YSize, 
	float32 Red, float32 Green, float32 Blue
)
{
	if(XOffset < 0)
	{
		XSize += XOffset;
		XOffset = 0;
	}

	if(YOffset < 0)
	{
		YSize += YOffset;
		YOffset = 0;
	}

	if(XOffset + XSize >= WINDOW_WIDTH)
	{
		XSize = WINDOW_WIDTH - XOffset;
	}

	if(YOffset + YSize >= WINDOW_HEIGHT)
	{
		YSize = WINDOW_HEIGHT - YOffset;
	}

	int32 XOffsetInt = FloorFloat32ToInt32(XOffset);
	int32 YOffsetInt = FloorFloat32ToInt32(YOffset);
	int32 XSizeInt = FloorFloat32ToInt32(XSize);
	int32 YSizeInt = FloorFloat32ToInt32(YSize);

	uint32 *Row = (uint32 *)Buffer->Memory;

	Row += XOffsetInt;
	Row += (Buffer->Pitch / 4) * (WINDOW_HEIGHT - 1 - YOffsetInt);

	uint32 PixelColour = 
	(
		(0xFF << 24) |
		(RoundFloat32ToUInt32(255.0f * Red) << 16)|
		(RoundFloat32ToUInt32(255.0f * Green) << 8)|
		(RoundFloat32ToUInt32(255.0f * Blue) << 0)
	);

	for (int32 Y = 0; Y < YSizeInt; ++Y)
	{
		uint32 *Pixel = Row;
		for(int32 X = 0; X < XSizeInt; ++X)
		{
			*Pixel++ = PixelColour;
		}
		Row -= Buffer->Pitch/4;
	}
}

// NOTE: Drawing with alpha is much slower since we need to blend with the existing background
internal void DrawRectangle
(
	offscreen_buffer *Buffer, 
	float32 XOffset, float32 YOffset, 
	float32 XSize, float32 YSize, 
	float32 Red, float32 Green, float32 Blue, float32 Alpha
)
{
	if(XOffset < 0)
	{
		XSize += XOffset;
		XOffset = 0;
	}

	if(YOffset < 0)
	{
		YSize += YOffset;
		YOffset = 0;
	}

	if(XOffset + XSize >= WINDOW_WIDTH)
	{
		XSize = WINDOW_WIDTH - XOffset;
	}

	if(YOffset + YSize >= WINDOW_HEIGHT)
	{
		YSize = WINDOW_HEIGHT - YOffset;
	}

	int32 XOffsetInt = FloorFloat32ToInt32(XOffset);
	int32 YOffsetInt = FloorFloat32ToInt32(YOffset);
	int32 XSizeInt = FloorFloat32ToInt32(XSize);
	int32 YSizeInt = FloorFloat32ToInt32(YSize);

	uint32 *Row = (uint32 *)Buffer->Memory;

	Row += XOffsetInt;
	Row += (Buffer->Pitch / 4) * (WINDOW_HEIGHT - 1 - YOffsetInt);

	for (int32 Y = 0; Y < YSizeInt; ++Y)
	{
		uint32 *Pixel = Row;
		for(int32 X = 0; X < XSizeInt; ++X)
		{
			uint8 *Colour = (uint8 *)Pixel;
			float32 DestBlue = (float32)*Colour++;
			float32 DestGreen = (float32)*Colour++;
			float32 DestRed = (float32)*Colour;

			float32 Ratio = (float32)Alpha / 1.0f; 

			int32 ResultRed = RoundFloat32ToInt32(DestRed*(1-Ratio) + 255.0f * Red*Ratio);
			int32 ResultGreen = RoundFloat32ToInt32(DestGreen*(1-Ratio) + 255.0f * Green*Ratio);
			int32 ResultBlue = RoundFloat32ToInt32(DestBlue*(1-Ratio) + 255.0f * Blue*Ratio);

			*Pixel++ = 
			(
				(0xFF << 24) |
				(ResultRed << 16) |
				(ResultGreen << 8) |
				(ResultBlue << 0)
			);
		}
		Row -= Buffer->Pitch/4;
	}
}

internal void DrawCircle
(
	offscreen_buffer *Buffer, 
	float32 XOffset, float32 YOffset, float32 Radius, 
	float32 Red, float32 Green, float32 Blue
)
{
	int32 LowerBoundX = RoundFloat32ToInt32(XOffset - Radius);
	int32 UpperBoundX = RoundFloat32ToInt32(XOffset + Radius);
	int32 LowerBoundY = RoundFloat32ToInt32(YOffset - Radius);
	int32 UpperBoundY = RoundFloat32ToInt32(YOffset + Radius);

	if(LowerBoundX < 0)
	{
		LowerBoundX = 0;
	}

	if(LowerBoundY < 0)
	{
		LowerBoundY = 0;
	}

	if(UpperBoundX >= WINDOW_WIDTH)
	{
		UpperBoundX = WINDOW_WIDTH;
	}

	if(UpperBoundY >= WINDOW_HEIGHT)
	{
		UpperBoundY = WINDOW_HEIGHT;
	}

	uint32 *Row = (uint32 *)Buffer->Memory;
	Row += LowerBoundX;
	Row += (Buffer->Pitch / 4) * (WINDOW_HEIGHT - 1 - LowerBoundY);

	uint32 PixelColour = 
	(
		(0xFF << 24) |
		(RoundFloat32ToUInt32(255.0f * Red) << 16)|
		(RoundFloat32ToUInt32(255.0f * Green) << 8)|
		(RoundFloat32ToUInt32(255.0f * Blue) << 0)
	);

	for(int32 PixelY = LowerBoundY; PixelY < UpperBoundY; PixelY++)
	{
		uint32 *Pixel = Row;
		for(int32 PixelX = LowerBoundX; PixelX < UpperBoundX; PixelX++)
		{

			float32 RelativePixelX = PixelX - XOffset;
			float32 RelativePixelY = PixelY - YOffset;

			float32 Hypothenuse = RootFloat32((float32)(RelativePixelX * RelativePixelX + RelativePixelY * RelativePixelY));
			if(Hypothenuse <= Radius)
			{
				*Pixel = PixelColour;
			}
			Pixel++;
		}
		Row -= Buffer->Pitch/4;
	}
}

// NOTE: Drawing with alpha is much slower since we need to blend with the existing background
internal void DrawCircle
(
	offscreen_buffer *Buffer, 
	float32 XOffset, float32 YOffset, float32 Radius, 
	float32 Red, float32 Green, float32 Blue, float32 Alpha
)
{
	int32 LowerBoundX = RoundFloat32ToInt32(XOffset - Radius);
	int32 UpperBoundX = RoundFloat32ToInt32(XOffset + Radius);
	int32 LowerBoundY = RoundFloat32ToInt32(YOffset - Radius);
	int32 UpperBoundY = RoundFloat32ToInt32(YOffset + Radius);

	if(LowerBoundX < 0)
	{
		LowerBoundX = 0;
	}

	if(LowerBoundY < 0)
	{
		LowerBoundY = 0;
	}

	if(UpperBoundX >= WINDOW_WIDTH)
	{
		UpperBoundX = WINDOW_WIDTH;
	}

	if(UpperBoundY >= WINDOW_HEIGHT)
	{
		UpperBoundY = WINDOW_HEIGHT;
	}

	uint32 *Row = (uint32 *)Buffer->Memory;
	Row += LowerBoundX;
	Row += (Buffer->Pitch / 4) * (WINDOW_HEIGHT - 1 - LowerBoundY);

	for(int32 PixelY = LowerBoundY; PixelY < UpperBoundY; PixelY++)
	{
		uint32 *Pixel = Row;
		for(int32 PixelX = LowerBoundX; PixelX < UpperBoundX; PixelX++)
		{

			float32 RelativePixelX = PixelX - XOffset;
			float32 RelativePixelY = PixelY - YOffset;

			float32 Hypothenuse = RootFloat32((float32)(RelativePixelX * RelativePixelX + RelativePixelY * RelativePixelY));
			if(Hypothenuse <= Radius)
			{
				// Draw pixel
				uint8 *Colour = (uint8 *)Pixel;
				float32 DestBlue = (float32)*Colour++;
				float32 DestGreen = (float32)*Colour++;
				float32 DestRed = (float32)*Colour;

				float32 Ratio = (float32)Alpha / 1.0f; 

				int32 ResultRed = RoundFloat32ToInt32(DestRed*(1-Ratio) + 255.0f * Red*Ratio);
				int32 ResultGreen = RoundFloat32ToInt32(DestGreen*(1-Ratio) + 255.0f * Green*Ratio);
				int32 ResultBlue = RoundFloat32ToInt32(DestBlue*(1-Ratio) + 255.0f * Blue*Ratio);

				*Pixel = 
				(
					(0xFF << 24) |
					(ResultRed << 16) |
					(ResultGreen << 8) |
					(ResultBlue << 0)
				);
			}
			Pixel++;
		}
		Row -= Buffer->Pitch/4;
	}
}

internal void Initialise()
{

}

internal void Update(keyboard_input *Input)
{
	ProcessInput(Input);
}

internal void Render(offscreen_buffer *Buffer)
{
	// Blank
	DrawRectangle(Buffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0);
	
	float32 Offset = 100;

	DrawRectangle(Buffer, Offset, Offset, WINDOW_WIDTH - Offset * 2, WINDOW_HEIGHT - Offset * 2, 1, 0, 1, 0.5f);

	DrawCircle(Buffer, 0, 0, 200, 1, 0, 0, 1);
	DrawCircle(Buffer, WINDOW_WIDTH, 0, 200, 0, 1, 0, 1);
	DrawCircle(Buffer, 0, WINDOW_HEIGHT, 200, 0, 0, 1, 1);
	DrawCircle(Buffer, WINDOW_WIDTH, WINDOW_HEIGHT, 200, 1, 1, 1, 0.5f);



}
