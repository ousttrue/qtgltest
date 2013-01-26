#pragma once


class OpenGLWorld
{
    // draw
    unsigned int m_polyList;

    // update timer
    int ms_prev;

	int texEnvModeSave;	
	int lightingSave;
	int depthTestSave;

    double m_projection[16];
    double m_view[16];

public:
    OpenGLWorld();
    ~OpenGLWorld();
    void resize(int w, int h);

	void update(int ms);
   
	void clear();
    void drawImage(
            int x, int y,
            const unsigned char *image, 
            int w, int h,
            int pixFormat, int pixType);
    void render();

    void keyboard(unsigned char key, int x, int y);

private:
    void drawCube();
    void save();
    void restore();
};

