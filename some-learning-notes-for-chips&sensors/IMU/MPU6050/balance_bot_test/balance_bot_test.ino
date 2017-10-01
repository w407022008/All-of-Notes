/*
   SCL(clock line)(pin A5)
   SDA(data line)(pin A4)
   INT(interrupt)(pin D2)
*/
#include <MPU6050.h>
#include <Timer.h>
#include <I2Cdev.h>
#include <Wire.h>
//#include <MSMotorShield.h>
//MS_DCMotor motor(3, MOTOR12_1KHZ); // create motor #2, 64KHz pwm
Timer t;//时间类
MPU6050 accelgyro;//加速度计陀螺仪类
#define ENA 3
#define IN1 4
#define IN2 5
#define ENB 6
#define IN3 7
#define IN4 8
//驱动
float targetAngle,targetAngle_error;
//采样时间
float timeChange = 20; //滤波法采样时间间隔毫秒
float dt = timeChange * 0.001; //注意：dt的取值为滤波器采样时间
// 加速度计、陀螺仪
float angleAx, gyroGx, angleAy, gyroGy, angleAz, gyroGz; //计算后的角度（与各轴夹角）和角速度
int16_t ax, ay, az, gx, gy, gz;//陀螺仪原始数据 3个加速度+3个角速度
float axo = 0, ayo = 0, azo = 0;             //加速度计偏移量  
float angle_x_ini,angle_y_ini;               //初始欧拉角度
float gxo = 0, gyo = 0, gzo = 0;             //陀螺仪偏移量  
float norm;                                   //方向模值
//常数
float pi = 3.1415926;  
float AcceRatio = 16384.0;                  //加速度计比例系数,采用最小量程±2g：系数=  2^16/4 LSB/g
float GyroRatio = 131.0;                    //陀螺仪比例系数，采用最小量程±250°/s：系数= 2^16/500 LSB/(°/s) 
//卡尔曼滤波参数与函数
float angle_x,angle_x_dot, angle_x_dot2=0.,angle_y,angle_y_dot, angle_y_dot2=0.;//x,y轴角度、角速度、角加速度状态量
float P_x[3][3] = {{ 10, 0, 0 },
                 { 0, 10, 0 },
                 { 0, 0, 10 }};
float P_y[3][3] = {{ 10, 0, 0 },
                 { 0, 10, 0 },
                 { 0, 0, 10 }};
float Q_angle = 1, Q_velo = 1, Q_acce = 10; //角度数据置信度,角速度数据置信度
float R_angle = 1, R_velo = 1,angle_m_x,gyro_m_x,angle_m_y,gyro_m_y;
//smoothing
float list_x[3][5],list_y[3][5];
/*
************* setup & calibration ***************
 */
void setup() {
    Wire.begin();  
    Serial.begin(115200);  
    pinMode(ENA, OUTPUT); //PWM right wheel
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT); //PWM left wheel
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    accelgyro.initialize();                 //初始化  
    Serial.println("Now,we make samples firstly!");
////////////////////////////////////////////////////////////////
    unsigned short times = 200;             //采样次数  
    for(int i=0;i<times;i++)  
    {  
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //读取六轴原始数值  
        axo += ax/AcceRatio; ayo += ay/AcceRatio; azo += az/AcceRatio;      //采样和  
        gxo += gx/GyroRatio; gyo += gy/GyroRatio; gzo += gz/GyroRatio;  
//        Serial.print("The ");Serial.print(i+1);Serial.println("th times sample");
    }  
    axo /= (times); ayo /= (times); azo /= (times); //计算加速度计偏移  
    gxo /= (times); gyo /= (times); gzo /= (times); //计算陀螺仪偏移  
    Serial.println("\nSample finished!");Serial.println("The sample biases we get are");
    Serial.println("axo,\t ayo,\t azo,\t angle_xo,\t angle_yo,\t gxo,\t\t gyo,\t\t gzo");
    norm = sqrt(axo*axo + ayo*ayo + azo*azo);
    Serial.print(axo/norm);Serial.print("g,\t");  
    Serial.print(ayo/norm);Serial.print("g,\t");  
    Serial.print(azo/norm);Serial.print("g,\t");  
    angle_x_ini = atan2(ay, az) * 180 / PI; //计算与x轴夹角
    angle_y_ini = -atan2(ax, az) * 180 / PI; //计算与y轴夹角
    Serial.print(angle_x_ini);Serial.print("deg,\t");
    Serial.print(angle_y_ini);Serial.print("deg,\t");
    Serial.print(gxo);Serial.print("degree,\t");  
    Serial.print(gyo);Serial.print("degree,\t");  
    Serial.print(gzo);Serial.println("degree\n\n"); 
    Serial.println("Here we go!");
//////////////////////////////////////////////////////////////////////
//  motor.setSpeed(169); // set the speed to 200/255

  int tickEvent1 = t.every(timeChange, getangle); //本语句执行以后timeChange毫秒执行回调函数getangle
  int tickEvent2 = t.every(50, printout) ; //本语句执行以后50毫秒执行回调函数printout，串口输出
//  while(1);
}

void loop() {

  t.update();//时间操作系统运行

}

/*
************ print function **************** 
 */
void printout(){
  switch (0) //0:x&y;;  1:only x;;  2:only y;;  3:nothing
  {
    case 0:
      Serial.println("angle_m_x \t angle_kf_x \t velo_m_x \t velo_kf_x \t acce_kf_x \t\t angle_m_y \t angle_kf_y \t velo_m_y \t velo_kf_y \t acce_kf_y");
      Serial.print(angleAx);Serial.print(" \t\t");
      Serial.print(angle_x);Serial.print("\t\t");
      Serial.print(gx);Serial.print("\t\t");
      Serial.print(angle_x_dot);Serial.print("\t\t");
      Serial.print(angle_x_dot2);Serial.print("\t\t\t");
      Serial.print(angleAy);Serial.print(" \t\t");
      Serial.print(angle_y);Serial.print("\t\t");
      Serial.print(gy);Serial.print("\t\t");
      Serial.print(angle_y_dot);Serial.print("\t\t");
      Serial.println(angle_y_dot2);
      break;
    case 1:
      Serial.println("angle_m_x \t angle_kf_x \t velo_m_x \t velo_kf_x \t acce_kf_x");
      Serial.print(angleAx);Serial.print(" \t\t");
      Serial.print(angle_x);Serial.print("\t\t");
      Serial.print(gx);Serial.print("\t\t");
      Serial.print(angle_x_dot);Serial.print("\t\t");
      Serial.println(angle_x_dot2);
      break;
    case 2:
      Serial.println("angle_m_y \t angle_kf_y \t velo_m_y \t velo_kf_y \t acce_kf_y");
      Serial.print(angleAy);Serial.print(" \t\t");
      Serial.print(angle_y);Serial.print("\t\t");
      Serial.print(gy);Serial.print("\t\t");
      Serial.print(angle_y_dot);Serial.print("\t\t");
      Serial.println(angle_y_dot2);
      break;
    case 3:
      break;
  }
 
    modify();
}

/*
************ control function **************** 
 */
void Foreword(){//B逆A顺
  digitalWrite(IN1,HIGH);//pin4
  digitalWrite(IN2,LOW);//pin5
  digitalWrite(IN3,LOW);//pin7
  digitalWrite(IN4,HIGH);//pin8
}

void Backword(){//A逆B顺
  digitalWrite(IN1,LOW);//pin4
  digitalWrite(IN2,HIGH);//pin5
  digitalWrite(IN3,HIGH);//pin7
  digitalWrite(IN4,LOW);//pin8
}

void Stop(){
  digitalWrite(IN1,LOW);//pin4
  digitalWrite(IN2,LOW);//pin5
  digitalWrite(IN3,LOW);//pin7
  digitalWrite(IN4,LOW);//pin8
}

void modify()
{
  targetAngle=angle_x_ini;
  targetAngle_error = angle_x - targetAngle;
  Serial.println(targetAngle_error);
  if(targetAngle_error>10)
  {
    //foreword
    analogWrite(ENA,60);
    analogWrite(ENB,100);
    Foreword();
  }
  else if(targetAngle_error<-10)
  {
    //backword
    analogWrite(ENA,60);
    analogWrite(ENB,100);
    Backword();
  }
  else
  {
    float velo = map(abs(angle_x_dot),1,50,50,70);
    if(angle_x_dot <-1&&angle_x<0)
    {
      analogWrite(ENA,abs(velo));
      analogWrite(ENB,abs(velo));
      Backword();
    }
    else if(angle_x_dot>1&&angle_x>0)
    {
      analogWrite(ENA,abs(velo));
      analogWrite(ENB,abs(velo));
      Foreword();
    }
    else
    {
      Stop();
    }
//    motor.run(RELEASE); // stopped
  }
}

/*
************ get Roll & Pitch angle **************** 
 */
void getangle(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//读取原始6个数据
  angleAx = atan2(ay, az) * 180 / PI; //计算与x轴夹角
  angleAy = -atan2(ax, az) * 180 / PI; //计算与y轴夹角
  angleAz = atan2(ax, ay) * 180 / PI; //计算与z轴夹角 

  gx = gx/GyroRatio-gxo;gy = gy/GyroRatio-gyo;gz = gz/GyroRatio-gzo;
  getangle_x();
  getangle_y();
}

void getangle_x(){
  static float K[3][3],error_angle,error_velo, E; 

  if (1) {//1:一阶卡尔曼双测量滤波器  
      float angle_m_x=angleAx,gyro_m_x=gx;
      angle_x = angle_x + angle_x_dot*dt;
    
      P_x[0][0] += (P_x[1][0]+P_x[0][1])*dt + P_x[1][1]*dt*dt + Q_angle;
      P_x[0][1] += P_x[1][1]*dt;
      P_x[1][0] += P_x[0][1];
      P_x[1][1] += Q_velo;
    
      E = (P_x[0][0]+R_angle)*(P_x[1][1]+R_velo)-P_x[0][1]*P_x[1][0];
      K[0][0]= ((P_x[1][1]+R_velo)*P_x[0][0]-P_x[0][1]*P_x[1][0])/E;
      K[0][1]= ((P_x[0][0]+R_angle)*P_x[0][1]-P_x[0][0]*P_x[0][1])/E;
      K[1][0]= (P_x[1][0]*(P_x[1][1]+R_velo)-P_x[1][1]*P_x[1][0])/E;
      K[1][1]= (P_x[1][1]*(P_x[0][0]+R_angle)-P_x[1][0]*P_x[0][1])/E;
    
      P_x[0][0] += -K[0][0]*P_x[0][0] - K[0][1]*P_x[1][0];
      P_x[0][1] += -K[0][0]*P_x[0][1] - K[0][1]*P_x[1][1];
      P_x[1][0] += -K[1][1]*P_x[1][0] - K[1][0]*P_x[0][0];
      P_x[1][1] += -K[1][0]*P_x[0][1] - K[1][1]*P_x[1][1];
    
      angle_x += K[0][0]*(angle_m_x-angle_x) + K[0][1]*(gyro_m_x-angle_x_dot);
      angle_x_dot += K[1][0]*(angle_m_x-angle_x) + K[1][1]*(gyro_m_x-angle_x_dot);
  }
  else{//0:二阶卡尔曼双参滤波器
      float angle_m_x=angleAx,gyro_m_x=gx;
      angle_x = angle_x + angle_x_dot*dt + 1/2*angle_x_dot2*dt*dt;
      angle_x_dot = angle_x_dot + angle_x_dot2*dt;
      angle_x_dot2 = angle_x_dot2;
    
      P_x[0][0] += (P_x[0][1]+P_x[1][0])*dt + (1/2*P_x[2][0]+P_x[1][1]+1/2*P_x[0][2])*dt*dt + (1/2*P_x[2][1]+1/2*P_x[1][2])*dt*dt*dt + 1/4*P_x[2][2]*dt*dt*dt*dt + Q_angle;
      P_x[0][1] = (P_x[0][1]+P_x[1][1]*dt+1/2*P_x[2][1]*dt*dt) + (P_x[0][2]+P_x[1][2]*dt+1/2*P_x[2][2]*dt*dt)*dt;
      P_x[0][2] = (P_x[0][2]+P_x[1][2]*dt+1/2*P_x[2][2]*dt*dt);
      P_x[1][0] += (P_x[2][0]+P_x[1][1])*dt + (P_x[2][1]+1/2*P_x[1][2])*dt*dt + 1/2*P_x[2][2]*dt*dt*dt;
      P_x[1][1] = P_x[1][1]+P_x[2][1]*dt + (P_x[1][2]+P_x[2][2]*dt)*dt + Q_velo;
      P_x[1][2] = P_x[2][2]*dt;
      P_x[2][0] += P_x[2][1]*dt + 1/2*P_x[2][2]*dt*dt;
      P_x[2][1] += P_x[2][2]*dt;
      P_x[2][2] += Q_acce;
    
      error_angle = angle_m_x - angle_x;
      error_velo = gyro_m_x-angle_x_dot;
      
      E = (P_x[0][0]+R_angle)*(P_x[1][1]+R_velo)-P_x[0][1]*P_x[1][0];
      K[0][0]= ((P_x[1][1]+R_velo)*P_x[0][0]-P_x[0][1]*P_x[1][0])/E;
      K[0][1]= ((P_x[0][0]+R_angle)*P_x[0][1]-P_x[0][0]*P_x[0][1])/E;
      K[1][0]= (P_x[1][0]*(P_x[1][1]+R_velo)-P_x[1][1]*P_x[1][0])/E;
      K[1][1]= (P_x[1][1]*(P_x[0][0]+R_angle)-P_x[1][0]*P_x[0][1])/E;
      K[2][0]= (P_x[2][0]*(P_x[1][1]+R_velo)-P_x[2][1]*P_x[1][0])/E;
      K[2][1]= (P_x[2][1]*(P_x[0][0]+R_angle)-P_x[2][0]*P_x[0][1])/E;
      
      P_x[2][0] -= K[2][0]*P_x[0][0]+K[2][1]*P_x[1][0];
      P_x[2][1] -= K[2][0]*P_x[0][1]+K[2][1]*P_x[1][1];
      P_x[2][2] -= K[2][0]*P_x[0][2]+K[2][1]*P_x[1][2];
      static float p0=P_x[0][0],p1=P_x[0][1],p2=P_x[0][2];
      P_x[0][0] -= K[0][0]*P_x[0][0]+K[0][1]*P_x[1][0];
      P_x[0][1] -= K[0][0]*P_x[0][1]+K[0][1]*P_x[1][1];
      P_x[0][2] -= K[0][0]*P_x[0][2]+K[0][1]*P_x[1][2];
      P_x[1][0] -= K[1][0]*p0+K[1][1]*P_x[1][0];
      P_x[1][1] -= K[1][0]*p1+K[1][1]*P_x[1][1];
      P_x[1][2] -= K[1][0]*p2+K[1][1]*P_x[1][2];
    
      angle_x += K[0][0]*error_angle+K[0][1]*error_velo;
      angle_x_dot += K[1][0]*error_angle+K[1][1]*error_velo;
      angle_x_dot2 += K[2][0]*error_angle+K[2][1]*error_velo;
  }

//  Serial.print(angle_x);Serial.print("\t");
//  Serial.print(angle_x_dot);Serial.print("\t");
//  Serial.print(angle_x_dot2);Serial.println("\t");

  float sum_angle=0., sum_angle_dot=0., sum_angle_dot2=0.;
  int count=0,i=0,j=0,k=0;
  if(count<2) 
  {
    count++;
  }
  for(j=0; j<3;++j)
  {
    for(i=0; i<1; ++i)
    {
      list_x[j][i]=list_x[j][i+1];
    }
  }
  list_x[0][1]=angle_x;list_x[1][1]=angle_x_dot;list_x[2][1]=angle_x_dot2;
  if(count=2){
    for(i=0;i<2;++i)
    {
      sum_angle += list_x[0][i]*(i+1)/3;
      sum_angle_dot += list_x[1][i]*(i+1)/3;
      sum_angle_dot2 += list_x[2][i]*(i+1)/3;
    }
    angle_x = sum_angle;
    angle_x_dot = sum_angle_dot;
    angle_x_dot2 = sum_angle_dot2;
  }
  i=0;j=0;k=0;
}

void getangle_y(){
  static float K[3][3],error_angle,error_velo, E; 
  if (1){//1:一阶卡尔曼双测量滤波器  
      float angle_m_y=angleAy,gyro_m_y=gy;
      angle_y = angle_y + angle_y_dot*dt;
    
      P_y[0][0] += (P_y[1][0]+P_y[0][1])*dt + P_y[1][1]*dt*dt + Q_angle;
      P_y[0][1] += P_y[1][1]*dt;
      P_y[1][0] += P_y[0][1];
      P_y[1][1] += Q_velo;
    
      E = (P_y[0][0]+R_angle)*(P_y[1][1]+R_velo)-P_y[0][1]*P_y[1][0];
      K[0][0]= ((P_y[1][1]+R_velo)*P_y[0][0]-P_y[0][1]*P_y[1][0])/E;
      K[0][1]= ((P_y[0][0]+R_angle)*P_y[0][1]-P_y[0][0]*P_y[0][1])/E;
      K[1][0]= (P_y[1][0]*(P_y[1][1]+R_velo)-P_y[1][1]*P_y[1][0])/E;
      K[1][1]= (P_y[1][1]*(P_y[0][0]+R_angle)-P_y[1][0]*P_y[0][1])/E;
    
      P_y[0][0] += -K[0][0]*P_y[0][0] - K[0][1]*P_y[1][0];
      P_y[0][1] += -K[0][0]*P_y[0][1] - K[0][1]*P_y[1][1];
      P_y[1][0] += -K[1][1]*P_y[1][0] - K[1][0]*P_y[0][0];
      P_y[1][1] += -K[1][0]*P_y[0][1] - K[1][1]*P_y[1][1];
    
      angle_y += K[0][0]*(angle_m_y-angle_y) + K[0][1]*(gyro_m_y-angle_y_dot);
      angle_y_dot += K[1][0]*(angle_m_y-angle_y) + K[1][1]*(gyro_m_y-angle_y_dot);
  }
  else{//0:二阶卡尔曼双参滤波器
      float angle_m_y=angleAy,gyro_m_y=gy;
      angle_y = angle_y + angle_y_dot*dt + 1/2*angle_y_dot2*dt*dt;
      angle_y_dot = angle_y_dot + angle_y_dot2*dt;
      angle_y_dot2 = angle_y_dot2;
    
      P_y[0][0] += (P_y[0][1]+P_y[1][0])*dt + (1/2*P_y[2][0]+P_y[1][1]+1/2*P_y[0][2])*dt*dt + (1/2*P_y[2][1]+1/2*P_y[1][2])*dt*dt*dt + 1/4*P_y[2][2]*dt*dt*dt*dt + Q_angle;
      P_y[0][1] = (P_y[0][1]+P_y[1][1]*dt+1/2*P_y[2][1]*dt*dt) + (P_y[0][2]+P_y[1][2]*dt+1/2*P_y[2][2]*dt*dt)*dt;
      P_y[0][2] = (P_y[0][2]+P_y[1][2]*dt+1/2*P_y[2][2]*dt*dt);
      P_y[1][0] += (P_y[2][0]+P_y[1][1])*dt + (P_y[2][1]+1/2*P_y[1][2])*dt*dt + 1/2*P_y[2][2]*dt*dt*dt;
      P_y[1][1] = P_y[1][1]+P_y[2][1]*dt + (P_y[1][2]+P_y[2][2]*dt)*dt + Q_velo;
      P_y[1][2] = P_y[2][2]*dt;
      P_y[2][0] += P_y[2][1]*dt + 1/2*P_y[2][2]*dt*dt;
      P_y[2][1] += P_y[2][2]*dt;
      P_y[2][2] += Q_acce;
    
      error_angle = angle_m_y - angle_y;
      error_velo = gyro_m_y-angle_y_dot;
      
      E = (P_y[0][0]+R_angle)*(P_y[1][1]+R_velo)-P_y[0][1]*P_y[1][0];
      K[0][0]= ((P_y[1][1]+R_velo)*P_y[0][0]-P_y[0][1]*P_y[1][0])/E;
      K[0][1]= ((P_y[0][0]+R_angle)*P_y[0][1]-P_y[0][0]*P_y[0][1])/E;
      K[1][0]= (P_y[1][0]*(P_y[1][1]+R_velo)-P_y[1][1]*P_y[1][0])/E;
      K[1][1]= (P_y[1][1]*(P_y[0][0]+R_angle)-P_y[1][0]*P_y[0][1])/E;
      K[2][0]= (P_y[2][0]*(P_y[1][1]+R_velo)-P_y[2][1]*P_y[1][0])/E;
      K[2][1]= (P_y[2][1]*(P_y[0][0]+R_angle)-P_y[2][0]*P_y[0][1])/E;
      
      P_y[2][0] -= K[2][0]*P_y[0][0]+K[2][1]*P_y[1][0];
      P_y[2][1] -= K[2][0]*P_y[0][1]+K[2][1]*P_y[1][1];
      P_y[2][2] -= K[2][0]*P_y[0][2]+K[2][1]*P_y[1][2];
      static float p0=P_y[0][0],p1=P_y[0][1],p2=P_y[0][2];
      P_y[0][0] -= K[0][0]*P_y[0][0]+K[0][1]*P_y[1][0];
      P_y[0][1] -= K[0][0]*P_y[0][1]+K[0][1]*P_y[1][1];
      P_y[0][2] -= K[0][0]*P_y[0][2]+K[0][1]*P_y[1][2];
      P_y[1][0] -= K[1][0]*p0+K[1][1]*P_y[1][0];
      P_y[1][1] -= K[1][0]*p1+K[1][1]*P_y[1][1];
      P_y[1][2] -= K[1][0]*p2+K[1][1]*P_y[1][2];
    
      angle_y += K[0][0]*error_angle+K[0][1]*error_velo;
      angle_y_dot += K[1][0]*error_angle+K[1][1]*error_velo;
      angle_y_dot2 += K[2][0]*error_angle+K[2][1]*error_velo;
    
  }

//  Serial.print(angle_y);Serial.print("\t");
//  Serial.print(angle_y_dot);Serial.print("\t");
//  Serial.print(angle_y_dot2);Serial.println("\t");

  float sum_angle=0., sum_angle_dot=0., sum_angle_dot2=0.;
  int count=0,i=0,j=0,k=0;
  if(count<2) 
  {
    count++;
  }
  for(j=0; j<3;++j)
  {
    for(i=0; i<1; ++i)
    {
      list_x[j][i]=list_x[j][i+1];
    }
  }
  list_x[0][1]=angle_x;list_x[1][1]=angle_x_dot;list_x[2][1]=angle_x_dot2;
  if(count=2){
    for(i=0;i<2;++i)
    {
      sum_angle += list_x[0][i]*(i+1)/3;
      sum_angle_dot += list_x[1][i]*(i+1)/3;
      sum_angle_dot2 += list_x[2][i]*(i+1)/3;
    }
    angle_x = sum_angle;
    angle_x_dot = sum_angle_dot;
    angle_x_dot2 = sum_angle_dot2;
  }
  i=0;j=0;k=0;
}

