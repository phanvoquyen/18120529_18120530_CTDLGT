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
	// hàm thực hiện thay thế các vị trí trùng lấp khi thực hiện phép dán hai số nhị phân bằng dontcares
	// chẳng hạn 1000 với 1001 sẽ thế thành 100-
	string replace_complements(string a, string b);
	// hàm kiểm tra chuỗi b có nằm trong string a hay không
	bool in_vector(vector<string> a, string b);
	// hàm thực hiện phép dán để giảm dần các giá trị minterm
	// ví dụ: 1000 dán với 1001 chỉ thành 1 giá trị đó là 100-
	vector<string> reduce(vector<string> minterms);
	// hàm chuyển giá trị số thành biến
	// Ví dụ: 011- thành a'bc
	string getValue(string a);
	// Kiểm tra 2 vector có bằng nhau hay không
	bool VectorsEqual(vector<string> a, vector<string> b);
	// Hàm ghi ra các giá trị prime implicant hay còn gọi là các phần tử phủ, các phần tử này có thể là tế bào lớn, có thể là minterm, thỏa điều kiện chắc chắn phủ hết các minterm được nhập vào
	vector<string> getPrimeImp(vector<string> minterms, vector<string> &mintermsTemp, string temp);
	//kiểm tra xem nguyên tố phủ có thỏa minterm hay không
	bool primeIncludes(string imp, string minTerm);
	// hàm đếm số biến trong các phép phủ có thể có
	int CountVar(set<int> comb, vector<string> primeImp);
	// Hàm thực hiện tối tiểu
	void minimise(vector<string> primeImp, vector<string> mintermsTemp, vector< set<int> > &functions);
	void OutputFunctions(vector< set<int> > functions, vector<string> primeImp);
	void getPosComb(vector< set<int> > &patLogic, int level, set<int> prod, set< set<int> > &posComb);
};





