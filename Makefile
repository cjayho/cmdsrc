all:
	@echo "MKDIR .tmp"
	@mkdir -p .tmp
	@echo "CXX cErrc.o"
	@c++ -c -std=c++11 -I./classes/include ./classes/cErrc.cpp -Wall -Wextra -Werror -pedantic-errors -std=c++17 -o .tmp/cErrc.o
	@echo "CXX cCmd.o"
	@c++ -c -std=c++11 -I./classes/include ./classes/cCmd.cpp -Wall -Wextra -Werror -pedantic-errors -std=c++17 -o .tmp/cCmd.o
	@echo "CXX main.o"
	@c++ -c -std=c++11 -I./classes/include ./main.cpp -Wall -Wextra -Werror -pedantic-errors -std=c++17 -o .tmp/main.o
	@echo "LDD cmd"
	@c++ -o cmd ./.tmp/main.o ./.tmp/cErrc.o ./.tmp/cCmd.o

clean:
	@echo "CLEAN"
	@rm -rf ./cmd ./.tmp
