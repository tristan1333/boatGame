#ifndef EVENTS_FILE_AAA
#define EVENTS_FILE_AAA
class LuaContext;
class tilemap;
class eventHandler
{
public:
	void handle(LuaContext*, tilemap*);
	eventHandler();
};

#endif