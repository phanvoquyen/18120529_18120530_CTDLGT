#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
class MaTran
{
private:
	int dong;
	int cot;
	float** matrix;
public:
	//ham khoi tao mac dinh
	MaTran();
	//ham xoa
	~MaTran();
	//ham khoi tao co hai tham so
	MaTran(int n, int m);
	//ham copy constructor
	MaTran(const MaTran &x);
	//nhap man tran
	void Nhap();
	//xuat ma tran
	void Xuat();
	//nhap he phuong trinh
	void NhapHe();
	//xuat he phuong trinh
	void XuatHe();
	//thu hoi o nho da cap phat
	void ThuHoi();
	//tinh dinh thuc cua ma tran
	float DinhThuc();
	//nhan hai ma tran khac nhau
	MaTran NhanMaTran(MaTran m);
	//
	void swapRow(int, int);
	int GaussElim();
	void Solve();
	void GetValue();
	//rut gon mot ma tran, tra ve la ma tran rut gon
	MaTran RutGonMaTran();
	//tim kiem ma tran nghich dao, tra ve la ma tran chich dao

	MaTran NghichDao();
	//tim kiem hang cua ma tran, tra ve la hang cua ma tran
	int HangMaTran();
	//tu vi tri matrix[i][j] tro len cung cot j dua ve 0
	void XuLiHangTren(MaTran &y, int i, int j);
	//tu vi tri matrix[i][j] tro xuong cung cot j dua ve 0
	void XuLiHangDuoi(MaTran &y, int i, int j);
	//KT tai vi tri matrix[i][j] có bang hay khong, neu co thi kiem tri tri lien ke sau, co vi tri nao khac 0,
	bool KTBang0VaTimHangKhac0(int &i, int &j);
};



