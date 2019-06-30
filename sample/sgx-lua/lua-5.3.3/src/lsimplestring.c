#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int dostring(const char* c)
{
  lua_State *L;
  int        r;

  L = (lua_State *) luaL_newstate();
  printf("State created successfully\n");
  luaL_openlibs(L); /* open all built-in Lua libraries */
  luaL_dostring(L,c);
  printf("Executed string successfully\n");
  r = luaL_checkinteger(L, -1);
  printf("\nResult = %d\n",r);
  lua_close(L);
  return EXIT_SUCCESS;
}

