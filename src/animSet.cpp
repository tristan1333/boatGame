#include "animSets.h"
#include "timers.h"
std::vector<animLoop*> anims;


void animLoop::handleChange()
{
	if (this->activeTex - 1 == this->textures.size())
	{
		this->activeTex = 0;
		return;
	}
	else
	{
		this->activeTex++;
		return;
	}
}

void animLoop::checkLoop()
{
	if (loop->check_pass(SDL_GetTicks()))
	{
		loop->set_time(SDL_GetTicks());
		this->handleChange();
	}
}