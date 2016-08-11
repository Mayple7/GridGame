/*!****************************************************************************
\file    ProfileSample.h
\author  Colin Averech
\date    

\brief   

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#pragma once
#include "CustomTypes.h"


class ProfileSample
{
public:
	ProfileSample( const char* executionName = "", const f32& executionTime = 0.0f)
		           : m_executionName(executionName), m_executionTime(executionTime) 
	{}

	~ProfileSample(){}

	const char* GetName(void) const	{	return m_executionName;	}

	f32 GetTime(void) const	{	return m_executionTime;	}

//private:
  const char* m_executionName;
	f32 m_executionTime;
};


//bool SampleCMP(const ProfileSample& lhs, const ProfileSample& rhs) { return lhs.GetTime() > rhs.GetTime(); }
