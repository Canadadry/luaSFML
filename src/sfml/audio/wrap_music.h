#include <lua.hpp>
#include <SFML/Audio/Music.hpp>

void register_MusicEnums(lua_State * l);

void register_sfMusic(lua_State * l);

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<sf::Music>();

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<sf::Music*>();
