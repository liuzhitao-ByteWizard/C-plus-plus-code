#include "string.h"

namespace byte {
	string::string()
		:_str(new char[15] {'\0'})
		, _size(0)
		, _capacity(15) {

	}

	string::string(const char* str)
		:_str(new char[strlen(str) + 1] {'\0'})
		, _size(strlen(str))
		, _capacity(strlen(str))
	{
		strcpy(_str, str);
	}

	string::~string() {
		delete[] _str;
		_str = nullptr; //特殊类型的字面量
		_size = _capacity = 0;
	}

	void string::reserve(size_t n) {
		// 仅当目标容量超过当前容量时才扩容，不缩容
		if (n > _capacity) {
			// 多申请一个字符的位置，用于存放末尾的 '\0'
			char* tmp = new char[n + 1];

			// 将原字符串（包括末尾的 '\0'）复制到新空间
			strcpy(tmp, _str);

			// 释放原来的字符数组
			delete[] _str;

			// 让 _str 指向新空间tmp
			_str = tmp;

			// 容量不计入末尾 '\0' 占用的位置
			_capacity = n;
		}
	}

	void string::push_back(char ch) {
		//要判断push_back中的capacity为0的情况
		if (_size == _capacity) {
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';
	}

	string& string::append(const char* s) {
		//当当前字符串的大小小于当前有效字符的个数加上要追加的字符串中字符的个数，才扩容
		size_t len = strlen(s);
		if (_capacity < _size + len) {
			reserve(_size + len);
		}
		//将字符串追加到原字符串的末尾
		strcpy(_str + _size, s);
		_size += len;
		return *this;
	}

	string& string::operator+=(char ch) {
		push_back(ch);
		return *this;
	}

	string& string::operator+=(const char* s) {
		append(s);
		return *this;
	}

	void string::insert(size_t pos, char ch) {
		assert(pos <= _size);
		//扩容
		if (_capacity == _size) {
			reserve(_capacity * 2);
		}
		//将pos及其之后的值向后移动一个单位
		//1. 强制类型转化
		// 	int end = _size; //支持尾插
		//while (end >= (int)pos) {
		//	_str[end + 1] = _str[end];
		//	end--;
		//}
		// 2.将end放在\0的下一个位置
		size_t end = _size + 1;
		while (end > pos) {
			_str[end] = _str[end - 1];
			--end;
		}
		//将当前插入的值放入pos位置
		_str[pos] = ch;
		_size++;
	}

	void string::insert(size_t pos, const char* s) {
		assert(pos <= _size);
		//确保足够的空间
		size_t len = strlen(s);
		if (_capacity < len + _size) {
			reserve(len + _size);
		}
		//将pos以及pos之后的位置全部向后进行一移动
		size_t end = _size + len;
		//while (end - len >= (int)pos) {
		//	_str[end] = _str[end - len];
		//	--end;
		//}
		while (end > pos + len - 1) {
			_str[end] = _str[end - len];
			--end;
		}

		//将要插入的子串中的字符依次赋值到主串中
		for (int i = 0; i < len; i++) {
			_str[pos + i] = s[i];
		}
		_size += len;
	}
	string& string::erase(size_t pos, size_t len) {
		if (len == npos) {
			_str[pos] = '\0';
			_size = pos;
		}
		else if (len > _size - pos) {
			_str[pos] = '\0';
			_size = pos;
		}
		else {
			for (int i = pos + len; i <= _size; i++) {
				_str[i - len] = _str[i];
			}
			_size -= len;
		}
		return *this;
	}
	size_t string::find(char ch, size_t pos) const {
		assert(pos < _size);
		for (int i = pos ; i < _size ; i++) {
			if (_str[i] == ch)
				return i;
		}
		return npos;
	}

	size_t string::find(const char* s, size_t pos) const {
		if (strstr(this->_str, s + pos))
			return strstr(this->_str, s + pos) - _str;
		else
			return npos;
	}

	string string::substr(size_t pos, size_t len) const {
		if (len == npos || len > _size - pos) {
			len = _size - pos;
		}
		string sub;
		sub.reserve(len);
		for (int i = 0; i < len; i++) {
			sub += _str[pos + i];
		}
		return sub;
	}

	string::string(const string& s)
	:_str(new char[s._capacity + 1])
	,_size(s.size())
	,_capacity(s.capacity())
	{
		//拷贝值
		strcpy(_str, s._str);
	}

	string& string::operator=(const string& s) {
		//避免自己给自己赋值
		if (*this != s) {
			delete[] _str;
			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}
	string operator+(const string& lhs, const string& rhs) {
		string sub(lhs);
		sub += rhs.c_str();
		return sub;
	}

	string operator+(const string& lhs, const char* rhs) {
		string sub(lhs);
		sub += rhs;

		return sub;
	}

	string operator+(const char* lhs, const string& rhs) {
		string sub(lhs);
		sub += rhs.c_str();

		return sub;
	}

	ostream& operator<<(ostream& out, const string& s) {
		for (auto ch : s) {
			out << ch;
		}
		return out;
	}

	istream& operator>> (istream& is, string& str) {
		char ch;
		//in >> ch //err
		ch = is.get();
		while (ch != ' ' && ch != '\n') {
			str += ch;
			//in >> ch err
			ch = is.get();
		}
		return is;
	}

	istream& getline(istream& is, string& str) {
		char ch;
		ch = is.get();
		while (ch != '\n') {
			str += ch;
			ch = is.get();
		}
		return is;
	}

	bool operator== (const string& lhs, const string& rhs) {
		return strcmp(lhs.c_str(), rhs.c_str()) == 0;
	}
	bool operator!= (const string& lhs, const string& rhs) {
		return !operator==(lhs, rhs);
	}
	bool operator>(const string& lhs, const string& rhs) {
		return strcmp(lhs.c_str(), rhs.c_str()) > 0;
	}
	bool operator<(const string& lhs, const string& rhs) {
		return strcmp(lhs.c_str(), rhs.c_str()) < 0;
	}
	bool operator>= (const string& lhs, const string& rhs) {
		return operator>(lhs, rhs) || operator==(lhs, rhs);
	}
	bool operator<= (const string& lhs, const string& rhs) {
		return operator==(lhs, rhs) || operator<(lhs, rhs);
	}

	void string::swap(string& s) {
		std::swap(s._str, _str);
		std::swap(s._capacity, _capacity);
		std::swap(s._size, _size);
	}

}

void swap(byte::string& s1, byte::string& s2) {
	s1.swap(s2);
}



