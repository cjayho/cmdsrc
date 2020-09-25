/*
|
|	cCmd.cpp
|
|	Commandsystem container
|	_____________________
|
|	(c) cjayho, 2015+
|
*/

#include "cCmd.h"

void cCmd::add( std::string name, func f )
{
	container_full->push_back( name );
	
	do
	{
		auto it = container->find( name );

		if( it == container->end() )
		{
			container->insert( std::pair<std::string, func>( name, f ) );
		}

		name = name.substr( 0, name.size() -1 );
	}
	while( name != "" );
}

void cCmd::list()
{
	for( auto it = container_full->begin(); it != container_full->end(); ++it )
	{
		std::cout << *it << std::endl;
	}
}

std::string cCmd::make_prompt()
{
	std::string out = prompt + 
					  ( conf_t == true ? configure_mark : "" ) + 
					  ( enabled == true ? enabled_mark : not_enabled_mark ) + 
					  " ";
	return out;
}

void cCmd::request()
{
	bool* cmd_exists = new bool( false );

	std::string* cmd = new std::string( "" );

	std::cout << make_prompt();
	std::getline( std::cin, *cmd );

	for( auto it = container->begin(); it != container->end(); ++it )
	{
		if( it->first == *cmd )
		{
			it->second();
			*cmd_exists = true;
			break;
		} 
	}

	if( *cmd_exists == false )
	{
		errsys->cerr( "E005" );	
	}

	delete cmd_exists;
}

void cCmd::set_prompt( std::string in )
{
	prompt = in;
}

std::string cCmd::get_prompt()
{
	return prompt;
}

void cCmd::set_enable_password( std::string in )
{
	enable_password = in;
}

std::string cCmd::get_enable_password()
{
	return enable_password;
}

bool cCmd::is_enabled()
{
	return enabled;
}

void cCmd::enable()
{
	if( enabled == true )
	{
		errsys->cerr( "E001" );		
		return;
	}

	std::string* pwd = new std::string( "" );

	for( uint8_t i = 0; i < 3; ++i )
	{
		std::cout << "Password, chance " << i + 1 << " of 3: ";
		std::getline( std::cin, *pwd );

		if( *pwd != enable_password )
		{
			sleep( 3 );

			if( i <= 2 )
			{
				errsys->cerr( "E002" );	
			}
			else
			{
				errsys->cerr( "E003" );
				break;
			}
		}
		else
		{
			enabled = true;
			break;
		}
	}

	delete pwd;
}

void cCmd::disable()
{
	if( enabled == false )
	{
		errsys->cerr( "E006" );
		return;
	}
	
	if( conf_t == true )
	{
		errsys->cerr( "E004" );
		return;
	}

	enabled = false;
}

void cCmd::conf()
{
	if( enabled )
	{
		if( !conf_t )
		{
			conf_t = true;
		}
		else
		{
			errsys->cerr( "E007" );
		}
	}
	else
	{
		errsys->cerr( "E006" );
	}
}

bool cCmd::is_configuring()
{
	return conf_t;
}

void cCmd::unconf()
{
	if( enabled )
	{
		if( conf_t )
		{
			conf_t = false;
		}
		else
		{
			errsys->cerr( "E008" );
		}
	}
	else
	{
		errsys->cerr( "E006" );
	}
}

std::string cCmd::get_not_enabled_mark()
{
	return not_enabled_mark;
}

void cCmd::set_not_enabled_mark( std::string in )
{
	not_enabled_mark = in;
}

std::string cCmd::get_enabled_mark()
{
	return enabled_mark;
}

void cCmd::set_enabled_mark( std::string in )
{
	enabled_mark = in;
}

std::string cCmd::get_configure_mark()
{
	return configure_mark;
}

void cCmd::set_configure_mark( std::string in )
{
	configure_mark = in;
}

cCmd::cCmd( cErrc* in ) :container( new( std::map <std::string, func> ) ),
						 container_full( new( std::list <std::string > ) ),
						 prompt( "Console" ),
						 enable_password( "123456" ),
						 not_enabled_mark( ">" ),
						 enabled_mark( "#" ),
						 configure_mark( "(configure)" ),
						 enabled( false ),
						 conf_t( false ),
						 errsys( in )
{
	errsys->add( "E001", "We're already enabled. Not doing anything" );
	errsys->add( "E002", "Enable password incorrect." );
	errsys->add( "E003", "Enable password incorrect. Exiting to disabled mode prompt." );
	errsys->add( "E004", "Issue 'end' command first" );
	errsys->add( "E005", "No such command. Type 'help' to see available commands." );
	errsys->add( "E006", "This operation works in enabled mode only. Sorry." );
	errsys->add( "E007", "Already in conf mode." );
	errsys->add( "E008", "We're not in conf mode." );
}

cCmd::~cCmd()
{
	delete container;
}
