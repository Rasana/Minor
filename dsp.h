#include <math.h>
#define WS 128

///Global Variables
uint8_t xMan[WS]; ///Manipulated signal
uint8_t xOrg[WS*2]; ///Signal from ADC
uint8_t xOld[WS]; ///old data for echo
uint8_t speedIndex =0;

/*
void speedFast(int p,int q)
void play(uint8_t volButton)
void hpFIlter(int bCount)
void lpFilter(int bCount)
void speedFast(int p,int q)
void speedSlow(int p, int q)
*/

void play(int *x,int length)
{
	for(int i=0; i<length; i++)
	PORTC=*x[i]++;
}

void volume(int *x,int offset, uint8_t volButton)
{
	for(int i=0; i<WS; i++)
//	xOrg[i]=x[offset+i]*volButton;
//	PORTC=xOrg[i];

	PORTC =x[offset+i]*volButton;
}

void hpFIlter(int *x,int offset,int bCount)
{
	///Increase alpha to decrease corner frequency
	///Large alpha means output will decay slowly but will be
	///strongly affected by even small changes in input
	///Low value of alpha passes relatively only higher frequencies
	///We might want to change value of alpha based on bCount

	float alpha = 0.4;
	xMan[0]=*x;

	for (int i = 1; i<=WS; i++)
	{
		xMan[i]=alpha*(xMan[i-1]+xOrg[offset+i]-xOrg[offset+i-1]);
	}
	play(xMan,WS);
}

void lpFilter(int *x, int offset, int bCount)
{
	/// Return RC low-pass filter output samples, given input samples,
	/// time interval dt, and time constant RC

	float alpha = 0.1;
	xMan[0]=*x;
	for (int i = 1; i<=WS; i++)
	{
		xMan[i]=alpha*x[offset+i]+(1-alpha)*xMan[offset+i-1];
	}
	play(xMan,WS);
}

void speed(int b)
{
	///It may receive 1 or -1 as argument from buttons
	speedIndex=speedIndex+b;
	///P and Q of speed controls
	int speedP[11]={1,2,3,4,1,6,7,8,9,2,3};
	int speedQ[11]={5,5,5,5,1,6,7,8,9,1,1};

	if(speedP[speedIndex]<speedQ[speedIndex])
	speedSlow(speedP[speedIndex],speedQ[speedIndex]);

	else if(speedP[speedIndex]>speedQ[speedIndex])
	speedFast(speedP[speedIndex],speedQ[speedIndex]);

	else
	play(1);///Or whatever value that sounds normal
}

void speedFast(int p,int q,int offset)
{
	///-------6/5--8/5--10/5
	///p/q representation needed for playback speed
	///Skip every q-p signals after playing p signal
	///Seems like fast and slow playback needs to done separately

	for(int i=0;i<WS;i++)
	xOrg[i]=i;

	int length = q*WS/p;
	int xMan[WS];
	int j=0; ///Counterpart of i for new signal
	int r = q;///We always need to know the original value of p
	for(int i=0; i<128; i++)
	{
		if(i<r)
		xMan[j]=xOrg[i+offset];
		else
		{
			i=i+p-q+1;
			r=r+p;
		}
		j=j+1;
	}
	play(xMan,length);
	///release the old variable if possible
	///Tell the system how many variables to expect
}

void speedSlow(int p, int q,int offset)
{
	///------4/5--3/5........p/q
	///Need to know many signals are going to be in the modified sound signal
	///p/q repeat signals after every p signals
	uint8_t j=0; ///Counterpart of i for new signal
	uint8_t r = p;///We always need to know the original value of p
	int length = WS*q/p;

	uint8_t xMan[length];
	for(int i=0; i<length; i++)
	{
		if(i<r)
		{
			xMan[i]=xOrg[j+offset];
			j=j+1;
		}
		else
		{
			xMan[i]=xOrg[j+offset];
			if(i==r+q-p-1)
			r=r+q;
		}
	}
	play(xMan,length);
}

void echo()
{
	xMan=xOrg;
	int N= 10;
	for(int n=0; n<WS; n++)
	{
		if (n<N)
		xMan[n]=xOrg[n];
		else
		xMan[n]=xOrg[n]+xOrg[n-N];
	}
}
