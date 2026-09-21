#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

//class Solution {
//public:
//    string addStrings(string num1, string num2) {
//        string retstr; // 保存相加结果
//        // 从两个字符串的末尾（个位）开始，向前逐位计算
//        int end1 = num1.size() - 1, end2 = num2.size() - 1;
//        int next = 0; // 进位
//
//        // 只要还有一个字符串未遍历完，就继续计算
//        while (end1 >= 0 || end2 >= 0) {
//            // 数字字符减去 '0' 得到对应数值，取值后下标前移
//            // 已遍历完的字符串，当前位按 0 处理
//            int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
//            int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
//
//            // 当前位总和包含上一位的进位
//            int ret = val1 + val2 + next;
//            next = ret / 10; // 计算下一位的进位
//            ret = ret % 10; // 保留当前位数字
//
//            // 头插：将数字转为字符，在下标 0 处插入 1 个该字符
//            // 从低位向高位计算，通过头插使结果保持正确顺序
//            retstr.insert(0, 1, '0' + ret);
//        }
//
//        // 遍历结束后，若仍有进位，则在最高位补 '1'
//        if (next == 1) {
//            // 头插
//            retstr.insert(0, 1, '1');
//        }
//
//        // 每次头插需要移动已有字符，整体时间复杂度为 O(n²)
//        // n 为两个输入字符串长度的较大值
//        return retstr;
//    }
//};

//class Solution {
//public:
//    string addStrings(string num1, string num2) {
//        string retstr; // 保存结果，先按低位到高位的顺序追加
//
//        // 提前预留容量，减少追加过程中的扩容次数，不改变字符串长度
//        // 注意：原代码中 max 的两个参数均为 num1.size()；
//        // 若要按较长字符串的长度预留容量，第二个参数应为 num2.size()
//        // 此处保留原代码，容量不足时 string 仍会自动扩容
//        retstr.reserve(max(num1.size(), num1.size()) + 1);
//
//        // 从两个字符串的末尾（个位）开始，向前逐位计算
//        int end1 = num1.size() - 1, end2 = num2.size() - 1;
//        int next = 0; // 进位
//
//        while (end1 >= 0 || end2 >= 0) {
//            int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
//            int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
//
//            int ret = val1 + val2 + next;
//            next = ret / 10; // 计算下一位的进位
//            ret = ret % 10; // 保留当前位数字
//
//            // 将数字转为字符后尾插，避免头插时反复移动已有字符
//            retstr += ('0' + ret);
//        }
//
//        // 所有位处理完后，若仍有进位，则追加最高位 '1'
//        if (next == 1) {
//            retstr += '1';
//        }
//
//        // 尾插得到的是逆序结果，反转后恢复正常的数字顺序
//        reverse(retstr.begin(), retstr.end());
//
//        // 尾插加反转：整体时间复杂度为 O(n)，结果占用 O(n) 空间
//        // n 为两个输入字符串长度的较大值
//        return retstr;
//    }
//};

string multiply(string num1, string num2) {
    // 假设输入均为非负整数，且除 "0" 外不含前导零
    if (num1 == "0" || num2 == "0") {
        return "0";
    }

    string retstr1 = "0"; // 累加结果
    int count = 0;       // 当前部分积需要补零的数量

    // 从 num2 的个位开始，逐位与 num1 相乘
    for (int end2 = (int)num2.size() - 1; end2 >= 0; --end2) {
        string retstr2; // 每轮重新保存一个部分积
        int next = 0;  // 每轮的进位从 0 开始
        int nums2 = num2[end2] - '0';

        for (int end1 = (int)num1.size() - 1; end1 >= 0; --end1) {
            int nums1 = num1[end1] - '0';
            int ret = nums1 * nums2 + next;

            next = ret / 10;
            ret = ret % 10;

            // 从低位到高位尾插，暂时得到逆序部分积
            retstr2 += ('0' + ret);
        }

        // 保存最高位的进位
        if (next != 0) {
            retstr2 += ('0' + next);
        }

        // 转换为正常顺序，供 addStrings 使用
        reverse(retstr2.begin(), retstr2.end());

        // 个位补 0 个零，十位补 1 个零，百位补 2 个零……
        retstr2.append(count, '0');

        // 将当前部分积加入总结果
        retstr1 = addStrings(retstr1, retstr2);
        ++count;
    }

    // addStrings 返回的已经是正常顺序，无需再次反转
    return retstr1;
}