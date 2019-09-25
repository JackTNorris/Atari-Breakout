#include "Trump.h"
#include "Graphics.h"
void Trump::update()
{
	if (x <= 32) {
		x = 32;
	}
	if (x + width >= Graphics::ScreenWidth - 34) {
		x = Graphics::ScreenWidth - 34 - width;
	}
}
