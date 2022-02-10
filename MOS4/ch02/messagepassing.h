#pragma once
#include "producer_consumer.h"

using function = void (*)();

class Message
{

};

void build_message(Message &message, Item item);

void send(function sender, Message &message);

void receive(function listener, Message &message);

Item extract_message(Message &message);