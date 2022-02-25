#define STRING_SIZE 12800
#define DEPTH_SIZE 127 //26진수 자리수
#define TRUE 1
#define FALSE 0

int change_sign(char[], char[],int);

void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE])
{
	int question_index=0;
	int answer_index = 0, temp_index = 0, result_index = 0;
	char temp[DEPTH_SIZE+1];
	char answer_temp[STRING_SIZE];
	char calc;
	int answer_num, temp_num;
	int sum, carry, sign;
	
	for (int i = 0; i < STRING_SIZE; i++) //answer배열 초기화
		answer_temp[i] = 0;


	for (; question[question_index] != '+' && question[question_index] != '-'; question_index++) //맨앞 26진수
		temp[temp_index++] = question[question_index];


	for (; temp_index >= 0; temp_index--)
		answer_temp[answer_index++] = temp[temp_index];

	answer_temp[STRING_SIZE-1] = '+';

	for (; question[question_index] != '\0';) {
		temp_index = 0;
		calc = question[question_index++];

		for (int i = 0; i < DEPTH_SIZE + 1; i++) //계속해서 연산을 위해
			temp[i] = 0;


		for (;question[question_index] != '+' && question[question_index] != '-' && question[question_index] != '\0'; question_index++) {
			temp[temp_index] = question[question_index];
			temp_index++;
		}


		temp_index--;
		answer_index = 0; //1의 자리
		carry = 0; //1의 자리
		sign = change_sign(temp, answer_temp, temp_index);

		if (calc == answer_temp[STRING_SIZE-1]) {
			for (; temp_index >= 0; temp_index--)
			{
				temp_num = (int)(temp[temp_index]-65);
				answer_num = (int)(answer_temp[answer_index]-65);
				sum = (temp_num + answer_num + carry) % 26;
				carry = (temp_num + answer_num + carry) / 26;

				answer_temp[answer_index] = (char)(sum + 65);

				answer_index++;
			}

			for (;carry == 1 && answer_temp[answer_index] != '\0'; answer_index++)
			{
				answer_num = (int)(answer_temp[answer_index]-65);
				sum = (carry + answer_num) % 26;
				carry = (carry + answer_num) / 26;
				answer_temp[answer_index] = (char)(sum+65);
			}
		}

		else if (calc != answer_temp[STRING_SIZE -1])
		{
			for (; temp_index >= 0; temp_index--)
			{
				temp_num = (int)(temp[temp_index] - 65);
				answer_num = (int)(answer_temp[answer_index] - 65);
				if ((answer_num - temp_num - carry) < 0)
					sum = answer_num - temp_num - carry + 26;
				else
					sum = answer_num - temp_num - carry;

				if ((answer_num - temp_num - carry) < 0)
					carry = 1;
				else
					carry = 0;

				answer_temp[answer_index] = (char)(sum + 65);
				answer_index++;
			}

			for (; carry == 1 && answer_temp[answer_index] != '\0'; answer_index++)
			{
				answer_num = (int)(answer_temp[answer_index] - 65);
				if ((answer_num - carry) < 0)
					sum = answer_num - carry + 26;
				else
					sum = answer_num - carry;

				if ((answer_num - carry) < 0)
					carry = 1;
				else
					carry = 0;
				answer_temp[answer_index] = (char)(sum + 65);
			}

			if (sign == TRUE) {
				if (answer_temp[STRING_SIZE - 1] == '+')
					answer_temp[STRING_SIZE - 1] = '-';
				else
					answer_temp[STRING_SIZE - 1] = '+';
			}
		}
	}

	if (answer_temp[STRING_SIZE - 1] == '-') {
		answer[0] = '-';
		result_index++;
	}
	for (answer_index = STRING_SIZE - 2; answer_temp[answer_index] == '\0'; answer_index--);

	for (; answer_index >= 0; answer_index--)
		answer[result_index++] = answer_temp[answer_index];
}

int change_sign(char temp[], char answer_temp[], int temp_index)
{
	int answer_msb;
	int temp_msb = 0;
	for (answer_msb = 0; answer_temp[answer_msb] != '\0'; answer_msb++);
	answer_msb--;

	if (answer_msb > temp_index)
		return FALSE;
	else if (answer_msb == temp_index)
	{
		for (; answer_temp[answer_msb] == temp[temp_msb];)
		{
			answer_msb--;
			temp_msb++;
		}

		if (answer_temp[answer_msb] >= temp[temp_msb])
			return FALSE;
		else
			return TRUE;
	}
	else
		return TRUE;
}