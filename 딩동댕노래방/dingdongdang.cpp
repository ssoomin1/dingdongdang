#include <iostream>
#include <my_global.h>
#include <mysql.h>
#include <Windows.h>
#include <string>
#include <cstring>
#include <conio.h>
#include <stdlib.h>
#pragma comment(lib,"libmySQL.lib")

using namespace std;

#define UP 0 
#define DOWN 1 
#define LEFT 2 
#define RIGHT 3
#define NEXT 4 //다음장면으로 넘어간다. (엔터키)

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "111111"
#define DB_NAME "dingdongdang"

int input_key;

void init() {
	//콘솔 설정
	system("mode con cols=110 lines=27 | title 딩 동 댕"); //콘솔창 크기

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setxy(int x, int y) {
	//원하는 위치에 놓기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int keyControl() {
	//방향키,엔터 설정
	input_key = _getch();
	if (input_key == 224 || input_key == 0) {
		input_key = _getch();
		if (input_key == 72) {
			return UP;
		}
		else if (input_key == 75) {
			return LEFT;
		}
		else if (input_key == 80) {
			return DOWN;
		}
		else if (input_key == 77) {
			return RIGHT;
		}
	}
	else {
		if (input_key == 13) {
			return NEXT;
		}
	}
}

class startGame {
private:
	int key;
public:

	static string nickname;
	void titleDraw() {
		//타이틀 설정
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "                       = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
		cout << "                       =                                                         = " << endl;
		cout << "                       =  ♬       딩         댕                                 = " << endl;
		cout << "                       =                동            노    래    방     ♬      = " << endl;
		cout << "                       =                                                         = " << endl;
		cout << "                       ===========================================================" << endl;
	}

	//닉네임 설정
	void setnickname() {
		setxy(43, 12);
		cout << "nickname: ";
		cin >> nickname;
	}

	string getNickname() {
		return this->nickname;
	}

	void start();
};

string startGame::nickname = "";


class Score {
private:
public:
	static int my_score;
	void setScore(int jumsu) {
		my_score += jumsu;
		setxy(98, 3);
		cout << "점수: " << my_score;
	}
	int getScore() {
		return my_score;
	}
};

int Score::my_score = 0;

class Hint {
private:
public:
	static int my_hint;
	void setHint(int minus) {
		my_hint -= minus;
		setxy(98, 5);
		cout << "힌트: " << my_hint;
	}
	int getHint() {
		return my_hint;
	}
};

int Hint::my_hint = 3;

class basic_game {
protected:
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	int jumsu = 0;

	string answer="";
public:
	basic_game() {
		mysql_init(&mysql); //mysql 초기화
		mysql_set_character_set(&mysql, "euckr");
		mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "euckr");
		mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES euckr");
		mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}
	void showFinal() {
		system("cls");
		init();
		setxy(30, 2);
		cout << "■■■■";
		setxy(30, 3);
		cout << "■";
		setxy(30, 4);
		cout << "■■■";
		setxy(30, 5);
		cout << "■";
		setxy(30, 6);
		cout << "■";

		setxy(40, 2);
		cout << "■";
		setxy(40, 4);
		cout << "■";
		setxy(40, 5);
		cout << "■";
		setxy(40, 6);
		cout << "■";

		setxy(43, 2);
		cout << "■      ■";
		setxy(43, 3);
		cout << "■■    ■";
		setxy(43, 4);
		cout << "■  ■  ■";
		setxy(43, 5);
		cout << "■    ■■";
		setxy(43, 6);
		cout << "■      ■";

		setxy(55, 2);
		cout << "■";
		setxy(55, 4);
		cout << "■";
		setxy(55, 5);
		cout << "■";
		setxy(55, 6);
		cout << "■";

		setxy(60, 2);
		cout << "■■■■";
		setxy(60, 3);
		cout << "■";
		setxy(60, 4);
		cout << "■■■■";
		setxy(60, 5);
		cout << "      ■";
		setxy(60, 6);
		cout << "■■■■";

		setxy(70, 2);
		cout << "■    ■";
		setxy(70, 3);
		cout << "■    ■";
		setxy(70, 4);
		cout << "■■■■";
		setxy(70, 5);
		cout << "■    ■";
		setxy(70, 6);
		cout << "■    ■";

	}
	virtual void goGame() = 0;
	virtual void showResult() = 0;
};

//1990년대
class period_1 : public basic_game {
private:
	Score s;
	Hint h;
	startGame sg1;
public:
	period_1() : basic_game() {   }

	virtual void showResult() {
		showFinal();
		//결과출력
		setxy(42, 10);
		cout << "이름: " << sg1.getNickname();
		setxy(42, 12);
		cout << "점수 : " << s.getScore() << " /100";
		setxy(42, 14);
		cout << "시대: 1990년 ~ 1999년 ";
		cout << endl; cout << endl; cout << endl; cout << endl;
	}
	virtual void goGame() {
		int count = 1;
		mysql_query(&mysql, "select * from period_1 order by rand() limit 10");
		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res)) != NULL) {
			setxy(48, 19);
			//cout << "                                                                                                                                        ";
			setxy(55, 1);
			cout << count << " /10";
			setxy(2, 1);
			cout << "[1990 ~ 1999]";
			setxy(98, 3);
			cout << "점수: " << s.getScore();
			setxy(98, 5);
			cout << "힌트: " << h.getHint();

			setxy(10, 3);
			cout << "가수: " << row[1];
			setxy(25, 6);
			cout << "===========================================================";
			setxy(48, 8);
			cout << row[3];
			setxy(25, 10);
			cout << "===========================================================";
			setxy(30, 13);
			cout << "가사 : " << row[4];

			setxy(33, 15);
			cout << "** 힌트를 보고 싶다면 ↓키를 누르세요 **";
			setxy(38, 16);
			cout << " 아니라면 엔터를 치세요 ";
			int k = keyControl();
			if (k == DOWN) {
				setxy(38, 16);
				cout << "                                                             ";
				setxy(33, 15);
				cout << "                                                                                              ";
				setxy(30, 15);
				if (h.getHint() != 0) {
					cout << "힌트: " << row[5];
					h.setHint(1);
				}
				else {
					cout << "힌트를 더 이상 볼 수 없습니다.";
				}
			}

			setxy(42, 19);
			cout << "정답: ";
			setxy(48, 19);
			if (count == 1) {
				cin.ignore();
			}
			getline(cin, answer);
			setxy(41, 20);
			//cout << answer;

			if (answer == row[2]) {
				s.setScore(10);
				setxy(43, 22);
				cout << "정답입니다.";
			}
			else {
				s.setScore(-10);
				setxy(43, 22);
				cout << "오답입니다.";
			}
			Sleep(2000);
			system("cls");
			count++;
		}

		Sleep(500);
		showResult();

		mysql_free_result(res);
		mysql_close(&mysql);
	}
};

//2000년대
class period_2 : public basic_game {
private:
	Score s;
	Hint h;
	startGame sg1;
public:
	period_2() : basic_game() {   }

	virtual void showResult() {
		showFinal();
		//결과출력
		setxy(42, 10);
		cout << "이름: " << sg1.getNickname();
		setxy(42, 12);
		cout << "점수 : " << s.getScore() << " /100";
		setxy(42, 14);
		cout << "시대: 2000년 ~ 2009년 ";
	
		cout << endl; cout << endl; cout << endl; cout << endl;
	}
	virtual void goGame() {
		int count = 1;
		mysql_query(&mysql, "select * from period_2 order by rand() limit 10");
		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res)) != NULL) {
			setxy(48, 19);
			//cout << "                                                                                                                                        ";
			setxy(55, 1);
			cout << count << " /10";
			setxy(2, 1);
			cout << "[2000 ~ 2009]";
			setxy(98, 3);
			cout << "점수: " << s.getScore();
			setxy(98, 5);
			cout << "힌트: " << h.getHint();

			setxy(10, 3);
			cout << "가수: " << row[1];
			setxy(25, 6);
			cout << "===========================================================";
			setxy(48, 8);
			cout << row[3];
			setxy(25, 10);
			cout << "===========================================================";
			setxy(30, 13);
			cout << "가사 : " << row[4];

			setxy(33, 15);
			cout << "** 힌트를 보고 싶다면 ↓키를 누르세요 **";
			setxy(38, 16);
			cout << " 아니라면 엔터를 치세요 ";
			int k = keyControl();
			if (k == DOWN) {
				setxy(38, 16);
				cout << "                                                             ";
				setxy(33, 15);
				cout << "                                                                                              ";
				setxy(30, 15);
				if (h.getHint() != 0) {
					cout << "힌트: " << row[5]; 
					h.setHint(1);
				}
				else {
					cout << "힌트를 더 이상 볼 수 없습니다.";
				}
			}

			setxy(42, 19);
			cout << "정답: ";
			setxy(48, 19);
			if (count == 1) {
				cin.ignore();
			}
			getline(cin, answer);
			setxy(41, 20);

			if (answer == row[2]) {
				s.setScore(10);
				setxy(43, 22);
				cout << "정답입니다.";
			}
			else {
				s.setScore(-10);
				setxy(43, 22);
				cout << "오답입니다.";
			}
			Sleep(2000);
			system("cls");
			count++;
		}

		Sleep(500);
		showResult();

		mysql_free_result(res);
		mysql_close(&mysql);
	}
};

//2010년대
class period_3 : public basic_game {
private:
	Score s;
	Hint h;
	startGame sg1;
public:
	period_3() : basic_game() {   }

	virtual void showResult() {
		showFinal();
		//결과출력
		setxy(42, 10);
		cout << "이름: " << sg1.getNickname();
		setxy(42, 12);
		cout << "점수 : " << s.getScore() << " /100";
		setxy(42, 14);
		cout << "시대: 2010년 ~ 2020년 ";
		cout << endl; cout << endl; cout << endl; cout << endl;
	}
	virtual void goGame() {
		int count = 1;
		mysql_query(&mysql, "select * from period_3 order by rand() limit 10");
		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res)) != NULL) {
			setxy(48, 19);
			//cout << "                                                                                                                                        ";
			setxy(55, 1);
			cout << count << " /10";
			setxy(2, 1);
			cout << "[2010 ~ 2020]";
			setxy(98, 3);
			cout << "점수: " << s.getScore();
			setxy(98, 5);
			cout << "힌트: " << h.getHint();

			setxy(10, 3);
			cout << "가수: " << row[1];
			setxy(25, 6);
			cout << "===========================================================";
			setxy(48, 8);
			cout << row[3];
			setxy(25, 10);
			cout << "===========================================================";
			setxy(30, 13);
			cout << "가사 : " << row[4];

			setxy(33, 15);
			cout << "** 힌트를 보고 싶다면 ↓키를 누르세요 **";
			setxy(38, 16);
			cout << " 아니라면 엔터를 치세요 ";
			int k = keyControl();
			if (k == DOWN) {
				setxy(38, 16);
				cout << "                                                             ";
				setxy(33, 15);
				cout << "                                                                                              ";
				setxy(30, 15);
				if (h.getHint() != 0) {
					cout << "힌트: " << row[5];
					h.setHint(1);
				}
				else {
					cout << "힌트를 더 이상 볼 수 없습니다.";
				}
			}

			setxy(42, 19);
			cout << "정답: ";
			setxy(48, 19);
			if (count == 1) {
				cin.ignore();
			}
			getline(cin, answer);
			setxy(48, 20);
			//cout << answer;
			
			if(answer == row[2]){
				s.setScore(10);
				setxy(43, 22);
				cout << "정답입니다.";
			}
			else {
				s.setScore(-10);
				setxy(43, 22);
				cout << "오답입니다.";
			}
			Sleep(2000);
			system("cls");
			count++;
		}

		Sleep(500);
		showResult();
		
		mysql_free_result(res);
		mysql_close(&mysql);
	}
};

//시대 고르기
class GameReady {
	int number=0;
public:
	void choose_year() {
		init();
		int number = 0;
		setxy(47, 5);
		cout << "[ 시대 고르기 ]";

		setxy(12, 9);
		cout << "1  ====================";
		setxy(12, 10);
		cout << "   =                  = ";
		setxy(12, 11);
		cout << "   =    1990 ~ 1999   =";
		setxy(12, 12);
		cout << "   =                  = ";
		setxy(12, 13);
		cout << "   ====================";

		setxy(42, 9);
		cout << "2  ====================";
		setxy(42, 10);
		cout << "   =                  = ";
		setxy(42, 11);
		cout << "   =    2000 ~ 2009   =";
		setxy(42, 12);
		cout << "   =                  = ";
		setxy(42, 13);
		cout << "   ====================";

		setxy(72, 9);
		cout << "3  ====================";
		setxy(72, 10);
		cout << "   =                  = ";
		setxy(72, 11);
		cout << "   =    2010 ~ 2020   =";
		setxy(72, 12);
		cout << "   =                  = ";
		setxy(72, 13);
		cout << "   ====================";

		setxy(40, 17);
		cout << " 선택해주세요 (1~3): ";
		cin >> number;

		if (number == 1) {
			system("cls");
			Sleep(300);
			period_1 p1;
			p1.goGame();
		}
		else if (number == 2) {
			system("cls");
			Sleep(300);
			period_2 p2;
			p2.goGame();
		}
		else if (number == 3) {
			system("cls");
			Sleep(300);
			period_3 p3;
			p3.goGame();
		}
	}
};

//게임 방법
class howToPlay {
	startGame s1;
	int x = 27;
public:
	void information() {
		init();
		system("cls");
		cout << " " << endl; cout << " " << endl;
		cout << " " << endl; cout << " " << endl;
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 핸드 가져오기
		CONSOLE_CURSOR_INFO ConsoleCursor;
		ConsoleCursor.bVisible = 0; //핸들 숨기기 false도 가능
		ConsoleCursor.dwSize = 1;
		SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

		setxy(45, 2);
		cout << "[HOW TO PLAY]";
		setxy(x, 4);
		cout << "'딩동댕 노래방' 은 노래 제목을 맞추는 초성퀴즈입니다.";
		setxy(x, 5);
		cout << "시대는 1990년대와 2000년대, 2010년대가 있습니다.";
		setxy(x, 6);
		cout << "노래를 얼마나 알고 있는지 확인해볼까요??";
		setxy(x, 8);
		cout << "1. 조작키";
		setxy(x, 10);
		cout << "방향키 ←,↑,↓,→ 로 조작합니다. ";
		setxy(x, 11);
		cout << "다음으로 넘어가고 싶다면! Enter 키를 눌러주세요.";
		setxy(x, 12);
		cout << "이전 화면으로 넘어가기: ↓누르면 커서가 뜹니다.  그 후에 Enter키를 눌러주세요";
		setxy(x, 14);
		cout << "2. 힌트와 점수";
		setxy(x, 16);
		cout << "가수 이름과 가사 1개는 기본으로 제공되며 힌트 개수는 시대별 3개입니다!";
		setxy(x, 17);
		cout << "점수는 한 문제당 10점입니다." << endl;

		setxy(85, 21);
		cout << " 돌아가기 ";
		if (keyControl() == DOWN) {
			setxy(84, 21);
			cout << ">";
			if (keyControl() == NEXT) {
				Sleep(300);
				system("cls");
				s1.titleDraw();
				setxy(43, 12);
				cout << "nickname: ";
				setxy(55, 12);
				cout << s1.getNickname();
				s1.start();
			}
		}
	}
};

void startGame::start() {
	int chooseN = 0;
	int x = 43;
	int y = 15;
	setxy(x, y);
	cout << "1. 게 임 시 작 ";
	setxy(x, y + 1);
	cout << "2. 게 임 정 보 ";
	setxy(x, y + 2);
	cout << "3. 게 임 종 료 " << endl;
	setxy(x-4, y + 4);
	cout << "기능을 선택하세요 (1~3) : ";
	cin >> chooseN;

	if (chooseN == 1) {
		GameReady gr;
		gr.choose_year();
	}
	else if (chooseN == 2) {
		howToPlay htp;
		htp.information();
	}
	else if (chooseN == 3) {
		system("exit");
	}
	else {
		setxy(x, y + 5);
		cout << "1~3 중에서 선택해주세요.";
	}
}

int main() {
	init();
	startGame sg;
	sg.titleDraw();
	sg.setnickname();
	sg.start();
	return 0;
}

