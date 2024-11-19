#pragma once

#include "ft_irc.hpp"

class Client {
    private:
        int         socket;
        bool        logged_in;
        std::string user_name;
        std::string nick_name;
        std::string pass;
        std::string ip;
        int         receiver;
    public:
		Client();
		Client(int clientfd);
        int         getSocket();
        bool        getLoggedIn();
        std::string getUserName();
        std::string getNickName();
        std::string getPass();
        std::string getIp();
        int         getReceiver();

		void        sender(std::string str);
		void        setSocket(int sockfd);
        void        setLoggedIn(bool sign);
        void        setUserName(std::string user_name);
        void        setNickName(std::string nick_name);
        void        setPass(std::string pass);
		void		setIp(std::string ip);
        void        setReceiver(int receiver);


		~Client();    
};