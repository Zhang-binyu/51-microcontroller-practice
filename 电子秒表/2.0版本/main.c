#include"reg52.h"

typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;//����38�������������

//��������������ƽ�
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;

u8 ms=0;
u8 second=0;
u8 minute=0;
u8 hour=0;		//����ʱ����

u16 num=0;
//��������ܳ�ֵ�Լ��жϴ�������

unsigned char code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//��Ϊ���ǵĵ�Ƭ��������ͺ���3461AS-1Ϊ�����������

//ʹ�ú궨������������µļ�ֵ
#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY_UNPRESS	0

#define KEY_MATRIX_PORT P1	//	ʹ�ú궨����󰴼����ƿ�

void DelayMS(u8 i)
{
	//��Լ 1ms
	u8 j=100;
	while(i--){
		while(j--);  
	}
}

/*
	������		��	key_matrix_ranks_scan
	��������	:	ʹ������ʽɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
	����		��	��
	���		�� 	key_value:1-16����Ӧs1-s16����
					0:����δ����
*/

u8 key_matrix_ranks_scan(void)
{
	u8 key_value=0;

	KEY_MATRIX_PORT=0xf7;	//	����һ�и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xf7)	//	�жϵ�һ�а����Ƿ���
	{
		DelayMS(10);	// ����
		switch(KEY_MATRIX_PORT)	//	�����һ�а������º�ļ�ֵ
		{
			case 0x77:key_value=1;break;
			case 0xb7:key_value=5;break;
			case 0xd7:key_value=9;break;
			case 0xe7:key_value=13;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xf7);	//	�ȴ������ɿ�

	KEY_MATRIX_PORT=0xfb;	//	���ڶ��и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfb)	//	�жϵڶ��а����Ƿ���
	{
		DelayMS(10);	//	����
		switch(KEY_MATRIX_PORT)	//	����ڶ��а������º�ļ�ֵ
		{
			case 0x7b:key_value=2;break;
			case 0xbb:key_value=6;break;
			case 0xdb:key_value=10;break;
			case 0xeb:key_value=14;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfb);	//	�ȴ������ɿ�

	KEY_MATRIX_PORT=0xfd;	//	�������и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfd)	//	�жϵ����а����Ƿ���
	{
		DelayMS(10);	//	����
		switch(KEY_MATRIX_PORT)	//	��������а������º�ļ�ֵ
		{
			case 0x7d:key_value=3;break;
			case 0xbd:key_value=7;break;
			case 0xdd:key_value=11;break;
			case 0xed:key_value=15;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfd);	//�ȴ������ɿ�

	KEY_MATRIX_PORT=0xfe;	//�������и�ֵ0������ȫΪ1
	if(KEY_MATRIX_PORT!=0xfe)	//�жϵ����а����Ƿ���
	{
		DelayMS(10);	//����
		switch(KEY_MATRIX_PORT)	//��������а������º�ļ�ֵ
		{
			case 0x7e:key_value=4;break;
			case 0xbe:key_value=8;break;
			case 0xde:key_value=12;break;
			case 0xee:key_value=16;break;
		}
	}
	while(KEY_MATRIX_PORT!=0xfe);	//�ȴ������ɿ�

	return key_value;
}

void DIGdisplay()
{	 	
	 	 LSA = 0 ;LSB = 0 ; LSC = 0 ;P0 = smgduan[second%10];DelayMS(1);P0=0x00;  	//��һλ����ܣ���Ӱ		
		 LSA = 1 ;LSB = 0 ; LSC = 0 ;P0 = smgduan[second/10];DelayMS(1);P0=0x00; 		//�ڶ�λ����ܣ���Ӱ
		 

		 LSA = 1 ;LSB = 1 ; LSC = 0 ;P0 = smgduan[minute%10];DelayMS(1);P0=0x00;		//����λ����ܣ���Ӱ
		 LSA = 0 ;LSB = 0 ; LSC = 1 ;P0 = smgduan[minute/10];DelayMS(1);P0=0x00;		//����λ����ܣ���Ӱ
		 
		 LSA = 0 ;LSB = 1 ; LSC = 1 ;P0 = smgduan[hour%10];DelayMS(1);P0=0x00;		//����λ����ܣ���Ӱ
		 LSA = 1 ;LSB = 1 ; LSC = 1 ;P0 = smgduan[hour/10];DelayMS(1);P0=0x00;		//����λ����ܣ���Ӱ
		 
		 LSA = 0 ;LSB = 1 ; LSC = 0 ;P0 = 0x40;DelayMS(1);P0=0x00;			
		 LSA = 1 ;LSB = 0 ; LSC = 1 ;P0 = 0x40;DelayMS(1);P0=0x00;		//����λ�͵���λ��ʾһ�ܣ���Ӱ													 
}	 


void time0_init(void)
{
	TMOD=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1
	TH0=0xFC;	//����ʱ������ֵ����ʱ50ms
	TL0=0x66;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	
}

void time0()interrupt 1//��ʱ��0�жϺ���
{
	TH0 = 0xFC;		//���ö�ʱ��ֵ  1ms
	TL0 = 0x66;		//���ö�ʱ��ֵ

	num++;
	if(num==1000)        //1ms
	{
   		num=0;
    	ms++;
		if(ms==1000){
			ms=0;
			second++;
		}
		if(second==60){
			second=0;
			minute++;
		}
		if(minute==60){
			minute=0;
			hour++;
		}
		if(hour==24){
			hour=0;
		}
	}						
}
void main()
{
	u8 key=0;
	time0_init();
	while(1){
		DIGdisplay();
		if(KEY1==0){
			DelayMS(1);
			if(KEY1==0){
				TR0=1;
				while(KEY1==0);
			}
		}if(KEY2==0){
			DelayMS(1);
			if(KEY2==0){
				TR0=0;
				while(KEY2==0);
			}
		}if(KEY3==0){
			DelayMS(1);
			if(KEY3==0){
				hour=0;
				minute=0;
				second=0;
				while(KEY3==0);
			}
		}
		key=key_matrix_ranks_scan();
		if(key!=0){
			switch(key){
				case 1:if(second!=59)second++;break;		//����һ
				case 2:if(second!=0)second--;break;			//���һ
				case 3:second=59;break;						//����Ϊ��ʮ��
				case 4:second=0;break;						//����Ϊ��
			
				case 5:if(minute!=59)minute++;break;		//������һ
				case 6:if(minute!=0)minute--;break;			//���Ӽ�һ
				case 7:minute=59;break;						//������Ϊ��ʮ��
				case 8:minute=0;break;						//������Ϊ��
			
				case 9:if(hour!=23)hour++;break;			//Сʱ��һ
				case 10:if(hour!=0)hour--;break;			//Сʱ��һ
				case 11:hour=23;break;						//Сʱ��Ϊ��ʮ��
				case 12:hour=0;break;						//Сʱ��Ϊ��
			}
		}
	}
}
