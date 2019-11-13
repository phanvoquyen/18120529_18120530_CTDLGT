#include "Vector.h"




Vector::Vector() {
	a.resize(0);
	a.empty();
}
Vector::~Vector() {
	a.clear();
}
void Vector::NhapVector() {
	int soluong;
	int n;
	cout << "nhap so phan tu cua vector" << endl;
	cin >> soluong;
	cout << "nhap phan tu vector" << endl;
	for (int i = 0; i < soluong; i++) {
		cout << "a[" << i << "]=   ";
		cin >> n;
		a.push_back(n);

	}
}
void  Vector::XuatVector() {
	if (a.size() == 0)
		cout << endl << "vector rong" << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << "  ";
	}
	cout << endl;
}
const Vector Vector::operator+(const Vector& b)const {
	Vector temp;
	if (a.size() != b.a.size())
		return temp;
	for (int i = 0; i < a.size(); i++) {
		temp.a.push_back(a[i] + b.a[i]);
	}
	return temp;
}
Vector& Vector::operator*(int ampha) {
	Vector temp;
	if (a.size() == 0)
		return temp;
	for (int i = 0; i < a.size(); i++) {
		a[i] *= ampha;
	}
	return *this;
}
