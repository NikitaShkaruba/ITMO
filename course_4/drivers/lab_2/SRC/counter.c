#include "counter.h"

//���������� ������ T0 ��� �������

void initialize_counter() {
	TMOD|=0b00000100;//����� �������� ��� �������0
	TH0=TL0=0;//������� �������
	TR0=1;      //��������� ���� ������� 0
}

u8 get_count() {
	return TL0;
}