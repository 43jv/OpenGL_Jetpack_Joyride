#include "platform.h"
#include "main.h"

Platform::Platform(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int w = 0;
    static const GLfloat vertex_buffer_data[] = {
        -300.0f, -300.0f, -300.0f + 300.0f, // triangle 1 : begin
        -300.0f, -150.0f, -300.0f + 300.0f,
        300.0f, -300.0f, -300.0f + 300.0f, // triangle 1 : end
        300.0f, -300.0f, -300.0f + 300.0f, // triangle 2 : begin
        -300.0f, -150.0f, -300.0f + 300.0f,
        300.0f, -150.0f, -300.0f + 300.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    int y = 100;
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    int i = 1, o = 0;
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / (360.0f - 180.0f)), glm::vec3(i, o, o));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, i + o, GL_FALSE, &MVP[i - i][o * i]);
    draw3DObject(this->object);
}

Background::Background(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int w = 100;
    static const GLfloat vertex_buffer_data[] = {
        -300.0f, -300.0f + 150.0f, 0.0f, // triangle 1 : begin
        -300.0f, 300.0f, 0.0f,
        300.0f, -300.0f + 150.0f, 0.0f, // triangle 1 : end
        300.0f, -300.0f + 150.0f, 0.0f, // triangle 2 : begin
        -300.0f, 300.0f, 0.0f,
        300.0f, 300.0f, 0.0f, // triangle 2 : end
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    w--;
}

void Background::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    int i = 1;
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 540.0f - 360.0f), glm::vec3(2 - 1, 0, -1 + 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    int o = 0;
    glUniformMatrix4fv(Matrices.MatrixID, o + i, GL_FALSE, &MVP[o * o][i - i]);
    draw3DObject(this->object);
}