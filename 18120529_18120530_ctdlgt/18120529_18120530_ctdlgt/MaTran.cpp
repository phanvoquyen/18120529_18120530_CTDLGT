#include "MaTran.h"
MaTran::MaTran() {
	cot = 0;
	dong = 0;
	matrix = NULL;
}
MaTran::MaTran(int n, int m) {
	dong = n;
	cot = m;
	if (m < 0 || n < 0)
		return;
	matrix = (float**)malloc(n * sizeof(float*));
	if (matrix == NULL)
		return;
	for (int i = 0; i < n; i++) {
		matrix[i] = (float*)malloc(m * sizeof(float));
		if (matrix[i] == NULL)
			return;
	}
	for (int i = 0; i < dong; i++) {
		for (int j = 0; j < cot; j++) {
			if (i == j) {
				matrix[i][j] = 1;
			}
			else {
				matrix[i][j] = 0;
			}
		}
	}
}
MaTran::MaTran(const MaTran &x) {
	cot = x.cot;
	dong = x.dong;
	matrix = (float**)malloc(dong * sizeof(float*));
	if (matrix == NULL)
		return;
	for (int i = 0; i < dong; i++) {
		matrix[i] = (float*)malloc(cot * sizeof(float));
		if (matrix[i] == NULL)
			return;
	}
	for (int i = 0; i < dong; i++) {
		for (int j = 0; j < cot; j++) {
			matrix[i][j] = x.matrix[i][j];
		}
	}
}
void MaTran::NhapHe()
{
	// nhập số dòng, cột của ma trận
	cout << "Moi ban nhap so dong cua phuong trinh (dong cua ma tran): ";
	cin >> dong;
	cout << "Moi ban nhap so an cua phuong trinh (cot cua ma tran): ";
	cin >> cot;

	// khởi tạo ma trận
	matrix = new float*[dong];
	for (int i = 0; i < dong; i++)
		matrix[i] = new float[cot];

	// Nhập các phần tử của ma trận
	cout << "Moi ban nhap cac phan tu cua he theo thu tu trai sang phai tren xuong duoi: " << endl;
	for (int i = 0; i < dong; i++)
		for (int j = 0; j <= cot; j++)
		{
			cout << "matrix[" << i << "][" << j << "]=";
			cin >> matrix[i][j];
		}
}

void MaTran::Nhap()
{
	// nhập số dòng, cột của ma trận
	cout << "Moi ban nhap so dong cua ma tran: ";
	cin >> dong;
	cout << "Moi ban nhap so cot cua ma tran: ";
	cin >> cot;

	// khởi tạo ma trận
	matrix = new float*[dong];
	for (int i = 0; i < dong; i++)
		matrix[i] = new float[cot];

	// Nhập các phần tử của ma trận
	cout << "Moi ban nhap cac phan tu cua he theo thu tu trai sang phai tren xuong duoi: " << endl;
	for (int i = 0; i < dong; i++)
		for (int j = 0; j < cot; j++)
		{
			cout << "matrix[" << i << "][" << j << "]=";
			cin >> matrix[i][j];
		}
}

// Hàm này dùng để xuất hệ pt, khác với hàm Xuat, do hệ thì nó nhiều hơn một cột
void MaTran::XuatHe()
{
	for (int i = 0; i < dong; i++)
	{
		for (int j = 0; j <= cot; j++)
			cout << matrix[i][j] << setw(16);
		cout << "\n";
	}
}

void MaTran::Xuat()
{
	for (int i = 0; i < dong; i++)
	{
		for (int j = 0; j < cot; j++)
			cout << matrix[i][j] << setw(16);
		cout << "\n";
	}
}
void MaTran::ThuHoi()
{
	for (int i = 0; i < dong; i++)
		delete[] matrix[i];
	delete[] matrix;
}
MaTran MaTran::RutGonMaTran() {
	MaTran b(dong, cot);
	int i, j;
	for (i = 0, j = 0; i < dong && j < cot; i++, j++) {
		//kiem tra gia tri tai vi tri a[i][j] co bi bang 0 hay khong, neu co thi tim o cac dong sau vi tri khac khong de hoan doi vi tri 
		//cac cot
		if (matrix[i][j] == 0)
		{
			//neu ktbang0vaTimHangKhac khong tim thay gia tri mot gia tri khac khong nao con ton tai trong mang sau a[i][j] thi se thoat
			//chuong trinh
			bool kt = KTBang0VaTimHangKhac0(i, j);
			if (kt)
				break;
		}

		if (i == dong - 1) {
			XuLiHangTren(b, i, j);

		}
		else
			if (i == 0) {
				XuLiHangDuoi(b, i, j);

			}
			else
			{
				XuLiHangTren(b, i, j);
				XuLiHangDuoi(b, i, j);
			}
	}

	return b;
}
bool MaTran::KTBang0VaTimHangKhac0(int &i, int &j) {
	//ham kiem tra tai vi trin matrix[i][j] den a[n-1][j] vi tri nao khac khong, neu tai vi tri k ma matrix[k][j[khac
	//khong thi hoan doi vi tri dong i va j, roi thoat khoi ham
	bool kt = false;
	bool kt1 = false;
	while (1) {
		int l = i;
		for (; l < dong; l++)
			if (matrix[l][j]) {//kt tai cung cot j co phan tu nao khac khong hay khong
				kt = true;//neu co bien kt=true;
				for (int k = 0; k < cot; k++) {//hoan doi vi tri hai hang
					float temp = matrix[i][k];
					matrix[i][k] = matrix[l][k];
					matrix[l][k] = temp;
				}
			}
		if (kt) {//phan tu khac khong dau tien duoc kiem ra, thoat khoi chuong trinh
			kt = false;
			break;
		}
		if (!kt&&l == dong && j == cot - 1) {//neu chay den het mang khong co thi thoat khoi chuong trinh
			kt1 = true;
			break;
		}

		j++;//neu cot khong co sang hang tiep theo
	}
	return kt1;
}
void MaTran::XuLiHangTren(MaTran &y, int i, int j) {
	float bien = matrix[i][j];
	int dem = 1;
	float luuGtri;
	for (int k = 0; k < cot; k++) {
		matrix[i][k] = matrix[i][k] / bien;
		y.matrix[i][k] = y.matrix[i][k] / bien;
	}
	//xu ly tu dong thu i-1 den 0
	for (int dongthu = i; dongthu > 0; dem++, dongthu--) {
		//gia tri ma 
		luuGtri = (float(matrix[i - dem][i]) / matrix[i][j]);
		for (int k = 0; k < cot; k++) {
			matrix[i - dem][k] = matrix[i - dem][k] - luuGtri * matrix[i][k];
			y.matrix[i - dem][k] = y.matrix[i - dem][k] - luuGtri * y.matrix[i][k];
		}

	}

}
void MaTran::XuLiHangDuoi(MaTran &y, int i, int j) {
	float bien = matrix[i][j];
	int dem = 1;
	float luuGtri;
	for (int k = 0; k < cot; k++) {
		matrix[i][k] = matrix[i][k] / bien;
		y.matrix[i][k] = y.matrix[i][k] / bien;
	}
	for (int dongthu = i + 1; dongthu < dong; dem++, dongthu++) {
		luuGtri = matrix[i + dem][j] / matrix[i][j];
		for (int k = 0; k < cot; k++) {
			matrix[i + dem][k] = matrix[i + dem][k] - luuGtri * matrix[i][k];
			y.matrix[i + dem][k] = y.matrix[i + dem][k] - luuGtri * y.matrix[i][k];
		}
	}

}


float MaTran::DinhThuc() {
	float det = 0;

	// ma trận phụ
	MaTran submatrix;
	submatrix.dong = submatrix.cot = dong - 1;
	submatrix.matrix = new float*[submatrix.dong];
	for (int i = 0; i < submatrix.dong; i++)
		submatrix.matrix[i] = new float[submatrix.dong];

	// lấy biến dòng để chạy vì trong ma trận vuông, dòng = cột
	if (dong == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		// mặc định dòng 1 được đem đi làm chuẩn tính định thức, biến index đánh dấu vị trí cột của phần tử được lấy làm chuẩn đi tính ma trận
		for (int index = 0; index < dong; index++) {
			int subi = 0;
			for (int i = 1; i < dong; i++) {
				int subj = 0;
				for (int j = 0; j < dong; j++) {
					// điều kiện if loại bỏ phần tử ở cùng cột với x
					if (j == index)
						continue;
					submatrix.matrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}

			det = det + (pow(-1, index) * matrix[0][index] * submatrix.DinhThuc());
		}
	}
	return det;
}

MaTran MaTran::NhanMaTran(MaTran m)
{
	MaTran result;
	result.dong = dong;
	result.cot = m.cot;
	result.matrix = new float*[dong];
	for (int i = 0; i < dong; i++)
		result.matrix[i] = new float[m.cot];

	// khởi tạo result.matrix với các phần tử đều là 0
	for (int i = 0; i < result.dong; i++)
		for (int j = 0; j < result.cot; j++)
			result.matrix[i][j] = 0;

	while (cot != m.dong)
	{
		cout << "Loi! So cot cua ma tran thu nhat phai bang so hang cua ma tran thu hai!" << endl;
		cout << "Nhap lai ma tran thu hai!" << endl;
		m.Nhap();
	}

	// Thực hiện nhân hai ma trận
	for (int i = 0; i < dong; i++)
		for (int j = 0; j < m.cot; j++)
			for (int k = 0; k < cot; k++)
				result.matrix[i][j] += matrix[i][k] * m.matrix[k][j];

	return result;
}

MaTran::~MaTran()
{
}