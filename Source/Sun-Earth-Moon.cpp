#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>  
#include "Utility.h"


// 键盘控制旋转变量
static float xRot = 0.0f;
static float yRot = 0.0f;


// 光照属性参数
float  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float  sourceLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float  specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float  lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };


//纹理参数
#define SUN_TEXTURE  0  
#define EARTH_TEXTURE  1
#define MOON_TEXTURE  2
#define NUM_TEXTURES    3
GLuint  textureObjects[NUM_TEXTURES];
const char *TextureFiles[] = {"sun.tga", "earth.tga", "moon.tga"};

// 选择参数
int selectedSun = 0;
int selectedEarth = 0;
int selectedMoon = 0;

#define SUN 4
#define EARTH 5
#define MOON 6


// 渲染场景
void Render(void)
	{
	// 太阳、地球和月亮的自转变量
	static float fMoonRot = 0.0f;	
	static float fEarthRot = 0.0f;
	static float fSunRot = 0.0f;
	
	// 地球和月亮的公转变量
    static float fMoonRev = 0.0f;
	static float fEarthRev = 0.0f;

	// 清除场景
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 保存当前模型坐标
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// 将整个场景朝前（z轴）移动400个单位
	glTranslatef(0.0f, 0.0f, -400.0f);

	// 初始化names stack，用于选取动作
    glInitNames();
	glPushName(0);

    // 更新当前键盘控制的旋转
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	// 画太阳，包括自转运动
	glPushMatrix();	
    glDisable(GL_LIGHTING);

	// 若点击太阳，则使用纹理，以下类似代码功能相同
	if(selectedSun == SUN)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255,255,255);
		glBindTexture(GL_TEXTURE_2D, textureObjects[SUN_TEXTURE]);
	}
	// 若再次点击太阳，则不使用纹理，以下类似代码功能相同
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

	// 更新太阳的自转变量
	fSunRot -= 1.0f;
	if(fSunRot < -360.0f)
		fSunRot = 0.0f;

	// 定位光源
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

	// 画地球，包括公转和自转运动
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

	// 更新地球的公转变量
	fEarthRev += 1.0f;
	if(fEarthRev > 360.0f)
		fEarthRev = 0.0f;

	// 更新地球的自转变量
	fEarthRot += 5.0f;
	if(fEarthRot > 360.0f)
		fEarthRot = 0.0f;

	// 画月球，包括公转和自转运动
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

	// 更新月球的公转变量
	fMoonRev+= 5.0f;
	if(fMoonRev > 360.0f)
		fMoonRev = 0.0f;

	// 更新月球的自转变量
	fMoonRot -= 10.0f;
	if(fMoonRot < -360.0f)
		fMoonRot = 0.0f;

	// 恢复模型坐标
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






	// 移动场景，使坐标轴与整个场景的位置匹配
    glTranslatef(0.0f, 0.0f, -400.0f);
	glTranslatef(0.0f, -200.0f, 0.0f);
	glTranslatef(-250.0f, 0.0f, 0.0f);


    // 更新当前键盘控制的旋转
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// 画坐标轴
	DrawAxes();




	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);




	glPopMatrix();

	// 显示图像
	glutSwapBuffers();
	}


// 在窗口上显示鼠标选取的对象名称
void NameDisplay(int id)
	{
	switch(id)
		{
		case SUN:
			glutSetWindowTitle("太阳被选取！");
			break;

		case EARTH:
			glutSetWindowTitle("地球被选取！");
			break;

		case MOON:
			glutSetWindowTitle("月球被选取！");
			break;

		default:
			glutSetWindowTitle("什么也没有选取！");
			break;
		}		
	}


// 处理选取动作
#define BUFFER_LENGTH 64
void Selection(int xPos, int yPos)
	{
	float fAspect;

	// 定义selection buffer
	static GLuint selectBuff[BUFFER_LENGTH];

	// 定义鼠标点击的标识及用于选取动作的视口
	int hits, viewport[4];

	// 获取selection buffer
	glSelectBuffer(BUFFER_LENGTH, selectBuff);
	
	// 获取用于选取动作的视口
	glGetIntegerv(GL_VIEWPORT, viewport);

	// 转换到透视坐标，并存储当前状态
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	// 调整到选取模式进行渲染
	glRenderMode(GL_SELECT);

	// 确定鼠标周围的裁减空间
	glLoadIdentity();
	gluPickMatrix(xPos, viewport[3] - yPos + viewport[1], 2,2, viewport);

	// 设置选取渲染得窗口属性
	fAspect = (float)viewport[2] / (float)viewport[3];
	gluPerspective(60.0f, fAspect, 1.0, 1000.0);

	// 进行渲染
	Render();

	hits = glRenderMode(GL_RENDER);

    GLuint nErr = glGetError();

	// 若有鼠标点击动作，则进行处理
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
		glutSetWindowTitle("什么也没有选取！");

	// 恢复透视坐标
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// 回到模型坐标
	glMatrixMode(GL_MODELVIEW);
	}


// 初始化 
void Initialize()
	{
    int i;

	// 设置深度检测、正反面及取消内面的计算
	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);		
	glEnable(GL_CULL_FACE);		

	// 启动光照
	//glEnable(GL_LIGHTING);

	// 设置光源的属性，如环境光照、漫射光照及光源位置的参数
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);
    
	// 光照下的材质颜色属性
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

    // 设置纹理
    glEnable(GL_TEXTURE_2D);
    glGenTextures(NUM_TEXTURES, textureObjects);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for(i = 0; i < NUM_TEXTURES; i++)
        {
        GLbyte *pBytes;
        GLint iWidth, iHeight, iComponents;
        GLenum eFormat;
        
        glBindTexture(GL_TEXTURE_2D, textureObjects[i]);
        
        // 读取纹理图片
        pBytes = LoadTGA(TextureFiles[i], &iWidth, &iHeight, &iComponents, &eFormat);
        gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
		
		free(pBytes);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

	// 设置背景颜色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    glEnable(GL_MULTISAMPLE);
    }


// 渲染更新时间间隔
void Timer(int value)
    {
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 1);
    }


// 键盘控制
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


// 处理鼠标动作
void MouseClick(int button, int state, int x, int y)
	{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		Selection(x, y);
	}


// 关闭资源
void Shutdown(void)
    {
    // 删除textureObjects对象
    glDeleteTextures(NUM_TEXTURES, textureObjects);
    }


// 视口属性
void Viewport(int w, int h)
    {
    float fAspect;

    // 防止除数为0
    if(h == 0)
        h = 1;

    // 建立相对于窗口的视口
    glViewport(0, 0, w, h);

    // 计算窗口纵横比
    fAspect = (float)w/(float)h;

    // 转换到投影坐标
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 投影变换，60度角，可视的最近和最远位置
    gluPerspective(60.0f, fAspect, 1.0, 1000.0);

    // 恢复到模型坐标
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }


// 主函数
int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(1024, 768);
	glutCreateWindow("太阳-地球-月亮");
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
