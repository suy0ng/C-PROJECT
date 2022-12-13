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



int i, j, k; //i = for�� �������, j = for�� �������2

int year_temp = 0, month_temp = 0, day_temp = 0; // ���� �����Ϳ� ����

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
	draw_start_Calendar(); //�޷��� ùȭ�� ���
	draw_Calendar(); //�޷����
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
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
	timer = time(NULL); // 1970�� 1�� 1�� 0�� 0�� 0�ʺ��� �����Ͽ� ��������� ��
	t = localtime(&timer); // �������� ���� ����ü�� �ֱ�
	int year = t->tm_year + 1900;

	printf("\n\n\n"); //��ĭ �پ��
	printf("    "); // ��ĭ ���
	for (int i = 0; i < 59; i++) //'='��� 
		printf("=");
	for (int i = 0; i < 14; i++) // �ٹٲ� 14��
		printf("\n");
	for (int j = 0; j < 24; j++) //��ĭ ���
		printf(" ");
	printf("  %d ", year); //���� ��� 
	printf("CALENDAR"); //Ķ���� ��� 
	printf("\n"); //�ٹٲ�
	for (int i = 0; i < 14; i++) //14�� �ٹٲ�
		printf("\n");
	printf("    "); //�� ĭ ���
	for (int i = 0; i < 59; i++) //'='��� 
		printf("=");
	gotoxy(33, 5); printf("  ������ ���� ���� Ư�� ���ڸ� �Ѿ� ���� ");
	gotoxy(33, 6); printf("  ���ڰ� �ڵ����� �߸��ϴ�.              ");
	gotoxy(33, 7); printf("                                         ");
	gotoxy(33, 8); printf("  Ư�� ���� : �� 220, �ѱ��� �� ���� ����");
	gotoxy(35, 20); printf("       �ƹ� Ű�� ������ ����            ");
	getch();
	system("cls"); //ȭ�� ����
}

void add_Schedule(int year, int month, int day)
{
	char add_answer[100]; //������ �� �� �ְ� �ϴ� ���� ����
	gotoxy(2, 33); // ��� �̵�


	for (int i = 0; i < 100; i++) printf("="); // �и��� ����
	printf("\n");
	printf("\n     ������ �߰��Ͻðڽ��ϱ�? ( Y / N ) : "); // ���� �߰� ���� ���
	scanf("%s", add_answer); //add_answer�� ��� ����
	printf("\n    "); //4ĭ ��� ����
	for (int i = 0; i < 100; i++) printf("="); // �и��� ����
	printf("\n");


	//������ �߰����� �ʴ´� ���� ��
	if (add_answer[0] == 'n' || add_answer[0] == 'N')
	{
		printf("\n     �Է�â�� �����մϴ�. \n"); //�Է�â ���� �� �ȳ��� ���
		Sleep(500);
		system("cls"); //ȭ�� �����
		add_answer[0] = NULL;
	}

	//������ �߰��Ѵ� ���� ��
	else if (add_answer[0] == 'y' || add_answer[0] == 'Y')
	{
		if (schedule[year][month][day][0] != 0)
		{
			printf("\n    %d�� %d�� %d�Ͽ��� �̹� ������ �ֽ��ϴ�. ������ �߰��� �� �����ϴ�.\n", year, month, day);
			Sleep(500); //0.5�� ���
			printf("\n    �Է�â�� �����մϴ�. \n"); //�Է�â ���� �� �ȳ��� ���
			Sleep(2000); // 2�� ���
			system("cls"); //�ܼ�ȭ�� �ʱ�ȭ
			add_answer[0] = NULL;
			return 0;
		}

		printf("\n     %d�� %d�� %d���� ������ �߰����ּ���! : ", year, month, day); //������ �߰��Ҽ��ְ��ϴ� ������ ����Ѵ�.
		scanf(" %[^\n]", schedule[year][month][day]); //������ �Է¹޽��ϴ�



		fpp = fopen("pile.txt", "at");

		if (fpp == NULL) {
			return 0;
		}

		fprintf(fpp, "\n%d.%d.%d : %s", year, month, day, schedule[year][month][day]);

		fclose(fpp);



		printf("\n     ������ �߰��ϰڽ��ϴ�.\n"); //������ �߰��ϰڴٴ� �ȳ��� ���
		Sleep(500); //0.5�� ���
		printf("\n     �Է�â�� �����մϴ�. \n"); //�Է�â ���� �� �ȳ��� ���
		Sleep(1500); // 1.5�� ���
		system("cls"); //�ܼ�ȭ�� �ʱ�ȭ
		add_answer[0] = NULL;
		return 0;
	}

	else // y �Ǵ� n �� �ƴ� ���ڸ� �Է��������
	{
		printf("\n     �Է�â�� �����մϴ�. �Է�â�� �ٽ� ��������ֽʽÿ�. \n"); //�Է�â�� �����Ų�ٰ� �ȳ����� ����Ѵ�
		Sleep(500); //0.5�� ���
		printf("\n     �Է�â�� �����մϴ�. \n"); //�Է�â ���� �� �ȳ��� ���
		Sleep(500); //0.5�� ���
		system("cls");
		add_answer[0] = NULL;
		return 0;
	}

}

void Edit_Schedule(int year, int month, int day)
{
	char Edit_Schedule[100];

	gotoxy(2, 33);
	for (int i = 0; i < 100; i++) printf("="); // �и��� ����
	printf("\n");

	gotoxy(2, 43);
	for (int i = 0; i < 100; i++) printf("="); // �и��� ����

	gotoxy(2, 33);

	printf("\n\n     %d�� %d�� %d���� �����ϰڽ��ϱ� ( Y / N ) : ", year, month, day);
	scanf("%s", Edit_Schedule);

	if ((Edit_Schedule[0] == 'Y' || Edit_Schedule[0] == 'y') && schedule[year][month][day] != NULL)
	{
		if (schedule[year][month][day][0] == 0)
		{
			Sleep(300);
			printf("\n     ������ �������� �ʽ��ϴ�. �߰����� ���� ������ ������ �� �����ϴ�\n");
			Sleep(700);
			system("cls");
			return 0;
		}
		else {
			Sleep(300);
			printf("\n     ������ �����ϰڽ��ϴ�. ������ ������ ������ �� �����ϴ�.\n");
			Sleep(700);
			schedule[year][month][day] == NULL;
			printf("\n     %d�� %d�� %d���� ������ �������ּ��� : ", year, month, day);
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
			printf("\n     ������ �����Ͽ����ϴ�. ������ ������ ������ �� �����ϴ�.\n");
			system("cls");
			return 0;
		}

	}
	else {
		Sleep(300);
		printf("\n     ������ �������� �ʰ� �Է�â�� �����մϴ�. \n");
		Sleep(700);
		system("cls");
		return 0;
	}
}

void Remove_Schedule(int year, int month, int day)
{
	char Remove_Schedule_Y_N[100];

	gotoxy(2, 33);
	for (int i = 0; i < 100; i++) printf("="); // �и��� ����
	printf("\n");

	gotoxy(2, 43);
	for (int i = 0; i < 100; i++) printf("="); // �и��� ����

	gotoxy(2, 33);

	printf("\n\n     ������ �����ϸ� ������ ������ �����ϰų� �ٽ� Ȯ���� �� �����ϴ�.\n");
	Sleep(500);
	printf("\n     %d�� %d�� %d���� ������ ������ �����Ͻðڽ��ϱ� ( Y / N ) :", year, month, day);
	scanf("%s", Remove_Schedule_Y_N);

	if (Remove_Schedule_Y_N[0] == 'Y' || Remove_Schedule_Y_N[0] == 'y')
	{
		if (schedule[year][month][day][0] == 0)
		{
			Sleep(500);
			printf("\n     ������ �� �ִ� ������ �������� �ʽ��ϴ�. �Է�â�� �����մϴ�.\n");
			Sleep(500);
			schedule[year][month][day][0] = 0;
			system("cls");
			return 0;
		}
		else
		{
			Sleep(500);
			printf("\n     ������ �����ϰڽ��ϴ�. ������ ������ ������ �� �����ϴ�.\n");
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
		printf("\n     ������ �������� �ʰ� �Է�â�� �����մϴ�. \n");
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
	for (i = 0; i < 100; i++) printf("="); // �и��� ����
	printf("\n");

	for (int day = 1; day <= 31; day += j)  //������ �ִ� �� ã��
	{
		if (schedule[year][month][day][0] != NULL) //������ ��������ʴ´ٸ�
		{
			if (Not_Schedule < 6) //�ִ� 6�� ��°���
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
					printf("\n\t   %d �� : ", day);
				else
					printf("\n\t   %d~%d �� : ", day, day + j - 1);

				for (i = 0; schedule[year][month][day][i] != NULL; i++) { // �ٹٲ� �Լ�
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
			Not_Schedule++;  //Not_Schedule ������ ���� ��µǴ� �����Ǽ� ����
		}
	}


	if (Not_Schedule == 0) //������ �ϳ��� ����̵����ʴ´ٸ�
	{
		printf("\n \n \n \n        �̹��޿��� ������ �����! CŰ�� ���� ������ �߰����ּ���! VŰ�� ������ �ȳ�â�� ����˴ϴ�!                      \n \n \n \n "); //������ ������ �˸���
	}
	printf("\n");
	printf("    ");
	for (int i = 0; i < 100; i++) printf("="); // �и��� ����

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
	int enter = 0, enter2 = 0; // ���� �� �ٹٲ� ��� ����
	int nokorean = 0;
	gotoxy(33, 3); printf("======================================");
	gotoxy(33, 5); printf("         %d�� %d�� %d�� ����         ", year, month, day);

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
		printf("  ���� : ");
		for (i = 0; schedule[year][month][day][i] != NULL; i++) { // �ٹٲ� �Լ�
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
		gotoxy(33, 8);  printf("  ������ �����ϴ�.                   ");

	}
	gotoxy(33, 16); printf("                                         ");
	gotoxy(33, 17); printf("  * ����Ű�� ���� �� ����� ���ּ���!    ");
	gotoxy(33, 18); printf("                                         ");
	gotoxy(33, 19); printf("======================================   ");
	gotoxy(33, 20); printf("                                         ");
	gotoxy(33, 21); printf("****************���۹�****************   ");
	gotoxy(33, 22); printf("                                         ");
	gotoxy(33, 23); printf("  A: ���� ��     D: ���� ��              ");
	gotoxy(33, 24); printf("                                         ");
	gotoxy(33, 25); printf("  S: ���� ��     W: ���� ��              ");
	gotoxy(33, 26); printf("                                         ");
	gotoxy(33, 27); printf("  C: ���� �߰�   E: ���� ����            ");
	gotoxy(33, 28); printf("                                         ");
	gotoxy(33, 29); printf("  R: ���� ����   V: ���� ����            ");
	gotoxy(33, 30); printf("                                         ");
	gotoxy(33, 31); printf("  ����Ű: ��¥ �̵�                      ");
	gotoxy(33, 32); printf("                                         ");
}

void draw_Calendar()
{
	{
		time_t timer;
		struct tm* t;
		timer = time(NULL); // 1970�� 1�� 1�� 0�� 0�� 0�ʺ��� �����Ͽ� ��������� ��
		t = localtime(&timer); // �������� ���� ����ü�� �ֱ�

		int month = t->tm_mon + 1, week, day = t->tm_mday, year = t->tm_year + 1900; // month : �� ���� ��ü ����, week = �� ��° ������ �˷��ִ� �Լ�, day : ��� ��¥ ��¿�, year : ��� �⵵ ��¿�
		int pin_day = 1, past_day = 0, next_day = 0, reader1 = 0, reader2 = 0, view_month_Schedule_cls = 0; // pin_day : �޷� ��¿�, past_day : ���� �� ��¥ ��¿�, nex_day : ���� �� ��¥ ��¿�, reader1, 2 : �޷� ���� ������, x : gotoxy �Լ� x��ǥ, view_month_Schedule_cls : view_month_Schedule �Լ��� �� �� ����Ǿ��°��� Ȯ���Ͽ� ȭ�� Ŭ��� �ϴ� �Լ�
		int pin_day_of_the_week, day_of_the_week, next_day_of_the_week = 0; // pin_day_of_the_week = ��¥�� ���Ͽ� ���缭 ����� �� �ְ� ���ִ� �Լ�, day_of_the_week : ����Ű�� �Ϸ� �������� ��¥�� �ٲ� �� ���� ��ġ�� ���Ͽ� ���缭 ����� �� �ְ� ���ִ� �Լ�, next_day_of_the_week : ���� �� ��¥�� ���Ͽ� ���缭 ����� �� �ְ� �ϴ� �Լ�
		char q = '^'; //�Է� �޴� �뵵

		while (day > 7)//1�ϰ� ���� ���Ͽ� �ִ� 
			day -= 7;
		pin_day_of_the_week = t->tm_wday - day + 2;
		//+ 2�� �ϴ� ���� : �Ͽ����� ù��° ������ �������� �� �ڵ��� oneweek ������ ������ 1 ~ 7�ε�, tm_wday �Լ��� ������ 0 ~ 6�̶� + 1�� �� ��� �ϰ�
		//1�� �������� �帥 ��¥�� ���� ��¥ - 1�̱� ������ + 1�� �� �ؼ� + 2�̴�

		if (pin_day_of_the_week <= 0) {
			pin_day_of_the_week += 7;
		}


		day = t->tm_mday; //oneweek �ʱ�ȭ�� ���� day ���� ���������Ƿ� day ���� �ٽ� �ʱ�ȭ
		day_of_the_week = t->tm_wday + 1;
		while (1) {
			CursorView();
			week = (day + pin_day_of_the_week - 2) / 7;

			// ������ Ű�� �������� �޷� ���
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
				printf("\n\t\t\t%4d�� %2d�� %2d��\n", year, month, day);
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

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //���� �� ��¥ ȸ������ ���


				if (pin_day_of_the_week > 7)
					pin_day_of_the_week -= 7;
				// ���� �� ��¥ ���
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
							past_day = 31 - pin_day_of_the_week + 2; // ���� ���� 31�� �� ���
							break;
						case 5:
						case 7:
						case 10:
						case 12:
							past_day = 30 - pin_day_of_the_week + 2; // ���� ���� 30�� �� ���
							break;
						case 3:
							past_day = 28 - pin_day_of_the_week + 2; // ���� ���� 28�� �� ���
							if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) // ����
								past_day++;
							break;
						}
					}
					printf("\t%2d", past_day);
					past_day++;
				}

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // ���� �� �ٽ� ������� �ٲٱ�


				// �̹� �� ��¥ ���
				pin_day = 1;
				switch (month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					for (; pin_day <= 31; pin_day++) { // 31���� ��
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
					for (; pin_day <= 30; pin_day++) { // 30���� ��
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
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) { // ����
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
						for (; pin_day <= 28; pin_day++) { // 28���� ��
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



				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); // ���� �� �ٽ� ȸ������ ����


				// ���� �� ��¥ ���
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
					next_day_of_the_week += 3;//(�̹� �� - 28)��ŭ ���ϱ�;
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

				//���� �� ��¥�� Ư�� ��ġ���� ���߰� �ϴ� �Լ�
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
							if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) { // ����
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //���� �� �ٽ� ������� ����
				Daily_Schedule(year, month, day);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //���� �� �ٽ� ������� ����

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



			q = _getch(); // q�� ���ڸ� �Է� ����


			//����Ű �Է¹޾Ƽ� ������ ���ݰ� �Ϸ� �������� �̵�
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
					if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) { // ����
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



			// d�� ������ ������ �޷����� ����
			if ((q == 'd' || q == 'D') && (year < 3999 || month != 12)) {
				switch (month) {
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					pin_day_of_the_week += 3;//(�̹� �� - 28)��ŭ ���ϱ�;
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

			// a�� ������ ������ �޷����� ����
			if ((q == 'a' || q == 'A') && (year > 1 || month != 1)) {
				switch (month) {
				case 1:
				case 2:
				case 4:
				case 6:
				case 8:
				case 9:
				case 11:
					pin_day_of_the_week -= 3;//(���� �� - 28)��ŭ ����;
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
					//oneweek�� ��¥�� ���Ͽ� ���� ����ϱ� ���� �Լ��̰� �޷� ����� ������ �� �� �޿� 1���� ���Ͽ� ��ġ�� �ִµ�,
					//�׷��� ���� �޿� �������� ���� ���� ���� 1��, �� ������ ���� ���� ���� ��ġ�� oneweek�� ��ġ�� �����Ƿ�,
					//���� �� - 28�� �ϸ� ���� ���� 1���� ��ġ�� oneweek�� ����.
				}

				month--;

				COORD pos = { 0 , 0 };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				//system("cls");
			}

			// s�� ������ �⵵�� ����
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

			// w�� ������ �⵵�� ����
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

			// v�� �������� veiw_month_Schedule ����
			if (q == 'v' || q == 'V')
			{
				view_month_Schedule(year, month, day);
			}

			// c�� ������ �� add_Schedule �Լ� ����
			if (q == 'c' || q == 'C')
			{
				add_Schedule(year, month, day);
			}

			//r�� �������� Remove�Լ� ����
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
				printf("                           ��¿Ƽ��");
				system("cls");
			}


			COORD pos = { 0 , 0 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			//system("cls");
		}
	}
}