#include <stdio.h>

#define GL_CLAMP_TO_EDGE 0x812F
#define GL_MULTISAMPLE 0x809D

// ∂®“ÂtargaÕº∆¨µƒÕ∑–≈œ¢
#pragma pack(1)
typedef struct
{
    GLbyte	identsize;              
    GLbyte	colorMapType;           
    GLbyte	imageType;              
    unsigned short	colorMapStart;          
    unsigned short	colorMapLength;        
    unsigned char 	colorMapBits;   
    unsigned short	xstart;                 
    unsigned short	ystart;                 
    unsigned short	width;                  
    unsigned short	height;                 
    GLbyte	bits;                   
    GLbyte	descriptor;             
} TGAHEADER;
#pragma pack(8)


// ∂¡»°targaÕº∆¨
GLbyte *LoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
	{
    FILE *pFile;			
    TGAHEADER tgaHeader;		
    unsigned long lImageSize;		
    short sDepth;			
    GLbyte	*pBits = NULL;          
    

    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;
    

    pFile = fopen(szFileName, "rb");
    if(pFile == NULL)
        return NULL;
	

    fread(&tgaHeader, 18, 1, pFile);
	
	

    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;
    
    if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;
	
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pBits == NULL)
        return NULL;
    
    if(fread(pBits, lImageSize, 1, pFile) != 1)
		{
        free(pBits);
        return NULL;
		}
    
    switch(sDepth)
		{
        case 3:     
            *eFormat = GL_BGR_EXT;
            *iComponents = GL_RGB8;
            break;
        case 4:
            *eFormat = GL_BGRA_EXT;
            *iComponents = GL_RGBA8;
            break;
        case 1:
            *eFormat = GL_LUMINANCE;
            *iComponents = GL_LUMINANCE8;
            break;
		};
	
    
    fclose(pFile);
	
    return pBits;
	}



// ª≠«ÚÃÂ
void DrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
	{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;	
	GLfloat s = 0.0f;
    GLint i, j;     
	
	for (i = 0; i < iStacks; i++) 
		{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));
		
		glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
		for ( j = 0; j <= iSlices; j++) 
			{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));
			
			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
			}
        glEnd();

        t -= dt;
        }
    }


// ª≠◊¯±Í÷·
void DrawAxes(void)
	{
	GLUquadricObj *pObj;
	
	float fAxisRadius = 2.5f;
	float fAxisHeight = 25.0f;
	float fArrowRadius = 3.0f;
	float fArrowHeight = 5.0f;


	/*float fAxisRadius = 100.0f;
	float fAxisHeight = 100.0f;
	float fArrowRadius = 100.0f;
	float fArrowHeight = 100.0f;*/

	
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);
	gluQuadricNormals(pObj, GLU_SMOOTH);
	gluQuadricOrientation(pObj, GLU_OUTSIDE);
	gluQuadricTexture(pObj, GLU_FALSE);
	
	// ª≠Z÷·
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 25.0f);
	gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
	glPopMatrix();
	
	// ª≠X÷·
    glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 25.0f);
	gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
	glPopMatrix();
	glPopMatrix();
	
	// ª≠Y÷·
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 25.0f);
	gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
	glPopMatrix();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	gluSphere(pObj, 4.0f, 15, 15);
	
	gluDeleteQuadric(pObj);
	}