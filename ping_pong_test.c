#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

#ifdef __cplusplus
#error NO C++ PLEASE
#endif

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

static int latestFps = 0;
static int screenWidth = 80;
static int screenHeight = 60; 
static char **screenBuffer;

/* Also handle difference in width and height of console characters */
static float ballPositionX = 0.4f;
static float ballPositionY = 0.5f;
static float ballSpeedX = 0.4f;
static float ballSpeedY = 0.5f;

void CalculatePhysics(int millisecondsElapsed);
void Draw();

int main(int argc, char *argv[])
{
    printf("Pinball v1");

    screenBuffer = (char **)malloc(screenHeight * sizeof(char *));
    for (int i = 0; i < screenHeight; i++)
    {
        screenBuffer[i] = (char *)malloc(screenWidth * sizeof(char));
        for (int j = 0; j < screenWidth; j++)
        {
            printf("%c ", screenBuffer[i][j]);
            screenBuffer[i][j] = 'x';
        }
        printf("\n");
    }

    /* Consider replacing with timeval and using microseconds */
    struct timeb previousTime, currentTime;
    ftime( &previousTime );
    
    int counter = 0;
    while (1)
    {
        usleep(10000);
        counter++;
        ftime( &currentTime );
        int millisecondsPassed = (int) (1000.0 * (currentTime.time - previousTime.time) +
            (currentTime.millitm - previousTime.millitm));
        ftime( &previousTime );
        if (counter % 40 == 0)
        {
            latestFps = millisecondsPassed == 0 ? 1000000 : (int) (1000 / millisecondsPassed);
        }

        CalculatePhysics(millisecondsPassed);

        Draw();
    }
}

void CalculatePhysics(int millisecondsElapsed)
{

}

void Draw()
{
    printf("\e[1;1H\e[2J");
    printf("FPS: %d\n", latestFps);
    
    for (int i = 0; i < screenHeight; i++)
    {
        for (int j = 0; j < screenWidth; j++)
        {
            printf("%c", screenBuffer[i][j]);
            if (j == screenWidth - 1)
            {
                printf("\n");
            }
        }
    }
}