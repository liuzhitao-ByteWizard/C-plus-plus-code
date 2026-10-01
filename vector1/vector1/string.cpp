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

	void string::insert(size_t pos, char ch) {
		//扩容
		if (_capacity == _size) {
			reserve(_capacity * 2);
		}
		int end = _size;
		//将pos及其之后的值向后移动一个单位
		while (end >= pos) {
			_str[end + 1] = _str[end];
			end--;
		}
		//将当前插入的值放入pos位置
		_str[pos] = ch;
		_size++;
	}

	// 拷贝构造函数：使用已有对象初始化新对象，例如 string s6(s5)
	string::string(const string& s) {
		string tmp(s._str);
		swap(tmp);
	}

	// 成员 swap：交换缓冲区指针、容量和长度，时间复杂度为 O(1)
	void string::swap(string& s) {
		// 交换缓冲区的所有权，无需复制字符内容
		std::swap(s._str, _str);

		// 容量和长度必须与对应的缓冲区一起交换
		std::swap(s._capacity, _capacity);
		std::swap(s._size, _size);
	}

	// 非成员 swap：支持 swap(s1, s2) 形式的调用
	void swap(string& s1, string& s2) {
		// 复用成员函数，完成交换
		s1.swap(s2);
	}

	// 重载流插入运算符，支持通过 cout << s 输出自定义字符串
	ostream& operator<<(ostream& out, const string& s) {
		// 使用范围 for 遍历字符串，将每个字符依次写入输出流
		for (auto ch : s) {
			out << ch;
		}

		// 返回原输出流的引用，支持连续输出，如 cout << s1 << s2
		return out;
	}

	// 重载流提取运算符，支持 cin >> str 形式的调用
	istream& operator>>(istream& is, string& str) {
		str.erase();
		// 0 - 127
		char ch;
		ch = is.get();
		char buffer[128];
		int i = 0; //遍历buffer数组
		while (ch != ' ' && ch != '\n') {
			buffer[i++] = ch; //i = 126时，还可以读
			if (i == 127) {
				//默认达到字符串末尾，将i置为0，重新读取
				buffer[i] = '\0';
				str += buffer;
				i = 0;
			}
			ch = is.get(); //读下一个字符
		}

		//buffer数组没有存满，读取字符结束时
		if (i > 0) {
			buffer[i] = '\0';
			str += buffer;
		}

		return is;
	}

	//string& string::operator=(const string& s) {

	//	string tmp(s);
	//	swap(tmp);

	//	// 返回当前对象的引用，支持连续赋值
	//	return *this;		
	//}

	string& string::operator=(string tmp) {
		swap(tmp);
		return *this;
	}

	void string::erase(size_t pos, size_t len) {
		// 检查删除位置，允许 pos == _size，此时不删除任何字符
		assert(pos <= _size);

		// len 为 npos，或删除长度达到、超过剩余字符数时，删除到末尾
		if (len == string::npos || len >= _size - pos) {
			// 在 pos 处设置结束符，截断字符串
			_str[pos] = '\0';

			// 截断后的长度为 pos
			_size = pos;
		}
		else {
			// 从前向后，将删除区间之后的字符整体左移 len 位
			// i 表示源位置，pos 表示目标位置
			// 使用 i <= _size，将末尾的 '\0' 一并移动
			for (size_t i = pos + len; i <= _size; i++) {
				_str[pos++] = _str[i];
			}

			// 更新字符串长度，容量保持不变
			_size -= len;
		}
	}

	istream& getline(istream& in, string& str, char delim) {
		str.erase();

		char ch;
		//in >> ch;
		ch = in.get();
		char buff[128];
		int i = 0;

		while (ch != delim) {
			buff[i++] = ch;
			// buff满了
			if (i == 127) {
				buff[i] = '\0';
				str += buff;
				i = 0;
			}

			ch = in.get();
		}

		if (i > 0) {
			buff[i] = '\0';
			str += buff;
		}

		return in;
	}

	const size_t string::npos = -1;  // 声明静态成员常量

}
