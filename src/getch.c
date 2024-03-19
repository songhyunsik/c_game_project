#include <termios.h>
#include <stdio.h>
#include <unistd.h>

/* 타이머  */
#define CCHAR 0
#ifdef CTIME
#undef CTIME
#endif
#define CTIME 1

/*문자를 바로 입력 받을 수 있는 함수*/
int getch(void)
{
    char ch;
    int error;
    static struct termios Otty, Ntty;

    //  fflush(stdout);
    tcgetattr(0, &Otty);
    Ntty = Otty;
    Ntty.c_iflag = 0;
    Ntty.c_oflag = 0;
    Ntty.c_lflag &= ~ICANON;
#if 1
    Ntty.c_lflag &= ~ECHO;
#else
    Ntty.c_lflag |= ECHO;
#endif
    Ntty.c_cc[VMIN] = CCHAR;
    Ntty.c_cc[VTIME] = CTIME;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

    if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
    {
        error = read(0, &ch, 1);
        error += tcsetattr(0, FLAG, &Otty);
    }

    return (error == 1 ? (int)ch : -1);
}