#include "movingbeam.h"
#include "main.h"

Movingbeam::Movingbeam(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int l = 1;
    this->dirn = 1;
    this->burning = l + 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float o = 0.0;
    const GLfloat vertex_buffer_data[] = {
        -90.0,
        0.0,
        o,
        -90.0,
        5.0,
        o,
        90.0,
        0.0,
        o,
        90.0,
        0.0,
        o,
        -90.0,
        5.0,
        o,
        90.0,
        5.0,
        o,
        // Square 1
        -80.0,
        10.0,
        o,
        -80.0,
        -10.0,
        o,
        -100.0,
        -10.0,
        o,
        -100.0,
        -10.0,
        o,
        -80.0,
        10.0,
        o,
        -100.0,
        10.0,
        o,
        // Square 2
        100.0,
        10.0,
        o,
        100.0,
        -10.0,
        o,
        80.0,
        -10.0,
        o,
        80.0,
        -10.0,
        o,
        100.0,
        10.0,
        o,
        80.0,
        10.0,
        o,

    };
    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, COLOR_FLAME, GL_FILL);
}

void Movingbeam::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    float y = 90.0, w = 10;
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / (2 * y)), glm::vec3(1, 0, 0));
    w--;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    int z = 0;
    glm::mat4 MVP = VP * Matrices.model;
    int o = 0, l = 1;
    glUniformMatrix4fv(Matrices.MatrixID, o + l, GL_FALSE, &MVP[1 * o][l - l]);
    w--;
    draw3DObject(this->object);
}

void Movingbeam::tick()
{
    this->position.x -= 2 * Level;
    this->position.y += 2 * Level * dirn;
    float l = 1.0;
    if (this->position.y >= 250)
        this->dirn = -l;
    if (this->position.y <= (-300+200))
        this->dirn = l;
}