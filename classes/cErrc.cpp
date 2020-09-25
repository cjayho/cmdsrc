/*
|
|	cErrc.cpp
|
|	Error codes container
|	_____________________
|
|	(c) cjayho, 2015+
|
*/

#include "cErrc.h"

void cErrc::add( std::string code, std::string desc )
{
	container->insert( std::pair<std::string, std::string>( code, desc ) );
}

void cErrc::cerr( std::string reason )
{
	for( auto e_it = container->begin(); e_it != container->end(); ++e_it )
	{
		if( e_it->first == reason )
		{
			std::cout << e_it->first << ": " << e_it->second << std::endl;
			break;
		} 
	}
}

cErrc::cErrc() :container( new( std::map <std::string, std::string> ) )
{
	// leaved blank
}

cErrc::~cErrc()
{
	delete container;
}
