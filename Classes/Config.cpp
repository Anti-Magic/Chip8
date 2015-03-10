#include "Config.h"

Config Config::_instance;
Config::Config()
{
	_rate = 1;
	_issound = true;
}

Config* Config::getInstance()
{
	return &_instance;
}

int Config::getRate()
{
	return _rate;
}

void Config::setRate(int rate)
{
	_rate = rate;
}

bool Config::getSound()
{
	return _issound;
}

void Config::setSound(bool sound)
{
	_issound = sound;
}