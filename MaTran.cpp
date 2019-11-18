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

int MaTran::HangMaTran() {
	int hang = 0;

	MaTran the = *this;
	MaTran b = the.RutGonMaTran();
	bool kt = false;
	for (int i = 0; i < dong; i++) {
		for (int j = i; j < cot; j++)
			if (the.matrix[i][j] != 0) {
				kt = true;
				break;
			}
		if (kt) {
			kt = false;
			hang++;
		}
	}
	return hang;
}
MaTran MaTran::NghichDao() {
	MaTran c;
	if (dong != cot)
		return c;
	MaTran the = *this;
	MaTran b = the.RutGonMaTran();
	if (the.HangMaTran() != dong)
		return c;
	return b;
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

// Hoán vị dòng
void MaTran::swapRow(int i, int j)
{
	for (int k = 0; k <= dong; k++)
	{
		float temp = matrix[i][k];
		matrix[i][k] = matrix[j][k];
		matrix[j][k] = temp;
	}
}

// Thực hiện phép khử gauss
int MaTran::GaussElim()
{
	// for k chạy theo số cột
	for (int k = 0; k < cot; k++)
	{
		// Khởi tạo giá trị lớn nhất, vị trí có giá trị lớn nhất 
		int index_max = k;
		double value_max = abs(matrix[index_max][k]);

		// Đi tìm giá trị lớn nhất, vị trí có giá trị lớn nhất
		for (int i = k + 1; i < dong; i++)
			if (fabs(matrix[i][k]) > value_max)
				value_max = matrix[i][k], index_max = i;

		// Kiểm tra khác 0, phòng trường hợp chia cho 0
		if (!matrix[index_max][k])
			return k; // ma trận singular 
		for (int i = 0; i < dong; i++)
		{
			for (int j = 0; j < cot; j++)
			{
				if (matrix[i][j] != 0)
					break;
				if (matrix[i][cot] == 0)
					cout << "Ma tran vo so nghiem";
				else if (dong < cot)
					cout << "Ma tran vo so nghiem";
				else
					cout << "Ma tran vo nghiem";
				return 100;
			}

		}
		// đổi chỗ dòng có giá trị lớn nhất với dòng đang xét
		if (index_max != k)
			swapRow(k, index_max);

		// i chạy theo hàng
		for (int i = k + 1; i < dong; i++)
		{
			float f = matrix[i][k] / matrix[k][k];

			// trừ dòng, j chạy theo cột
			for (int j = k + 1; j <= cot; j++)
				matrix[i][j] -= matrix[k][j] * f;

			// gán lại phần tử mốc bằng 0
			matrix[i][k] = 0;
		}
		cout << "---------------------------------------" << endl;
		XuatHe();
	}
	cout << "------------------------------" << endl;
	XuatHe();
	return -1;
}

// Giải nghiệm của hệ 
void MaTran::Solve()
{
	float *x = new float[cot];  // mảng một chiều lưu nghiệm

	// Tình từ dưới tính lên
	for (int i = dong - 1; i >= 0; i--)
	{
		// bắt đầu từ vế phải của phương trình
		x[i] = matrix[i][dong];

		for (int j = i + 1; j < dong; j++)
		{
			// trừ tất cả các giá trị bên vế trái, ngoại trừ hệ số của biến đang được tính
			x[i] -= matrix[i][j] * x[j];
		}

		// chia hệ số của biến đang tính cho vế phải
		x[i] = x[i] / matrix[i][i];
	}

	cout << "Nghiem cua he phuong trinh la: " << endl;
	for (int i = 0; i < dong; i++)
		cout << x[i] << endl;
}

// Giải hệ
void MaTran::GetValue()
{
	if (dong == cot)
	{
		int singular_flag = GaussElim();

		// Nếu là ma trận singular
		if (singular_flag != -1)
		{
			// singular matrix là mà trận chưa khẳng định được vô nghiệm hay vô số nghiệm
			cout << "Ma tran singular" << endl;

			// nếu vế phải vế trái đều bằng 0 thì kết luận vô nghiệm
			if (matrix[singular_flag][dong])
				cout << "He phuong trinh vo nghiem" << endl;
			else
				cout << "He phuong trinh co vo so nghiem" << endl;

			return;
		}

		// Nếu không phải hai trường hợp trên thì tiến hành tính nghiệm
		Solve();
	}
	else
	{
		int singular_flag = GaussElim();
	}

}


MaTran::~MaTran()
{
}