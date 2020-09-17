#include <avr/io.h>
#include <util/delay.h>

unsigned char FONT[16][8] = {	0B01111110,				//dotmatrix�� ǥ���� 
								0B01000010,
								0B01000010,
								0B01000010,
								0B01000010,
								0B01000010,
								0B01111110,
								0B00000000,

								0B00010000,
								0B00011000,
								0B00010100,
								0B00010010,
								0B00010000,
								0B00010000,
								0B01111110,
								0B00000000,

								0B01111110,
								0B01000000,
								0B01000000,
								0B01111110,
								0B00000010,
								0B00000010,
								0B01111110,
								0B00000000,

								0B01111110,
								0B01000000,
								0B01000000,
								0B01111110,
								0B01000000,
								0B01000000,
								0B01111110,
								0B00000000,

								0B01000010,
								0B01000010,
								0B01000010,
								0B01111110,
								0B01000000,
								0B01000000,
								0B01000000,
								0B00000000,

								0B01111110,
								0B00000010,
								0B00000010,
								0B01111110,
								0B01000000,
								0B01000000,
								0B01111110,
								0B00000000,

								0B01111110,
								0B00000010,
								0B00000010,
								0B01111110,
								0B01000010,
								0B01000010,
								0B01111110,
								0B00000000,

								0B01111110,
								0B01000010,
								0B01000010,
								0B01000000,
								0B01000000,
								0B01000000,
								0B01000000,
								0B00000000,

								0B01111110,
								0B01000010,
								0B01000010,
								0B01111110,
								0B01000010,
								0B01000010,
								0B01111110,
								0B00000000,

								0B01111110,
								0B01000010,
								0B01000010,
								0B01111110,
								0B01000000,
								0B01000000,
								0B01111110,
								0B00000000};

unsigned char  DATA[]= {		0b00101001,
								0b00101111,
								0b01101001,
								0b00101111,
								0b00000000,
								0b00111110,
								0b00100000,
								0b00000000,

								0b00001000,
								0b00011100,
								0b00110110,
								0b01100011,
								0b01001001,
								0b00001000,
								0b01111111,
								0b00000000,

								0b01000110,
								0b01101001,
								0b01001001,
								0b01100110,
								0b01000000,
								0b00000010,
								0b01111110,
								0b00000000	};

unsigned char buho[2][8] = {	0B00001000,
								0B00001000,
								0B00001000,
								0B01111111,
								0B00001000,
								0B00001000,
								0B00001000,
								0B00000000,

								0B00000000,
								0B01111110,
								0B01111110,
								0B00000000,
								0B00000000,
								0B01111110,
								0B01111110,
								0B00000000 };

unsigned char Key = 0, Row0, Row1, Row2, Row3, N = 0, L, R, M, C;
unsigned char up = 0, down = 0, right = 0, left = 0, i;
unsigned char num1, num2, sum = 0, count = 0;

unsigned char key_scan(unsigned char Row);
void numprint(unsigned char num);
void buhoprint(unsigned char num);
void fontprint();

int main(void)
{
	DDRA = 0xff;
	DDRC = 0xff;

	do {
		Row0 = key_scan(0x01);									// �� ��� 1��
		Row1 = key_scan(0x02);									//Ű �� ��� 2��
		Row2 = key_scan(0x04);									//Ű �� ��� 3��
		Row3 = key_scan(0x08);									//Ű �� ��� 4��
		Key = (Row1 | Row2 | Row3 | Row0);						//1~4�� ����ؼ� Ű �� ��� 

		switch (Key){											//Ű ���� ���� 'N' �� ����
			case 0b00010001: N=1; break;	case 0b00010010: N=2; break;	case 0b00010100: N=3; break;	case 0b00011000: N=10; break;
			case 0b00100001: N=4; break;	case 0b00100010: N=5; break;	case 0b00100100: N=6; break;	case 0b00101000: N=11; break;
			case 0b01000001: N=7; break;	case 0b01000010: N=8; break;	case 0b01000100: N=9; break;	case 0b01001000: N=12; break;
			case 0b10000001: N=14; break;	case 0b10000010: N=0; break;	case 0b10000100: N=15; break;	case 0b10001000: N=13; break;
		}

		if(N == 0){
			for(i = 0; i < up; i++){							//�̸��� �����¿�� �������� �� �����·� �����ִ� ��
				C = DATA[23];
    			for(L = 23; L > 0; L--)
					DATA[L] = DATA[L-1];
				DATA[0] = C;
			}

			for(i = 0; i < down; i++){
				C = DATA[0];
		   		for(L = 0; L < 23; L++)
					DATA[L] = DATA[L+1];
				DATA[23] = C;
			}

			for(i = 0; i < right; i++){
				for(L = 0; L < 8; L++) 
			        DATA[L] = (DATA[L] << 1) | ((DATA[L] & 0x80) >> 7);
			}

			for(i = 0; i < left; i++){
				for(L = 0; L < 8; L++) 
		        	DATA[L] = (DATA[L] << 1) | ((DATA[L] & 0x80) >> 7);
			}
			up = down = left = right = 0;

			fontprint();											//ù ȭ��� '0'�� ������ �� �̸��� ����
		}
				
		if(N == 10){											//�̸� ���� �ø���
			C = DATA[0];
		   	for(L = 0; L < 23; L++)
				DATA[L] = DATA[L+1];
			DATA[23] = C;
			up++;
			fontprint();
		}

		if(N == 11){											//�̸� �Ʒ��� ������
			C = DATA[23];
	    	for(L = 23; L > 0; L--)
				DATA[L] = DATA[L-1];
			DATA[0] = C;
			down++;
			fontprint();
		}

		if(N == 12){											//�̸� �������� �����̱�
			for(L = 0; L < 8; L++) 
		   	    DATA[L] = (((DATA[L] & 0x01) << 7) | (DATA[L] >> 1));
			left++;
			fontprint();
			}

		if(N == 13){											//�̸� ���������� �����̱�
			for(L = 0; L < 8; L++) 
		        DATA[L] = (DATA[L] << 1) | ((DATA[L] & 0x80) >> 7);
			right++;
			fontprint();
		}

		if(N == 14){											//���ϱ� ����
			count++;
			buhoprint(0);
		}

		if(N == 15){
			count = 0;
			buhoprint(1);
		}
		switch(sum){
		if(sum >= 10){
			numprint(sum/10);				
			numprint(sum%10);
		}

		if(N > 0 && N < 10) {									//�� ���� Ű�е带 ������ �� �� Ű�е忡 �´� ���ڸ� ���
			if(count == 0)
				num1 = N;

			if(count == 1)
				num2 = N;

			numprint(N);
		}

		sum = num1 + num2;


	} while(1);
}
unsigned char key_scan(unsigned char Row)						//Ű �� ���
{
	unsigned char in;

	DDRE = 0xff;
	PORTE = Row;

	DDRE = 0x0f;
	_delay_ms(5);
	in = PINE & 0xf0;

	if(in != 0x00) {
		in |= Row;
		return in;
	}
	return 0;
}

void numprint(unsigned char num)
{
	for(R = 0; R < 5; R++){
		for (L = 0; L < 8; L++){
    		PORTA = ~(0x01 << L);
        	PORTC = FONT[num][L];
			_delay_ms(3);	
    	}
	}
}

void buhoprint(unsigned char num)
{
	for(R = 0; R < 50; R++){
		for (L = 0; L < 8; L++){
   			PORTA = ~(0x01 << L);
   	   		PORTC = buho[num][L];
    		_delay_ms(1);	
   		}
	}
}



void fontprint()
{
	for(R = 0; R < 100; R++){
		for (L = 0; L < 8; L++){
   			PORTA = ~(0x01 << L);
   	   		PORTC = DATA[L];
    		_delay_ms(1);	
   		}
	}
}
