/*
|
|	cCmd.h
|
|	Error codes container
|	_____________________
|
|	(c) cjayho, 2015+
|
*/

#ifndef CCMD_H

	#define CCMD_H

	#include <string>
	#include <iostream>
	#include <map>
	#include <unistd.h>
	#include <cstdbool>
	#include <cstdint>
	#include <list>

	#include "cErrc.h"

	typedef void ( *func )(  );

	class cCmd
	{
		public:
			void		add( std::string, func );
			void		list();
			void		request();
			void		set_prompt( std::string );
			std::string	get_prompt();
			void		set_enable_password( std::string );
			std::string	get_enable_password();
			void		set_not_enabled_mark( std::string );
			std::string	get_not_enabled_mark();
			void		set_enabled_mark( std::string );
			std::string	get_enabled_mark();
			void		set_configure_mark( std::string );
			std::string	get_configure_mark();
			void		enable();
			bool		is_enabled(); // returns true if in enabled mode
			void		disable();
			void		conf();
			bool		is_configuring(); // returns true if in cfg mode
			void		unconf();
						cCmd( cErrc* );
						~cCmd(  );

		private:
			std::map <std::string, func>* container;
			std::list <std::string>* container_full;
			std::string prompt;
			std::string enable_password;
			std::string not_enabled_mark;
			std::string enabled_mark;
			std::string configure_mark;
			bool enabled;
			bool conf_t;
			cErrc* errsys;
			std::string make_prompt();
	};

#endif // ifndef CCMD_H
