#include <lua.hpp>
#include <SFML/Audio/Sound.hpp>

void register_SoundEnums(lua_State * l);

void register_sfSound(lua_State * l);

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<sf::Sound>();

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<sf::Sound*>();
