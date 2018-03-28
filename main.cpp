#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS           //để dùng được hàm fwscanf
#endif
#include<stdio.h>
#include<cstdlib>


struct sinhvien{
	wchar_t mssv[10], hoten[30], khoa[30], ngaysinh[10], hinh[100], mota[1000];
	int khoahoc;
};
int demsosv(FILE*p){
	int n = 0;
	wchar_t ch;
	while (!feof(p)){
		fwscanf(p, L"%c", &ch);
		if (ch == L'\n'){
			n++;
		}
	}
	n--;
	return n;
}
void docthongtin(FILE*p, sinhvien*&sv,int n){
	sv = new sinhvien[n];
	fseek(p, 0L, SEEK_SET);
	for (int i = 0; i < n; i++){
		fwscanf(p, L"%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", &sv[i].mssv, &sv[i].hoten, &sv[i].khoa, &sv[i].khoahoc, &sv[i].ngaysinh, &sv[i].hinh, &sv[i].mota);
	}
}

void main(){
	
	FILE*filein, *fileout;
	sinhvien *sv;
	int n;
	_wfopen_s(&filein, L"thongtinsinhvien.csv", L"rt,ccs=UTF-8");
	_wfopen_s(&fileout, L"web.html", L"wt,ccs=UTF-8");
	if (filein != NULL){
		if (fileout != NULL){
			
			n = demsosv(filein);
			docthongtin(filein, sv, n);
			fclose(filein);
			fclose(fileout);
		}
	}
	
	
	system("pause");
}
