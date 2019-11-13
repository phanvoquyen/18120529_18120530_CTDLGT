#pragma once
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <set>

using namespace std;

// Tạo class Quine McClusky
class QM
{
public:
	QM()
	{

	}
	~QM()
	{
	}
	int VARIABLES; // số biến
	string dontcares; // chuỗi lưu các giá trị không quan tâm
	// Hàm dựng tham số
	QM(int a);
	// hàm lấy chữ cái để thể hiện các biến, có thể lấy các biến từ 1 đến 26 phù hợp với bảng chữ cái alphabet
	vector<string> getVars();
	// hàm tạo một vector char chứa các kí tự alphabet phục vụ cho việc so sánh kí tự ở hàm charToBin
	string getChar();
	// hàm chuyển chuỗi kí tự nhập vào thành nhị phân minterm
	// ví dụ: bd -> -b-d -> -1-1
	string charToBin(string a);
	// hàm kiểm tra hai số nhị phân khác nhau một bit, tuân theo quy tắc mã xám trong thuật toán Quine McClusky, nếu khác nhau đúng 1 bit trả về true
	bool isGreyCode(string a, string b);
};





