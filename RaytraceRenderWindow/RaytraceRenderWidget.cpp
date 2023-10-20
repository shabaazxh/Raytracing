//////////////////////////////////////////////////////////////////////
//
//  University of Leeds
//  COMP 5812M Foundations of Modelling & Rendering
//  User Interface for Coursework
////////////////////////////////////////////////////////////////////////


#include <math.h>
#include <random>
#include <QTimer>
#include <omp.h>
#include <QTimer>
// include the header file
#include "RaytraceRenderWidget.h"

#define N_THREADS 16
#define N_LOOPS 100
#define N_BOUNCES 5
#define TERMINATION_FACTOR 0.35f

// constructor
RaytraceRenderWidget::RaytraceRenderWidget
        (   
        // the geometric object to show
        std::vector<ThreeDModel>      *newTexturedObject,
        // the render parameters to use
        RenderParameters    *newRenderParameters,
        // parent widget in visual hierarchy
        QWidget             *parent
        )
    // the : indicates variable instantiation rather than arbitrary code
    // it is considered good style to use it where possible
    : 
    // start by calling inherited constructor with parent widget's pointer
    QOpenGLWidget(parent),
    // then store the pointers that were passed in
    texturedObjects(newTexturedObject),
    renderParameters(newRenderParameters)
    { // constructor

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &RaytraceRenderWidget::ForceRepaint);
        timer->start(30);

        ray = new Ray({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f});
        scene = new Scene(texturedObjects, renderParameters, ray);

    } // constructor


// destructor
RaytraceRenderWidget::~RaytraceRenderWidget()
    { // destructor
    // empty (for now)
    // all of our pointers are to data owned by another class
    // so we have no responsibility for destruction
    // and OpenGL cleanup is taken care of by Qt


        delete m_Camera;
    } // destructor                                                                 

// mouse-handling
void RaytraceRenderWidget::mousePressEvent(QMouseEvent *event)
    { // RaytraceRenderWidget::mousePressEvent()
    // store the button for future reference
    int whichButton = int(event->button());
    // scale the event to the nominal unit sphere in the widget:
    // find the minimum of height & width   
    float size = (width() > height()) ? height() : width();
    // scale both coordinates from that
    float x = (2.0f * event->x() - size) / size;
    float y = (size - 2.0f * event->y() ) / size;

    
    // and we want to force mouse buttons to allow shift-click to be the same as right-click
    unsigned int modifiers = event->modifiers();
    
    // shift-click (any) counts as right click
    if (modifiers & Qt::ShiftModifier)
        whichButton = Qt::RightButton;
    
    // send signal to the controller for detailed processing
    emit BeginScaledDrag(whichButton, x,y);
    } // RaytraceRenderWidget::mousePressEvent()
    
void RaytraceRenderWidget::mouseMoveEvent(QMouseEvent *event)
    { // RaytraceRenderWidget::mouseMoveEvent()
    // scale the event to the nominal unit sphere in the widget:
    // find the minimum of height & width   
    float size = (width() > height()) ? height() : width();
    // scale both coordinates from that
    float x = (2.0f * event->x() - size) / size;
    float y = (size - 2.0f * event->y() ) / size;
    
    // send signal to the controller for detailed processing
    emit ContinueScaledDrag(x,y);
    } // RaytraceRenderWidget::mouseMoveEvent()
    
void RaytraceRenderWidget::mouseReleaseEvent(QMouseEvent *event)
    { // RaytraceRenderWidget::mouseReleaseEvent()
    // scale the event to the nominal unit sphere in the widget:
    // find the minimum of height & width   
    float size = (width() > height()) ? height() : width();
    // scale both coordinates from that
    float x = (2.0f * event->x() - size) / size;
    float y = (size - 2.0f * event->y() ) / size;
    
    // send signal to the controller for detailed processing
    emit EndScaledDrag(x,y);
    } // RaytraceRenderWidget::mouseReleaseEvent()

// called when OpenGL context is set up
void RaytraceRenderWidget::initializeGL()
    { // RaytraceRenderWidget::initializeGL()
	// this should remain empty
    } // RaytraceRenderWidget::initializeGL()

// called every time the widget is resized
void RaytraceRenderWidget::resizeGL(int w, int h)
    { // RaytraceRenderWidget::resizeGL()
    // resize the render image
    frameBuffer.Resize(w, h);
    } // RaytraceRenderWidget::resizeGL()
    
// called every time the widget needs painting
void RaytraceRenderWidget::paintGL()
    { // RaytraceRenderWidget::paintGL()
    // set background colour to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // and display the image
    glDrawPixels(frameBuffer.width, frameBuffer.height, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer.block);
    } // RaytraceRenderWidget::paintGL()


#include <random>
    // Function to generate a random double between 0.0 and 1.0
    double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
    }

    // Function for cosine sampling a hemisphere
    Cartesian3 cosine_sample_hemisphere() {
    double xi1 = random_double();
    double xi2 = random_double();

    double theta = acos(sqrt(1.0 - xi1));
    double phi = 2.0 * M_PI * xi2;

    double xs = sin(theta) * cos(phi);
    double ys = sin(theta) * sin(phi);
    double zs = cos(theta);

    return Cartesian3(xs, ys, zs);
    }

Homogeneous4 RaytraceRenderWidget::TraceAndShadeWithRay(Ray& ray, int bounces, float value)
{
    Homogeneous4 color = {0.f, 0.0f, 0.0f , 0.0f};

    auto collision = scene->ClosestTriangle(ray);

    if(collision.t == std::numeric_limits<float>::max())
    {
        float t = 0.5f * (ray.GetRayDirecion().y + 1.0f); // norm to 0-1
        return (1.0f - t) * Homogeneous4(0.5f, 0.7f, 1.0f) + t * Homogeneous4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    // hit position
    auto hit_pos = ray.GetRayOrigin() + ray.GetRayDirecion() * collision.t;
    auto baricentric = collision.tri.baricentric(hit_pos);

    // Calculate normals
    Cartesian3 normalA = Cartesian3(collision.tri.normals[0].x, collision.tri.normals[0].y, collision.tri.normals[0].z);
    Cartesian3 normalB = Cartesian3(collision.tri.normals[1].x, collision.tri.normals[1].y, collision.tri.normals[1].z);
    Cartesian3 normalC = Cartesian3(collision.tri.normals[2].x, collision.tri.normals[2].y, collision.tri.normals[2].z);
    Cartesian3 interpNormal = baricentric.x * normalA + baricentric.y * normalB + baricentric.z * normalC;
    interpNormal = interpNormal.unit();

    float bias = 0.001;
    for(unsigned int i = 0; i < renderParameters->lights.size(); i++)
    {
        Cartesian3 lightPos = {
                               renderParameters->lights[i]->GetPositionCenter().x,
                               renderParameters->lights[i]->GetPositionCenter().y,
                               renderParameters->lights[i]->GetPositionCenter().z};

        Cartesian3 lightDirection = lightPos - hit_pos;
        float shadowRayDistance = (lightPos - hit_pos).length();
        lightDirection = lightDirection.unit();

        // Shadows
        auto displacedRay = hit_pos + Cartesian3(interpNormal.x, interpNormal.y, interpNormal.z) * bias;
        Ray shadowRay(displacedRay, lightDirection);
        bool inShadow = false;
//        auto shadowcollide = scene->ClosestTriangle(shadowRay);
//        if(shadowcollide.t < shadowRayDistance - 2 * bias)
//            inShadow = true;
        color = color + collision.tri.PhongShading(lightPos,
                                                   renderParameters->lights[i]->GetColor(), ray, {baricentric.x, baricentric.y, baricentric.z}, inShadow);
    }

    if(bounces >= MAX_BOUNCES)
    {
        return color;
    }

    // do reflections
    Cartesian3 reflectionDirection = ray.GetRayDirecion().reflect(interpNormal);
    Ray reflectionRay(hit_pos  + bias * reflectionDirection, reflectionDirection);
   // Homogeneous4 reflectedColor = TraceAndShadeWithRay(reflectionRay, bounces + 1, 1.0f);


    float reflectivity = collision.tri.shared_material->reflectivity;

    // linear interpolate between scene colour and reflective
    //color = (1 - reflectivity) * color + Cartesian3(reflectivity,reflectivity,reflectivity) * Cartesian3(reflectedColor.x, reflectedColor.y, reflectedColor.z);

    return color;
}


Ray RaytraceRenderWidget::calculateRay(int pixelx, int pixely, bool perspective)
{
    auto origin = ray->GetRayOrigin();


    // calculate perspective
    int width = frameBuffer.width;
    int height = frameBuffer.height;

    auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    //https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
    // map coordiates to view plane (Lecture 4[36] mentions convert from DCS to NDCS
    // need to map to range [-1, 1] normalized device coordinates
    // temp = (pixel + 0.5 / width [0,1] range
    // apply: 2.0f * temp - 1.0f = [-1,1]
    float x = (2.0f * (pixelx + 0.5f) / static_cast<float>(width) - 1.0f) * aspectRatio;

    // for y, we need to flip the y since y increases downwards on the image
    // this is not how cartesian y axis works
    //float y = (1.0f - 2.0f * (pixely + 0.5f) / static_cast<float>(height));

    float y = (2.0f * (pixely + 0.5f) / static_cast<float>(height) - 1.0f);


    auto dir = Cartesian3(x,y, -1);
    ray->SetDirection(dir);


    dir = dir.unit();

    return {origin, dir};


}
void RaytraceRenderWidget::Raytrace()
{

    // launch a new thread for the RaytraceThread function
    raytracingThread = std::thread(&RaytraceRenderWidget::RaytraceThread, this);
    raytracingThread.detach(); //detach launches the thread

}

void RaytraceRenderWidget::RaytraceThread()
{

    scene->updateScene();

    std::cout << "the raytracing function has been invoked " << std::endl;
    frameBuffer.clear(RGBAValue(0.0f, 0.0f, 0.0f, 1.0f));
#pragma omp parallel for schedule(dynamic)
    for(int j = 0; j < frameBuffer.height; j++)
    {
        for(int i = 0; i < frameBuffer.width; i++){

            auto ray = calculateRay(i, j, false);
            auto color = TraceAndShadeWithRay(ray, 0, 1.0f);

            // multiply by 255 to convert from 0-1 to 0-255 (8-bit form)
            frameBuffer[j][i] = RGBAValue(
                color.x*255.0f + 0.5,
                color.y*255.0f + 0.5,
                color.z*255.0f + 0.5, 255.0f);

            frameBuffer[j][i].alpha = 255;
        }

        //std::cout << "Done" << std::endl;
    }
}

void RaytraceRenderWidget::ForceRepaint()
{
    update();
}
