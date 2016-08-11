/*!****************************************************************************
\file    Hash.inl
\author  Melvin Tan (melvin.tan)
\date    

\brief   

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
// Hashed string object.
namespace Hash
{
	inline Hash::Hash( )
		: mText( "" )
		, mHash( 0 )
	{
	}

	inline Hash::Hash( const char * name )
		: mText( name ? name : "" )
		, mHash( name ? Generate( name ) : 0 )
	{
	}

	inline Hash::Hash( const std::string& name )
		: mText( name )
		, mHash( Generate( name ) )
	{
	}

	inline bool Hash::operator != ( const Hash & rhs ) const
	{
		return mHash != rhs.GetHash( );
	}

	inline bool Hash::operator == ( const Hash & rhs ) const
	{
		return mHash == rhs.GetHash( );
	}

	inline bool Hash::operator == ( const HashValue & rhs ) const
	{
		return mHash == rhs;
	}

	inline bool Hash::operator < ( const Hash & rhs ) const
	{
		return mHash < rhs.GetHash( );
	}

	inline bool Hash::operator >( const Hash & rhs ) const
	{
		return mHash > rhs.GetHash( );
	}

	inline HashValue Hash::Generate( const char * string )
	{
		return Generate( std::string( string ) );
	}

	inline HashValue Hash::Generate( const std::string& string )
	{
		if ( string == "" )
			return 0;

		return HashFunctor( )( string );
	}
}