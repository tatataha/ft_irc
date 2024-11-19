#pragma once

#include "ft_irc.hpp"

class Server {
	private:
		int							sockfd;
		std::string					port;
		std::string					password;
		std::vector<struct pollfd>	pollfd;
		std::vector<Client *>		clients;
		std::vector<std::string>	commands;
	public:
		Server(std::string port, std::string password);
		~Server();

        void Start();
        void InitializeServer();
		void ClientsHandler();
		void MessageHandler(struct pollfd &client, Client &client_obj);
};