#include <GL/glut.h>
#include <iostream>
#include <stdexcept>

#include <iostream>

#include "Light.h"

int Light::light_number = 0;

Light::Light(LIGHT * pt_light){
        setLight();
        glLightf(light, GL_QUADRATIC_ATTENUATION, pt_light->quadratic_attenuation);
        glLightf(light, GL_LINEAR_ATTENUATION, pt_light->linear_attenuation);
        glLightf(light, GL_CONSTANT_ATTENUATION, pt_light->constant_attenuation);
}

void Light::setLight(void){
        switch(light_number){
                case 0:
                        light = GL_LIGHT0;
                        break;
                case 1:
                        light = GL_LIGHT1;
                        break;
                case 2:
                        light = GL_LIGHT2;
                        break;
                case 3:
                        light = GL_LIGHT3;
                        break;
                case 4:
                        light = GL_LIGHT4;
                        break;
                case 5:
                        light = GL_LIGHT5;
                        break;
                case 6:
                        light = GL_LIGHT6;
                        break;
                case 7:
                        light = GL_LIGHT7;
                        break;
                default:
                        throw std::range_error("Invalid number of light");
                        break;
        }
        light_number++;
}
