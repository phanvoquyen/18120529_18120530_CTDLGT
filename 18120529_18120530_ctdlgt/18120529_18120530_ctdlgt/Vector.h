#pragma once
#include<vector>
#include<iostream>
using namespace std;

class Vector
{
	//luu cac gia tri cua vector
	vector<int> a;
public:
	//khoi tao mac dinh
	Vector();
	//xoa vector
	~Vector();
	//nhap gia tri thanh phan cua vector
	void NhapVector();
	//xuat gia tri thanh phan cua vector
	void XuatVector();
	//cong hai vector
	const Vector operator+(const Vector&)const;
	//nhan vector voi mot so
	Vector& operator*(int ampha);
};

