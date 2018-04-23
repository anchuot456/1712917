#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS           //để dùng được hàm fwscanf
#endif
#include<stdio.h>
#include<cstdlib>
#include"Header.h"
#include<wchar.h>


struct sinhvien{
	wchar_t mssv[10], hoten[30], khoa[30], ngaysinh[11], hinh[100], mota[1000], email[50],sothich[50][50];
	int khoahoc,n;
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
	return n-2;
}
void docthongtin(FILE*p, sinhvien*&sv,int n){
	sv = new sinhvien[n];
	fseek(p, 92L, SEEK_SET);
	for (int i = 0; i < n; i++){
		fwscanf(p, L"%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],", &sv[i].mssv, &sv[i].hoten, &sv[i].khoa, &sv[i].khoahoc, &sv[i].email, &sv[i].ngaysinh, &sv[i].hinh);
		wchar_t ch ;
		ch = fgetwc(p);
		if (ch == L'\"'){
			fwscanf(p, L"%[^\"]\",", &sv[i].mota);
		}
		else{
			fseek(p, -1L, SEEK_CUR);
			fwscanf(p, L"%[^,],", &sv[i].mota);
			sv[i].mota[0] = ch;
		}
		ch = fgetwc(p);
		wchar_t str[100];
		if (ch == L'\"'){                                // đọc vào chuỗi str r cắt ra
			fwscanf(p, L"%[^\"]\"\n", &str);
		}
		else{
			fseek(p, -1L, SEEK_CUR);
			fwscanf(p, L"%[^\n]\n", &str);
			str[0] = ch;
		}
		sv[i].n = 0;
		int j = 0;
		for (int k = 0; k < strlen(str); k++){
			if (str[k] == L'.'){
				j = 0;
				sv[i].n++;
				k++;
			}
			sv[i].sothich[sv[i].n][j] = str[k];
			sv[i].sothich[sv[i].n][j + 1] = L'\0';
			j++;
		}
	}
}
void VietWeb(FILE*webmau, FILE**&web, sinhvien*sv, int n){
	web = new FILE*[n];
	for (int number = 0; number < n; number++){
		wchar_t *tenweb=new wchar_t[20];
		 tenweb =nhapchuoi( L"websinhvien\\",nhapchuoi(sv[number].mssv, L".html"));
		_wfopen_s(&web[number], tenweb, L"wt,ccs=UTF-8");
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
			dauhieu[10] = L"Sở thích</div>\n                        <div>\n                            <ul class=\"TextInList\">\n";         //điểm nhận biết ghi sở thích
			dauhieu[11] = L"\"Description\">";         //điểm nhận biết ghi mô tả
			dauhieu[12] = L"TH2012/03</br>\n";
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
			str[10] = NULL;
			for (int i = 0; i <= sv[number].n; i++){
				str[10] = nhapchuoi(str[10], nhapchuoi(nhapchuoi(L"<li>", sv[number].sothich[i]), L"</li>\n"));
			}
			str[11] = sv[number].mota;
			str[12] = L"1712917 - Bùi Anh Vũ";
			wchar_t* xoa[13];
			xoa[0] = L"HCMUS - Nguyễn Văn A";
			xoa[1] = L"NGUYỄN VĂN A - 1212123";
			xoa[2] = L"KHOA CÔNG NGHỆ THÔNG TIN";
			xoa[3] = L"nva@gmail.com";
			xoa[4] = L"HinhCaNhan.jpg";
			xoa[5] = L"Nguyễn Văn A";
			xoa[6] = L"1212123";
			xoa[7] = L"Công nghệ thông tin";
			xoa[8] = L"20/01/1994";
			xoa[9] = L" nva@gmail.com";
			xoa[10] = L"                                <li>Âm nhạc: POP, Balad</li>\n								<li>Ẩm thực: bún riêu, bún thịt nướng</li>";
			xoa[11] = L"                             Tôi là một người rất thân thiện.";
			xoa[12] = L"				MSSV - Tên sinh viên thực hiện";
			wchar_t*webnhap = new wchar_t[10000];//viết vào chuỗi web nháp 
			wchar_t*webin = new wchar_t[10000];//sao chép chuỗi web nháp r chỉnh sủa chuổi đó và in ra
			fseek(webmau, 0L, SEEK_SET);
			int i = 0;
			while(!feof(webmau)){
				fwscanf(webmau, L"%c", &webnhap[i]);
				webnhap[i + 1] = L'\0';
				i++;
			}
			int vt[13];
			for (int j = 0; j < 13; j++){
				vt[j] = ViTriChenThongTin(webnhap, dauhieu[j]);
			}
			for (int i = 12; i >= 0; i--){
				XoaChuoi(webnhap, vt[i], strlen(xoa[i]));
			}
			for (int j = 0; j < 13; j++){
				vt[j] = ViTriChenThongTin(webnhap, dauhieu[j]);
			}
			int k = 0;
			for (int i = 0; i <= strlen(webnhap); i++){
				int t = 0;
				for (int j = 0; j < 13;j++){                 // chèn các thong tin sinh viên vào
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
			fclose(web[number]);
		}
		delete[]tenweb;
	}
	delete[]web;
}
void main(){
	FILE*filein,*webmau, **fileout;
	sinhvien *sv=NULL;
	int n;
	_wfopen_s(&filein, L"thongtinsinhvien.csv", L"rt,ccs=UTF-8");
	_wfopen_s(&webmau, L"1212123.htm", L"rt,ccs=UTF-8");
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
