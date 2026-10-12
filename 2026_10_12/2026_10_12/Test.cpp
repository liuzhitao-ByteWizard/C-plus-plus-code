#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        //当遇到操作数时，直接入栈
        for (auto& str : tokens) {
            //遇到操作符，取栈顶两个元素，第一个是右操作数，第二个是左操作数
            if (str == "+" || str == "-" || str == "*" || str == "/") {
                int right = st.top();
                st.pop();
                int left = st.top();
                st.pop();
                //计算完成的结果直接入栈
                //注意：switch中的case中必须是常量表达式，不能直接传str
                switch (str[0]) {
                case '+':
                    st.push(left + right);
                    break;
                case '-':
                    st.push(left - right);
                    break;
                case '*':
                    st.push(left * right);
                    break;
                case '/':
                    st.push(left / right);
                    break;
                }
            }
            else {
                //stoi将字符串转为整型
                st.push(stoi(str));
            }          
        }
        return st.top();
    }
    stack<int> st;
};

class MyQueue {
public:
    MyQueue() {
        //...
    }

    void push(int x) {
        pushst.push(x);
    }

    int pop() {
        //复用peek，保证popst里面是有数据的
        int front = peek();
        popst.pop();
        return front;
    }

    int peek() {
        if (popst.empty()) {
            //如果出栈的元素为空，先将pushst中的数据倒过来
            while (!pushst.empty()) {
                popst.push(pushst.top());
                pushst.pop();
            }
        }
        return popst.top();
    }

    bool empty() {
        //两个栈都为空
        return pushst.empty() && popst.empty();
    }

    //两个栈实现队列
    stack<int> pushst;
    stack<int> popst;
};

class MyStack {
public:
    MyStack() {
        //调用默认构造函数
        //...
    }

    void push(int x) {
        //默认_q1为空，_q2不为空
        if (!_q1.empty()) {
            _q1.push(x);
        }
        else {
            _q2.push(x);
        }
    }

    int pop() {
        //假设法：始终保持_q1不为空
        if (!_q2.empty()) {
            _q1.swap(_q2);
        }

        while (_q1.size() > 1) {
            _q2.push(_q1.front());
            _q1.pop();
        }
        int front = _q1.front();
        return front;

    }

    int top() {
        int top = pop();
        if (!_q1.empty()) {
            _q2.push(top);
        }
        else {
            _q1.push(top);
        }
        return top;
    }

    bool empty() {
        return _q1.empty() && _q2.empty();
    }
    queue<int> _q1;
    queue<int> _q2;
};





int main() {
    Solution v;
    vector<string> tokens = { "2", "1", "+", "3", "*" };
    v.evalRPN(tokens);
    cout << v.st.top() << endl;
	return 0;
}
