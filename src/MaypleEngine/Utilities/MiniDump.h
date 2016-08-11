/*!****************************************************************************
\file    MiniDump.h
\author  Dan Muller (d.muller)
\date    Jul 18, 2015

\brief   Holds the functionality for debugging the game after a crash.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "CustomTypes.h" // Diesel engine types

LONG WINAPI WriteDump(EXCEPTION_POINTERS* pException);
