#include <iostream>
#include <algorithm>
#include <random>
#include <conio.h>
#include <windows.h>
#include <chrono>

using namespace std;

int row, col, mine;
int left_cells = 0;

void plant_mine(int **hidden_map, char **map, int row, int col, int mine); // 지뢰를 설치하는 함수
void start_game(int **hidden_map, char **map, int row, int col, int mine); // 게임을 시작하는 함수
bool is_safety(int x, int y); // 박스를 재귀적으로 열 때 배열의 범위를 벗어나는지 체크하는 함수
void open(char **map, int **hidden_map, int x, int y, int count); // 박스를 여는 함수
int count_mine(int **hidden_map, int x, int y); // 주변의 지뢰 개수를 반환하는 함수
void open_around(char **map, int **hidden_map, int x, int y); // 만약 주변의 지뢰가 없다면 재귀적으로 주변 전체를 열게 만들 재귀함수
void gotoxy(int x, int y); // 커서를 (x, y)로 이동시키는 함수



int main() {
    while(1) {
        /*** 가로, 세로, 지뢰 개수 입력 ***/
        while(row*col <= mine || mine <= 0 || col <= 0 || row <= 0) { // 이 조건에 해당되면 재입력 시킴
            printf("Enter the number of rows, columns and mines. ex)10 10 10: ");
            cin >> col >> row >> mine;
            system("cls"); // 콘솔 전체 지움
        }
        int **hidden_map;
        char **map;

        /*** 맵 이차원 배열 생성 ***/
        hidden_map = new int *[row];
        map = new char *[row];

        for (int i = 0; i < row; i++) {
            hidden_map[i] = new int[col];
            fill_n(hidden_map[i], col, 0);
            map[i] = new char[col];
            fill_n(map[i], col, 'O');
        }

        /*** 지뢰 심기 ***/
        plant_mine(hidden_map, map, row, col, mine);

        /*** 게임 시작 ***/
        start_game(hidden_map, map, row, col, mine);

        // 동적 할당 해제
        for (int i = 0; i < 3; i++)
            delete[] hidden_map[i];

        delete[] hidden_map;

        // 다시 게임을 할건지 입력받음
        Sleep(3000);
        printf("Quit to enter q, restart to enter any key without q: ");
        char check = _getch();
        system("cls");
        if(check == 'q')
            break;
        row = col = mine = 0;
    }
}



void plant_mine(int **hidden_map, char **map, int row, int col, int mine) {
    // random_device 객체 생성
    random_device rd;

    // 메르센 트위스터 난수 생성 알고리즘으로 난수 생성
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    // 세로 분포 정의
    uniform_int_distribution<int> row_dis(0, row - 1);

    // 가로 분포 정의
    uniform_int_distribution<int> col_dis(0, col - 1);

    int mine_cnt = 0;

    // 지뢰 개수만큼 지뢰 삽입
    while (mine_cnt < mine) {
        int rand_row = row_dis(gen), rand_col = col_dis(gen);
        if (!hidden_map[rand_row][rand_col]) {
            hidden_map[rand_row][rand_col] = -1;
            mine_cnt++;
        }
    }
}

// 게임이 시작되는 중심이 되는 함수
void start_game(int **hidden_map, char **map, int row, int col, int mine){
    bool is_end = false; // 게임을 끝났는지 확인하는 변수
    bool is_win = false; // 칸을 다 열었는지 확인하는 변수

    int x = 0, y = 0; // 포인트 행, 열 좌표
    left_cells = row*col - mine;

    while (1) {
        printf("columns: %d, rows: %d, mines: %d, box left: %d\n", col, row, mine, left_cells);
        printf("quit: q\n");
        printf("------------------------------\n\n");

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << map[i][j] << "  ";
            }
            cout << "\n\n";
        }
        if(is_win) {
            printf("You win!\n");
            break;
        }
        if(is_end) {
            printf("You lose\n");
            break;
        }
        gotoxy(y * 3, x * 2 + 4);

        int key = _getch();
        if (key == 224)
        { // 화살표 키가 눌렸다면?
            key = _getch();
            switch (key) {
            case 77: // 오른쪽
                if(y < col - 1) y++;
                break;
            case 75: // 왼쪽
                if(y > 0) y--;
                break;
            case 72: // 위
                if(x > 0) x--;
                break;
            case 80: // 아래
                if(x < row - 1) x++;
                break;
            }
        }
        if(key == 13 || key == 32) { // 엔터가 눌렸다면?
            if(hidden_map[x][y] == -1) { // 누른 칸이 지뢰 칸이라면?
                map[x][y] = 'X'; // 지뢰 표시 후
                is_end = true;
            } // 지뢰 칸이 아니라면
            else open_around(map, hidden_map, x, y);
        }
        if(key == 'q') {
            system("cls");
            return;
        }

        if(left_cells == 0) is_win = true;
        // 콘솔창 화면 지우기
        system("cls");
    }
}

bool is_safety(int x, int y) { // 배열의 범위를 벗어난다면 false, 그렇지 않다면 true를 반환한다.
    if(x < 0 || x >= row || y < 0 || y >= col) return false;
    return true;
}

void open(char **map, int **hidden_map, int x, int y, int count) { // 칸을 열 때 
    hidden_map[x][y] = -2; // hidden_map에는 -2로 열었다는 표시를 해주고
    map[x][y] = count ? count + '0': ' '; // map에는 주변 지뢰의 개수를 표시하는데 만약 0개일 경우 공백 문자를 표시하게 한다.
    left_cells--; // 열 때마다 남은 칸의 개수를 하나 뺀다.
}

int count_mine(int **hidden_map, int x, int y) {
    int mineCount = 0, search_x, search_y; // 주변 지뢰의 개수를 담는 변수, 탐색할 때 행 값, 탐색할 때 열 값
    for(int i = 0; i < 9; i++) { // 주변 칸을 탐색하기 위해 9번 반복한다.
        search_x = x + i / 3 - 1; // 주변에 존재하는 칸의 행 위치 식
        search_y = y + i % 3 - 1; // 주변에 존재하는 칸의 열 위치 식
        if(i == 4 || !is_safety(search_x, search_y)) continue; // 자기자신은 탐색할 필요가 없으니 continue 또는 배열 범위를 벗어난다면 continue
        if(hidden_map[search_x][search_y] == -1) mineCount++; // 만약 주변에 지뢰가 존재한다면 주변 지회의 개수를 담는 변수를 1 추가한다.
    }
    return mineCount; // 주변 지뢰의 개수를 반환한다.
}

void open_around(char **map, int **hidden_map, int x, int y) {
    int count = count_mine(hidden_map, x, y); // 주변 지뢰의 개수를 받아온다.
    open(map, hidden_map, x, y, count); // 클릭한 칸을 연다. (재귀적으로 열린 주변 칸을 연다.)
    if(count == 0) { // 만약 주변 지뢰의 개수가 0개라면 
        int search_x, search_y; // 주변 칸 전체를 열기 위한 행, 열 값을 담는 변수
        for(int i = 0; i < 9; i++) { // 주변 칸 전체를 열기 위해 9번 반복한다.
            search_x = x + i / 3 - 1; // 주변에 존재하는 칸의 행 위치 식
            search_y = y + i % 3 - 1; // 주변에 존재하는 칸의 열 위치 식
            // 자시 자신은 열 필요가 없으므로 continue 또는 배열 범위를 벗어나거나 지뢰칸이라면 continue (열면 안되는 칸)
            if(i == 4 || !is_safety(search_x, search_y) || hidden_map[search_x][search_y] == -2) {
                continue; // 열려는 위치가 클릭한 위치거나 배열을 벗어나는 위치라면?
            }
            open_around(map, hidden_map, search_x, search_y); // 주변에 칸을 연다.
        }
    }
}

void gotoxy(int x, int y) {
      COORD Cur; // 좌표를 담는 구조체 변수
      Cur.X = x; // 좌표를 담는 구조체의 X값
      Cur.Y = y; // 좌표를 담는 구조체의 Y값
      // (x, y)로 커서 이동
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}