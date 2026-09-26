#include "string.h"

namespace byte{
	string::string()
		:_str(new char[15] {'\0'})
		, _size(0)
		, _capacity(15) {

	}

	string::string(const char* str)
	:_str(new char[strlen(str) + 1] {'\0'})
	,_size(strlen(str))
	,_capacity(strlen(str))
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
		if (_size == _capacity) {
			reserve(_capacity * 2);
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

	void string::insert(size_t pos, char ch){
	//扩容
		if(_capacity == _size){
			reserve(_capacity * 2);
		}
		int end = _size;
		//将pos及其之后的值向后移动一个单位
		while(end >= pos){
			_str[end + 1] = _str[end];
			end--;
		}
		//将当前插入的值放入pos位置
		_str[pos] = ch;
		_size++;
	}
	
}



