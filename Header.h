#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS           //để dùng được hàm fwscanf
#endif
#include<stdio.h>
long strlen(wchar_t str[]){
	long strlen = 0;
	while (1){                               //đếm dộ dài chuỗi
		if (str[strlen] == L'\0'){
			break;
		}
		strlen++;
	}
	return strlen;                        // k tính kí tự \0
}
int ViTriChenThongTin(FILE*webmau, wchar_t dauhieu[]){
	fseek(webmau, 0, SEEK_END);
	long max = ftell(webmau);
	wchar_t* str = new wchar_t[max];
	fseek(webmau, 0L, SEEK_SET);
	int i = 0;
	while (!feof(webmau)){
		fwscanf(webmau, L"%c", &str[i]);
		i++;
	}
	for (int i = 0; i < strlen(str); i++){
		int k = 1;
		for (int j = 0; j<strlen(dauhieu); j++){
			int str_j = i - strlen(dauhieu) + j;
			if (dauhieu[j] != str[str_j]){
				k = 0;
				break;
			}
		}
		if (k == 1){
			fseek(webmau, 0L, SEEK_SET);
			delete[]str;
			return i;      
		}
	}
}
wchar_t* nhapchuoi(wchar_t* str1, wchar_t* str2){
	wchar_t* str = new wchar_t[strlen(str1) + strlen(str2) + 1];
	for (int i = 0; i <= strlen(str1); i++){
		str[i] = str1[i];
	}
	for (int i = 0; i <= strlen(str2); i++){
		str[strlen(str1) + i] = str2[i];
	}
	return str;
}
