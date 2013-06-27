#define LS 0x1
#define PULL 0x2
#define PUSH 0x4
#define EXIT 0x8

typedef struct
{
	char comname[5];
	unsigned int comflag;
	char file[20];
}CTL;

