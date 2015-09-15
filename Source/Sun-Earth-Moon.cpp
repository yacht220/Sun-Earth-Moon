#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>  
#include "Utility.h"


// ���̿�����ת����
static float xRot = 0.0f;
static float yRot = 0.0f;


// �������Բ���
float  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float  sourceLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float  lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };


//�������
#define SUN_TEXTURE  0  
#define EARTH_TEXTURE  1
#define MOON_TEXTURE  2
#define NUM_TEXTURES    3
GLuint  textureObjects[NUM_TEXTURES];
const char *TextureFiles[] = {"sun.tga", "earth.tga", "moon.tga"};

// ѡ�����
int selectedSun = 0;
int selectedEarth = 0;
int selectedMoon = 0;

#define SUN 4
#define EARTH 5
#define MOON 6


// ��Ⱦ����
void Render(void)
	{
	// ̫�����������������ת����
	static float fMoonRot = 0.0f;	
	static float fEarthRot = 0.0f;
	static float fSunRot = 0.0f;
	
	// ����������Ĺ�ת����
    static float fMoonRev = 0.0f;
	static float fEarthRev = 0.0f;

	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ���浱ǰģ������
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// ������������ǰ��z�ᣩ�ƶ�400����λ
	glTranslatef(0.0f, 0.0f, -400.0f);

	// ��ʼ��names stack������ѡȡ����
    glInitNames();
	glPushName(0);

    // ���µ�ǰ���̿��Ƶ���ת
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	// ��̫����������ת�˶�
	glPushMatrix();	
    glDisable(GL_LIGHTING);

	// �����̫������ʹ�������������ƴ��빦����ͬ
	if(selectedSun == SUN)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255,255,255);
		glBindTexture(GL_TEXTURE_2D, textureObjects[SUN_TEXTURE]);
	}
	// ���ٴε��̫������ʹ�������������ƴ��빦����ͬ
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 0);
	}
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(fSunRot, 0.0f, 0.0f, 1.0f);
    glLoadName(SUN);
	DrawSphere(70.0f,100, 50);
    glEnable(GL_LIGHTING);
    glPopMatrix();

	// ����̫������ת����
	fSunRot -= 1.0f;
	if(fSunRot < -360.0f)
		fSunRot = 0.0f;

	// ��λ��Դ
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	// �����򣬰�����ת����ת�˶�
	if(selectedEarth == EARTH)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255,255,255);
		glBindTexture(GL_TEXTURE_2D, textureObjects[EARTH_TEXTURE]);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	    glColor3ub(0,0,255);
	}
	glRotatef(fEarthRev, 0.0f, 1.0f, 0.0f);
	glTranslatef(200.0f,0.0f,0.0f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(fEarthRot, 0.0f, 0.0f, 1.0f);
	glLoadName(EARTH);
	DrawSphere(20.0f,100, 50);
	glPopMatrix();

	// ���µ���Ĺ�ת����
	fEarthRev += 1.0f;
	if(fEarthRev > 360.0f)
		fEarthRev = 0.0f;

	// ���µ������ת����
	fEarthRot += 5.0f;
	if(fEarthRot > 360.0f)
		fEarthRot = 0.0f;

	// �����򣬰�����ת����ת�˶�
	if(selectedMoon == MOON)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255,255,255);
		glBindTexture(GL_TEXTURE_2D, textureObjects[MOON_TEXTURE]);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor3ub(200,200,200);
	}
	glRotatef(fMoonRev,0.0f, 1.0f, 0.0f);
	glTranslatef(40.0f, 0.0f, 0.0f);
	glPushMatrix();	
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(fMoonRot, 0.0f, 0.0f, 1.0f);
	glLoadName(MOON);
	DrawSphere(5.0f,100, 50);
	glPopMatrix();

	// ��������Ĺ�ת����
	fMoonRev+= 5.0f;
	if(fMoonRev > 360.0f)
		fMoonRev = 0.0f;

	// �����������ת����
	fMoonRot -= 10.0f;
	if(fMoonRot < -360.0f)
		fMoonRot = 0.0f;

	// �ָ�ģ������
	glPopMatrix();

	glPushMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);




		// Remap the viewing volume to match window coordinates (approximately)
		/*glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		
		// Establish clipping volume (left, right, bottom, top, near, far)
		glOrtho(-512.0, 512.0, -384.0, 384.0, 1, 1000.0);
		glMatrixMode(GL_MODELVIEW);*/






	// �ƶ�������ʹ������������������λ��ƥ��
    glTranslatef(0.0f, 0.0f, -400.0f);
	glTranslatef(0.0f, -200.0f, 0.0f);
	glTranslatef(-250.0f, 0.0f, 0.0f);


    // ���µ�ǰ���̿��Ƶ���ת
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// ��������
	DrawAxes();




	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);




	glPopMatrix();

	// ��ʾͼ��
	glutSwapBuffers();
	}


// �ڴ�������ʾ���ѡȡ�Ķ�������
void NameDisplay(int id)
	{
	switch(id)
		{
		case SUN:
			glutSetWindowTitle("̫����ѡȡ��");
			break;

		case EARTH:
			glutSetWindowTitle("����ѡȡ��");
			break;

		case MOON:
			glutSetWindowTitle("����ѡȡ��");
			break;

		default:
			glutSetWindowTitle("ʲôҲû��ѡȡ��");
			break;
		}		
	}


// ����ѡȡ����
#define BUFFER_LENGTH 64
void Selection(int xPos, int yPos)
	{
	float fAspect;

	// ����selection buffer
	static GLuint selectBuff[BUFFER_LENGTH];

	// ����������ı�ʶ������ѡȡ�������ӿ�
	int hits, viewport[4];

	// ��ȡselection buffer
	glSelectBuffer(BUFFER_LENGTH, selectBuff);
	
	// ��ȡ����ѡȡ�������ӿ�
	glGetIntegerv(GL_VIEWPORT, viewport);

	// ת����͸�����꣬���洢��ǰ״̬
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	// ������ѡȡģʽ������Ⱦ
	glRenderMode(GL_SELECT);

	// ȷ�������Χ�Ĳü��ռ�
	glLoadIdentity();
	gluPickMatrix(xPos, viewport[3] - yPos + viewport[1], 2,2, viewport);

	// ����ѡȡ��Ⱦ�ô�������
	fAspect = (float)viewport[2] / (float)viewport[3];
	gluPerspective(60.0f, fAspect, 1.0, 1000.0);

	// ������Ⱦ
	Render();

	hits = glRenderMode(GL_RENDER);

    GLuint nErr = glGetError();

	// �������������������д���
	if(hits == 1)
	{
		NameDisplay(selectBuff[3]);
		if(selectedSun == selectBuff[3])
			selectedSun = 0;
		else if(selectBuff[3] == SUN)
			selectedSun = selectBuff[3];

		else if(selectedEarth == selectBuff[3])
			selectedEarth = 0;
		else if(selectBuff[3] == EARTH)
			selectedEarth = selectBuff[3];

		else if(selectedMoon == selectBuff[3])
			selectedMoon = 0;
		else if(selectBuff[3] == MOON)
			selectedMoon = selectBuff[3];
	}
	  
	else
		glutSetWindowTitle("ʲôҲû��ѡȡ��");

	// �ָ�͸������
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// �ص�ģ������
	glMatrixMode(GL_MODELVIEW);
	}


// ��ʼ�� 
void Initialize()
	{
    int i;

	// ������ȼ�⡢�����漰ȡ������ļ���
	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);		
	glEnable(GL_CULL_FACE);		

	// ��������
	//glEnable(GL_LIGHTING);

	// ���ù�Դ�����ԣ��绷�����ա�������ռ���Դλ�õĲ���
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);
    
	// �����µĲ�����ɫ����
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

    // ��������
    glEnable(GL_TEXTURE_2D);
    glGenTextures(NUM_TEXTURES, textureObjects);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for(i = 0; i < NUM_TEXTURES; i++)
        {
        GLbyte *pBytes;
        GLint iWidth, iHeight, iComponents;
        GLenum eFormat;
        
        glBindTexture(GL_TEXTURE_2D, textureObjects[i]);
        
        // ��ȡ����ͼƬ
        pBytes = LoadTGA(TextureFiles[i], &iWidth, &iHeight, &iComponents, &eFormat);
        gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
		
		free(pBytes);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

	// ���ñ�����ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    glEnable(GL_MULTISAMPLE);
    }


// ��Ⱦ����ʱ����
void Timer(int value)
    {
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 1);
    }


// ���̿���
void Keys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	glutPostRedisplay();
	}


// ������궯��
void MouseClick(int button, int state, int x, int y)
	{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		Selection(x, y);
	}


// �ر���Դ
void Shutdown(void)
    {
    // ɾ��textureObjects����
    glDeleteTextures(NUM_TEXTURES, textureObjects);
    }


// �ӿ�����
void Viewport(int w, int h)
    {
    float fAspect;

    // ��ֹ����Ϊ0
    if(h == 0)
        h = 1;

    // ��������ڴ��ڵ��ӿ�
    glViewport(0, 0, w, h);

    // ���㴰���ݺ��
    fAspect = (float)w/(float)h;

    // ת����ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ͶӰ�任��60�Ƚǣ����ӵ��������Զλ��
    gluPerspective(60.0f, fAspect, 1.0, 1000.0);

    // �ָ���ģ������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }


// ������
int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(1024, 768);
	glutCreateWindow("̫��-����-����");
	glutReshapeFunc(Viewport);
	glutSpecialFunc(Keys);
	glutMouseFunc(MouseClick);
	glutDisplayFunc(Render);
    glutTimerFunc(50, Timer, 1);
	Initialize();
	glutMainLoop();
	Shutdown();

	return 0;
	}
