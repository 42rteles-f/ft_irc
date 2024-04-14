/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:18:54 by rteles-f          #+#    #+#             */
/*   Updated: 2024/04/14 13:12:52 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Channel.hpp>

Channel::Channel() : _topic(""), _op()
{
	_functions['o'] = &Channel::operatorMode;
	_functions['i'] = &Channel::inviteAndTopicMode;
	_functions['t'] = &Channel::inviteAndTopicMode;
	_functions['k'] = &Channel::keyAndLimitMode;
	_functions['l'] = &Channel::keyAndLimitMode;
}

Channel::Channel(const Channel& tocopy)
{
	*this = tocopy;
}

Channel::~Channel()
{}

Channel& Channel::operator()(const std::string name) {
	_name = name;
	return(*this);
}

const std::string& Channel::name(void) {
	return (_name);
}

Channel& Channel::operator=(const Channel& tocopy) {
	if (this == &tocopy)
		return (*this);
	this->_name = tocopy._name;
	for(int i = 0; i < 255; i++)
		this->_modes[i] = tocopy._modes[i];
	this->_topic = tocopy._topic;
	this->_functions = tocopy._functions;
	this->_clients = tocopy._clients;
	this->_op = tocopy._op;
	return (*this);
}

void	Channel::addClient(Client& client, std::string password) {

	if (!_modes[(int)'i'].empty() && std::find(client.getChannels().begin(), client.getChannels().end(), this) == client.getChannels().end())
		return client.sendMessage(Server::makeMessage(" 473 " + client.getNick() + " " + this->_name + " :Cannot join channel (+i)"));
	if (!_modes[(int)'k'].empty() && _modes[(int)'k'].compare(password) != 0)
		return client.sendMessage(Server::makeMessage(" 475 " + client.getNick() + " " + this->_name + " :Cannot join channel (+k)"));
	if (!_modes[(int)'l'].empty() && this->getClients().size() >= (size_t)std::atol(_modes[(int)'l'].c_str()))
		return client.sendMessage(Server::makeMessage(" 471 " + client.getNick() + " " + this->_name + " :Cannot join channel (+l)"));

	std::vector<Client*>::iterator find = std::find(_clients.begin(), _clients.end(), &client);

	if (find == _clients.end())
		_clients.push_back(&client);
	if (_op.size() == 0)
		_op.push_back(&client);
	this->broadcast(client.makeMessage());
	client.addChannel(this);
}

void	Channel::removeClient(Client& remove) {
	std::vector<Client*>::iterator find;

	find = std::find(_op.begin(), _op.end(), &remove);
	if (find != _op.end())
		_op.erase(find);

	find = std::find(_clients.begin(), _clients.end(), &remove);
	if (find != _clients.end())
		_clients.erase(find);

	if (_clients.size() && _op.size() == 0)
		_op.push_back(_clients[0]);
	remove.removeChannel(this);
}

void Channel::removeClient(std::string clientName) {
	std::vector<Client*>::iterator find = _clients.begin();

	while (find != _clients.end() && clientName.compare((*find)->getNick()))
		find++;
	if (find != _clients.end())
		this->removeClient(**find);
}

size_t Channel::NumberOfClients() {
	return _clients.size();
}

void	Channel::broadcast(Client& sender)
{
	std::string	message = sender.makeMessage();

	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (sender.socket->fd != _clients[i]->socket->fd)
			send(_clients[i]->socket->fd, message.c_str(), message.size(), 0);
	}
}

void	Channel::broadcast(std::string message)
{
	for (size_t i = 0; i < _clients.size(); i++)
		send(_clients[i]->socket->fd, message.c_str(), message.size(), 0);
}

Client& Channel::getClient(size_t index){
	return (*(_clients[index]));
}

std::vector<Client*>& Channel::getClients() {
	return (_clients);
}

Client* Channel::findClient(std::string clientName) {
	std::vector<Client*>::iterator find;

	find = _clients.begin();
	for (;find != _clients.end(); ++find) {
		if (clientName.compare((*find)->getNick()) == 0)
			return (*find);
	}
	return (NULL);
}

bool Channel::isClientInChannel(Client* guest) {
	std::vector<Client *>::iterator it = std::find(_clients.begin(), _clients.end(), guest);

	if (it != _clients.end())
		return true;
	return false;
}

void Channel::update(void) {
	for (size_t id = 0; id < _clients.size(); id++) {
		_clients[id]->sendMessage(Server::makeMessage(" 332 " + _clients[id]->getNick() + " " + _name + " " + _topic));
		std::vector<Client*>::iterator it = _clients.begin();
		std::string message;
		for (; it != _clients.end(); it++) {
			if (this->isOp(**it))
				message += "@" + (*it)->getNick() + " ";
			else
				message += (*it)->getNick() + " ";
		}
		_clients[id]->sendMessage(Server::makeMessage(" 353 " + _clients[id]->getNick() + " = " + _name + " :" + message));
		_clients[id]->sendMessage(Server::makeMessage(" 366 " + _clients[id]->getNick() + " " + _name + " :End of /WHO list."));
	}
}
