#include "../includes/ft_irc.hpp"

Server::Server(std::string port, std::string password) {
    this->port = port; this->password = password;
}

Server::~Server() {
    std::cout << std::endl;
    std::cout << RED << "      Server stopped!" << RESET << std::endl;
    std::cout << std::endl;
}

////////////////////////

void Server::Start() {
    InitializeServer(); 
    std::cout << std::endl;
    std::cout << GREEN << "      Server started" << RESET << std::endl;
    std::cout << "      Port: " << CYAN << this->port << RESET << std::endl;
    std::cout << "      Password: " << CYAN << this->password << RESET << std::endl;
    std::cout << std::endl;
    std::cout << YELLOW << "  Waiting for connections..." << RESET << std::endl;
    std::cout << std::endl;

	while (poll(&pollfd[0], pollfd.size(), -1)) {
		for (size_t i = 0; i < pollfd.size(); i++) {
			if (i == 0)
				ClientsHandler();
			else
				MessageHandler(pollfd[i], *clients[i - 1]);
		}
	}
}

void Server::InitializeServer() {
	int opt = 1;
	this->sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	fcntl(this->sockfd, F_SETFL, O_NONBLOCK);

	if (this->sockfd < 0)
		throw std::runtime_error("server socket creation failed");

	sockaddr_in6 server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_addr = in6addr_any;
	server_addr.sin6_port = htons(std::stoi(port));

	if (setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("socket option");

	if (bind(this->sockfd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0)
		throw std::runtime_error("bind server socket failed");

	if (listen(this->sockfd, 5) < 0)
		throw std::runtime_error("listening error");

	pollfd.resize(1);
	pollfd[0].fd = sockfd;
	pollfd[0].events = POLLIN;
}

void Server::ClientsHandler() {
	if (pollfd[0].revents & POLLIN) {
		sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		int client_fd = accept(this->sockfd, reinterpret_cast<sockaddr *>(&client_addr), &client_len);
		if (client_fd < 0)
			throw std::runtime_error("accept error");
		else {
			Client *client = new Client(client_fd);
			client->sender("Welcome to the server, please enter your password: |COMMAND:PASS|\r\n");
			clients.push_back(client);
			std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
			fcntl(client_fd, F_SETFL, O_NONBLOCK);
			pollfd.resize(pollfd.size() + 1);
			pollfd[pollfd.size() - 1].fd = client_fd;
			pollfd[pollfd.size() - 1].events = POLLIN;
		}
	}
}

void Server::MessageHandler(struct pollfd &client, Client &client_obj) {
	if (client.revents & POLLIN) {
		char buffer[1024];
		client_obj.setReceiver(recv(client.fd, buffer, 1024, 0));
		if (client_obj.getReceiver() <= 0)
			throw std::runtime_error("recv error");
		else {
			std::string message(buffer, client_obj.getReceiver());
			std::cout << "Message from client: " << message << std::endl;
			client_obj.sender("Message received: " + message);
		}
	}
}