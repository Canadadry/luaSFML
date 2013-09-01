#include <lua.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


void register_sfSoundBuffer(lua_State * l);

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<sf::SoundBuffer>();

#include "../../bindingHelper/lua_template.hpp"
template <>
const char* metaTableName<sf::SoundBuffer*>();
