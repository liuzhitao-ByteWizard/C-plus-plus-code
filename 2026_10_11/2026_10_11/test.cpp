#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <iostream>

using namespace std;

class MinStack {
public:
    MinStack() {
        //调用默认构造函数
    }

    void push(int value) {
        //最小栈为空时，直接入栈
        if (minst.empty()) {
            minst.push(value);
        }
        else {
            //当新元素小于等于最小栈的栈顶元素，入栈
            if (value <= minst.top())
                minst.push(value);
        }
        st.push(value);
      
    }

    void pop() {
        //数据栈和最小栈的栈顶元素相等，最小栈出栈
        if (st.top() == minst.top())
            minst.pop();
        st.pop();

    }

    int top() {
        return st.top();
    }

    int getMin() {
        return minst.top();
    }

    stack<int> st;
    stack<int> minst;
};

int main() {
    MinStack st1;
    st1.push(1);
    st1.push(4);
    st1.push(5);
    st1.push(8);
    st1.push(7);

    int min = st1.getMin();
    cout << min << endl;

    return 0;
}



