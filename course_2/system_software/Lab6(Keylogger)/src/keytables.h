#pragma once

#include <linux/input.h>
#include <string>
using namespace std;

bool is_char_key(unsigned int keycode);
bool is_func_key(unsigned int keycode);

char charCode_to_char(unsigned int keycode);
string funcCode_to_string(unsigned int keycode);
