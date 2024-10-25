#include "main.h"
#include "display.h"

Display::Display(float x, float y, color_t color)
{

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float o = 0.0, t = 10.0;
    GLfloat vertex_buffer_data[] = {
        t, t, o,
        t, o, o,
        13.0f, o, o,
        13.0f, o, o,
        t, t, o,
        13.0f, t, o,
        10.0, 10.0, 0.0,
        13.0, 10.0, 0.0,
        11.5, 12.0, o,
        10.0, 0.0, 0.0,
        13.0, 0.0, 0.0,
        11.5, -2.0, o};
    this->object[0] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, color, GL_FILL);

    float r = 4.0, e = 14.0;
    GLfloat vertex_buffer_data1[] = {
        t, -r, o,
        t, -14.0f, o,
        13.0f, -14.0f, o,
        13.0f, -14.0f, o,
        t, -r, o,
        13.0f, -r, o,
        10.0, -r, 0.0,
        13.0, -4.0, 0.0,
        11.5, -2.0, 0.0,
        10.0, -e, 0.0,
        13.0, -e, 0.0,
        11.5, -16.0, 0.0};
    this->object[1] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data1, color, GL_FILL);
    float q = 17.0;
    GLfloat vertex_buffer_data2[] = {
        0.0, -17.0, 0.0,
        0.0, -14.0, 0.0,
        10.0, -q, 0.0,
        10.0, -17.0, 0.0,
        0.0, -14.0, 0.0,
        10.0, -e, 0.0,
        10.0, -14.0, 0.0,
        10.0, -q, 0.0,
        12.0, -16.5, 0.0,
        0.0, -17.0, 0.0,
        0.0, -e, 0.0,
        -2.0, -16.5, 0.0};
    this->object[2] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, color, GL_FILL);
    float m = -3.5;
    GLfloat vertex_buffer_data3[] = {
        -r, -r, o,
        -r, -14.0f, o,
        -1.0f, -14.0f, o,
        -1.0f, -14.0f, o,
        -r, -r, o,
        -1.0f, -r, o,
        -4.0, -4.0, 0.0,
        -1.0, -4.0, 0.0,
        -m, -2.0, 0.0,
        -4.0, -14.0, 0.0,
        -1.0, -14.0, 0.0,
        -m, -16.0, 0.0};
    this->object[3] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, color, GL_FILL);
    float v = 2.0;
    GLfloat vertex_buffer_data4[] = {
        -r, t, o,
        -r, o, o,
        -1.0f, o, o,
        -1.0f, o, o,
        -r, t, o,
        -1.0f, t, o,
        -4.0, 10.0, 0.0,
        -1.0, 10.0, 0.0,
        -3.5, 12.0, o,
        -4.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -3.5, -2.0, o};
    this->object[4] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data4, color, GL_FILL);
    float h = 13.0;
    GLfloat vertex_buffer_data5[] = {
        0.0, h, 0.0,
        0.0, 16.0, 0.0,
        10.0, h, 0.0,
        10.0, h, 0.0,
        0.0, 16.0, 0.0,
        10.0, 16.0, 0.0,
        10.0, 16.0, o,
        10.0, h, 0.0,
        12.0, 14.5, 0.0,
        0.0, h, 0.0,
        0.0, 16.0, 0.0,
        -2.0, 14.5, o};
    this->object[5] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data5, color, GL_FILL);
    float w = 1.5;
    GLfloat vertex_buffer_data6[] = {
        0.0, -v, 0.0,
        0.0, 1.0, 0.0,
        10.0, -v, 0.0,
        10.0, -2.0,o,
        0.0, 1.0, 0.0,
        10.0, 1.0, 0.0,
        10.0, 1.0, o,
        10.0, -2.0, 0.0,
        12.0, -w, o,
        0.0, -2.0, 0.0,
        o, 1.0, 0.0,
        -2.0, -w, 0.0};
    this->object[6] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data6, color, GL_FILL);
}

void Display::draw(glm::mat4 VP, float zoom, int num)
{
    int o = 0, l = 1;
    int numberMap[10][7] = {
        {l, 1, 1, 1, 1, 1, 0},
        {1, l, 0, 0, 0, o, 0},
        {1, 0, 1, l, 0, 1, 1},
        {1, 1, 1, 0, 0, 1, 1},
        {1, 1, o, 0, 1, 0, 1},
        {0, 1, 1, 0, l, 1, 1},
        {o, 1, 1, 1, 1, l, 1},
        {1, l, 0, 0, o, 1, 0},
        {1, 1, 1, 1, l, 1, 1},
        {1, l, 1, 0, 1, 1, 1}};

    this->position.x /= zoom;
    this->position.y /= zoom;
    float y = 180.0, w = 100.0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / y), glm::vec3(o+1, o, o));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    w--;
    glUniformMatrix4fv(Matrices.MatrixID, o + 1, GL_FALSE, &MVP[l-1][o]);
    for (int i = o; i < 7*l; i++)
    {
        if (numberMap[num / (o+100)][i] == (int)true)
        {
            draw3DObject(this->object[i]);
        }
    }

    num %= 100;
    this->position.x += 20;
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate(this->position); // glTranslatef
    rotate = glm::rotate((float)(this->rotation * M_PI / y), glm::vec3(l, o, o));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    w--;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for (int i = 0; i < 7; i++)
    {
        if (numberMap[num / 10][i] == 1)
        {
            draw3DObject(this->object[i]);
        }
    }

    num %= 10;
    this->position.x += 20;
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate(this->position); // glTranslatef
    rotate = glm::rotate((float)(this->rotation * M_PI /y), glm::vec3(l * l, l-l, o));
    w--;
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    w--;
    glUniformMatrix4fv(Matrices.MatrixID, l + o , GL_FALSE, &MVP[l-l][o*l]);
    for (int i = 0; i < 7; i++)
    {
        if (numberMap[num][i] == l)
        {
            draw3DObject(this->object[i]);
        }
    }
    this->position.x -= 40 + o;
    this->position.x *= zoom;
    this->position.y *= zoom;
}
