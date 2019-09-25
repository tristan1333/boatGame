#ifndef RESOLUTION_HED
#define RESOLUTION_HED

class resHandler
{
	public:
		int w, h;
		float resMod;
		int wldToScrx, wldToScry;
		resHandler(int, int, float, float, float);
};

#endif