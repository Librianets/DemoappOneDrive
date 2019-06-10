////////////////////////////////////////////////////
// 				Support Unicode
//
//
// Тестовая программа с ограниченным функционалом
// Подавление веб регистрации и согласия пользователя
// Алгоритмы защиты и шифрования отсутствуют
//
//
// Повторюсь, программа с "автоподавлением" запросов согласия
// Так же замечены некоторые ошибки из-за времени обновления 
// статуса авторизации (исправимые). Но они врятли проявятся у кого-то
//
//
// Для того кто смотрит этот код:
// goto и отсутствие изящных классов и красивых функций
// диктуется не желанием тратить время на столь большое тестовое задание
// "автоподавление" запросов требует времени на изучение трафика, 
// а это не прочтешь в книгах
//
//
//////////////////////////////////////////////////////////////////////////////////////////
//					//				//			//			//			//				//
//	programm.exe	//	-first		//	-get	//	-src	// -email	// -nameupload	//
//					//	-notfirst	//	-put	//	-dst	// -passwd	//				//
//					//				//			//			//			//				//
//////////////////////////////////////////////////////////////////////////////////////////
// nameupload для будущей совместимости (возможно)

#include "main.hpp"

int main ()
{
	int DEFEXIT = 0x0;
	unsigned char iFirstLaunch	= 0x0;
	unsigned char iFlagSend		= 0x0;
	
	wchar_t aLogin [100];
	wchar_t aPassword [100];
	wchar_t aNameDst [200]; 
	wchar_t aNameSrc [200];
	wchar_t aNameUpload [200];
	
	memset(aLogin, 0, (100)*sizeof(wchar_t));
	memset(aPassword, 0, (100)*sizeof(wchar_t));
	memset(aNameDst, 0, (200)*sizeof(wchar_t));
	memset(aNameSrc, 0, (200)*sizeof(wchar_t));
	memset(aNameUpload, 0, (200)*sizeof(wchar_t));
	//vector <wchar_t> aLogin;
	//vector <wchar_t> aPassword;

	HINTERNET hInitInetOpen = NULL, hInetSession = NULL, hInetRequest = NULL;
	int iSend = 0x0;
	char *lpSearchStr = NULL;
	wchar_t *lpSearchStrTwo = NULL;
	wchar_t *lpSearchStrTempTwo = NULL;
	char *lpSearchStrTemp = NULL;
#ifdef MINGW32
long unsigned int iSizeStrSearchVal = 0x0;
#else
#ifdef VSMS
DWORD iSizeStrSearchVal = 0x0;
#else
unsigned int iSizeStrSearchVal = 0x0;
#endif
#endif
	
	wchar_t aBrouser [130];
	wchar_t aRequest [1024];
	wchar_t aSendInfo [1024];
	wchar_t aClientID [37+1];
	wchar_t aScope [216+1];
	wchar_t aUAID [32+1];
	wchar_t aPPFT [220+1];
	wchar_t aBK [10+1];
	wchar_t aCONTEXTID [16+1];
	wchar_t aPID [5+1];
	char aDataPage [204800];
	wchar_t aDataPageTWO [8192]; // Оптимизировать буферы
	wchar_t aTempOne [2048];
	char aTempTwo [2048];
	wchar_t aACCESSTOKEN [2048];
	wchar_t aCANARY [100];
	
	wchar_t aActionTemp[250];
	wchar_t aIPT[1024];
	wchar_t aPPRID[20];
	wchar_t aClientIDTemp[20];
	wchar_t aScopeTemp[200];
	wchar_t aOPID[20];
	wchar_t aOPIDT[20];
	wchar_t aLocation[500];
	
	// в fullversion выровнять и в структуру
	EXIT_APP:
	
	memset(aLocation, 0, 500*sizeof(wchar_t)); 
	memset(aUAID, 0, (32+1)*sizeof(wchar_t));
	memset(aDataPage, 0, 204800);
	memset(aDataPageTWO, 0, 8192*sizeof(wchar_t));
	memset(aBrouser, 0, 130*sizeof(wchar_t));
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	memset(aClientID, 0, (37+1)*sizeof(wchar_t));
	memset(aScope, 0, (216+1)*sizeof(wchar_t));
	memset(aTempOne, 0, 2048*sizeof(wchar_t));
	memset(aTempTwo, 0, 2048);
	memset(aPPFT, 0, (220+1)*sizeof(wchar_t));
	memset(aCONTEXTID, 0, (16+1)*sizeof(wchar_t));
	memset(aBK, 0, (10+1)*sizeof(wchar_t));
	memset(aPID, 0, (5+1)*sizeof(wchar_t));
	memset(aACCESSTOKEN, 0, (2048)*sizeof(wchar_t));
	memset(aCANARY, 0, (100)*sizeof(wchar_t));
	
	memset(aActionTemp, 0, 250*sizeof(wchar_t));
	memset(aIPT, 0, 1024*sizeof(wchar_t));
	memset(aPPRID, 0, 20*sizeof(wchar_t));
	memset(aClientIDTemp, 0, 20*sizeof(wchar_t));
	memset(aScopeTemp, 0, 200*sizeof(wchar_t));
	memset(aOPID, 0, 20*sizeof(wchar_t));
	memset(aOPIDT, 0, 20*sizeof(wchar_t));
	
	if (DEFEXIT == 1) {exit(1);}
////////////////////////////
////////////////////////////
	int iArgc;
	LPWSTR *lpArgv;
	
	lpArgv = CommandLineToArgvW(GetCommandLineW(), &iArgc);
	if (lpArgv == NULL) {wprintf(L"Error: argv not correct, use -help"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	for (int i = 0; i < iArgc; i++) 
	{
		if (wcscmp(lpArgv[i], L"-first") 	== 0)		{iFirstLaunch = DEFFLAGFIRST;}
		if (wcscmp(lpArgv[i], L"-notfirst") == 0)		{iFirstLaunch = DEFFLAGNOTFIRST;}
		if (wcscmp(lpArgv[i], L"-get") 		== 0)		{iFlagSend = DEFFLAGGET;}
		if (wcscmp(lpArgv[i], L"-put") 		== 0)		{iFlagSend = DEFFLAGPUT;}
		
		if (wcscmp(lpArgv[i], L"-email") == 0)
		{
			if (wcsstr(lpArgv[i+1], L"@") == NULL) {wprintf(L"Error: email not correct"); DEFEXIT = 1; goto EXIT_APP; }
			unsigned int iSizeLogin = wcslen(lpArgv[i+1]);
			if (iSizeLogin < 5) {wprintf(L"Error: email size < 5"); DEFEXIT = 1; goto EXIT_APP; }
			if (iSizeLogin > 100) {wprintf(L"Error: email size > 100"); DEFEXIT = 1; goto EXIT_APP; }
			for(int bb = 0; bb < iSizeLogin; bb++){aLogin[bb] = lpArgv[i+1][bb];} // not use memcpy
			// на будущее vector использовать острожней из-за особенностей реализации
			memset(lpArgv[i+1], 0, iSizeLogin); // стираем логин // в fullversion проверить целесообразность
		}

		if (wcscmp(lpArgv[i], L"-src") == 0)
		{
			//if (wcsstr(lpArgv[i+1], L"@") == NULL) {wprintf(L"Error: email not correct"); DEFEXIT = 1; goto EXIT_APP; }
			unsigned int iSizeSrc = wcslen(lpArgv[i+1]);
			if (iSizeSrc < 2) {wprintf(L"Error: file src size < 2"); DEFEXIT = 1; goto EXIT_APP; }
			if (iSizeSrc > 100) {wprintf(L"Error: src size > 150"); DEFEXIT = 1; goto EXIT_APP; }
			for(int bb = 0; bb < iSizeSrc; bb++){aNameSrc[bb] = lpArgv[i+1][bb];} // not use memcpy
		}
		
		if (wcscmp(lpArgv[i], L"-dst") == 0)
		{
			//if (wcsstr(lpArgv[i+1], L"@") == NULL) {wprintf(L"Error: email not correct"); DEFEXIT = 1; goto EXIT_APP; }
			unsigned int iSizeDst = wcslen(lpArgv[i+1]);
			if (iSizeDst < 2) {wprintf(L"Error: file src size < 2"); DEFEXIT = 1; goto EXIT_APP; }
			if (iSizeDst > 100) {wprintf(L"Error: src size > 150"); DEFEXIT = 1; goto EXIT_APP; }
			for(int bb = 0; bb < iSizeDst; bb++){aNameDst[bb] = lpArgv[i+1][bb];} // not use memcpy
		}
		
		if (wcscmp(lpArgv[i], L"-passwd") == 0)
		{
			//if (wcsstr(lpArgv[i+1], L"@") == NULL) {wprintf(L"Error: email not correct"); DEFEXIT = 1; goto EXIT_APP; } // сделать fullversion проверку на символы
			unsigned int iSizePasswd = wcslen(lpArgv[i+1]);
			if (iSizePasswd < 4) {wprintf(L"Error: password size < 4"); DEFEXIT = 1; goto EXIT_APP; }
			if (iSizePasswd > 100) {wprintf(L"Error: password size > 100"); DEFEXIT = 1; goto EXIT_APP; }
			for(int bb = 0; bb < iSizePasswd; bb++){aPassword[bb] = lpArgv[i+1][bb];} // not use memcpy
			//memcpy(&aPassword[0x0], lpArgv[i+1], iSizePasswd);
			memset(lpArgv[i+1], 0, iSizePasswd); // стираем пароль // в fullversion проверить целесообразность
		}
		
		if (wcscmp(lpArgv[i], L"-nameupload") == 0)
		{
			//if (wcsstr(lpArgv[i+1], L"@") == NULL) {wprintf(L"Error: email not correct"); DEFEXIT = 1; goto EXIT_APP; } // сделать fullversion проверку на символы
			unsigned int iSizeName = wcslen(lpArgv[i+1]);
			if (iSizeName < 4) {wprintf(L"Error: name upload < 4"); DEFEXIT = 1; goto EXIT_APP; }
			if (iSizeName > 100) {wprintf(L"Error: name upload > 100"); DEFEXIT = 1; goto EXIT_APP; }
			for(int bb = 0; bb < iSizeName; bb++){aNameUpload[bb] = lpArgv[i+1][bb];} // not use memcpy
			//memcpy(&aPassword[0x0], lpArgv[i+1], iSizePasswd);
			memset(lpArgv[i+1], 0, iSizeName); // стираем пароль // в fullversion проверить целесообразность
		}
		
		if (wcscmp(lpArgv[i], L"-help") == 0)
		{
			wprintf(L"\r\n");
			wprintf(L"Minimal Count argument - 10\r\n");
			wprintf(L"Programm.exe -first/-notfirst -get/-put -src ***** -dst ***** -email ***** -passwd **** \r\n");
			wprintf(L"Flag first using for first launch \r\n");
			wprintf(L"Use path disk:/path/to/file \r\n");
			//wprintf(L"Use -nameupload for put \r\n");
			wprintf(L"Sample: \r\n");
			wprintf(L"Programm.exe -first -get -src picture.jpg -dst d:/multimedia/picture.jpg -email test@test.com -passwd TestTest");
			wprintf(L"\r\n");			
			wprintf(L"Programm.exe -nofirst -get -src picture.jpg -dst d:/multimedia/picture.jpg -email test@test.com -passwd TestTest");
			wprintf(L"\r\n");
			wprintf(L"Programm.exe -nofirst -put -dst picture.jpg -src d:/multimedia/picture.jpg -email test@test.com -passwd TestTest");
			wprintf(L"\r\n");
			wprintf(L"Programm.exe -first -put -dst picture.jpg -src d:/multimedia/picture.jpg -email test@test.com -passwd TestTest");
			wprintf(L"\r\n");
			
			DEFEXIT = 1; goto EXIT_APP;
		}
	}
	
	if (iArgc < 10 ) {wprintf(L"Error: count argument < 10, use -help"); DEFEXIT = 1; goto EXIT_APP; } else {}
		
	/////////////////////////////////
	wcscat(aBrouser, L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134");
	wcscat(aRequest, L"/common/oauth2/v2.0/authorize?");
	wcscat(aClientID, L"9b3c4ea3-9ccc-4283-aacd-51f6cc0cfb16");
	wcscat(aScope, L"Files.ReadWrite.All");
	
	DWORD iDataPage; // InternetReadFile автоматически сбросит в ноль
	BOOL bStatusData;

	
	///////////////////// Logout///////////////////// /**/
	InternetClearAllPerSiteCookieDecisions();
	hInitInetOpen = NULL, hInetSession = NULL, hInetRequest = NULL;
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen Logout failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	hInetSession = InternetConnectW(hInitInetOpen, L"login.microsoftonline.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession Logout failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", L"/common/oauth2/v2.0/logout?post_logout_redirect_uri=https://localhost:80/", NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest Logout failure");	DEFEXIT = 1; goto EXIT_APP; }
	//HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	iSend = HttpSendRequestW(hInetRequest, NULL, 0, NULL, 0);
	if (iSend == FALSE) {wprintf(L"Error: iSend Logout failure"); DEFEXIT = 1; goto EXIT_APP; }	
	hInitInetOpen = NULL, hInetSession = NULL, hInetRequest = NULL;
	///////////////////// Logout/////////////////////
	
	///////////////////// State 1
	///////////////////// GET 1
	
	//////////// aRequest 1 ////////////
	wcscat(aRequest, L"client_id=");
	wcscat(aRequest, aClientID);
	wcscat(aRequest, L"&response_type=token");
	wcscat(aRequest, L"&redirect_uri=https://localhost:80/");
	wcscat(aRequest, L"&scope=");
	wcscat(aRequest, aScope);
	
	/////////////////////////////////
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen GET 1 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"login.microsoftonline.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession GET 1 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}

	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest GET 1 failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	
	iSend = HttpSendRequestW(hInetRequest, NULL, 0, NULL, 0);
	if (iSend == FALSE) {wprintf(L"Error: iSend GET 1 failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
	///////////////////// Disassembler 1
	bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	if (bStatusData == FALSE) {wprintf(L"Error: ReadPage GET 1 failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	//for (int iConvertCount = 0; iConvertCount < iDataPage; iConvertCount++) {aDataPage[iConvertCount] = ntohs(aDataPage[iConvertCount]);} // UTF16LE->UTF16BE	 // отставить на будующие преобразования
	lpSearchStr = strstr(aDataPage, "uaid=");
	if (lpSearchStr == NULL) {wprintf(L"Error: Search GET 1 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=5;
	iSizeStrSearchVal = 32;
	for(int i = 0; i < iSizeStrSearchVal; i++){aUAID[i] = *(lpSearchStr+i);}
	iSizeStrSearchVal = 0;
	
	
	///////////////////// POST 1
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	wcscat(aRequest, L"/common/GetCredentialType?mkt=ru-RU");
	InternetCloseHandle(hInetRequest);
	hInetRequest = HttpOpenRequestW(hInetSession, L"POST", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest POST 1 failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Origin: https://login.microsoftonline.com", 41, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: application/json", 24, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Content-type: application/json; charset=utf-8", 45, HTTP_ADDREQ_FLAG_COALESCE);
	
	wcscat(aSendInfo, L"{\"username\":\"");
	wcscat(aSendInfo, aLogin);
	wcscat(aSendInfo, L"\"}");

	WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);	//winapi
	
	iSend = HttpSendRequestW(hInetRequest, NULL, 0, aTempTwo, strlen(aTempTwo));
	if (iSend == FALSE)	{wprintf(L"Error: iSend POST 1 failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);
	memset(aDataPage, 0, 204800);
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	memset(aTempTwo, 0, 2048);
	
	///////////////////// State 2
	///////////////////// GET 2
	
	//////////// aRequest 2 ////////////
	wcscat(aRequest, L"/oauth20_authorize.srf?");
	wcscat(aRequest, L"username=");
	wcscat(aRequest, &aLogin[0x0]);
	wcscat(aRequest, L"&client_id=");
	wcscat(aRequest, aClientID);
	wcscat(aRequest, L"&scope=");
	wcscat(aRequest, aScope);
	wcscat(aRequest, L"&redirect_uri=https://localhost:80/");
	wcscat(aRequest, L"&response_type=token");
	wcscat(aRequest, L"&msproxy=1&issuer=mso&tenant=common&ui_locales=ru-RU");
	wcscat(aRequest, L"&uaid=");
	wcscat(aRequest, aUAID);
	//////////////////////////////////////////
	
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"login.live.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}

	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest GET 2 failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	
	iSend = HttpSendRequestW(hInetRequest, NULL, 0, NULL, 0);
	if (iSend == FALSE) {wprintf(L"Error: iSend GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
	///////////////////// Disassembler 2
	
	bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	if (bStatusData == FALSE) {wprintf(L"Error: ReadPage GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; }

	lpSearchStr = strstr(aDataPage, "name=\"PPFT\" id=\"i0327\" value=\"");
	lpSearchStrTemp = strstr(aDataPage, "\"/>',");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search PPFT GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=30;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aPPFT[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;
	
	lpSearchStr = strstr(aDataPage, "contextid=");
	if (lpSearchStr == NULL) {wprintf(L"Error: Search contextid GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=10;
	iSizeStrSearchVal = 16;
	for(int i = 0; i < iSizeStrSearchVal; i++){aCONTEXTID[i] = *(lpSearchStr+i);}
	iSizeStrSearchVal = 0;

	lpSearchStr = strstr(aDataPage, "bk=");
	if (lpSearchStr == NULL) {wprintf(L"Error: Search bk GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=3;
	iSizeStrSearchVal = 10;
	for(int i = 0; i < iSizeStrSearchVal; i++){aBK[i] = *(lpSearchStr+i);}
	iSizeStrSearchVal = 0;

	lpSearchStr = strstr(aDataPage, "&pid=");
	if (lpSearchStr == NULL) {wprintf(L"Error: Search pid GET 2 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=5;
	iSizeStrSearchVal = 5;
	for(int i = 0; i < iSizeStrSearchVal; i++){aPID[i] = *(lpSearchStr+i);}
	iSizeStrSearchVal = 0;
	
	///////////////////// POST 2
	InternetCloseHandle(hInetRequest);
	
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	wcscat(aRequest, L"/ppsecure/post.srf?");
	wcscat(aRequest, L"username=");
	wcscat(aRequest, &aLogin[0x0]);
	wcscat(aRequest, L"&client_id=");
	wcscat(aRequest, aClientID);
	wcscat(aRequest, L"&scope=");
	wcscat(aRequest, aScope);
	wcscat(aRequest, L"&response_type=token");
	wcscat(aRequest, L"&msproxy=1&issuer=mso&tenant=common&ui_locales=ru-RU");
	wcscat(aRequest, L"&uaid=");
	wcscat(aRequest, aUAID);
	wcscat(aRequest, L"&bk=");
	wcscat(aRequest, aBK);
	wcscat(aRequest, L"&pid=");
	wcscat(aRequest, aPID);
	wcscat(aRequest, L"&contextid=");
	wcscat(aRequest, aCONTEXTID);
	wcscat(aRequest, L"&redirect_uri=https://localhost:80/");
	wcscat(aRequest, L"\0");
	memset(aTempOne, 0, 2048*sizeof(wchar_t));
	memset(aTempTwo, 0, 2048);
	//WideCharToMultiByte(CP_UTF8, 0, aRequest, wcslen(aRequest), &aTempTwo[0x0], 2048, NULL, 0);
	
	
	hInetRequest = HttpOpenRequestW(hInetSession, L"POST", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest POST 2 failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Cache-Control: max-age=0", 24, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Content-Type: text/html; charset=utf-8", 39, HTTP_ADDREQ_FLAG_COALESCE);
	
	wcscat(aSendInfo, L"i13=0");
	wcscat(aSendInfo, L"&login=");
	wcscat(aSendInfo, &aLogin[0x0]);
	wcscat(aSendInfo, L"&loginfmt=");
	wcscat(aSendInfo, &aLogin[0x0]);
	wcscat(aSendInfo, L"&type=11");
	wcscat(aSendInfo, L"&LoginOptions=3");
	wcscat(aSendInfo, L"&lrt=");
	wcscat(aSendInfo, L"&lrtPartition=");
	wcscat(aSendInfo, L"&hisRegion=");
	wcscat(aSendInfo, L"&hisScaleUnit=");
	wcscat(aSendInfo, L"&passwd=");
	wcscat(aSendInfo, &aPassword[0x0]);
	wcscat(aSendInfo, L"&ps=2");
	wcscat(aSendInfo, L"&psRNGCDefaultType=");
	wcscat(aSendInfo, L"&psRNGCEntropy=");
	wcscat(aSendInfo, L"&psRNGCSLK=");
	wcscat(aSendInfo, L"&canary=");
	wcscat(aSendInfo, L"&ctx=");
	wcscat(aSendInfo, L"&hpgrequestid=");
	wcscat(aSendInfo, L"&PPFT=");
	wcscat(aSendInfo, aPPFT);
	wcscat(aSendInfo, L"&PPSX=Passport&NewUser=1&FoundMSAs=");
	wcscat(aSendInfo, L"&fspost=0&i21=0&CookieDisclosure=0");
	wcscat(aSendInfo, L"&IsFidoSupported=0&i2=1&i17=0&i18=");
	wcscat(aSendInfo, L"\0");
	memset(aTempOne, 0, 2048*sizeof(wchar_t));
	memset(aTempTwo, 0, 2048);
	
	WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);
	
	wchar_t asdccc[1024] = L"Content-Type: application/x-www-form-urlencoded";
	
	iSend = HttpSendRequestW(hInetRequest, asdccc, wcslen(asdccc), aTempTwo, strlen(aTempTwo));
	if (iSend == FALSE)	{wprintf(L"Error: iSend POST 2 failure"); DEFEXIT = 1; goto EXIT_APP; }
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	
if (iFirstLaunch == DEFFLAGNOTFIRST)
{
	///////////////////// Disassembler Access Token
	memset(aDataPageTWO, 0, 8192*sizeof(wchar_t));
	
	iSizeStrSearchVal = 0x0;
	
	memset(aDataPage, 0, 204800);
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	// потом разобраться... бред какой-то. Не удается с первого раза получить заголовок, видимо они идут каскадами
	if (iSizeStrSearchVal < 1024 ) {wprintf(L"Error: Search Access Token failure (size Query < 1024)"); DEFEXIT = 1; goto EXIT_APP;}

	lpSearchStr = strstr(aDataPage, "#access_token=");
	lpSearchStrTemp = strstr(aDataPage, "&token_type=");
	if (lpSearchStrTemp == NULL || lpSearchStr == NULL) {wprintf(L"Error: Search Access Token failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
	lpSearchStr+=14;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for (int i = 0; i < iSizeStrSearchVal; i++){aACCESSTOKEN[i] = *(lpSearchStr+i);} // not use memcpy
	//for (int i = 0; i < iSizeStrSearchVal; i++) {printf("%02X, ", aACCESSTOKEN[i]);}

	//FILE *pFile;
	//pFile = _wfopen (L"Test2.txt", L"wb");
	//fwrite(&aACCESSTOKEN[0x0], sizeof(char), iSizeStrSearchVal, pFile);
	//fclose(pFile);

	memset(aTempTwo, 0, 2048);
	memset(aDataPage, 0, 204800);
	memset(aDataPageTWO, 0, 8192*sizeof(wchar_t));
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);
	lpSearchStrTemp = NULL;
	lpSearchStr = NULL;
	
}

if (iFirstLaunch == DEFFLAGFIRST)
{	
	///////////////////// State 3
	///////////////////// Disassembler 3.1
	if (iFirstLaunch != DEFFLAGFIRST) {DEFEXIT = 1; goto EXIT_APP;}  // for fullversion
	memset(aDataPage, 0, 204800);
	bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	if (bStatusData == FALSE) {wprintf(L"Error: ReadPage POST 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	lpSearchStr = strstr(aDataPage, "mkt=RU-RU&uiflavor");
	lpSearchStrTemp = strstr(aDataPage, "\" method=");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search UIFLAVOR State 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	//lpSearchStr+=18;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aActionTemp[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;
	
	lpSearchStr = strstr(aDataPage, "id=\"ipt\" value=\"");
	lpSearchStrTemp = strstr(aDataPage, "\"><input type=\"hidden\" name=\"pprid\"");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search IPT State 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=16;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aIPT[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;
	
	lpSearchStr = strstr(aDataPage, "id=\"pprid\" value=\"");
	lpSearchStrTemp = strstr(aDataPage, "\"><input type=\"hidden\" name=\"uaid\"");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search PPRID State 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=18;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aPPRID[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;

	lpSearchStr = strstr(aDataPage, "id=\"client_id\" value=\"");
	lpSearchStrTemp = strstr(aDataPage, "\"><input type=\"hidden\" name=\"scope\"");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search ClientIDTemp State 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=22;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aClientIDTemp[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;

	lpSearchStr = strstr(aDataPage, "id=\"scope\" value=\"");
	lpSearchStrTemp = strstr(aDataPage, "\"></form>");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search ScopeTemp State 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=18;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aScopeTemp[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;
	
	memset(aDataPage, 0, 204800);
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);	
	
	///////////////////// POST 3.1

	//////////// aRequest 3 ////////////
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	wcscat(aRequest, L"/Consent/Update?");
	wcscat(aRequest, aActionTemp);
	//////////////////////////////////////////
	
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen POST 3.1 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"account.live.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession POST 3.1 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetRequest = HttpOpenRequestW(hInetSession, L"POST", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest POST 3.1 failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Cache-Control: max-age=0", 24, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);

	wcscat(aSendInfo, L"rd=localhost");
	wcscat(aSendInfo, L"&ipt=");
	wcscat(aSendInfo, aIPT);
	wcscat(aSendInfo, L"&pprid=");
	wcscat(aSendInfo, aPPRID);
	wcscat(aSendInfo, L"&uaid=");
	wcscat(aSendInfo, aUAID);
	wcscat(aSendInfo, L"&client_id=");
	wcscat(aSendInfo, aClientIDTemp);
	wcscat(aSendInfo, L"&scope=");
	wcscat(aSendInfo, aScopeTemp);
	memset(aTempTwo, 0, 2048);
	
	WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);
	
	iSend = HttpSendRequestW(hInetRequest, L"Content-Type: application/x-www-form-urlencoded", 47, aTempTwo, strlen(aTempTwo));
	if (iSend == FALSE) {wprintf(L"Error: iSend POST 3 failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
	///////////////////// Disassembler 3.2
	
	bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	if (bStatusData == FALSE) {wprintf(L"Error: ReadPage POST 3.1 failure"); DEFEXIT = 1; goto EXIT_APP; }

	lpSearchStr = strstr(aDataPage, "id=\"canary\" name=\"canary\" value=\"");
	//lpSearchStrTemp = strstr(aDataPage, "\"/>',");
	if (lpSearchStr == NULL) {wprintf(L"Error: Search CANARY POST 3.1 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=33;
	iSizeStrSearchVal = 45;
	for(int i = 0; i < iSizeStrSearchVal; i++){aCANARY[i] = *(lpSearchStr+i);} // not use memcpy
	//lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;

	///////////////////// POST 3.2
	memset(aDataPage, 0, 204800);
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);	
	
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen POST 3.2 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"account.live.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession POST 3.2 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetRequest = HttpOpenRequestW(hInetSession, L"POST", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest POST 3.2 failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Cache-Control: max-age=0", 24, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	
	wcscat(aSendInfo, L"canary=");
	wcscat(aSendInfo, aCANARY);
	wcscat(aSendInfo, L"&client_id=");
	wcscat(aSendInfo, aClientIDTemp);
	wcscat(aSendInfo, L"&scope=");
	wcscat(aSendInfo, aScopeTemp);
	wcscat(aSendInfo, L"&cscope=");
	wcscat(aSendInfo, L"&ucaccept=");
	wcscat(aSendInfo, L"Да");
	memset(aTempTwo, 0, 2048);
		
	WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);
	
	iSend = HttpSendRequestW(hInetRequest, L"Content-Type: application/x-www-form-urlencoded", 47, aTempTwo, strlen(aTempTwo));
	if (iSend == FALSE) {wprintf(L"Error: iSend POST 3.2 failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
	///////////////////// GET 3
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));

//aActionTemp = mkt=RU-RU&uiflavor=web
//&id=******
//&ru=https://login.live.com/oauth20_authorize.srf
//%3fuaid%3d[32]
//%26opid%3d[16]
//%26opidt%3d[10]

	lpSearchStrTwo = wcsstr(aActionTemp, L"%26opid%3d");
	if (lpSearchStrTwo == NULL) {wprintf(L"Error: Search opid GET 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStrTwo+=10;
	iSizeStrSearchVal = 16;
	for(int i = 0; i < iSizeStrSearchVal; i++){aOPID[i] = *(lpSearchStrTwo+i);}
	iSizeStrSearchVal = 0;

	lpSearchStrTwo = wcsstr(aActionTemp, L"%26opidt%3d");
	if (lpSearchStrTwo == NULL) {wprintf(L"Error: Search opidt GET 3 failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStrTwo+=11;
	iSizeStrSearchVal = 10;
	for(int i = 0; i < iSizeStrSearchVal; i++){aOPIDT[i] = *(lpSearchStrTwo+i);}
	iSizeStrSearchVal = 0;
	
	wcscat(aRequest, L"/oauth20_authorize.srf?");
	wcscat(aRequest, L"uaid=");
	wcscat(aRequest, aUAID);
	wcscat(aRequest, L"&opid=");
	wcscat(aRequest, aOPID);
	wcscat(aRequest, L"&opidt=");
	wcscat(aRequest, aOPIDT);
	wcscat(aRequest, L"&res=success");
	
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen GET 3 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"login.live.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession GET 3 failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest GET 3 failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Cache-Control: max-age=0", 24, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	
	iSend = HttpSendRequestW(hInetRequest, L"Content-Type: application/x-www-form-urlencoded", 47, NULL, 0);
	if (iSend == FALSE) {wprintf(L"Error: iSend GET 3 failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
		///////////////////////////////////////////////////////////////
	///////////////////// Disassembler Access Token /////////////////////
		///////////////////////////////////////////////////////////////
	memset(aDataPage, 0, 204800);
	iSizeStrSearchVal = 0x0;
	
	memset(aDataPage, 0, 204800);
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	// потом разобраться... бред какой-то. Не удается с первого раза получить заголовок, видимо они идут каскадами
	if (iSizeStrSearchVal < 1024 ) {wprintf(L"Error: Search Access Token failure (size Query < 1024)"); DEFEXIT = 1; goto EXIT_APP;}

	lpSearchStr = strstr(aDataPage, "#access_token=");
	lpSearchStrTemp = strstr(aDataPage, "&token_type=");
	if (lpSearchStrTemp == NULL || lpSearchStr == NULL) {wprintf(L"Error: Search Access Token failure"); DEFEXIT = 1; goto EXIT_APP; }	
	
	lpSearchStr+=14;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for (int i = 0; i < iSizeStrSearchVal; i++){aACCESSTOKEN[i] = *(lpSearchStr+i);} // not use memcpy

	memset(aTempTwo, 0, 2048);
	memset(aDataPage, 0, 204800);
	memset(aDataPageTWO, 0, 8192*sizeof(wchar_t));
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);
	lpSearchStrTemp = NULL;
	lpSearchStr = NULL;
}



if (iFlagSend == DEFFLAGGET)
{
	//wprintf(L"Get start");
	wcscat(aRequest, L"/v1.0/me/drive/root:/");
	wcscat(aRequest, aNameSrc);
	wcscat(aRequest, L":/content");
	
	//drive/root:/path/to/file
/*
HTTP/1.1 302 Found
Cache-Control: private
Content-Type: text/plain
Location: https://public.dm.files.1drv.com/*************
request-id: 
*/

	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"graph.microsoft.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}

	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest GET FILE failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	wcscat(aSendInfo, L"Authorization: Bearer ");
	wcscat(aSendInfo, aACCESSTOKEN);
	wcscat(aSendInfo, L"\0");
	
	HttpAddRequestHeadersW(hInetRequest, aSendInfo, wcslen(aSendInfo), HTTP_ADDREQ_FLAG_COALESCE);
	
	//wcscat(aSendInfo, L"Authorization: Bearer =");
	//wcscat(aSendInfo, aACCESSTOKEN);
	//wcscat(aSendInfo, L"\0");
	//memset(aTempTwo, 0, 2048);
	 
	//WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);
	
	wchar_t asdccc[1024] = L"Content-Type: application/x-www-form-urlencoded";
	//aTempTwo, strlen(aTempTwo)
	iSend = HttpSendRequestW(hInetRequest, asdccc, wcslen(asdccc), NULL, 0);
	if (iSend == FALSE)	{wprintf(L"Error: iSend GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	//memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	
	// Get file
	
	//bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	//if (bStatusData == FALSE) {wprintf(L"Error: ReadPage Get File failure"); DEFEXIT = 1; goto EXIT_APP; }
	HttpQueryInfoW(hInetRequest, HTTP_QUERY_RAW_HEADERS_CRLF, aDataPage, &iSizeStrSearchVal, NULL);
	//for (int i = 0; i < iSizeStrSearchVal; i++) {printf("%02X, ", aDataPage[i]);}
	
	
		
	lpSearchStr = strstr(aDataPage, "Location:");
	lpSearchStrTemp = strstr(aDataPage, "request-id:");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search Location Get File failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=10;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	for(int i = 0; i < iSizeStrSearchVal; i++){aLocation[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;
	
	
	wcscat(aRequest, L"/v1.0/me/drive/root:/");
	wcscat(aRequest, aNameSrc);
	wcscat(aRequest, L"?select=size");
	
	InternetCloseHandle(hInetRequest);
	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest GET FILE failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	wcscat(aSendInfo, L"Authorization: Bearer ");
	wcscat(aSendInfo, aACCESSTOKEN);
	wcscat(aSendInfo, L"\0");
	
	HttpAddRequestHeadersW(hInetRequest, aSendInfo, wcslen(aSendInfo), HTTP_ADDREQ_FLAG_COALESCE);
	
	iSend = HttpSendRequestW(hInetRequest, asdccc, wcslen(asdccc), NULL, 0);
	if (iSend == FALSE)	{wprintf(L"Error: iSend GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	
	bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	if (bStatusData == FALSE) {wprintf(L"Error: ReadPage GET 1 failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	//for (int iConvertCount = 0; iConvertCount < iDataPage; iConvertCount++) {aDataPage[iConvertCount] = ntohs(aDataPage[iConvertCount]);} // UTF16LE->UTF16BE	 // отставить на будующие преобразования
	
	lpSearchStr = strstr(aDataPage, "\"size\":");
	if (lpSearchStr == NULL) {wprintf(L"Error: Search size file failure"); DEFEXIT = 1; goto EXIT_APP; }
	//lpSearchStrTemp = strstr(lpSearchStr, "}");
	lpSearchStr+=7;
	// size	Int64	Размер элемента (в байтах). Только для чтения.
	// Int64 -- (-9,223,372,036,854,775,808 to +9,223,372,036,854,775,807).
	// 1 073 741 824
	// 9,223,372,036,854,775,80
	//
	char aSizeFileIn [20];
	memset(aSizeFileIn, 0, 20);
	
	for(int i = 0; i < 20; i++)
	{
		if (isdigit (*(lpSearchStr+i)))
		{
			aSizeFileIn[i] = *(lpSearchStr+i);
		}
	}
	unsigned long long int iSizeGet = strtoull(aSizeFileIn, NULL, 0);
	//wprintf(L"\r\n size = %i\r\n", iSizeGet);	
	//for(int i = 0; i < 20; i++) {wprintf(L"%02X", aSizeFileIn[i]);}	
	
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);
		
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"public.dm.files.1drv.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}

	hInetRequest = HttpOpenRequestW(hInetSession, L"GET", &aLocation[33], NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest GET FILE failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	
	//wcscat(aSendInfo, L"Authorization: Bearer =");
	//wcscat(aSendInfo, aACCESSTOKEN);
	//wcscat(aSendInfo, L"\0");
	//memset(aTempTwo, 0, 2048);
	 
	//WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);
	
	//wchar_t asdccc[1024] = L"Content-Type: application/x-www-form-urlencoded";
	//aTempTwo, strlen(aTempTwo)
	iSend = HttpSendRequestW(hInetRequest, asdccc, wcslen(asdccc), NULL, 0);
	if (iSend == FALSE)	{wprintf(L"Error: iSend GET FILE failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	vector <char> aDataGet;
	aDataGet.resize(iSizeGet);
	memset(&aDataGet[0x0], 0, iSizeGet);
	
	
	bStatusData = InternetReadFile(hInetRequest, &aDataGet[0x0], iSizeGet, &iDataPage);
	if (iSizeGet != iDataPage) {wprintf(L"Error: size get file not eq size in onedrive"); DEFEXIT = 1; goto EXIT_APP; }
	if (bStatusData == FALSE) {wprintf(L"Error: GET file failure"); DEFEXIT = 1; goto EXIT_APP; }
	//for (int i = 0; i < 50; i++) {printf("%02X, ", aDataGet[i]);}
	
	FILE *pFile;
	//pFile = _wfopen (aNameDst, L"wb");
	pFile = _wfopen (aNameDst, L"wb");
	fwrite(&aDataGet[0x0], sizeof(char), iSizeGet, pFile);
	fclose(pFile);

	
memset(aTempTwo, 0, 2048);
memset(aDataPage, 0, 204800);
memset(aDataPageTWO, 0, 8192*sizeof(wchar_t));
memset(aRequest, 0, 1024*sizeof(wchar_t));
memset(aSendInfo, 0, 1024*sizeof(wchar_t));
InternetCloseHandle(hInetSession);
InternetCloseHandle(hInetRequest);
InternetCloseHandle(hInitInetOpen);
lpSearchStrTemp = NULL;
lpSearchStr = NULL;

}

if (iFlagSend == DEFFLAGPUT)
{
	wcscat(aRequest, L"/v1.0/me/drive/root:/");
	wcscat(aRequest, aNameDst);
	wcscat(aRequest, L":/createUploadSession");

	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"graph.microsoft.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}

	hInetRequest = HttpOpenRequestW(hInetSession, L"POST", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest POST FILE failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	wcscat(aSendInfo, L"Authorization: Bearer ");
	wcscat(aSendInfo, aACCESSTOKEN);
	wcscat(aSendInfo, L"\0");
	
	HttpAddRequestHeadersW(hInetRequest, aSendInfo, wcslen(aSendInfo), HTTP_ADDREQ_FLAG_COALESCE);
	
	//wcscat(aSendInfo, L"Authorization: Bearer =");
	//wcscat(aSendInfo, aACCESSTOKEN);
	//wcscat(aSendInfo, L"\0");
	//memset(aTempTwo, 0, 2048);
	 
	//WideCharToMultiByte(CP_UTF8, 0, aSendInfo, wcslen(aSendInfo), &aTempTwo[0x0], 2048, NULL, 0);
	
	wchar_t asdccc[1024] = L"Content-Type: application/x-www-form-urlencoded";
	//aTempTwo, strlen(aTempTwo)
	iSend = HttpSendRequestW(hInetRequest, asdccc, wcslen(asdccc), NULL, 0);
	if (iSend == FALSE)	{wprintf(L"Error: iSend POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	//memset(aSendInfo, 0, 1024*sizeof(wchar_t));
	memset(aRequest, 0, 1024*sizeof(wchar_t));
	memset(aDataPage, 0, 204800);
	
	bStatusData = InternetReadFile(hInetRequest, aDataPage, sizeof(aDataPage), &iDataPage);
	if (bStatusData == FALSE) {wprintf(L"Error: ReadPage POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	wchar_t aUploadURL [2048];
	memset(aUploadURL, 0, 2048*sizeof(wchar_t));
	
	lpSearchStr = strstr(aDataPage, "/rup/");
	lpSearchStrTemp = strstr(lpSearchStr, "\"}");
	if (lpSearchStr == NULL || lpSearchStrTemp == NULL) {wprintf(L"Error: Search uploadUrl failure"); DEFEXIT = 1; goto EXIT_APP; }
	lpSearchStr+=5;
	iSizeStrSearchVal = lpSearchStrTemp - lpSearchStr;
	if (iSizeStrSearchVal <= 0) {wprintf(L"Error: Size uploadUrl < 0 "); DEFEXIT = 1; goto EXIT_APP; }
	for(int i = 0; i < iSizeStrSearchVal; i++){aUploadURL[i] = *(lpSearchStr+i);} // not use memcpy
	lpSearchStrTemp = NULL;
	iSizeStrSearchVal = 0;
	memset(aDataPage, 0, 204800);
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);

	wcscat(aRequest, L"/rup/");
	wcscat(aRequest, aUploadURL);
	
	hInitInetOpen = InternetOpenW(aBrouser, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInitInetOpen == NULL) {wprintf(L"Error: InitInetOpen POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}
	
	hInetSession = InternetConnectW(hInitInetOpen, L"api.onedrive.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hInetSession == NULL) {wprintf(L"Error: InetSession POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; } else {}

	hInetRequest = HttpOpenRequestW(hInetSession, L"PUT", aRequest, NULL, NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_AUTO_REDIRECT, 0);
	if (hInetRequest == NULL){wprintf(L"Error: InetRequest POST FILE failure");	DEFEXIT = 1; goto EXIT_APP; }
	
	//HttpAddRequestHeadersW(hInetRequest, L"Upgrade-Insecure-Requests: 1", 28, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"X-Content-Type-Options: nosniff", 31, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Accept-Language: ru-RU", 22, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Expect: 100-continue", 20, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Content-Transfer-Encoding: Binary", 33, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", 71, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Content-Type: application/json", 30, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Content-Type: text/html; charset=utf-8", 38, HTTP_ADDREQ_FLAG_COALESCE);
	HttpAddRequestHeadersW(hInetRequest, L"Content-Type: application/octet-stream", 38, HTTP_ADDREQ_FLAG_COALESCE);
	//HttpAddRequestHeadersW(hInetRequest, L"Content-Disposition: form-data; name=\"description\"", 50, HTTP_ADDREQ_FLAG_COALESCE);
	
//PUT https://sn3302.up.1drv.com/up/fe6987415ace7X4e1eF866337
//Content-Length: 26
//Content-Range: bytes 0-25/128
//<bytes 0-25 of the file>
/*PUT /rup/https://api.onedrive.com/rup/be81409d42269813/eyJSZXNvdXJjZUlEIjoiQkU4MTQwOUQ0MjI2OTgxMyExMDEiLCJSZWxhdGlvbnNoaXBOYW1lIjoiMi5qcGcifQ/4mli1wikajOnxAoQEA5aHgA9CDEaYzAlgDWydvIYgDkESKdbUttPwnQ2BScF6UPiV9hUzUxHyoGekQlcTtVZlkmmZxkAd-JJQMO3emYzGGDQo/eyJuYW1lIjoiMi5qcGciLCJAbmFtZS5jb25mbGljdEJlaGF2aW9yIjoicmVwbGFjZSJ9/4wOwZXckjMPWpqvGR4hs6cythsJWwsirz1xfnyfziXWvq_4_jBU5VrC_mbHYbB7cz2Br84lt8Cv5RnByHWv8xMKjzL8oTvcXflI2lkD_KtYkMY7m8AStduFWL6DgPi_676pL1sPS3SYjDD56y_sDLJqYOZmwsPj1eGsBQ6o-PYUOO57zAExEIuj2l2g9vOqczXQPdyq-VxIi0bptV7G9b5NWYhnDSURjApfyqqSvPiYUMqvOXKHxGAMotIhyM7rFyeUtDTovxs-h-wcgNrOQEiigwtXQ-WincgQrYxK77ykEH_6Biji37bVXXH_3CJpeF9WTXsL9qewZcwKQV371Mr2uzdAagh-UBXJygg9gTwESXFUM_3mXC4p4dRIgon46eGgcoJ97owKznMuuxw7VZz5EZy3C0EHG73jfcq0NcL8WI-3USVm40gn2pLE76fx7dwkewLhvDx77uAZ2Gks5BFzUQW8pR1XfrRlUgAN0yXlvMXx5VMkZwLnK1X4Lfu55rGDVjExUik1hEslsnmprnERnWeMe15oCQ93lTxdH7uDw8PVQgMY2bGpE6WU3AmXjMR HTTP/1.1*/
	
	
	// 10 mb = 10485760 b
	int iFragment = 0;
	long int iFragmentDiv = 0;
	unsigned long int iSizeFragment = 10485760;
	
	//wprintf(L"Error: iSizeFragment = %i", iSizeFragment);
	
	FILE *pFile = NULL;
	//pFile = _wfopen (aNameSrc, L"rb");
	pFile = _wfopen (aNameSrc, L"rb");
	if (pFile == NULL) {fclose(pFile); wprintf(L"Error: read file failure");DEFEXIT = 1; goto EXIT_APP; }
	
	fseek(pFile, 0, SEEK_END);
	long long int iNumberReadByte = ftell(pFile);
	if (iNumberReadByte == -1L) {fclose(pFile); wprintf(L"Error: read file failure (size null)");DEFEXIT = 1; goto EXIT_APP;}
	
	//wprintf(L"Error: iNumberReadByte = %i", iNumberReadByte);
	
	if ( (iNumberReadByte > 1073741824) || (iNumberReadByte <= 0) ) {fclose(pFile); wprintf(L"Error: read file failure (size > 1 073 741 824) "); DEFEXIT = 1; goto EXIT_APP;}
	fseek(pFile, 0, SEEK_SET);
	
	iFragment = iNumberReadByte / iSizeFragment;
	if (iFragment > 0) {iFragmentDiv = iNumberReadByte - iSizeFragment*iFragment;}
	
	vector <char> aDataGet;
	aDataGet.resize(iSizeFragment+1);
	memset(&aDataGet[0x0], 0, iSizeFragment+1);
	
	//wprintf(L"Error: iFragment = %i", iFragment);
	char aTemp[20];
	memset(aTemp, 0, 20);
	const char *lpPointer = &aTemp[0x0];
	wchar_t iHeader [100];
	memset(iHeader, 0, 100*sizeof(wchar_t));	
	wchar_t iHeader2 [100];
	memset(iHeader2, 0, 100*sizeof(wchar_t));
	wchar_t aValTell [20];
	memset(aValTell, 0, 20*sizeof(wchar_t));
	mbstate_t mbs;
	
	vector <wchar_t> aTempThree;
	aTempThree.resize(iSizeFragment+1);
	//wchar_t aTempThree [iSizeFragment];
	//memset (aTempThree, 0, iSizeFragment);
	
	for (; iFragment >= 0; iFragment--)
	{
	
	unsigned long long int iNextSize = 0;
	if (iFragment == 0) 
	{
		if (iFragmentDiv != 0) {iNextSize = iFragmentDiv;} else {iNextSize = iNumberReadByte;}
	}
	if (iFragment > 0) {iNextSize = iSizeFragment;}
	
	long long int iPrevftell = 0;
	long long int iNextftell = 0;
	//wprintf(L"\r\niPrevftell = %i",  iPrevftell);
	//wprintf(L"\r\niNextftell = %i",  iNextftell);
	aDataGet.clear();
	iPrevftell = ftell(pFile);	
	fread(&aDataGet[0], sizeof(char), iNextSize, pFile);
	//fseek(pFile, iNextSize, SEEK_CUR);
	iNextftell = ftell(pFile);
	//wprintf(L"\r\n %i \r\n", iFragment);
	//wprintf(L"\r\niPrevftell = %i",  iPrevftell);
	//wprintf(L"\r\niNextftell = %i",  iNextftell);
	
	memset(iHeader, 0, 100*sizeof(wchar_t));
	wcscat(iHeader, L"Content-Range:");
	wcscat(iHeader, L" bytes ");
	
	memset (&mbs, 0, sizeof(mbstate_t));
	memset(aTemp, 0, 20);
	memset(aValTell, 0, 20*sizeof(wchar_t));
	lpPointer = &aTemp[0x0];
	itoa(iPrevftell, aTemp, 10);
	mbsrtowcs (aValTell, &lpPointer, sizeof(long long int), NULL);
	
	if (iPrevftell != 0) {wcscat(iHeader, aValTell);} else {wcscat(iHeader, L"0");}
	wcscat(iHeader, L"-");
	
	memset (&mbs, 0, sizeof(mbstate_t));
	memset(aValTell, 0, 20*sizeof(wchar_t));
	memset(aTemp, 0, 20);
	itoa((iNextftell-1), aTemp, 10);
	lpPointer = &aTemp[0x0];
	//wprintf(L"\r\n \r\n");
	//for(int i = 0; i < 20; i++){wprintf(L"%02X, ",  aTemp[i]);}
	mbsrtowcs (aValTell, &lpPointer, sizeof(long long int), NULL);
	//wprintf(L"\r\n strlen = %i \r\n", strlen(aTemp));
	//wprintf(L"\r\n \r\n");
	//for(int i = 0; i < 20; i++){wprintf(L"%02X, ",  aValTell[i]);}

	
	wcscat(iHeader, aValTell);
	wcscat(iHeader, L"/");
	
	memset (&mbs, 0, sizeof(mbstate_t));
	memset(aValTell, 0, 20*sizeof(wchar_t));
	memset(aTemp, 0, 20);
	itoa(iNumberReadByte, aTemp, 10);
	lpPointer = &aTemp[0x0];
	mbsrtowcs (aValTell, &lpPointer, sizeof(long long int), NULL);
	wcscat(iHeader, aValTell);
	//wprintf(L"\r\n");
	//for(int i = 0; i < 100; i++){wprintf(L"%02X, ",  iHeader[i]);}
	//memset(aTempTwo, 0, 2048);
	//WideCharToMultiByte(CP_UTF8, 0, aValTell, wcslen(aValTell), &aTempTwo[0x0], 2048, NULL, 0);
	
	HttpAddRequestHeadersW(hInetRequest, iHeader, wcslen(iHeader), HTTP_ADDREQ_FLAG_REPLACE);
	
	memset(iHeader, 0, 100*sizeof(wchar_t));
	memset (&mbs, 0, sizeof(mbstate_t));
	memset(aValTell, 0, 20*sizeof(wchar_t));
	memset(aTemp, 0, 20);
	itoa(iNextSize, aTemp, 10);
	lpPointer = &aTemp[0x0];
	mbsrtowcs (aValTell, &lpPointer, sizeof(long long int), NULL);
	wcscat(iHeader, L"Content-Length:");
	wcscat(iHeader, L" ");
	wcscat(iHeader, aValTell);
	//wprintf(L"\r\n");
	//for(int i = 0; i < 100; i++){wprintf(L"%02X, ",  iHeader[i]);}
	HttpAddRequestHeadersW(hInetRequest, iHeader, wcslen(iHeader), HTTP_ADDREQ_FLAG_REPLACE);
	//HttpAddRequestHeadersW(hInetRequest, L"Content-Type: application/octet-stream", 38, HTTP_ADDREQ_FLAG_REPLACE);
	
	//wprintf(L"\r\n");
	//for (int i = 0; i < 50; i++) {wprintf(L"%02X, ",  aDataGet[i]);}
	//wprintf(L"\r\n");
	
	
	//aTempThree.clear();
	//memset (aTempThree, 0, iSizeFragment);
	//MultiByteToWideChar (CP_UTF8, 0, &aDataGet[0], iNextSize, &aTempThree[0x0], iSizeFragment);
	
	//wprintf(L"\r\n");
	//for (int i = 0; i < 50; i++) {wprintf(L"%02X, ",  aTempThree[i]);}
	//wprintf(L"\r\n");
	
	//HttpAddRequestHeadersW(hInetRequest, &aTempThree[0x0], iNextSize*2, HTTP_ADDREQ_FLAG_COALESCE);
	
	//Content-Range: bytes 0-25/128
	//Content-Length: 26 
	//wcscat(aSendInfo, L"Authorization: Bearer ");
	//wcscat(aSendInfo, aACCESSTOKEN);
	//wcscat(aSendInfo, L"\0");
	
//	HttpAddRequestHeadersW(hInetRequest, aSendInfo, wcslen(aSendInfo), HTTP_ADDREQ_FLAG_COALESCE);
	
	//wcscat(aSendInfo, L"Authorization: Bearer =");
	//wcscat(aSendInfo, aACCESSTOKEN);
	//wcscat(aSendInfo, L"\0");
	//memset(aTempTwo, 0, 2048);
	 
	//
	
	//wchar_t asdccc[1024] = L"";//L"Content-Type: application/x-www-form-urlencoded";
	//wchar_t asdccc[1024] = L"Content-Type: text/html; charset=utf-8";//L"Content-Type: application/x-www-form-urlencoded";
	//wchar_t asdccc[1024] = L"Content-Type: application/octet-stream";//L"Content-Type: application/x-www-form-urlencoded";
	//aTempTwo, strlen(aTempTwo)
	//DWORD val;
	//Content-Range: bytes 0-220737/220737
	
	
	iSend = HttpSendRequestW(hInetRequest, NULL, 00, &aDataGet[0], iNextSize);
	//iSend = HttpSendRequestW(hInetRequest, iHeader, wcslen(iHeader), &aDataGet[0], iNextSize);
	//InternetWriteFile(hInetRequest, &aDataGet[0x0], iNextSize, &val);
	
	
	//INTERNET_BUFFERSW InetBufferInfo;
	//InetBufferInfo.dwStructSize = sizeof(INTERNET_BUFFERSW);
	//InetBufferInfo.Next->lpcszHeader = NULL;
	//InetBufferInfo.Next->dwHeadersLength = 0;
	//InetBufferInfo.Next->dwHeadersTotal = 0;
	//InetBufferInfo.Next->lpvBuffer = &aDataGet[0x0];
	//InetBufferInfo.Next->dwBufferLength = iNextSize;
	//InetBufferInfo.Next->dwBufferTotal = iNextSize;
	//InetBufferInfo.Next->dwOffsetLow = 0;
	//InetBufferInfo.Next->dwOffsetHigh = 0;

	//InternetWriteFile(hInetRequest, &aDataGet[0x0], iNextSize, &val);
	//iSend = HttpSendRequestExW(hInetRequest, &InetBufferInfo, NULL, 0, 0);
	if (iSend == FALSE)	{wprintf(L"Error: iSend POST FILE failure"); DEFEXIT = 1; goto EXIT_APP; }
	
	}
	
	fclose(pFile);
	memset(&aDataGet[0x0], 0, iSizeFragment+1);	

/*
{"@odata.context":"https://graph.microsoft.com/v1.0/$metadata#microsoft.graph.uploadSession","expirationDateTime":"2019-06-17T02:13:56.234Z","nextExpectedRanges":["0-"],
"uploadUrl":"https://api.onedrive.com/rup/be81409d42269813/eyJSZXNvdXJ
jZUlEIjoiQkU4MTQwOUQ0MjI2OTgxMyExMDEiLCJSZWxhdGlvbnNoaXBOYW1lIjoiMi5qcGcifQ/4mLcwrRsfwLlBd9hPXHom8gYdpI4f1akowz54gmxmzwXe5GIdDyNEOYcSNvjzWtrYyyCpwl3s8YK4mqxOuFEth4bYIiMRVbLNP8-yNviafpc8/eyJuYW1lIjoiMi5qcGciLCJAbmFtZS5jb25mbGljdEJlaGF2aW9yIjoicmVwbGFjZSJ9/4wqtDuJyQE6Z5ZqD8fJlSNIxOn_Olw01DJWL_JEatMB8818kPyo7uvdyPrMHNYAF_04VrQECzhEw_UMNLu_HIIi6hsWKUP45khDGVftXq7QN6P8pVvQ7f3LqNv7W3s8XJ3ic8WvFNGSJ4E8WdHOuz96xgEtsKntgKcVMUczLy02jzx1e2Kd4isBjcsFT8dht2qwisMXmrqR0rUh1aloEqmZr2soE8YuofdtjCZBg4ePuH8jmcFiLrjv72xS_HpuvoddwjpGj8lK6ZmfhHLrSFtQtuH482NkkLlOeenGb7TRDQ9CFcTk0nGzMGcLw7Bpi-gXyRMIxnq7Ohs9L618hcVwcQD0i8MvDGIom2fZk6FAlb9u83Xjr_A6LEBt7Ue4iwiT1129BBEl9Yk8KhsK_rARiFaYNqJ-orQMPvlGDxAc-9nNBpFlsD0VU1Uyi7xOdNDE0LxsirsHPiYR5HQ_Suxy-hBmpwARNSalETFEQjf3o4nLeR7tCgGOU9GIa34bT3RlSIrFOTH1A8cncPRmxAuWXJxpHlIf1cRr5QyVK0HfR3G0fsmypajPLIXbYXCKSHS"}
*/
	
	InternetCloseHandle(hInetSession);
	InternetCloseHandle(hInetRequest);
	InternetCloseHandle(hInitInetOpen);
}

	DEFEXIT = 1; goto EXIT_APP;
	return 0;
}