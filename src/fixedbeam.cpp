#include "fixedbeam.h"
#include "main.h"

Fixedbeam::Fixedbeam(float x, float y, float angle)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle;
    this->angle = angle;
    float o = 0.0;
    this->burning = 1;
    const GLfloat vertex_buffer_data[] = {
        -60.0,
        0.0,
        -60.0 + 60.0,
        -120.0 + 60.0,
        5.0,
        0.0,
        120.0 - 60.0,
        0.0,
        -60.0 + 60.0,
        120.0 - 60.0,
        0.0,
        0.0,
        -120.0 + 60.0,
        5.0,
        0.0,
        120.0 - 60.0,
        5.0,
        -60.0 + 60.0,

        // Square 1
        -50.0,
        20.0 - 10.0,
        0.0,
        -50.0,
        -20.0 + 10.0,
        0.0,
        -100.0 + 30.0,
        -10.0,
        0.0,
        -100.0 + 30.0,
        -20.0 + 10.0,
        0.0,
        -100.0 + 50.0,
        10.0,
        0.0,
        -100.0 + 30.0,
        10.0,
        0.0,

        // Square 2
        70.0,
        20.0 - 10.0,
        0.0,
        70.0,
        -20.0 + 10.0,
        0.0,
        100.0 - 50.0,
        -20.0 + 10.0,
        0.0,
        50.0,
        -20.0 + 10.0,
        0.0,
        70.0,
        20.0 - 10.0,
        0.0,
        100.0 - 50.0,
        10.0,
        0.0,
    };
    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, COLOR_FLAME, GL_FILL);

}

void Fixedbeam::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    int y = 10 * 18;
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    int o = 0, l = 1;
    glm::mat4 rotate = glm::rotate((float)(this->rotation), glm::vec3(o*l, o+o, o+l));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, l, GL_FALSE, &MVP[o*1][o*l]);
    draw3DObject(this->object);
}

void Fixedbeam::tick()
{
    this->position.x -= 2 * Level;
}