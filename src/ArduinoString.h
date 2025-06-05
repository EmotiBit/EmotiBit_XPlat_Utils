#pragma once
#include <string>
using namespace std;
namespace EmotiBit
{
	class String
	{
	public:

		std::string str;

		String()
		{
			str = "";
		}

		String(std::string s)
		{
			str = s;
		}

		String& operator=(const String& s) {
			str = s.str;
			return *this;
		}

		String& operator=(const string& s) {
			str = s;
			return *this;
		}
		
		String& operator+=(const String& s)
		{
			str += s.str;
			return *this;
		}

		String& operator+=(const string& s)
		{
			str += s;
			return *this;
		}

		String operator+(const String& s) const
		{
			return String(str + s.str);
		}

		String operator+(const string& s) const
		{
			return String(str + s);
		}
		
		String& operator+=(char c)
		{
			str += c;
			return *this;
		}

		String operator+(char c) const
		{
			return String(str + c);
		}
		
		String& operator+=(int val)
		{
    		str += std::to_string(val);
    		return *this;
		}

		size_t indexOf(char val, size_t from) const
		{
			return str.find_first_of(val, from);
		}

		String substring(size_t from, size_t to) const
		{
			return String(str.substr(from, to - from));
		}

		bool equals(String s) const
		{
			return str.compare(s.str) == 0;
		}

		size_t length() const
		{
			return str.length();
		}

		int toInt() const
		{
			return stoi(str);
		}

	private:
	};
}