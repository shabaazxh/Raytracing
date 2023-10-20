#include "RenderParameters.h"

RenderParameters::~RenderParameters()
{
    for(unsigned int i = 0; i < lights.size(); i++)
    {
        delete(lights.at(i));
    }
}

void RenderParameters::findLights(std::vector<ThreeDModel> objects)
{
    for(ThreeDModel obj: objects)
    {
        //find objects that have a "light" material
        if(obj.material->isLight())
        {
            //if the object has exactly 2 triangles, its a rectangular area light.
            if(obj.faceVertices.size()== 2)
            {
                // find a vertex that is at the corner of the quad
                // since 2 triangles make up a quad, we need to find a vertex which
                // has not been found before since vertex points that are
                // diagnol will be shared among two triangles that form the quad and thus
                // would be found
                // A check for the same vertex is made using vertex ID
                for(unsigned int i = 0; i < 3; i++)
                {
                    // Take a vertex from first triangle and store it into vid
                    unsigned int vid = obj.faceVertices[0][i];
                    bool found = false;
                    for(unsigned int j = 0; j < 3; j++)
                    {
                        // loop through second triangle and see if any vertex
                        // is found with the same id
                        if(vid == obj.faceVertices[1][j])
                        {
                            found = true;
                            break;
                        }
                    }

                    // if a vertex is found which is not shared
                    // index i would be the current found vertex
                    if(!found)
                    {
                        unsigned int id1 = obj.faceVertices[0][i];
                        unsigned int id2 = obj.faceVertices[0][(i+1)%3];
                        unsigned int id3 = obj.faceVertices[0][(i+2)%3];
                        Cartesian3 v1 = obj.vertices[id1];
                        Cartesian3 v2 = obj.vertices[id2];
                        Cartesian3 v3 = obj.vertices[id3];
                        Cartesian3 vecA = v2 - v1;
                        Cartesian3 vecB = v3 - v1;
                        Homogeneous4 color = obj.material->emissive;
                        Homogeneous4 pos = v1 + (vecA/2) + (vecB/2); // set position to be center of triangle?
                        Homogeneous4 normal = obj.normals[obj.faceNormals[0][0]];
                        Light* l = new Light(Light::Area, color, pos, normal, vecA, vecB);
                        l->enabled = true;
                        lights.push_back(l);
                    }
                }
            }
            else
            {
                Cartesian3 center = Cartesian3(0,0,0);
                for(unsigned int i = 0; i < obj.vertices.size(); i++)
                {
                    center = center + obj.vertices[i];
                }

                center = center / obj.vertices.size();
                Light* l = new Light(Light::Point, obj.material->emissive, center,
                                     Homogeneous4(), Homogeneous4(), Homogeneous4());
                l->enabled = true;
                lights.push_back(l);
                std::cout << "Exercise #3, replace this with the code!" << std::endl;
            }
        }
    }
}
