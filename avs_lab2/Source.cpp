#include <iostream>
#include <random>

using namespace std;

/*21.	���������� ���������� ��������� ������� N1, ������� ������������ �������� � �������� ����������,
        � N2 � � ��������. � ������ ������ �������� �������� �������.*/


// ������ ������������ �������
const int N = 20;

//������ �������
void print_array(int arr[], int row, int column) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			cout << "\t" << arr[i*N + j];
		}
		cout << "\n\n";
	}
	cout << "\n";
}

int main() 
{
	setlocale(LC_ALL, "Russian"); //��� �������� ����� � �������

	//����������� �������
	int row = 0;
	int column = 0;
	bool correct_size = true; //���������� ��� �������� ������
	int result_arr[N][N];
	int input_arr[N][N];

	// ������� ���
	int left = 0;
	int right = 0;

	// ������� �������
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result_arr[i][j] = 0;
			input_arr[i][j] = 0;
		}
	}

	// ���� ������� ������� � �������� ������
	do {
		system("cls");

		cout << "������� ���������� �����: ";
		cin >> row;

		cout << "������� ���������� ��������: ";
		cin >> column;

		correct_size = column > 0 && row > 0;

		if (!correct_size) {
			cout << "\n�������� ������. ������� ������� ������� ��������.\n\n";
			system("pause");
		}

	} while (!correct_size);


	// ���������� ������� � ������� ���
	cout << "���������� ������� " << row << "x" << column;

	cout << "\n������� ����� ������� ��� ���������: ";
	cin >> left;

	cout << "������� ������ ������� ��� ���������: ";
	cin >> right;

	random_device rd;
	mt19937 generator(rd());

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			input_arr[i][j] = int(generator() % (abs(right - left) + 1) + left);
			result_arr[i][j] = input_arr[i][j];
		}
	}
	
	cout << "\n�������� ������:\n";
	print_array(&input_arr[0][0], row, column);

	//���������� ������� �� C++
	//������� N1, ������� ������������ �������� � �������� ����������, � N2 � � ��������

	unsigned char n1 = 0;
	unsigned char n2 = 0;
	int f = 0;


	//�������� �� ++
	//���������� n1 � n2
	for (int i = 0; i < row; i++) 
	{
		for (int j = 1; j < column; j++) 
		{
			if (j-1 != column - 1)
			{
				if (input_arr[i][j - 1] < input_arr[i][j])
				{
					n1++;
				}
				else if (input_arr[i][j - 1] > input_arr[i][j])
				{
					n2++;
				}
			}
			if (i != row - 1 && j == column -1){
				if (input_arr[i + 1][0] > input_arr[i][j])
				{
					n1++;
				}
				else if (input_arr[i + 1][0] < input_arr[i][j])
				{
					n2++;
				}
			}
		}
		if (column == 1 && row - 1 != i) {
			if (input_arr[i + 1][0] > input_arr[i][0])
			{
				n1++;
			}
			else if (input_arr[i + 1][0] < input_arr[i][0])
			{
				n2++;
			}
		}
		
	}
	//�����������
	if (row * column > 1) {
		for (int i = 0; i < row; i++)
		{
			for (int j = 1; j < column; j++)
			{

				if (result_arr[i][j] > result_arr[i][j - 1])
				{
					f = result_arr[i][j - 1];
					result_arr[i][j - 1] = result_arr[i][j];
					result_arr[i][j] = f;
				}
				if (i != row - 1 && j == column - 1 && result_arr[i + 1][0] > result_arr[i][j])
				{
					f = result_arr[i][j];
					result_arr[i][j] = result_arr[i + 1][0];
					result_arr[i + 1][0] = f;
				}
			}
			if (column == 1 && row-1 != i && result_arr[i + 1][0] > result_arr[i][0]) {
				f = result_arr[i][0];
				result_arr[i][0] = result_arr[i + 1][0];
				result_arr[i + 1][0] = f;
			}

		}
	}
	cout << "\n(�������� �� C++)\n";
	
	cout << "n1: " << (int)n1 << "\n";
	cout << "n1: " << (int)n2 << "\n";
	
	cout << "\n������� ������:\n";
	print_array(&result_arr[0][0], row, column);
	



	__asm {
		xor edx, edx                // ������� ������� �����
		xor ch, ch					// n1 (�������������� ������� ������)
		xor cl, cl					// n2 (�������������� ������� ������)

		mov eax, column             //�������� �� ������ �� ������ ��������
		mul row
		cmp eax, 1
		je end_prog

		jmp start
//-------------------------------------------------------------
		//subroutine ADDRESS
		//IN: esi - i, edi - j
		//OUT: ebx - address
		ADDRESS:
			lea ebx, input_arr			// ���������� ebx ����� ������ �������
			push eax	
			push edx
			mov eax, N					// ����������� eax ����� ������ �������
								
			mov edx, esi				// ����������� edx ��������� ������ �������� (i)
			mul dl						// eax = N * i					
			add eax, edi				// eax = N * i + j
			shl eax, 2					// eax = 4 * (N * i + j)
			add ebx, eax				// ebx = a0 + 4 * (N * i + j)
			
			pop edx
			pop eax						
			ret
//-------------------------------------------------------------
		//subroutine GET_VAL
		//IN: esi - i, edi - j
		//OUT: eax - element
		GET_VAL:
			push ebx					// ��������� �������� ebx � ����
			call ADDRESS				// ���������� ebx ����� �������� �������
			mov eax, [ebx]				// eax = a[i][j]
			pop ebx						// ��������������� �������� ebx �� �����
			ret
//-------------------------------------------------------------
		//subroutine SET_VAL
		//IN: esi - i, edi - j, eax - value
		SET_VAL:
			push ebx					// ��������� �������� ebx � ����
			call ADDRESS				// ���������� ebx ����� �������� �������
			mov[ebx], eax				// a[i][j] = eax
			pop ebx						// ��������������� �������� ebx �� �����
			ret
//-------------------------------------------------------------
		//subroutine KRAI
		//IN: esi - i, edi - j, eax - 2 value, ebx - 1 value 
		KRAI :
			push ecx              //��������� ��������
			push esi
			push edi
			
			mov ecx, eax          //���������� 2 �������
			mov eax, ebx          //�������� 1 ������� ��� ����������������

			call SET_VAL          //����������� ��������
			mov eax, ecx
			mov edi, column       //��������� �� ��������� ������� ���������� ������
			dec edi
			dec esi
			call SET_VAL
			
			pop edi               //���������� �������� 
			pop esi
			pop ecx
			ret
//-------------------------------------------------------------
		//subroutine SWAP
		//IN: esi - i, edi - j, eax - 2 value, ebx - 1 value	  [i][j-1] = ebx  [i][j] = eax
		SWAP :
			push ecx
			mov ecx, eax
			mov eax, ebx 
			call SET_VAL        //[i][j] = ebx
			dec edi             //[i][j-1]
			mov eax, ecx
			call SET_VAL        //[i][j-1] = eax
			inc edi
			pop ecx
			ret
//-------------------------------------------------------------
		start :
			xor eax, eax        // 2-�� ������� ����
			xor ebx,ebx         // 1-�� ������� ����
			
			xor esi, esi		// esi - i
			xor edi, edi		// edi - j
				
			call GET_VAL		// �������� ������ �������
			mov ebx, eax        // ebx = [0][0]
			
			
			inc edi             // j++
			cmp edi, column     // � ����� ����� ���� �������
			je next_row             

			jmp next_column     //������ ������� �������, �������� ����� ������

		next_row :
			xor edi, edi		// edi - j = 0 (��� �������� � ������� �������� ����� ������)

		next_column :			
			call GET_VAL        // eax = arr[i][j+1]
			        
			//  eax = [i][j + 1] - ������ ������� ����
			//  ebx = [i][j]     - ������ ������� ����

			//  jl - op1 < op2 
			cmp ebx, eax	
			jl plus_n1
			
		    //  jg - op1 > op2
			cmp ebx, eax
			jg plus_n2

			jmp without_swap
	
		plus_n1:
			cmp edx, 0           //���� ������ ������ (�� ������� ZF = 0)
			jnz swaping_el       //��

			inc ch			     //���
			jmp without_swap

		plus_n2:
			cmp edx, 0           //���� ������ ������ (�� ������� ZF = 0)
			jnz  without_swap    //��

			inc cl               //���
			jmp without_swap
		

		swaping_el:
			cmp edi, 0
			jz l1
			jnz l2
		l1:
			call KRAI
			jmp prog_continue
		l2 :
			call SWAP
			jmp prog_continue


		without_swap :
			mov ebx, eax

		prog_continue :
		// j++; if (j < column) ������� �� ����� �������
			inc edi //j++
			cmp edi, column
			jne next_column

		// i++; if (i < row) ������� �� ����� ������
			inc esi //i++
			cmp esi, row
			jne next_row

			cmp edx, 1     //�������? (ZF = 1) (�������� ��� ��������)
			jz end_prog    //��

			inc edx        //���
			jmp start

		end_prog:
			mov n1, ch
			mov n2, cl


	}
	
	// ����� �����������

	cout << "\n(�������� �� ����������)\n";
	cout << "n1: " << (int)n1 << "\n";
	cout << "n2: " << (int)n2 << "\n";
	
	print_array(&input_arr[0][0], row, column);

	system("pause");

	return 0;
}