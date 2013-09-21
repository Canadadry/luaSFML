#include <iostream>
#include <lua.hpp>
#include "sfml/sfml.h"
#include "external/graphics_wrap/wrap_tilemap.h"
#include "external/graphics_wrap/wrap_sgitem.h"
//#include "external/physfs/physfsstream.h"
#include <unistd.h>

#ifdef SFML_SYSTEM_WINDOWS
#deinfe EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

extern "C" EXPORT int luaopen_SFML(lua_State *l)
{
    registerSFMLModule(l);
    register_sfeTileMap(l);
    register_sfeSGItem(l);
    return 0;
}

int main(int argc,char** argv)
{
    // printf("Build time %s\n\n",__TIME__);

    if(argc < 2)
    {
	printf("you must provide a lua file to execute.\n");
	return 0;
    }
//    chdir(argv[1]);

//    PhysFsStream::init(argv[0]);
//    PhysFsStream::addSearchPath("./");

    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    luaopen_SFML(l);

    luaopen_math(l);
    luaopen_os(l);

    if(luaL_dofile(l, argv[1])) printf("Lua error: %s\n",luaL_checkstring(l, -1));
    lua_close(l);
    return 1;
}
