#include "../headers/Model.h"

void Model::prepare(int flag) {
    switch (flag)
    {
        case 0:
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
            break;
        case 1:
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3 * sizeof(float)));
            break; 
        case 2:
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float)*3));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
            break;
    }
    
}