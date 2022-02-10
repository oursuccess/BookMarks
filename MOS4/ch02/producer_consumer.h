#pragma once

//虚假的生产消费item的声明
using Item = int;

Item produce_item();

void insert_item(Item &item);

Item remove_item();

void consume_item(Item &item);