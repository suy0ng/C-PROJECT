#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <wchar.h>

#pragma warning(disable : 6031)
#pragma warning(disable : 4996)

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

char schedule[4000][12][31][500] = { 0 };

char schedule_temp[4000][12][31][500] = { 0 };

FILE* fpp = NULL;
FILE* fps = NULL;



int i, j, k; //i = for문 돌리기용, j = for문 돌리기용2

int year_temp = 0, month_temp = 0, day_temp = 0; // 파일 포인터에 쓸거

void CursorView();

void gotoxy(int x, int y);

void draw_start_Calendar();

void draw_Calendar();

void view_month_Schedule(int year, int month, int s_day);

void add_Schedule(int year, int month, int day);

void Remove_Schedule(int year, int month, int day);

void Edit_Schedule(int year, int month, int day);

void Daily_Schedule(int year, int month, int day);

int main()
{

	fps = fopen("pile.txt", "rt");
	if (fps == NULL) {
		printf(" ");
	}
	else {
		while (feof(fps) == 0) {
			fscanf(fps, "%d.%d.%d : ", &year_temp, &month_temp, &day_temp);
			fscanf(fps, "%[^\n]", schedule[year_temp][month_temp][day_temp]);
		}
		fclose(fps);
	}




	CursorView();
	system("mode con cols=115 lines=46");
	draw_start_Calendar(); //달력의 첫화면 출력
	draw_Calendar(); //달력출력
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y)
{
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw_start_Calendar()
{
	CursorView();
	time_t timer;
	struct tm* t;
	timer = time(NULL); // 1970년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초
	t = localtime(&timer); // 포맷팅을 위해 구조체에 넣기
	int year = t->tm_year + 1900;

	printf("\n\n\n"); //한칸 뛰어쓰기
	printf("    "); // 빈칸 출력
	for (int i = 0; i < 59; i++) //'='출력 
		printf("=");
	for (int i = 0; i < 14; i++) // 줄바꿈 14번
		printf("\n");
	for (int j = 0; j < 24; j++) //빈칸 출력
		printf(" ");
	printf("  %d ", year); //연도 출력 
	printf("CALENDAR"); //캘린더 출력 
	printf("\n"); //줄바꿈
	for (int i = 0; i < 14; i++) //14번 줄바꿈
		printf("\n");
	printf("    "); //빈 칸 출력
	for (int i = 0; i < 59; i++) //'='출력 
		printf("=");
	gotoxy(33, 5); printf("  일정의 글자 수가 특정 숫자를 넘어 가면 ");
	gotoxy(33, 6); printf("  글자가 자동으로 잘립니다.              ");
	gotoxy(33, 7); printf("                                         ");
	gotoxy(33, 8); printf("  특정 숫자 : 약 220, 한글은 두 글자 판정");
	gotoxy(35, 20); printf("       아무 키나 누르면 시작            ");
	getch();
	system("cls"); //화면 삭제
}

void add_Schedule(int year, int month, int day)
{
	char add_answer[100]; //실행을 할 수 있게 하는 변수 선언
	gotoxy(2, 33); // 출력 이동


	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성
	printf("\n");
	printf("\n     일정을 추가하시겠습니까? ( Y / N ) : "); // 일정 추가 여부 출력
	scanf("%s", add_answer); //add_answer에 대답 저장
	printf("\n    "); //4칸 띄어 쓰기
	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성
	printf("\n");


	//일정을 추가하지 않는다 했을 때
	if (add_answer[0] == 'n' || add_answer[0] == 'N')
	{
		printf("\n     입력창을 종료합니다. \n"); //입력창 종료 전 안내문 출력
		Sleep(500);
		system("cls"); //화면 지우기
		add_answer[0] = NULL;
	}

	//일정을 추가한다 했을 때
	else if (add_answer[0] == 'y' || add_answer[0] == 'Y')
	{
		if (schedule[year][month][day][0] != 0)
		{
			printf("\n    %d년 %d월 %d일에는 이미 일정이 있습니다. 일정을 추가할 수 없습니다.\n", year, month, day);
			Sleep(500); //0.5초 대기
			printf("\n    입력창을 종료합니다. \n"); //입력창 종료 전 안내문 출력
			Sleep(2000); // 2초 대기
			system("cls"); //콘솔화면 초기화
			add_answer[0] = NULL;
			return 0;
		}

		printf("\n     %d년 %d월 %d일의 일정을 추가해주세요! : ", year, month, day); //일정을 추가할수있게하는 문장을 출력한다.
		scanf(" %[^\n]", schedule[year][month][day]); //일정을 입력받습니다



		fpp = fopen("pile.txt", "at");

		if (fpp == NULL) {
			return 0;
		}

		fprintf(fpp, "\n%d.%d.%d : %s", year, month, day, schedule[year][month][day]);

		fclose(fpp);



		printf("\n     일정을 추가하겠습니다.\n"); //일정을 추가하겠다는 안내문 출력
		Sleep(500); //0.5초 대기
		printf("\n     입력창을 종료합니다. \n"); //입력창 종료 전 안내문 출력
		Sleep(1500); // 1.5초 대기
		system("cls"); //콘솔화면 초기화
		add_answer[0] = NULL;
		return 0;
	}

	else // y 또는 n 이 아닌 문자를 입력했을경우
	{
		printf("\n     입력창을 종료합니다. 입력창을 다시 실행시켜주십시오. \n"); //입력창을 종료시킨다고 안내문을 출력한다
		Sleep(500); //0.5초 대기
		printf("\n     입력창을 종료합니다. \n"); //입력창 종료 전 안내문 출력
		Sleep(500); //0.5초 대기
		system("cls");
		add_answer[0] = NULL;
		return 0;
	}

}

void Edit_Schedule(int year, int month, int day)
{
	char Edit_Schedule[100];

	gotoxy(2, 33);
	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성
	printf("\n");

	gotoxy(2, 43);
	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성

	gotoxy(2, 33);

	printf("\n\n     %d년 %d월 %d일을 수정하겠습니까 ( Y / N ) : ", year, month, day);
	scanf("%s", Edit_Schedule);

	if ((Edit_Schedule[0] == 'Y' || Edit_Schedule[0] == 'y') && schedule[year][month][day] != NULL)
	{
		if (schedule[year][month][day][0] == 0)
		{
			Sleep(300);
			printf("\n     일정이 존재하지 않습니다. 추가되지 않은 일정은 수정할 수 없습니다\n");
			Sleep(700);
			system("cls");
			return 0;
		}
		else {
			Sleep(300);
			printf("\n     일정을 수정하겠습니다. 수정된 일정은 복구할 수 없습니다.\n");
			Sleep(700);
			schedule[year][month][day] == NULL;
			printf("\n     %d년 %d월 %d일의 일정을 수정해주세요 : ", year, month, day);
			scanf(" %[^\n]", schedule[year][month][day]);





			fps = fopen("pile.txt", "rt");

			fpp = fopen("temp.txt", "at");
			while (feof(fps) == 0) {


				fscanf(fps, "%d.%d.%d : ", &year_temp, &month_temp, &day_temp);
				fscanf(fps, "%[^\n]", schedule_temp[year_temp][month_temp][day_temp]);


				if (year != year_temp || month != month_temp || day != day_temp) {

					fprintf(fpp, "\n%d.%d.%d : %s", year_temp, month_temp, day_temp, schedule_temp[year_temp][month_temp][day_temp]);

				}

				else
					fprintf(fpp, "\n%d.%d.%d : %s", year, month, day, schedule[year][month][day]);


			}

			fclose(fps);

			fclose(fpp);

			remove("pile.txt");

			rename("temp.txt", "pile.txt");





			Sleep(500);
			printf("\n     일정을 수정하였습니다. 수정된 일정은 복구할 수 없습니다.\n");
			system("cls");
			return 0;
		}

	}
	else {
		Sleep(300);
		printf("\n     일정을 수정하지 않고 입력창을 종료합니다. \n");
		Sleep(700);
		system("cls");
		return 0;
	}
}

void Remove_Schedule(int year, int month, int day)
{
	char Remove_Schedule_Y_N[100];

	gotoxy(2, 33);
	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성
	printf("\n");

	gotoxy(2, 43);
	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성

	gotoxy(2, 33);

	printf("\n\n     일정을 삭제하면 삭제된 일정을 복구하거나 다시 확인할 수 없습니다.\n");
	Sleep(500);
	printf("\n     %d년 %d월 %d일의 일정을 정말로 삭제하시겠습니까 ( Y / N ) :", year, month, day);
	scanf("%s", Remove_Schedule_Y_N);

	if (Remove_Schedule_Y_N[0] == 'Y' || Remove_Schedule_Y_N[0] == 'y')
	{
		if (schedule[year][month][day][0] == 0)
		{
			Sleep(500);
			printf("\n     삭제할 수 있는 일정이 존재하지 않습니다. 입력창을 종료합니다.\n");
			Sleep(500);
			schedule[year][month][day][0] = 0;
			system("cls");
			return 0;
		}
		else
		{
			Sleep(500);
			printf("\n     일정을 삭제하겠습니다. 삭제된 일정은 복구할 수 없습니다.\n");
			Sleep(500);
			schedule[year][month][day][0] = 0;




			fps = fopen("pile.txt", "rt");

			fpp = fopen("temp.txt", "at");
			do {


				fscanf(fps, "%d.%d.%d : ", &year_temp, &month_temp, &day_temp);
				fscanf(fps, "%[^\n]", schedule_temp[year_temp][month_temp][day_temp]);


				if (year != year_temp || month != month_temp || day != day_temp) {

					fprintf(fpp, "\n%d.%d.%d : %s", year_temp, month_temp, day_temp, schedule_temp[year_temp][month_temp][day_temp]);

				}
			} while (feof(fps) == 0);

			fclose(fps);

			fclose(fpp);

			remove("pile.txt");

			rename("temp.txt", "pile.txt");





			system("cls");
			return 0;
		}
	}

	else {
		Sleep(500);
		printf("\n     일정을 삭제하지 않고 입력창을 종료합니다. \n");
		Sleep(500);
		system("cls");
		return 0;
	}
}

void view_month_Schedule(int year, int month, int s_day)
{
	int Not_Schedule = 0, nokorean = 0, enter_condition = 0, bundle = 0;
	char EXIT = NULL;

	gotoxy(2, 33);
	for (i = 0; i < 100; i++) printf("="); // 분리선 생성
	printf("\n");

	for (int day = 1; day <= 31; day += j)  //일정이 있는 날 찾기
	{
		if (schedule[year][month][day][0] != NULL) //일정이 비어있지않는다면
		{
			if (Not_Schedule < 6) //최대 6개 출력가능
			{
				nokorean = 0;
				enter_condition = 0;
				for (j = 1; j < 30 - day; j++) {
					bundle = strcmp(schedule[year][month][day], schedule[year][month][day + j]);
					if (bundle != 0) {
						break;
					}
				}
				if (j == 1)
					printf("\n\t   %d 일 : ", day);
				else
					printf("\n\t   %d~%d 일 : ", day, day + j - 1);

				for (i = 0; schedule[year][month][day][i] != NULL; i++) { // 줄바꿈 함수
					printf("%c", schedule[year][month][day][i]);
					//printf("%3d", enter);

					enter_condition++;
					if (schedule[year][month][day][i] > 0) {
						nokorean++;
					}


					//if (day < 10) {
					//	if (j > 1) {

					//	}
					//	else if (day + j >= 10) {

					//	}
					//	else
					//}
					if (nokorean % 2 == 0) {
						if (enter_condition >= 80) {
							enter_condition = 0;
							if (day >= 10)
								printf("\n\t\t   ");
							else
								printf("\n\t\t  ");
							nokorean = 0;
						}
					}

					else {
						if (enter_condition >= 79) {
							enter_condition = 0;
							if (day >= 10)
								printf("\n\t\t   ");
							else
								printf("\n\t\t  ");
							nokorean = 0;
						}
					}
				}
				if (enter_condition != 0)
					printf("\n");
			}
			Not_Schedule++;  //Not_Schedule 변수를 통해 출력되는 일정의수 관리
		}
	}


	if (Not_Schedule == 0) //일정이 하나도 출력이되지않는다면
	{
		printf("\n \n \n \n        이번달에는 일정이 없어요! C키를 눌러 일정을 추가해주세요! V키를 누르면 안내창이 종료됩니다!                      \n \n \n \n "); //일정이 없음을 알린다
	}
	printf("\n");
	printf("    ");
	for (int i = 0; i < 100; i++) printf("="); // 분리선 생성

	while (1) {
		EXIT = _getch();

		if (EXIT == 'v' || EXIT == 'V')
		{
			system("cls");
			break;
			return 0;
		}
	}
}

void Daily_Schedule(int year, int month, int day)
{
	int enter = 0, enter2 = 0; // 여러 줄 줄바꿈 대비 변수
	int nokorean = 0;
	gotoxy(33, 3); printf("======================================");
	gotoxy(33, 5); printf("         %d년 %d월 %d일 일정         ", year, month, day);

	gotoxy(33, 8);  printf("                                     ");
	gotoxy(33, 9);  printf("                                     ");
	gotoxy(33, 10); printf("                                     ");
	gotoxy(33, 11); printf("                                     ");
	gotoxy(33, 12); printf("                                     ");
	gotoxy(33, 13); printf("                                     ");
	gotoxy(33, 14); printf("                                     ");
	gotoxy(33, 15); printf("                                     ");

	if (schedule[year][month][day][0] != 0) {
		gotoxy(33, 8);
		printf("  일정 : ");
		for (i = 0; schedule[year][month][day][i] != NULL; i++) { // 줄바꿈 함수
			printf("%c", schedule[year][month][day][i]);
			//printf("%3d", enter);

			enter++;
			if (schedule[year][month][day][i] > 0) {
				nokorean++;
			}

			if (nokorean % 2 == 0) {
				if (enter >= 28) {
					enter = 0;
					gotoxy(37, 9 + enter2);
					printf(" ");
					enter2++;
					nokorean = 0;
				}
			}

			else {
				if (enter >= 27) {
					enter = 0;
					gotoxy(37, 9 + enter2);
					printf(" ");
					enter2++;
					nokorean = 0;
				}
			}
		}
	}

	else if (schedule[year][month][day][0] == 0) {
		gotoxy(33, 8);  printf("  일정이 없습니다.                   ");

	}
	gotoxy(33, 16); printf("                                         ");
	gotoxy(33, 17); printf("  * 조작키를 누를 때 영어로 해주세요!    ");
	gotoxy(33, 18); printf("                                         ");
	gotoxy(33, 19); printf("======================================   ");
	gotoxy(33, 20); printf("                                         ");
	gotoxy(33, 21); printf("****************조작법****************   ");
	gotoxy(33, 22); printf("                                         ");
	gotoxy(33, 23); printf("  A: 이전 달     D: 다음 달              ");
	gotoxy(33, 24); printf("                                         ");
	gotoxy(33, 25); printf("  S: 이전 해     W: 다음 해              ");
	gotoxy(33, 26); printf("                                         ");
	gotoxy(33, 27); printf("  C: 일정 추가   E: 일정 수정            ");
	gotoxy(33, 28); printf("                                         ");
	gotoxy(33, 29); printf("  R: 일정 삭제   V: 일정 보기            ");
	gotoxy(33, 30); printf("                                         ");
	gotoxy(33, 31); printf("  방향키: 날짜 이동                      ");
	gotoxy(33, 32); printf("                                         ");
}

void draw_Calendar()
{
	{
		time_t timer;
		struct tm* t;
		timer = time(NULL); // 1970년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초
		t = localtime(&timer); // 포맷팅을 위해 구조체에 넣기

		int month = t->tm_mon + 1, week, day = t->tm_mday, year = t->tm_year + 1900; // month : 월 관련 전체 관여, week = 몇 번째 주인지 알려주는 함수, day : 상단 날짜 출력용, year : 상단 년도 출력용
		int pin_day = 1, past_day = 0, next_day = 0, reader1 = 0, reader2 = 0, view_month_Schedule_cls = 0; // pin_day : 달력 출력용, past_day : 저번 달 날짜 출력용, nex_day : 다음 달 날짜 출력용, reader1, 2 : 달력 높이 조절용, x : gotoxy 함수 x좌표, view_month_Schedule_cls : view_month_Schedule 함수가 몇 번 선언되었는가를 확인하여 화면 클리어를 하는 함수
		int pin_day_of_the_week, day_of_the_week, next_day_of_the_week = 0; // pin_day_of_the_week = 날짜를 요일에 맞춰서 출력할 수 있게 해주는 함수, day_of_the_week : 방향키로 하루 간격으로 날짜를 바꿀 때 밑줄 위치를 요일에 맞춰서 출력할 수 있게 해주는 함수, next_day_of_the_week : 다음 달 날짜를 요일에 맞춰서 출력할 수 있게 하는 함수
		char q = '^'; //입력 받는 용도

		while (day > 7)//1일과 같은 주일에 있는 
			day -= 7;
		pin_day_of_the_week = t->tm_wday - day + 2;
		//+ 2를 하는 이유 : 일요일이 첫번째 숫자인 기준으로 이 코드의 oneweek 변수의 단위는 1 ~ 7인데, tm_wday 함수의 단위는 0 ~ 6이라 + 1을 해 줘야 하고
		//1일 기준으로 흐른 날짜는 오늘 날짜 - 1이기 때문에 + 1을 또 해서 + 2이다

		if (pin_day_of_the_week <= 0) {
			pin_day_of_the_week += 7;
		}


		day = t->tm_mday; //oneweek 초기화를 위해 day 값을 변경했으므로 day 값을 다시 초기화
		day_of_the_week = t->tm_wday + 1;
		while (1) {
			CursorView();
			week = (day + pin_day_of_the_week - 2) / 7;

			// 지정된 키를 눌렀으면 달력 출력
			switch (q) {
			case 'a':
			case 'A':
			case 'd':
			case 'D':
			case 'w':
			case 'W':
			case 's':
			case 'S':
			case 'c':
			case 'C':
			case 'v':
			case 'V':
			case 'e':
			case 'E':
			case 'r':
			case 'R':
			case '^':
			case LEFT:
			case RIGHT:
			case UP:
			case DOWN:
				printf("\n\t\t\t%4d년 %2d월 %2d일\n", year, month, day);
				printf("\n    ");
				for (i = 0; i < 59; i++)
					printf("=");
				printf("\n\n\n");

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("\tSun");

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("\tMon\tTue\tWed\tThu\tFri");

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("\tSat\n\n\n");

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //저번 달 날짜 회색으로 출력


				if (pin_day_of_the_week > 7)
					pin_day_of_the_week -= 7;
				// 저번 달 날짜 출력
				for (i = 1; i < pin_day_of_the_week; i++) {
					if (i == 1) {
						switch (month) {
						case 1:
						case 2:
						case 4:
						case 6:
						case 8:
						case 9:
						case 11:
							past_day = 31 - pin_day_of_the_week + 2; // 저번 달이 31일 일 경우
							break;
						case 5:
						case 7:
						case 10:
						case 12:
							past_day = 30 - pin_day_of_the_week + 2; // 저번 달이 30일 일 경우
							break;
						case 3:
							past_day = 28 - pin_day_of_the_week + 2; // 저번 달이 28일 일 경우
							if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) // 윤년
								past_day++;
							break;
						}
					}
					printf("\t%2d", past_day);
					past_day++;
				}

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // 글자 색 다시 흰색으로 바꾸기


				// 이번 달 날짜 출력
				pin_day = 1;
				switch (month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					for (; pin_day <= 31; pin_day++) { // 31일인 달
						if (pin_day_of_the_week == 1)
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						if (pin_day_of_the_week == 7)
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

						printf("\t%2d", pin_day);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						pin_day_of_the_week++;
						if (pin_day_of_the_week > 7) {
							printf("\n\n\n\n");
							pin_day_of_the_week = 1;
						}
					}
					pin_day_of_the_week -= 3;
					break;


				case 4:
				case 6:
				case 9:
				case 11:
					for (; pin_day <= 30; pin_day++) { // 30일인 달
						if (pin_day_of_the_week == 1)
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						if (pin_day_of_the_week == 7)
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

						printf("\t%2d", pin_day);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						pin_day_of_the_week++;
						if (pin_day_of_the_week > 7) {
							printf("\n\n\n\n");
							pin_day_of_the_week = 1;
						}
					}
					pin_day_of_the_week -= 2;
					break;


				case 2:
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) { // 윤년
						for (; pin_day <= 29; pin_day++) {
							if (pin_day_of_the_week == 1)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							if (pin_day_of_the_week == 7)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

							printf("\t%2d", pin_day);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							pin_day_of_the_week++;
							if (pin_day_of_the_week > 7) {
								printf("\n\n\n\n");
								pin_day_of_the_week = 1;
							}
						}
						pin_day_of_the_week -= 1;
					}

					else {
						for (; pin_day <= 28; pin_day++) { // 28일인 달
							if (pin_day_of_the_week == 1)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							if (pin_day_of_the_week == 7)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

							printf("\t%2d", pin_day);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							pin_day_of_the_week++;
							if (pin_day_of_the_week > 7) {
								printf("\n\n\n\n");
								pin_day_of_the_week = 1;
							}
						}
					}
					break;
				}
				if (pin_day_of_the_week < 1)
					pin_day_of_the_week += 7;



				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); // 글자 색 다시 회색으로 변경


				// 다음 달 날짜 출력
				next_day = 1;
				reader1 = 0;
				reader2 = 0;
				next_day_of_the_week = 0;

				switch (month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					next_day_of_the_week += 3;//(이번 달 - 28)만큼 더하기;
					break;
				case 2:
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
						next_day_of_the_week++;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					next_day_of_the_week += 2;
					break;
				}

				//다음 달 날짜가 특정 위치에서 멈추게 하는 함수
				for (i = pin_day_of_the_week + next_day_of_the_week; i < 15; i++) {
					printf("\t%2d", next_day);
					next_day++;
					reader1++;
					if (i == 7) {
						switch (month) {
						case 1:
						case 3:
						case 5:
						case 7:
						case 8:
						case 10:
						case 12:
							if (reader1 < 5)
								reader2 = 1;
							break;
						case 4:
						case 6:
						case 9:
						case 11:
							if (reader1 < 6)
								reader2 = 1;
							break;
						case 2:
							if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) { // 윤년
								if (reader1 < 7)
									reader2 = 1;
							}
							else
								if (reader1 < 8)
									reader2 = 1;
						}
						if (reader2 == 1)
							printf("\n\n\n\n");
						else
							break;
					}
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //글자 색 다시 흰색으로 변경
				Daily_Schedule(year, month, day);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //글자 색 다시 흰색으로 변경

			switch (q) {
			case 'c':
			case 'C':
			case 'v':
			case 'V':
			case 'e':
			case 'E':
			case 'r':
			case 'R':
			case '^':
				Daily_Schedule(year, month, day);
			}

			for (i = 1; i < 7; i++) {
				for (j = 1; j < 8; j++) {
					gotoxy(3 + j * 4 - 4, 10 + i * 4 - 4);
					printf("     ");
				}
			}
			gotoxy(3 + day_of_the_week * 4 - 4, 10 + (week + 1) * 4 - 4);
			if (day < 10)
				printf("  ---");
			else
				printf(" ----");



			q = _getch(); // q에 문자를 입력 받음


			//방향키 입력받아서 일주일 간격과 하루 간격으로 이동
			if (q == -32) {
				q = _getch();
				switch (q) {
				case LEFT:
					if (year > 1 || month > 1 || day > 1) {
						day -= 1;
						day_of_the_week -= 1;
					}
					break;
				case RIGHT:
					if (year < 3999 || month < 12 || day < 31) {
						day += 1;
						day_of_the_week += 1;
					}
					break;
				case UP:
					if (year > 1 || month > 1 || day > 7)
						day -= 7;
					break;
				case DOWN:
					if (year < 3999 || month < 12 || day < 25)
						day += 7;
					break;
				}

				switch (month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if (day > 31) {
						day -= 31;
						month++;
						pin_day_of_the_week += 3;
					}
					break;

				case 4:
				case 6:
				case 9:
				case 11:
					if (day > 30) {
						day -= 30;
						month++;
						pin_day_of_the_week += 2;
					}
					break;

				case 2:
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
						if (day > 29) {
							day -= 29;
							month++;
							pin_day_of_the_week++;
						}
					}
					else if (day > 28) {
						day -= 28;
						month++;
					}
					break;
				}

				switch (month) {
				case 1:
				case 2:
				case 4:
				case 6:
				case 8:
				case 9:
				case 11:
					if (day < 1) {
						day += 31;
						month--;
						pin_day_of_the_week -= 3;
					}
					break;

				case 5:
				case 7:
				case 10:
				case 12:
					if (day < 1) {
						day += 30;
						month--;
						pin_day_of_the_week -= 2;
					}
					break;

				case 3:
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) { // 윤년
						if (day < 1) {
							day += 29;
							month--;
							pin_day_of_the_week--;
						}
					}
					else if (day < 1) {
						day += 28;
						month--;
					}
					break;
				}
				Daily_Schedule(year, month, day);
			}



			// d를 누르면 다음달 달력으로 변경
			if ((q == 'd' || q == 'D') && (year < 3999 || month != 12)) {
				switch (month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					pin_day_of_the_week += 3;//(이번 달 - 28)만큼 더하기;
					day_of_the_week += 3;
					break;

				case 4:
				case 6:
				case 9:
				case 11:
					pin_day_of_the_week += 2;
					day_of_the_week += 2;
					break;

				case 2:
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
						pin_day_of_the_week++;
						day_of_the_week++;
					}
					break;
				}
				month++;



				COORD pos = { 0 , 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				//system("cls");
			}

			// a를 누르면 저번달 달력으로 변경
			if ((q == 'a' || q == 'A') && (year > 1 || month != 1)) {
				switch (month) {
				case 1:
				case 2:
				case 4:
				case 6:
				case 8:
				case 9:
				case 11:
					pin_day_of_the_week -= 3;//(저번 달 - 28)만큼 빼기;
					day_of_the_week -= 3;
					break;

				case 5:
				case 7:
				case 10:
				case 12:
					pin_day_of_the_week -= 2;
					day_of_the_week -= 2;
					break;

				case 3:
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
						pin_day_of_the_week--;
						day_of_the_week--;
					}
					break;
					//oneweek는 날짜를 요일에 맞춰 출력하기 위한 함수이고 달력 출력이 끝났을 때 그 달에 1일의 요일에 위치해 있는데,
					//그려먼 저번 달에 관점에서 보면 다음 달의 1일, 즉 마지막 날의 다음 요일 위치에 oneweek가 위치해 있으므로,
					//저번 달 - 28을 하면 저번 달의 1일의 위치로 oneweek가 간다.
				}

				month--;

				COORD pos = { 0 , 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				//system("cls");
			}

			// s를 누르면 년도가 증가
			if ((q == 'w' || q == 'W') && year < 3999) {
				year++;
				pin_day_of_the_week++;
				day_of_the_week++;
				if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && month > 2 || (year % 400 == 1 || (year % 100 != 1 && year % 4 == 1)) && month < 3) {
					pin_day_of_the_week++;
					day_of_the_week++;
				}

				COORD pos = { 0 , 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				//system("cls");
			}

			// w를 누르면 년도가 감소
			if ((q == 's' || q == 'S') && year > 1) {
				pin_day_of_the_week--;
				day_of_the_week--;
				if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && month > 2 || (year % 400 == 1 || (year % 100 != 1 && year % 4 == 1)) && month < 3) {
					pin_day_of_the_week--;
					day_of_the_week--;
				}
				year--;

				COORD pos = { 0 , 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				//system("cls");
			}

			// v를 눌렀을떄 veiw_month_Schedule 실행
			if (q == 'v' || q == 'V')
			{
				view_month_Schedule(year, month, day);
			}

			// c를 눌렀을 때 add_Schedule 함수 실행
			if (q == 'c' || q == 'C')
			{
				add_Schedule(year, month, day);
			}

			//r을 눌렀을때 Remove함수 실행
			if (q == 'r' || q == 'R')
			{
				Remove_Schedule(year, month, day);
			}

			//e
			if (q == 'e' || q == 'E')
			{
				Edit_Schedule(year, month, day);
			}

			switch (month) {
			case 4:
			case 6:
			case 9:
			case 11:
				if (day > 30) {
					day = 30;
					day_of_the_week--;
				}
				break;
			case 2:
				if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
					if (day > 29) {
						day_of_the_week -= day - 29;
						day = 29;
					}
				}
				else if (day > 28) {
					day_of_the_week -= day - 28;
					day = 28;
				}
				break;
			}

			while (pin_day_of_the_week < 1)
				pin_day_of_the_week += 7;
			while (pin_day_of_the_week > 7)
				pin_day_of_the_week -= 7;
			while (month < 1) {
				month += 12;
				year--;
			}
			while (month == 13) {
				month = 1;
				year++;
			}
			while (day_of_the_week > 7)
				day_of_the_week -= 7;
			while (day_of_the_week < 1)
				day_of_the_week += 7;

			if (q == '^') {
				gotoxy(40, 45);
				printf("                           어쩔티비");
				system("cls");
			}


			COORD pos = { 0 , 0 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			//system("cls");
		}
	}
}