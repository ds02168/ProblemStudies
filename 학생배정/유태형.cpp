#define NUM_STUDENT 10000
#define FALSE 0
#define TRUE 1

void get_school_position(int, int*, int*);
void get_student_position(int, int*, int*);
void set_student_school(int, int);
int search_NearStudent(long[],int[]); //���� ����� �л� ���ϴ� �Լ�


void run_contest(void)
{
	long temp_A[NUM_STUDENT], temp_B[NUM_STUDENT], temp_C[NUM_STUDENT]; //���� �б� A,B,C�� �л������ �Ÿ��� �����ϴ� �迭
	int temp_student[NUM_STUDENT]; //�̹� �������� �л����� �Ǻ��ϴ� �迭
	int student_x, student_y; //�л� ��ġ
	int school_x,  school_y; //�б� ��ġ
	int near_student; //���� ����� �л�
	long distance; //�Ÿ�
	int turn; //A->B->C �������


	for (int i = 0; i < NUM_STUDENT; i++) //��� ���� ���� ���� ���·� �ʱ�ȭ
		temp_student[i] = FALSE;


	get_school_position(0, &school_x, &school_y); //A�б��� �л������ �Ÿ� �ʱ�ȭ
	for (int i = 0; i < NUM_STUDENT; i++) {
		get_student_position(0, &student_x, &student_y);
		distance = ((school_x - student_x) * (school_x - student_x)) + ((school_y - student_y) * (school_y - student_y));
		temp_A[i] = distance;
	}

	get_school_position(1, &school_x, &school_y); //B�б��� �л������ �Ÿ� �ʱ�ȭ
	for (int i = 0; i < NUM_STUDENT; i++) {
		get_student_position(1, &student_x, &student_y);
		distance = ((school_x - student_x) * (school_x - student_x)) + ((school_y - student_y) * (school_y - student_y));
		temp_B[i] = distance;
	}

	get_school_position(2, &school_x, &school_y); //C�б��� �л������ �Ÿ� �ʱ�ȭ
	for (int i = 0; i < NUM_STUDENT; i++) {
		get_student_position(2, &student_x, &student_y);
		distance = ((school_x - student_x) * (school_x - student_x)) + ((school_y - student_y) * (school_y - student_y));
		temp_C[i] = distance;
	}
	//�Ÿ��� ������� ũ�� ���̱� ������ �������� �ʿ�� �����ϴ�.


	for (int i = 0; i < NUM_STUDENT; i++) { //��� �л����� �б��� ����
		turn = i % 3; //������ 3�� �������ν� A,B,C�б� ������� ���� ������ ���� �������� ���� �л����� �����ذ��ϴ�.
		switch (turn) 
		{
		case 0:near_student = search_NearStudent(temp_A, temp_student); //A�б� ����
			set_student_school(near_student, 0);
			break;

		case 1 :near_student = search_NearStudent(temp_B, temp_student); //B�б� ����
			set_student_school(near_student, 1);
			break;

		case 2: near_student = search_NearStudent(temp_C, temp_student); //C�б� ����
			set_student_school(near_student, 2);
			break;
		}
	}
}



int search_NearStudent(long temp[], int student[]) //���� ����� �л� ã�� �Լ�
{
	long min = 999999;
	int min_pos = 0;

	for (int i = 0; i < NUM_STUDENT; i++) {
		if (min > temp[i]) { //min���� �۰�
			if (student[i] == FALSE) { //���� ���� �ȵ� �л��̸�
				min_pos = i; //�ּ�
			}
		}
	}

	student[min_pos] = TRUE;
	return min_pos; //�ּ� index(�л�) ��ȯ
}