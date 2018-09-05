//Simple LineFollower

/*
#define trig 3
#define echo 4
#define buzzer 5
*/
#define p(x,y) pinMode(x,y)
//Change the motor pins here
int lmotor[]= {7,8,9,10};
int rmotor[]= {3,4,5,6};
int lsize=sizeof(lmotor)/sizeof(lmotor[0]);
int rsize=sizeof(rmotor)/sizeof(rmotor[0]);
//long duration;
#define d(x,y) digitalWrite(x,y)
void init(int a[],int size,int state)
{
    for(int i=0; i<size; i++)
        p(a[i],state);

}
void right()
{
    for(int i=0; i<=2; i+=2)
    {
        d(lmotor[i],1);
        d(lmotor[i+1],0);
        d(rmotor[i],0);
        d(rmotor[i+1],1);
    }
}
void left()
{
    for(int i=0; i<=2; i+=2)
    {
        d(rmotor[i],1);
        d(rmotor[i+1],0);
        d(lmotor[i],0);
        d(lmotor[i+1],1);
    }
}
void forward()
{
    for(int i=0; i<=2; i+=2)
    {
        d(rmotor[i],1);
        d(rmotor[i+1],0);
        d(lmotor[i],1);
        d(lmotor[i+1],0);

    }
}
void brake()
{
    for(int i=0; i<=2; i+=2)
    {
        d(lmotor[i],1);
        d(lmotor[i+1],1);
        d(rmotor[i],1);
        d(rmotor[i+1],1);
    }
}
/*
long ultrasonic()
{
d(trig,0);
delayMicroseconds(2);
d(trig,1);
delayMicroseconds(10);
d(trig,0);
duration=pulseIn(echo,1)/29/2;
return duration;
}
*/
void setup()
{
    Serial.begin(9600);
//pinMode(echo,0);
//pinMode(trig,1);
//third argument of init is the state which you want to initialize the pin with
    init(lmotor,lsize,1);
    init(rmotor,rsize,1);
//test drive
    forward();
    brake();
    left();
    right();

}
void loop()
{   int val[5];
    for(int i=0; i<5; i++)
        val[i]=analogRead(i);
    if((val[0]+val[1])>(val[3]+val[4])&&val[2]!=1)
    {   left();
    }
    else if((val[0]+val[1])>(val[3]+val[4])&&val[2]!=1)
    {   right();
    }
    else {
        forward();
    }
}
