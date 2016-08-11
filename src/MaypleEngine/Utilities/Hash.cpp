/*!****************************************************************************
\file    Hash.cpp
\author  Melvin Tan (melvin.tan)
\date    

\brief   

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#include "stdinc.h"

#include "Hash.h"
#include <string>

namespace Hash
{
	Hash::~Hash( )
	{
	}

	Hash& Hash::operator = ( const char * name )
	{
		mText = name ? name : "";
		mHash = name ? Generate( mText ) : 0;
		return *this;
	}

	Hash & Hash::operator = ( const std::string & name )
	{
		mText = name;
		mHash = Generate( mText );
		return *this;
	}
}