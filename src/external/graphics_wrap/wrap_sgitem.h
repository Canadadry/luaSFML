#include "../graphics/SGItem.h"
#include <lua.hpp>

void register_sfeSGItem(lua_State * l);

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<SGItem>();

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<SGItem*>();
