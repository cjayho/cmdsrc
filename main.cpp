/*
|
|	cmd.cpp
|
|	Cisco-like console
|	_____________________
|
|	(c) cjayho, 2015+
|
*/

#include <iostream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <cstdbool>
#include <fstream>

#include "cErrc.h"
#include "cCmd.h"

cErrc* errsys = new cErrc;
cCmd*  cmdsys = new cCmd( errsys );

bool need_exit = false;

func con_enable = []()
{
	cmdsys->enable();
};

func con_disable = []()
{
	cmdsys->disable();
};

func con_exit = []()
{
	if( cmdsys->is_enabled() )
	{
		cmdsys->disable();
	}
	else
	{
		std::cout << "Exiting..." << std::endl;
		need_exit = true;
	}
};

func con_cfg = []()
{
	cmdsys->conf();
};

func con_ucfg = []()
{
	cmdsys->unconf();
};

func con_help = []()
{
	cmdsys->list();
};

void init_cmds()
{
	cmdsys->add( "enable",    con_enable  );
	cmdsys->add( "disable",   con_disable );
	cmdsys->add( "configure", con_cfg     );
	cmdsys->add( "end",       con_ucfg    );
	cmdsys->add( "help",      con_help    );
	cmdsys->add( "?",         con_help    );
	cmdsys->add( "exit",      con_exit    );
}

int main()
{
	init_cmds();

	cmdsys->set_enable_password( "strong_pass" );
	cmdsys->set_prompt( "Console_example" );
	
	std::string motd_line;
	
	std::ifstream motd( "motd.txt" );
	
	if ( motd.is_open() )
	{
		while ( getline( motd, motd_line ) )
		{
			std::cout << motd_line << std::endl;
		}
		motd.close();
	}
	else std::cerr << "Unable to open file motd.txt"; 
	
	std::cout << "Type 'help' or '?' to see list of commands available." << std::endl << std::endl;
	
	while( true )
	{
		cmdsys->request();

		if( need_exit == true )
		{
			break;
		}
	}

	delete errsys;
	delete cmdsys;
}
