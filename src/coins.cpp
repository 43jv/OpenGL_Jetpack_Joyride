#include "coin.h"
#include "main.h"
#include <math.h>

Coin::Coin(float x, float y)
{
    int z = 0;
    this->position = glm::vec3(x, y, z);
    this->rotation = z;
    int g = 360, w = 100;
    this->taken = z;
    double angle, l = 1.0;
    GLfloat vertex_buffer_data[g * 9];
    w--;
    for (int i = 0; i < g; i++)
    {
        int n = 9 * i;
        vertex_buffer_data[n] = l - l;
        vertex_buffer_data[n + 1] = -l + l;
        vertex_buffer_data[n + 2] = l - l;

        angle = i * (l + l) * PI / (float)g;
        vertex_buffer_data[n + 3] = (l + 14.0) * cos(angle);
        vertex_buffer_data[n + 4] = 15.0 * sin(angle);
        vertex_buffer_data[n + 5] = l - l;
        // printf("%f %f\n", vertex_buffer_data[9*i+3], vertex_buffer_data[9*i+4]);

        angle = (i + l) * (l + l) * PI / 360.0;

        vertex_buffer_data[n + 6] = 15.0 * cos(angle);
        vertex_buffer_data[n + 7] = (l + 14.0) * sin(angle);
        vertex_buffer_data[n + 8] = l - l;
    }
    this->object = create3DObject(GL_TRIANGLES, g * 3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Coin::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    int x = 10 * 18;
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    int y = 0;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::tick()
{
    this->position.x -= Level * 2;
}
