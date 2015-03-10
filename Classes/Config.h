#ifndef __CONFIG_H__
#define __CONFIG_H__

class Config
{
public:
	static Config* getInstance();
	int getRate();
	void setRate(int rate);
	bool getSound();
	void setSound(bool sound);
private:
	Config();

	static Config _instance;
	bool _issound;
	int _rate;
};

#endif