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


// hàm thực hiện thay thế các vị trí trùng lấp khi thực hiện phép dán hai số nhị phân bằng dontcares
// chẳng hạn 1000 với 1001 sẽ thế thành 100-
string QM::replace_complements(string a, string b)
{
	string temp = "";
	for (int i = 0; i < a.length(); i++)
		if (a[i] != b[i])
			temp = temp + "-";
		else
			temp = temp + a[i];
	return temp;
}

// hàm kiểm tra chuỗi b có nằm trong string a hay không
bool QM::in_vector(vector<string> a, string b)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i].compare(b) == 0)
			return true;
	return false;
}

// hàm thực hiện phép dán để giảm dần các giá trị minterm
// ví dụ: 1000 dán với 1001 chỉ thành 1 giá trị đó là 100-
vector<string> QM::reduce(vector<string> minterms)
{
	vector<string> newminterms;

	int max = minterms.size();
	int* checked = new int[max];
	for (int i = 0; i < max; i++)
	{
		for (int j = i; j < max; j++)
		{
			// Nếu tìm được mã xám (tức là hai số nhị phân khác nhau một bit) thay thế bit đó với dontcare 
			if (isGreyCode(minterms[i], minterms[j]))
			{
				checked[i] = 1;
				checked[j] = 1;
				// kiểm tra xem minterm đã có trong vector newminterm chưa, có thì k thêm vào
				if (!in_vector(newminterms, replace_complements(minterms[i], minterms[j])))
					newminterms.push_back(replace_complements(minterms[i], minterms[j]));
			}
		}
	}
	// thêm các minterm chưa thực hiện phép dán nào vào trong newminterm
	for (int i = 0; i < max; i++)
	{
		if (checked[i] != 1 && !in_vector(newminterms, minterms[i]))
			newminterms.push_back(minterms[i]);
	}
	delete[] checked;
	return newminterms;
}

// hàm chuyển giá trị số thành biến
// Ví dụ: 011- thành a'bc
string QM::getValue(string a)
{
	string temp = "";
	vector<string> vars = this->getVars();
	if (a == dontcares)
		return "1";

	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] != '-')
		{
			if (a[i] == '0')
				temp = temp + vars[i] + "\'";
			else
				temp = temp + vars[i];
		}
	}
	return temp;
}

// Kiểm tra 2 vector có bằng nhau hay không
bool QM::VectorsEqual(vector<string> a, vector<string> b)
{
	if (a.size() != b.size())
		return false;

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
}