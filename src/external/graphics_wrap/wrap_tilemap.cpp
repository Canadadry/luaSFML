#include "wrap_tilemap.h"

#include <lua.hpp>

#include "../../bindingHelper/marco.hpp"
#include "../../bindingHelper/lua_template.hpp"
#include "../../sfml/graphics/wrap_render_window.h"

#include "../../sfml/graphics/wrap_texture.h"
#include "../../sfml/system/wrap_vector2u.h"
#include "../../sfml/system/wrap_vector2f.h"

#define TYPE_TO_BIND TileMap
#define NAME_TO_BIND sfeTileMap

IMPLEMENT_LUA_CLASS(sfeTileMap,TileMap)

#define FUNCTION_TO_BIND \
    X1(setTexture      , METHOD   , NO_RETURN , RET_NONE                , setTexture     , sf::Texture  , IS_POINTER )\
    X1(setTileSize     , METHOD   , NO_RETURN , RET_NONE                , setTileSize    , sf::Vector2u , IS_POINTER )\
    X2(setIDForTile    , METHOD   , NO_RETURN , RET_NONE                , setIDForTile   , unsigned int , NO_POINTER , sf::Vector2u , IS_POINTER)\
    X2(setSize         , METHOD   , NO_RETURN , RET_NONE                , setData        , unsigned int , NO_POINTER , unsigned int , NO_POINTER )\
    X1(getIDForTile    , METHOD   ,HAS_RETURN , RET_TYPE(unsigned int)  , getIDForTile   , sf::Vector2u , IS_POINTER )\
    \
    \
    X0(getPosition , METHOD   ,HAS_RETURN , RET_TYPE(sf::Vector2f)  , getPosition   )\
    X0(getRotation , METHOD   ,HAS_RETURN , RET_TYPE(       float)  , getRotation   )\
    X0(getScale    , METHOD   ,HAS_RETURN , RET_TYPE(sf::Vector2f)  , getScale      )\
    X0(getOrigin   , METHOD   ,HAS_RETURN , RET_TYPE(sf::Vector2f)  , getOrigin     )\
    X1(setPosition , METHOD   , NO_RETURN , RET_NONE                , setPosition   , sf::Vector2f , IS_POINTER )\
    X1(setRotation , METHOD   , NO_RETURN , RET_NONE                , setRotation   , float        , NO_POINTER )\
    X1(setScale    , METHOD   , NO_RETURN , RET_NONE                , setScale      , sf::Vector2f , IS_POINTER )\
    X1(setOrigin   , METHOD   , NO_RETURN , RET_NONE                , setOrigin     , sf::Vector2f , IS_POINTER )\
    X1(move        , METHOD   , NO_RETURN , RET_NONE                , move          , sf::Vector2f , IS_POINTER )\
    X1(scale       , METHOD   , NO_RETURN , RET_NONE                , scale         , sf::Vector2f , IS_POINTER )\
    X1(rotate      , METHOD   , NO_RETURN , RET_NONE                , rotate        , float        , IS_POINTER )\


#define __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

FUNCTION_TO_BIND

#undef __GO_FOR_IMPLEMENTATION__
#include "../../bindingHelper/macro2.hpp"

luaL_Reg sfeTileMap_regs[] =
{
    LUA_DEFAULT_CLASS_FUNC(sfeTileMap)
    FUNCTION_TO_BIND
    { NULL, NULL }
};


LUA_BEGIN_REGISTER_CLASS(sfeTileMap)
register_drawableType(metaTableName<TileMap>());
LUA_END_REGISTER_CLASS

