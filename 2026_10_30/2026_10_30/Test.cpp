#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>

using namespace std;

void test_map1() {
	map<string, string> st1;
	//隐式类型转换成pair
	pair<string, string> st2 = { "zhangsan" , "lisi" };
	// pair 这个对象呢，它也支持多参数的隐式类型转换
	//先initializerlist，在insert进去
	map<string, string> st3{ { "zhaangsan" , "1" } ,{ "lisi" , "2" } }; //initializerlist初始化
	map<string, string> st4(st3.begin() , st3.end()); //初始化列表初始化

	map<string, string> st5 = st4;

}

void test_map2() {
	map<string, string> dict;
	// insert插入pair对象的4种方式，对比之下，最后一种最方便
	pair<string, string> kv1("first", "第一个");
	dict.insert(kv1);
	dict.insert(pair<string, string>("second", "第二个"));
	dict.insert(make_pair("sort", "排序"));
	dict.insert({ "auto", "自动的" });

	for (auto& e : dict) {
		cout << e.first << " " << e.second << endl;
	}
	cout << endl;

}

void test_map3() {
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜","苹果", "香蕉", "苹果", "香蕉" };
	map<string, int> countMap;
	//for (auto& e : arr) {
	//	auto it = countMap.find(e);  //找到的是对应key的结点
	//	if (it == countMap.end())
	//		countMap.insert({ e,1 });
	//	else
	//		it->second++;
	//}

	for (auto& e : arr) {
		countMap[e]++;
	}

	for (auto& e : countMap) {
		cout << e.first << " " << e.second << endl;
	}
	cout << endl;
}

void test_map4() {
	map<string, string> dict;
	dict.insert(make_pair("sort", "排序"));
	// key不存在->插入 {"insert", string()}
	dict["insert"]; // {key, value默认构造}
	// 插入+修改
	dict["left"] = "左边";

	// key存在->查找
	cout << dict["left"] << endl;
	// 修改
	dict["left"] = "左边、剩余";
	cout << dict["left"] << endl;
}

void test_map5() {
	multimap<string, int> mm;
	map<string, int> m;
	//multimap只要可以插入，所有需要插入的pair对象都可以进行插入
	//insert是无法进行修改的，只有iterator和[]可以修改
	mm.insert({ "张三", 1 });
	mm.insert({ "张三", 2 });
	mm.insert({ "张三", 2 });

	m.insert({ "张三", 1 });
	m.insert({ "张三", 2 }); //不会修改value，key相同，不允许插入的
}

int main() {
	test_map5();
	return 0;
}