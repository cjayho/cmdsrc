/*
|
|	cErrc.h
|
|	Error codes container
|	_____________________
|
|	(c) cjayho, 2015+
|
*/

#ifndef CERRC_H

	#define CERRC_H

	#include <string>
	#include <iostream>
	#include <map>

	class cErrc
	{
		public:
			void add( std::string code, std::string desc );
			void cerr( std::string reason );
			cErrc();
			~cErrc();

		private:
			std::map <std::string, std::string>* container;
	};

#endif // ifndef CERRC_H
