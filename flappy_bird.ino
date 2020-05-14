#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LEDARRAY_D 6
#define LEDARRAY_C 7
#define LEDARRAY_B 8
#define LEDARRAY_A 9
#define LEDARRAY_G 10
#define LEDARRAY_DI 11
#define LEDARRAY_CLK 12
#define LEDARRAY_LAT 13

//************************************

unsigned counts = 0;
unsigned char first;
unsigned char score = 0;

unsigned char col1, col2;
unsigned char cols[16][24];
unsigned char col_result[16][2];
unsigned char rows[4][16];
unsigned char first_row = 2;
bool flag = true;
unsigned char bird_step = 0;
unsigned char col_speed = 100;
unsigned char tonepin = 3;

LiquidCrystal_I2C lcd(0x27,16,2);  //端口�?, 显示模式 16x2

unsigned char cols_over[16][24] = 
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

unsigned char cols_start[16][24] = 
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

//************************************************************************
//*************************************************************************

unsigned char bird_height = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDARRAY_D, OUTPUT);
  pinMode(LEDARRAY_C, OUTPUT);
  pinMode(LEDARRAY_B, OUTPUT);
  pinMode(LEDARRAY_A, OUTPUT);
  pinMode(LEDARRAY_G, OUTPUT);
  pinMode(LEDARRAY_DI, OUTPUT);
  pinMode(LEDARRAY_CLK, OUTPUT);
  pinMode(LEDARRAY_LAT, OUTPUT);
  randomSeed(analogRead(A0));
  init_rows();

  attachInterrupt(0, bird_up, RISING);

  game_begin();

  pinMode(3, OUTPUT); 
  
  lcd.init();                  // 初始化LCD
  lcd.backlight();//设置LCD背景等亮
  Serial.begin(9600);
}

//***********************************************


void loop() {
  // put your main code here, to run repeatedly:
  if (counts % 6 == 4)
  {
    random_row(first_row % 4);
    first_row--;
    score++;
  }
  if (flag){
  print_score();}
  for (unsigned char i = 1; i < col_speed; i++)
  {
    bird_step++;
    if (bird_step % 30 == 0)
    {
      bird_down();
    }
    calculate(counts);
    Display(col_result);
  }

  col_speed = 100 / (counts / 12);
  
  counts++;

}

void game_begin()
{
  for (unsigned char i = 1; i < 250; i++)
  {
    for (unsigned char i = 0; i < 16; i++)
    {
      for (unsigned char j = 0; j < 2; j++)
      {
        col_result[i][j] = 0; //鎭㈠涓洪浂
      }
    }
    for (unsigned char i = 0; i < 16; i++)
    {
      for (unsigned char j = 0; j < 16; j++)
      {
        if (cols_start[i][j] == 1)
        {
          Scan_col(j);
          col_result[i][0] += col2;
          col_result[i][1] += col1;
        }
      }
      col_result[i][0] = B11111111 - col_result[i][0];
      col_result[i][1] = B11111111 - col_result[i][1];
    }
    Display(col_result);
  }

}

//鐐瑰嚮楦熶笂锟�?
void bird_up()
{
  if (bird_height < 15)
  {
    bird_height++;
  }
  else
  {
    bird_height = 15;
  }
}

void print_score()
{
  lcd.init();                  // 初始化LCD
  lcd.print("score:");
  lcd.print(score);
  lcd.backlight();
}

void bird_down()
{
  if (bird_height != 0)
  {
    bird_height--;
  }
}

void gameover()
{
  flag = false;
}


//鍒濆鍖栬鐭╅樀
void init_rows()
{
  for (unsigned char i = 0; i < 16; i++)
  {
    for (unsigned char j = 0; j < 2; j++)
    {
      col_result[i][j] = 0; //鎭㈠涓洪浂
    }
  }

  for (unsigned char i = 0; i < 4; i++)
  {
    unsigned char ran_num = random(2, 12);
    for (unsigned char j = 0; j < 16; j++)
    {
      if (j != ran_num && j != ran_num + 1 && j != ran_num + 2)
      {
        rows[i][j] = 1;
      }
    }
  }
}

void random_row(unsigned char first_num)
{
  unsigned char ran_num = random(2, 12);
  for (unsigned char j = 0; j < 16; j++)
  {
    rows[first_num][j] = 0;//鍒濆锟�??
  }
  for (unsigned char j = 0; j < 16; j++)
  {
    if (j != ran_num && j != ran_num + 1 && j != ran_num + 2)
    {
      rows[first_num][j] = 1;//娑堝け锟�??
    }
  }
}

//璁＄畻鍚戦噺鐭╅樀
void calculate(unsigned char counts)
{
  for (unsigned char i = 0; i < 16; i++)
  {
    for (unsigned char j = 0; j < 2; j++)
    {
      col_result[i][j] = 0; //鎭㈠涓洪浂
    }
  }

  if (flag)
  {
    for (unsigned char i = 0; i < 16; i++)
    {
      for (unsigned char j = 0; j < 24; j++)
      {
        cols[i][j] = 0; //鎭㈠涓洪浂
      }
    }
    for (unsigned char i = 0 ; i < 16; i++)
    {
      for (unsigned char j = 0; j < 4; j++)
      {
        if (rows[j % 4][i] != 0 )
        {
          if (counts + 6 * j >= 0) {
            cols[i][(counts + 6 * j) % 24] = 1;
          }
          if (counts + 6 * j + 1 >= 0) {
            cols[i][(counts + 6 * j + 1) % 24] = 1; //瓒呰�?16涓洪澶囧垪锛屽綋寮€澶寸粨鏉熸椂渚胯繘锟�?
          }
        }
      }
    }

    if (cols[bird_height][15] == 1)
    {
      gameover();
    }
    else
    {
      cols[bird_height][15] = 1;
    }


    for (unsigned char i = 0; i < 16; i++)
    {
      for (unsigned char j = 0; j < 16; j++)
      {
        if (cols[i][j] == 1)
        {
          Scan_col(j);
          col_result[i][0] += col2;
          col_result[i][1] += col1;
        }
      }

      col_result[i][0] = B11111111 - col_result[i][0];
      col_result[i][1] = B11111111 - col_result[i][1];
    }
  }
  else
  {
    for (unsigned char i = 0; i < 16; i++)
    {
      for (unsigned char j = 0; j < 16; j++)
      {
        if (cols_over[i][j] == 1)
        {
          Scan_col(j);
          col_result[i][0] += col2;
          col_result[i][1] += col1;
        }
      }

      col_result[i][0] = B11111111 - col_result[i][0];
      col_result[i][1] = B11111111 - col_result[i][1];
    }
  }
}


//杈撳嚭绗琲锟�??
void Scan_col(unsigned char col_num)
{
  switch (col_num)
  {
    case 0:
      col1 = B00000000;
      col2 = B10000000;
      break;
    case 1:
      col1 = B00000000;
      col2 = B01000000;
      break;
    case 2:
      col1 = B00000000;
      col2 = B00100000;
      break;
    case 3:
      col1 = B00000000;
      col2 = B00010000;
      break;
    case 4:
      col1 = B00000000;
      col2 = B00001000;
      break;
    case 5:
      col1 = B00000000;
      col2 = B00000100;
      break;
    case 6:
      col1 = B00000000;
      col2 = B00000010;
      break;
    case 7:
      col1 = B00000000;
      col2 = B00000001;
      break;
    case 8:
      col1 = B10000000;
      col2 = B00000000;
      break;
    case 9:
      col1 = B01000000;
      col2 = B00000000;
      break;
    case 10:
      col1 = B00100000;
      col2 = B00000000;
      break;
    case 11:
      col1 = B00010000;
      col2 = B00000000;
      break;
    case 12:
      col1 = B00001000;
      col2 = B00000000;
      break;
    case 13:
      col1 = B00000100;
      col2 = B00000000;
      break;
    case 14:
      col1 = B00000010;
      col2 = B00000000;
      break;
    case 15:
      col1 = B00000001;
      col2 = B00000000;
      break;
  }
}

//************************************************************
//num涓哄瓧锟�??  dat[][32]涓哄瓧妯＄殑鍚嶇О
//*************************************************************
void Display(const unsigned char cols[16][2])
{
  for (unsigned char i = 0; i < 16; i++)
  {
    digitalWrite(LEDARRAY_G, HIGH);   //��������ʱ��ر���ʾ���ȸ��������ݣ���138��ʾ�С���ֹ��Ӱ��
    Send(cols[i][1]);
    Send(cols[i][0]);

    digitalWrite(LEDARRAY_LAT, HIGH);         
    delayMicroseconds(1);

    digitalWrite(LEDARRAY_LAT, LOW);
    delayMicroseconds(1);

    Scan_row(i);

    digitalWrite(LEDARRAY_G, LOW);
    delayMicroseconds(300);//��ʱһ��ʱ�䣬��LED������			
  }
}

//鏄剧ず锟�??

void Scan_row( unsigned char row_num)
{
  switch (row_num)
  {
    case 0:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 1:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 2:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 3:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 4:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 5:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 6:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 7:
      digitalWrite(LEDARRAY_D, LOW); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 8:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 9:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 10:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 11:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, LOW); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 12:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 13:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, LOW); digitalWrite(LEDARRAY_A, HIGH);
      break;
    case 14:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, LOW);
      break;
    case 15:
      digitalWrite(LEDARRAY_D, HIGH); digitalWrite(LEDARRAY_C, HIGH); digitalWrite(LEDARRAY_B, HIGH); digitalWrite(LEDARRAY_A, HIGH);
      break;
    default : break;
  }
}

//****************************************************
//鍙戦€佹暟锟�??
//****************************************************
void Send( unsigned char dat)
{
  unsigned char i;
  digitalWrite(LEDARRAY_CLK, LOW);
  delayMicroseconds(1);;
  digitalWrite(LEDARRAY_LAT, LOW);
  delayMicroseconds(1);;

  for ( i = 0 ; i < 8 ; i++ )
  {
    if ( dat & 0x01 )
    {
      digitalWrite(LEDARRAY_DI, HIGH);
    }
    else
    {
      digitalWrite(LEDARRAY_DI, LOW);
    }

    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK, HIGH);       //涓婂崌娌垮彂閫佹暟锟�??
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK, LOW);
    delayMicroseconds(1);
    dat >>= 1;

  }
}
