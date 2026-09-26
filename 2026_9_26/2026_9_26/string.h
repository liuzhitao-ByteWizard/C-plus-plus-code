#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <cstring>
using namespace std;
//模拟实现时如果使用string ， 而且在程序中全部展开命名空间，会照成命名冲突
//我们可以自己定义一个命名空间域
namespace byte {
	//string本质上就是一个字符顺序表
	class string {
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		string();
		~string();
		string(const char* str);
		iterator begin() { return _str; }
		iterator end() { return _str + _size; }

		const_iterator begin() const { return _str; }
		const_iterator end() const { return _str + _size; }

		//较短小的函数在类中直接定义默认是内联函数
		const char* c_str() const { return _str; }
		size_t size() const { return _size; }
		size_t capacity() const { return _capacity; }
		char& operator[](size_t pos) {
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const {
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n = 0);
		void push_back(char ch);
		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* s);

		string& append(const char* s);
		string& operator+=(const char* s);
		string& operator+=(char ch);
		string& erase(size_t pos = 0, size_t len = npos);
		size_t find(char ch, size_t pos = 0) const;
		size_t find(const char* s, size_t pos = 0) const;
		string substr(size_t pos = 0, size_t len = npos) const;

		string(const string& s);
		string& operator=(const string& s);

		static const size_t npos = -1;

		void swap(string& s);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};

	string operator+ (const string& lhs, const string& rhs);
	string operator+ (const string& lhs, const char* rhs);
	string operator+ (const char* lhs, const string& rhs);
	ostream& operator<<(ostream& out, const string& s);
	istream& operator>> (istream& is, string& str);
	istream& getline(istream& is, string& str);

	bool operator== (const string& lhs, const string& rhs);
	bool operator!= (const string& lhs, const string& rhs);
	bool operator>(const string& lhs, const string& rhs);
	bool operator<(const string& lhs, const string& rhs);
	bool operator>= (const string& lhs, const string& rhs);
	bool operator<= (const string& lhs, const string& rhs);
}

void swap(byte::string& s1, byte::string& s2);