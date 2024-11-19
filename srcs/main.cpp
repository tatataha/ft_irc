#include "./includes/Server.hpp"

int main(int ac, char **av) {
	try {
		if (ac != 3) {
			throw std::invalid_argument("This server only two parameters accepted!");
		}
		Server server(av[1], av[2]);
		server.Start();
	}
	catch (const std::exception& e) {
		std::cerr << "Error Handler: " << e.what() << std::endl;
		return (1);
	}
}
