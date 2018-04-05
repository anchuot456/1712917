#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS           //để dùng được hàm fwscanf
#endif
#include<stdio.h>
#include<cstdlib>
#include"Header.h"
#include<wchar.h>


struct sinhvien{
	wchar_t mssv[10], hoten[30], khoa[30], ngaysinh[11], hinh[100], mota[1000], email[50],monan[30],amnhac[30];
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
		fwscanf(p, L"%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", &sv[i].mssv, &sv[i].hoten, &sv[i].khoa, &sv[i].khoahoc, &sv[i].email, &sv[i].ngaysinh, &sv[i].hinh, &sv[i].monan, &sv[i].amnhac, &sv[i].mota);
	}
}
void VietWeb(FILE*webmau, FILE**&web, sinhvien*sv, int n){
	web = new FILE*[n];
	for (int number = 0; number < n; number++){
		_wfopen_s(&web[number], L"web.html", L"wt,ccs=UTF-8");
		if (web[number] != NULL){
			wchar_t* dauhieu[13];
			dauhieu[0] = L"<title>";                    //điểm nhận biết số title
			dauhieu[1] = L"\"Personal_FullName\">";     //điểm nhận biết số điền tên
			dauhieu[2] = L"\"Personal_Department\">";   //điểm nhận biết số điền khoa
			dauhieu[3] = L"Email:";                    //điểm nhận biết viết email
			dauhieu[4] = L"\"Personal_HinhcanhanKhung\">\n\t\t\t\t\t\t<img src=\"Images\/";//điểm nhận biết chèn hình ảnh
			dauhieu[5] = L"<li>Họ và tên: ";        //điểm nhận biết ghi họ tên
			dauhieu[6] = L"<li>MSSV: ";             //điểm nhận biết ghi mssv
			dauhieu[7] = L"<li>Sinh viên khoa ";    //điểm nhận biết ghi khoa
			dauhieu[8] = L"<li>Ngày sinh: ";        //điểm nhận biết ghi ngày sinh
			dauhieu[9] = L"<li>Email: ";            //điểm nhận biết ghi email
			dauhieu[10] = L"<li>Âm nhạc: ";         //điểm nhận biết ghi âm nhạc
			dauhieu[11] = L"<li>Ẩm thực: ";         //điểm nhận biết ghi món ăn
			dauhieu[12] = L"\"Description\">";      //điểm nhận biết ghi mô tả
			wchar_t* str[13];
			str[0] = nhapchuoi(L"HCMUS - ", sv[number].hoten);
			str[1] = nhapchuoi(nhapchuoi(sv[number].hoten, L" - "), sv[number].mssv);
			str[2] = sv[number].khoa;
			str[3] = sv[number].email;
			str[4] = sv[number].hinh;
			str[5] = sv[number].hoten;
			str[6] = sv[number].mssv;
			str[7] = sv[number].khoa;
			str[8] = sv[number].ngaysinh;
			str[9] = sv[number].email;
			str[10] = sv[number].amnhac;
			str[11] = sv[number].monan;
			str[12] = sv[number].mota;
			int vt[13];
			for (int j = 0; j < 13; j++){
				vt[j] = ViTriChenThongTin(webmau, dauhieu[j]);
			}
			fseek(webmau, 0L, SEEK_END);
			wchar_t*webnhap = new wchar_t[10000];//viết vào chuỗi web nháp 
			wchar_t*webin = new wchar_t[10000];//sao chép chuỗi web nháp r chỉnh sủa chuổi đó và in ra
			fseek(webmau, 0L, SEEK_SET);
			int i = 0;
			while(!feof(webmau)){
				fwscanf(webmau, L"%c", &webnhap[i]);
				webnhap[i + 1] = L'\0';
				i++;
			}
			int k = 0;
			for (int i = 0; i <= strlen(webnhap); i++){
				int t = 0;
				for (int j = 0; j < 13;j++){
					if (i == vt[j]){
						for ( t = 0; t < strlen(str[j]); t++){
							webin[k + t] = str[j][t];
						}
					}
				}
				k += t;
				webin[k] = webnhap[i];
				webin[k + 1] = L'\0';
				k++;
			}
			fwprintf(web[number],L"%s", webin);
			wprintf(L"%s", webin);
			delete[]webnhap;
			delete[]webin;
			/*wchar_t*new_name = nhapchuoi(sv[number].mssv, L".html");
			_wrename(L"web.html", new_name);*/
			fclose(web[number]);
		}
		delete[]web;
	}
}
void main(){
	FILE*filein,*webmau, **fileout;
	sinhvien *sv=NULL;
	int n;
	_wfopen_s(&filein, L"thongtinsinhvien.csv", L"rt,ccs=UTF-8");
	_wfopen_s(&webmau, L"webthu.htm", L"rt,ccs=UTF-8");
	if (filein != NULL){
		if (webmau != NULL){
			
			n = demsosv(filein);
			docthongtin(filein, sv, n);
			VietWeb(webmau, fileout, sv, n);
			fclose(filein);
			fclose(webmau);
		}
	}
	delete[] sv;
	system("pause");
}
