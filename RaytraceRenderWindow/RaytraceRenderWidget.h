//////////////////////////////////////////////////////////////////////
//
//	University of Leeds
//	COMP 5812M Foundations of Modelling & Rendering
//	User Interface for Coursework
//
//	September, 2020
//
//  -----------------------------
//  Raytrace Render Widget
//  -----------------------------
//
//	Provides a widget that displays a fixed image
//	Assumes that the image will be edited (somehow) when Render() is called
//  
////////////////////////////////////////////////////////////////////////

// include guard
#ifndef RAYTRACE_RENDER_WIDGET_H
#define RAYTRACE_RENDER_WIDGET_H

#include <vector>
#include <mutex>
#include <thread>
// include the relevant QT headers
#include <QOpenGLWidget>
#include <QMouseEvent>

// and include all of our own headers that we need
#include "ThreeDModel.h"
#include "RenderParameters.h"

#include "camera.h"

#include "scene.h"
#include "ray.h"

#define MAX_BOUNCES 2

// class for a render widget with arcball linked to an external arcball widget
class RaytraceRenderWidget : public QOpenGLWidget										
	{ // class RaytraceRenderWidget
	Q_OBJECT
	private:	
	// the geometric object to be rendered
    std::vector<ThreeDModel> *texturedObjects;

	// the render parameters to use
	RenderParameters *renderParameters;

	// An image to use as a framebuffer
	RGBAImage frameBuffer;


	public:
	// constructor
	RaytraceRenderWidget
			(
	 		// the geometric object to show
            std::vector<ThreeDModel> 		*newTexturedObject,
			// the render parameters to use
			RenderParameters 	*newRenderParameters,
			// parent widget in visual hierarchy
			QWidget 			*parent
			);
	
	// destructor
	~RaytraceRenderWidget();

    void Raytrace();

    void RaytraceThread();

    void ForceRepaint();

    Ray calculateRay(int pixelx, int pixely, bool perspective);

    Homogeneous4 TraceAndShadeWithRay(Ray& ray, int bounces, float value);
			
	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();
	
	// mouse-handling
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

    private:

    std::thread raytracingThread;

    Camera* m_Camera;
    Scene* scene;
    Ray* ray;

	signals:
	// these are general purpose signals, which scale the drag to 
	// the notional unit sphere and pass it to the controller for handling
	void BeginScaledDrag(int whichButton, float x, float y);
	// note that Continue & End assume the button has already been set
	void ContinueScaledDrag(float x, float y);
	void EndScaledDrag(float x, float y);





	}; // class RaytraceRenderWidget

#endif
