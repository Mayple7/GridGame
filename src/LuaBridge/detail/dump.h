/*!****************************************************************************
\file    dump.h
\author  ???
\date    

\brief   

\par     Checked By:

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#include <sstream>
#include <string>

std::string dumpLuaState(lua_State *L) {
	std::stringstream ostr;
	int i;
	int top = lua_gettop(L);
	ostr << "top=" << top << ":\n";
	for (i = 1; i <= top; ++i) {
		int t = lua_type(L, i);
		switch(t) {
		case LUA_TSTRING:
			ostr << "  " << i << ": '" << lua_tostring(L, i) << "'\n";
			break;
		case LUA_TBOOLEAN:
			ostr << "  " << i << ": " << 
					(lua_toboolean(L, i) ? "true" : "false") << "\n";
			break;
		case LUA_TNUMBER:
			ostr << "  " << i << ": " << lua_tonumber(L, i) << "\n";
			break;
		default:
			ostr << "  " << i << ": TYPE=" << lua_typename(L, t) << "\n";
			break;
		}
	}
	return ostr.str();
}
