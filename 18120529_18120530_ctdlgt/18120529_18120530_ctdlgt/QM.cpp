#include "QM.h"


using namespace std;


QM::QM(int a) // hàm khởi tạo tham số
{
	VARIABLES = a;
	dontcares.append(a, '-');
}

// hàm lấy chữ cái để thể hiện các biến, có thể lấy các biến từ 1 đến 26 phù hợp với bảng chữ cái alphabet
vector<string> QM::getVars()
{
	vector<string> v;
	string letters[] = { "a","b","c","d","e","f","g","h" };
	for (int i = 0; i < this->VARIABLES; i++)
		v.push_back(letters[i]);
	return v;
}

// hàm tạo một vector char chứa các kí tự alphabet phục vụ cho việc so sánh kí tự ở hàm charToBin
string QM::getChar()
{
	string letter = "abcdefgh";
	return letter;
}

// hàm chuyển chuỗi kí tự nhập vào thành nhị phân minterm
// ví dụ: bd -> -b-d -> -1-1
string QM::charToBin(string a)
{
	// vd string a = b'd
	vector<string> savedIndex;
	string temp = "";
	for (int i = 0; i < VARIABLES; i++)
	{
		string tmp = "-";
		savedIndex.push_back(tmp);
	}

	vector<string> vars = this->getVars();
	string letter = getChar();
	if (a == dontcares)
		return "1";

	for (int i = 0; i < a.size(); i++)
	{
		// vòng for chạy đối chiếu vars
		for (int j = 0; j < vars.size(); j++)
		{
			if (a[i] == letter[j] && a[i + 1] != '\'')
				savedIndex[j] = vars[j];
			if (a[i] == letter[j] && a[i + 1] == '\'')
			{
				savedIndex[j] = vars[j];
				savedIndex[j].append(1, '\'');
			}
		}
	}

	// hoàn thành bước đệm dấu "-" cho đầy đủ biểu thức
	for (int i = 0; i < VARIABLES; i++)
	{
		if (savedIndex[i] == "-")
			temp += "-";
		else if (savedIndex[i].size() == 2)
			temp += "0";
		else
			temp += "1";
	}
	return temp;
}

// hàm kiểm tra hai số nhị phân khác nhau một bit, tuân theo quy tắc mã xám trong thuật toán Quine McClusky, nếu khác nhau đúng 1 bit trả về true
bool QM::isGreyCode(string a, string b)
{
	int flag = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] != b[i])
			flag++;
	}
	return (flag == 1);
}