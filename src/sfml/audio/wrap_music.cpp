#include "wrap_music.h"

#include "../../bindingHelper/marco.hpp"
#include "../../bindingHelper/lua_template.hpp"
#include "../../bindingHelper/enum.hpp"


#include "../system/wrap_time.h"


void register_MusicEnums(lua_State * l)
{
    add_enum_to_lua(l,"sfMusicStatus",
		    "Playing"        , sf::Music::Status::Playing,
		    "Paused"         , sf::Music::Status::Paused,
		    "Stopped"        , sf::Music::Status::Stopped,
		    nullptr);

}


#define TYPE_TO_BIND sf::Music
#define NAME_TO_BIND sfMusic

IMPLEMENT_LUA_CLASS(sfMusic,sf::Music)

#define FUNCTION_TO_BIND \
X1(openFromFile     , METHOD   ,HAS_RETURN  , RET_TYPE(bool)      , openFromFile , std::string   , NO_POINTER )\
X0(getDuration      , METHOD   ,HAS_RETURN , RET_TYPE(sf::Time)   , getDuration )\
X0(play             , METHOD   ,NO_RETURN  , RET_NONE             , play )\
X0(pause            , METHOD   ,NO_RETURN  , RET_NONE             , pause)\
X0(stop             , METHOD   ,NO_RETURN  , RET_NONE             , stop )\
X0(getStatus        , METHOD   ,HAS_RETURN , RET_TYPE(int)        , getStatus )\
X0(getVolume        , METHOD   ,HAS_RETURN , RET_TYPE(float)      , getVolume   )\
X1(setVolume        , METHOD   , NO_RETURN , RET_NONE             , setVolume   , float , NO_POINTER )\
X0(getLoop          , METHOD   ,HAS_RETURN , RET_TYPE(bool)       , getLoop   )\
X1(setLoop          , METHOD   , NO_RETURN , RET_NONE             , setLoop     , bool  , NO_POINTER )\
X0(getPlayingOffset , METHOD   ,HAS_RETURN , RET_TYPE(sf::Time)   , getPlayingOffset   )\
X1(setPlayingOffset , METHOD   , NO_RETURN , RET_NONE             , setPlayingOffset   , sf::Time , IS_POINTER )\


#define __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

FUNCTION_TO_BIND

#undef __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

luaL_Reg sfMusic_regs[] =
{
    LUA_DEFAULT_CLASS_FUNC(sfMusic)
    FUNCTION_TO_BIND
    { NULL, NULL }
};

LUA_REGISTER_CLASS(sfMusic)
