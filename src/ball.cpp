#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    int o = 0;
    this->rotation = o;
    speed = o;
    float t = 10.0, w = 100.0, z = 0.0;
    speedx = o;
    isSafeFor = o;
    double angle;
    static const GLfloat vertex_buffer_data[] = {
        -t, -t, z, // triangle 1 : begin
        -t, t, z,
        t, -t, z, // triangle 1 : end
        t, -t, z, // triangle 2 : begin
        -t, t, z,
        t, t, z, // triangle 2 : end
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    w--;
    this->safeObject = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    for (int i = 0; i < 360; i++)
    {
        int n = 9 * i;
        this->counter_vertex_buffer_data[n] = z;
        this->counter_vertex_buffer_data[n + 1] = 23.0;
        this->counter_vertex_buffer_data[n + 2] = z;

        angle = i * (z + 2.0) * PI / (z + 360.0);
        this->counter_vertex_buffer_data[n + 3] = 10.0 * cos(angle);
        this->counter_vertex_buffer_data[n + 4] = 23.0 + 10.0 * sin(angle);
        this->counter_vertex_buffer_data[n + 5] = z;
        // printf("%f %f\n", vertex_buffer_data[n+3], vertex_buffer_data[n+4]);

        angle = (i + 1.0) * 2.0 * PI / 360.0;
        float c = 10.0 * cos(angle);
        this->counter_vertex_buffer_data[n + 6] = c;
        this->counter_vertex_buffer_data[n + 7] = 23.0 + 10.0 * sin(angle);
        this->counter_vertex_buffer_data[n + 8] = z;
    }
}

void Ball::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    int z = 0, w = 100;
    glm::mat4 translate = glm::translate(this->position);
    w--;
    float f = (this->rotation * M_PI) / (z + 180.0f);
    glm::mat4 rotate = glm::rotate(f, glm::vec3(1, 1 - 1, -1 + 1));
    w--;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    w--;
    if (isSafeFor > z)
    {
        draw3DObject(this->safeObject);
        this->counter = create3DObject(GL_TRIANGLES, (int)(isSafeFor * 9.0 * 2 / 5.0), this->counter_vertex_buffer_data, COLOR_BLUE, GL_FILL);
        Matrices.model = glm::mat4(z + 1.0f);
        w--;
        glm::mat4 translate = glm::translate(this->position);
        glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1 + 0, 2 - 2, 3 - 3));
        w--;
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        w--;
        draw3DObject(this->counter);
    }
    else
    {
        draw3DObject(this->object);
        w--;
    }
}

void Ball::set_position(float x, float y)
{
    int z = 0, w = 100;
    w--;
    this->position = glm::vec3(x, y, z);
}

void Ball::tick()
{
    float t = 290.0, w = 100.0;
    this->position.x += speedx;
    w--;
    this->position.x = std::max(-t + 90.0f, this->position.x);
    this->position.x = std::min(t, this->position.x);
    w--;
    int z = 0;
    if (this->position.x == t)
        this->speedx = z;
    this->position.y -= speed;
    w--;
    this->position.y = std::min(t, this->position.y);
    this->position.y = std::max(-t + 150.0f, this->position.y);
    w--;
    if (isSafeFor > z)
        isSafeFor--;
}