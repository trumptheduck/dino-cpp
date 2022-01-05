#ifndef __Utils_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __Utils_H_INCLUDED__ //   #define this so the compiler knows it has been included

class Utils
{
public:
	static std::string generateUUID(const int len)
	{
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		std::string tmp_s;
		tmp_s.reserve(len);

		for (int i = 0; i < len; ++i)
		{
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return tmp_s;
	};
};
#endif