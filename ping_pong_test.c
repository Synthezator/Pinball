#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <math.h>

#ifdef __cplusplus
#error NO C++ PLEASE
#endif

/* Needed for sleep */
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

static int latestFps = 0;

/* Screen height is actually 1.5 times bigger than width. The field borders ratio is also 3:2 */
static int screenWidth = 80;
static int screenHeight = 60; 
static char **screenBuffer;

static float ballPositionX = 1.9f;
static float ballPositionY = 0.05f;
static float ballSpeedX = 0.4f;
static float ballSpeedY = 0.5f;

static float leftFieldBorderX = 0.0f;
static float rightFieldBorderX = 2.0f;
static float topFieldBorderY = 3.0f;
static float bottomFieldBorderY = 0.0f;

void CalculatePhysics(int millisecondsElapsed);
void DrawElementsToBuffer();
void DrawBuffer();

int SleepCrossplatform(int milliseconds)
{
#ifdef _WIN32
    //Sleep((DWORD) milliseconds);
    return 0;
#else
    return usleep(milliseconds * 1000);
#endif
}

int main(int argc, char *argv[])
{
    printf("Pinball v1");

    screenBuffer = (char **)malloc((screenHeight + 2) * sizeof(char *));
    for (int i = 0; i < screenHeight + 2; i++)
    {
        screenBuffer[i] = (char *)malloc((screenWidth + 3) * sizeof(char));
        screenBuffer[i][screenWidth + 2] = '\0';
        if (i > 0 && i < screenHeight + 1)
        {
            screenBuffer[i][0] = screenBuffer[i][screenWidth + 1] = '*';
            for (int j = 1; j <= screenWidth; j++)
            {
                screenBuffer[i][j] = ' ';
            }
        }
        else
        {
            for (int j = 0; j < screenWidth + 2; j++)
            {
                screenBuffer[i][j] = '*';
            }
        }
    }

    /* Consider replacing with timeval and using microseconds */
    struct timeb previousTime, currentTime;
    ftime( &previousTime );
    
    int counter = 0;
    while (1)
    {
        SleepCrossplatform(5);
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

        DrawElementsToBuffer();

        DrawBuffer();
    }
}

void CalculatePhysics(int millisecondsElapsed)
{
    // 62 h = 1744 px -> h ~= 28 px
    // 82 w = 1158 px -> w ~= 14 px
    float deltaTime = ((float)millisecondsElapsed) / 1000.0f;
    ballPositionX += ballSpeedX * deltaTime;
    ballPositionY += ballSpeedY * deltaTime;

    if (ballPositionX <= leftFieldBorderX && ballSpeedX < 0)
    {
        ballSpeedX *= -1;
    }

    if (ballPositionX >= rightFieldBorderX && ballSpeedX > 0)
    {
        ballSpeedX *= -1;
    }

    if (ballPositionY >= topFieldBorderY && ballSpeedY > 0)
    {
        ballSpeedY *= -1;
    }

    if (ballPositionY <= bottomFieldBorderY && ballSpeedY < 0)
    {
        ballSpeedY *= -1;
    }
}

void DrawElementsToBuffer()
{
    for (int i = 1; i <= screenHeight; i++)
    {
        for (int j = 1; j <= screenWidth; j++)
        {
            screenBuffer[i][j] = ' ';
        }
    }

    float ballPositionInFieldX = (ballPositionX - leftFieldBorderX) / (rightFieldBorderX - leftFieldBorderX);
    float ballPositionInFieldY = (ballPositionY - bottomFieldBorderY) / (topFieldBorderY - bottomFieldBorderY);

    int ballScreenPositionX = (int) roundf(ballPositionInFieldX * (float)screenWidth);
    int ballScreenPositionY = (int) roundf((1 - ballPositionInFieldY) * (float)screenHeight);
    if (ballScreenPositionX >= 0 && ballScreenPositionX < screenWidth && 
        ballScreenPositionY >= 0 && ballScreenPositionY < screenHeight)
    {
        screenBuffer[ballScreenPositionY + 1][ballScreenPositionX + 1] = 'O';
    }
}

void DrawBuffer()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("FPS: %d\n", latestFps);
    
    for (int i = 0; i < screenHeight + 2; i++)
    {
        printf("%s\n", screenBuffer[i]);
    }
}