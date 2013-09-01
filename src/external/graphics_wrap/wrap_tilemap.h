#include "../graphics/tilemap.h"
#include <lua.hpp>



void register_sfeTileMap(lua_State * l);

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<TileMap>();

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<TileMap*>();
