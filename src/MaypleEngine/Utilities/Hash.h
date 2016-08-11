/*!****************************************************************************
\file    Hash.h
\author  Melvin Tan (melvin.tan)
\date    

\brief   

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#ifndef STRHASH_H_
#define STRHASH_H_

#include <functional>

namespace Hash
{
	// Use std::hash for now
	typedef std::hash<std::string>				HashFunctor;
	typedef HashFunctor::result_type			HashValue;

	/*
		The object hashes a string into an integer value and stores both the string
		and the hash value. Hash objects are compared using their hash values for
		fast hash comparisons.
		*/
	class Hash
	{

	public:
		static HashValue Generate( const char * string );
		static HashValue Generate( const std::string & string );

	public:
		// Default constructor.
		Hash( );

		// Destructor.
		~Hash( );

		// Constructor.
		Hash( const char  * name );

		// Constructor.
		Hash( const std::string & name );

		// Assignment operator for strings.
		Hash & operator = ( const char * name );

		// Assignment operator for strings.
		Hash & operator = ( const std::string & name );

		// Equality operator.
		bool operator == ( const Hash & rhs ) const;

		// Equality operator.
		bool operator == ( const HashValue & rhs ) const;

		// Inequality operator.
		bool operator != ( const Hash & rhs ) const;

		// Less than operator.
		bool operator < ( const Hash & rhs ) const;

		// More than operator.
		bool operator > ( const Hash & rhs ) const;

		// Getter
		HashValue GetHash( ) const
		{
			return mHash;
		}

	private:
		std::string				mText;			//!< Hash name.
		HashValue			mHash;			//!< Hash value.
	};
}

#include "Hash.inl"

#endif // BH_HASH_H
