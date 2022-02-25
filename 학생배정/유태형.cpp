#define NUM_STUDENT 10000
#define FALSE 0
#define TRUE 1

void get_school_position(int, int*, int*);
void get_student_position(int, int*, int*);
void set_student_school(int, int);
int search_NearStudent(long[],int[]); //가장 가까운 학생 구하는 함수


void run_contest(void)
{
	long temp_A[NUM_STUDENT], temp_B[NUM_STUDENT], temp_C[NUM_STUDENT]; //각각 학교 A,B,C가 학생들과의 거리를 저장하는 배열
	int temp_student[NUM_STUDENT]; //이미 배정받은 학생인지 판별하는 배열
	int student_x, student_y; //학생 위치
	int school_x,  school_y; //학교 위치
	int near_student; //가장 가까운 학생
	long distance; //거리
	int turn; //A->B->C 순서대로


	for (int i = 0; i < NUM_STUDENT; i++) //모두 배정 받지 않은 상태로 초기화
		temp_student[i] = FALSE;


	get_school_position(0, &school_x, &school_y); //A학교의 학생들과의 거리 초기화
	for (int i = 0; i < NUM_STUDENT; i++) {
		get_student_position(0, &student_x, &student_y);
		distance = ((school_x - student_x) * (school_x - student_x)) + ((school_y - student_y) * (school_y - student_y));
		temp_A[i] = distance;
	}

	get_school_position(1, &school_x, &school_y); //B학교의 학생들과의 거리 초기화
	for (int i = 0; i < NUM_STUDENT; i++) {
		get_student_position(1, &student_x, &student_y);
		distance = ((school_x - student_x) * (school_x - student_x)) + ((school_y - student_y) * (school_y - student_y));
		temp_B[i] = distance;
	}

	get_school_position(2, &school_x, &school_y); //C학교의 학생들과의 거리 초기화
	for (int i = 0; i < NUM_STUDENT; i++) {
		get_student_position(2, &student_x, &student_y);
		distance = ((school_x - student_x) * (school_x - student_x)) + ((school_y - student_y) * (school_y - student_y));
		temp_C[i] = distance;
	}
	//거리의 상대적인 크기 비교이기 때문에 제곱근할 필요는 없습니다.


	for (int i = 0; i < NUM_STUDENT; i++) { //모든 학생들을 학교에 배정
		turn = i % 3; //나머지 3을 해줌으로써 A,B,C학교 순서대로 가장 가깝고 아직 배정받지 않은 학생들을 배정해갑니다.
		switch (turn) 
		{
		case 0:near_student = search_NearStudent(temp_A, temp_student); //A학교 배정
			set_student_school(near_student, 0);
			break;

		case 1 :near_student = search_NearStudent(temp_B, temp_student); //B학교 배정
			set_student_school(near_student, 1);
			break;

		case 2: near_student = search_NearStudent(temp_C, temp_student); //C학교 배정
			set_student_school(near_student, 2);
			break;
		}
	}
}



int search_NearStudent(long temp[], int student[]) //가장 가까운 학생 찾는 함수
{
	long min = 999999;
	int min_pos = 0;

	for (int i = 0; i < NUM_STUDENT; i++) {
		if (min > temp[i]) { //min보다 작고
			if (student[i] == FALSE) { //아직 배정 안된 학생이면
				min_pos = i; //최소
			}
		}
	}

	student[min_pos] = TRUE;
	return min_pos; //최소 index(학생) 반환
}