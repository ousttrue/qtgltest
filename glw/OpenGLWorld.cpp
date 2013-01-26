#include "OpenGLWorld.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>


OpenGLWorld::OpenGLWorld()
: m_polyList(0), ms_prev(0)
{
    glEnable(GL_DEPTH_TEST);
}


OpenGLWorld::~OpenGLWorld()
{
}


void OpenGLWorld::resize(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void OpenGLWorld::clear()
{
    // Select correct buffer for this context.
    glDrawBuffer(GL_BACK);
    // Clear the buffers for new frame.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}


void OpenGLWorld::render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(m_projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(m_view);

    drawCube();
}


void OpenGLWorld::update(int ms)
{
    // Find out how long since Idle() last ran.
    float timeDelta = (float)(ms - ms_prev) * 0.001f;
    ms_prev = ms;
}


static GLuint initPolyList()
{
    // Colour cube data.
    float fSize = 0.5f;
    const GLfloat cube_vertices [8][3] = {
        {1.0, 1.0, 1.0}, 
        {1.0, -1.0, 1.0}, 
        {-1.0, -1.0, 1.0}, 
        {-1.0, 1.0, 1.0},
        {1.0, 1.0, -1.0}, 
        {1.0, -1.0, -1.0}, 
        {-1.0, -1.0, -1.0}, 
        {-1.0, 1.0, -1.0} 
    };
    const GLfloat cube_vertex_colors [8][3] = {
        {1.0, 1.0, 1.0}, 
        {1.0, 1.0, 0.0}, 
        {0.0, 1.0, 0.0}, 
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0}, 
        {1.0, 0.0, 0.0}, 
        {0.0, 0.0, 0.0}, 
        {0.0, 0.0, 1.0} 
    };
    GLint cube_num_faces = 6;
    const short cube_faces [6][4] = {
        {3, 2, 1, 0}, 
        {2, 3, 7, 6}, 
        {0, 1, 5, 4}, 
        {3, 0, 4, 7}, 
        {1, 2, 6, 5}, 
        {4, 5, 6, 7} 
    };

    GLuint polyList = glGenLists (1);
    glNewList(polyList, GL_COMPILE);
    glBegin (GL_QUADS);
    for (long f = 0; f < cube_num_faces; f++){
        for (long i = 0; i < 4; i++) {
            glColor3f (
                    cube_vertex_colors[cube_faces[f][i]][0], 
                    cube_vertex_colors[cube_faces[f][i]][1], 
                    cube_vertex_colors[cube_faces[f][i]][2]);
            glVertex3f(
                    cube_vertices[cube_faces[f][i]][0] * fSize, 
                    cube_vertices[cube_faces[f][i]][1] * fSize, 
                    cube_vertices[cube_faces[f][i]][2] * fSize);
        }
    }
    glEnd ();
    glColor3f (0.0, 0.0, 0.0);
    for (long f = 0; f < cube_num_faces; f++) {
        glBegin (GL_LINE_LOOP);
        for (long i = 0; i < 4; i++){
            glVertex3f(
                    cube_vertices[cube_faces[f][i]][0] * fSize, 
                    cube_vertices[cube_faces[f][i]][1] * fSize, 
                    cube_vertices[cube_faces[f][i]][2] * fSize);
        }
        glEnd ();
    }
    glEndList ();

    return polyList;
}


// Something to look at, draw a rotating colour cube.
void OpenGLWorld::drawCube()
{
    if (!m_polyList) {
        m_polyList=initPolyList();
    }

    glPushMatrix(); // Save world coordinate system.
    glTranslatef(0.0, 0.0, 0.5); // Place base of cube on marker surface.
    //glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glDisable(GL_LIGHTING);	// Just use colours.
    glCallList(m_polyList);	// Draw the cube.
    glPopMatrix();	// Restore world coordinate system.
}

void OpenGLWorld::drawImage(
        int x, int y,
        const unsigned char *image, 
        int w, int h,
        int pixFormat, int pixType)
{
	if(!image){
		return;
	}
    // draw capture image
    save();
    {
        glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
        int params[4];
        glGetIntegerv(GL_VIEWPORT, (GLint *)params);
        gluOrtho2D(
			0, static_cast<float>(params[2]), 
			0, static_cast<float>(params[3]));

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();		

        glDisable(GL_TEXTURE_2D);

		/*

        float zoomf = 1.0f;
        glPixelZoom(
                zoomf * ((float)(params[2]) / (float)w),
                -zoomf * ((float)(params[3]) / (float)h)
                );
				*/

        // flip vertical
        glPixelZoom(1.0f, -1.0f);
		// why?
        glRasterPos2f(
                static_cast<float>(x), 
                static_cast<float>(y)+static_cast<float>(h)-0.001f);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glDrawPixels(w, h, pixFormat, pixType, image);
    }
    restore();
}

void OpenGLWorld::save()
{
	// Prepare an orthographic projection, 
    // set camera position for 2D drawing, and save GL state.

    // Save GL texture environment mode.
	glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &texEnvModeSave); 
	if (texEnvModeSave != GL_REPLACE){
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    // Save enabled state of lighting.
	lightingSave = glIsEnabled(GL_LIGHTING);
	if (lightingSave == GL_TRUE){
        glDisable(GL_LIGHTING);
    }

    // Save enabled state of depth test.
	depthTestSave = glIsEnabled(GL_DEPTH_TEST);		
	if (depthTestSave == GL_TRUE){
        glDisable(GL_DEPTH_TEST);
    }

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void OpenGLWorld::restore()
{
	// Restore previous projection, camera position, and GL state.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    // Restore enabled state of depth test.
	if (depthTestSave == GL_TRUE){
        glEnable(GL_DEPTH_TEST);
    }
    // Restore enabled state of lighting.
	if (lightingSave == GL_TRUE){
        glEnable(GL_LIGHTING);			
    }
    // Restore GL texture environment mode.
	if (texEnvModeSave != GL_REPLACE){
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, texEnvModeSave);
    }
}
	
void OpenGLWorld::keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case ' ':
            //gDrawRotate = !gDrawRotate;
            break;
    }
}

