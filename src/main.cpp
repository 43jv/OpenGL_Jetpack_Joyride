#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coin.h"
#include "fixedbeam.h"
#include "movingbeam.h"
#include "display.h"
using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

Ball ball1;
Platform platform;
Background background;
Coin *coinarr;
Fixedbeam *fixedbeamarr;
Movingbeam *movingbeamarr;
Display display;

string metainfo;

int currScore = 0, y = 100, pos = 0, Life = 3, Level = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int numCoins = 500, statBeamNum = 20, movBeamNum = 50;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    glUseProgram(programID);

    // Eye - Location of camera.
    glm::vec3 eye(0, 0, pos + 10);
    // Target - Where is the camera looking at.
    glm::vec3 target(0, 0, 0);
    // Up - Up vector defines tilt of camera.
    glm::vec3 up(0, pos + 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    glm::mat4 VP = Matrices.projection * Matrices.view;
    y--;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    platform.draw(VP);
    background.draw(VP);
    ball1.draw(VP);
    for (int i = 0; i < numCoins; i++)
    {
        if (coinarr[i].taken == (int)false)
            coinarr[i].draw(VP);
    }
    for (int i = 0; i < statBeamNum; i++)
    {
        if (fixedbeamarr[i].burning == (int)true)
            fixedbeamarr[i].draw(VP);
    }
    for (int i = 0; i < movBeamNum; i++)
    {
        if (movingbeamarr[i].burning == (int)true)
            movingbeamarr[i].draw(VP);
    }
    y--;
    display.draw(VP, screen_zoom, currScore);
}

void tick_input(GLFWwindow *window)
{

    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (space == GLFW_PRESS)
    {
        y--;
        ball1.speed += -0.3;
    }
    else
    {
        if (ball1.position.y <= -200.0 + 60.0)
            ball1.speed = (int)false;
        else
        {
            if (ball1.position.y >= 300.0 - 10.0)
            {
                ball1.speed = (int)false;
                ball1.position.y--;
            }
            y--;
            ball1.speed += 3 * 0.05;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    y--;
}

void decLife()
{

    system("aplay ../Sounds/death.wav&");
    Life--;
    if (Life == 0)
    {
        printf("============================================\n");
        printf("============================================\n");
        printf("==================You Lose==================\n");
        printf("============================================\n");
        printf("============================================\n");
        y--;
        quit(window);
    }
    else
    {
        if (ball1.position.x > 0)
            ball1.set_position(-300 + 100, ball1.position.y);

        else
            ball1.set_position(400 / 2, ball1.position.y);
    }
    if (Level == 3 && Life == 0)
    {
        printf("============================================\n");
        printf("============================================\n");
        printf("==================You Win!==================\n");
        printf("============================================\n");
        printf("============================================\n");

        quit(window);
    }
}

void tick_elements()
{

    ball1.tick();
    camera_rotation_angle += 1;
    y--;
    int x = 100;
    for (int i = 0; i < numCoins; i++)
    {
        if (coinarr[i].taken == 0)
        {
            coinarr[i].tick();
            x--;
            if (abs(ball1.position.x - coinarr[i].position.x) < 20 && abs(ball1.position.y - coinarr[i].position.y) < 20)
            {
                system("aplay ../Sounds/collectcoin.wav&");
                currScore++;
                x--;
                coinarr[i].taken = 1;
            }
        }
    }

    for (int i = 0; i < statBeamNum; i++)
    {
        if (fixedbeamarr[i].burning == 1)
        {
            fixedbeamarr[i].tick();
            x--;
            if (ball1.isSafeFor == 0 && detect_collision_with_beam(ball1.position.x, ball1.position.y, fixedbeamarr[i].position.x, fixedbeamarr[i].position.y, fixedbeamarr[i].angle))
            {
                decLife();
                x--;
            }
        }
    }

    for (int i = 0; i < movBeamNum; i++)
    {
        if (movingbeamarr[i].burning == 1)
        {
            movingbeamarr[i].tick();
            x--;
            if (abs(ball1.position.x - movingbeamarr[i].position.x) <= 95 && abs(ball1.position.y - movingbeamarr[i].position.y) <= 10 && ball1.isSafeFor == 0)
            {
                decLife();
                x--;
            }
        }
    }
}

float dist(float ax, float ay, float bx, float by)
{
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

bool detect_collision_with_beam(float objX, float objY, float beamX, float beamY, float angle)
{

    if (2.0 * angle >= M_PI)
    {
        if ((objX >= beamX - 2.5 + 60.0 * cos(angle) && objX <= beamX + 2.5 - 65.0 * cos(angle) && objY >= beamY - 2.5 - 65.0 * sin(angle) && objY <= beamY + 2.5 + 65.0 * sin(angle) && abs(objY + (beamX - objX) * tan(angle) - beamY) < (15.0 / abs(cos(angle)))) || (dist(beamX + 60.0 * cos(angle), beamY + 60.0 * sin(angle), objX, objY) + dist(beamX - 60.0 * cos(angle), beamY - 60.0 * sin(angle), objX, objY) <= 80.0))
        {
            return true;
        }
        return false;
    }
    else
    {
        if ((objX >= beamX - 2.5 - 65.0 * cos(angle) && objX <= beamX + 2.5 + 65.0 * cos(angle) && objY >= beamY - 2.5 - 65.0 * sin(angle) && objY <= beamY + 2.5 + 65.0 * sin(angle) && abs(objY + (beamX - objX) * tan(angle) - beamY) < (15.0 / abs(cos(angle)))) || (dist(beamX + 60.0 * cos(angle), beamY + 60.0 * sin(angle), objX, objY) + dist(beamX - 60.0 * cos(angle), beamY - 60.0 * sin(angle), objX, objY) <= 80.0))
        {
            return true;
        }
        return false;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    float z = 90 * 3;
    display = Display(-z, z, COLOR_GREEN);
    y--;
    // Generating random coins
    coinarr = (Coin *)malloc(numCoins * sizeof(Coin));
    for (int i = 0; i < numCoins; i++)
    {
        coinarr[i] = Coin(400.0f * i, (float)(rand() % 300));
    }

    // Generating fixed beams
    fixedbeamarr = (Fixedbeam *)malloc(2 * statBeamNum * sizeof(Fixedbeam));
    y--;
    for (int i = 0; i < statBeamNum; i++)
    {
        fixedbeamarr[i] = Fixedbeam((300.0f * 2) * (i + 1), (float)(rand() % 300), (rand() / double(RAND_MAX)) * PI);
    }

    for (int i = 0; i < statBeamNum; i++)
    {
        fixedbeamarr[statBeamNum + i] = Fixedbeam((300.0f * 3) * (i + 20), (float)(rand() % 300), (rand() / double(RAND_MAX)) * PI);
    }
    statBeamNum <<= 1;
    y--;
    // Generating moving beams
    movingbeamarr = (Movingbeam *)malloc(2 * movBeamNum * sizeof(Movingbeam));
    for (int i = 0; i < movBeamNum; i += 2)
    {
        movingbeamarr[i] = Movingbeam(800.0f * (i + 16), (float)(rand() % 300));
        movingbeamarr[i + 1] = Movingbeam(800.0f * (i + 16), (float)(rand() % 300));
    }
    movBeamNum <<= 1;
    y--;
    ball1 = Ball(-100 * 2, -200 + 60, COLOR_RED);
    platform = Platform(0, 0, COLOR_BLACK);
    background = Background(0, 0, COLOR_DARK);
    y--;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    y--;
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / (128.0 * 2.0), COLOR_BACKGROUND.g / (128.0 * 2.0), COLOR_BACKGROUND.b / (128.0 * 2.0), 0.0f); // R, G, B, A
    y--;
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

int main(int argc, char **argv)
{
    srand(time(0));
    int s = 700;
    window = initGLFW(s, s);
    initGL(window, s, s);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {

            // 60 fps
            // OpenGL Draw commands
            draw();
            y--;
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // Level Decider
            if (currScore <= 10)
                Level = 1;
            else if (currScore <= 20)
                Level = 2;
            else
                Level = 3;
            y--;
            // Generating MetaInfo
            metainfo += " Level: ";
            ostringstream str1;
            str1 << Level;
            metainfo += str1.str();
            metainfo += " Lives: ";
            str1.str("");
            str1.clear();
            str1 << Life;
            metainfo += str1.str();
            glfwSetWindowTitle(window, metainfo.c_str());
            metainfo = "Barry the Square";
            y--;
            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        y--;
    }

    quit(window);
}

void reset_screen()
{
    float h = 300.0;
    float top = screen_center_y + h / screen_zoom;
    float bottom = screen_center_y - h / screen_zoom;
    y--;
    float left = screen_center_x - h / screen_zoom;
    float right = screen_center_x + h / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, h - h, h + 200.0f);
}
