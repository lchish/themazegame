#include <cstdio>
#include <GL/glut.h>

/* Generates a generic texture with some parameters already set
	Example usage:

	GLuint wall_texture = genTexture("images/textures/wall.raw",TRUE)
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
	glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
	glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
	glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
	glEnd();

*/
GLuint genTexture(char *filename,int wrap){
	GLuint texture;
	int width,height;
	char *data;
	FILE *file;

	width = 256;
	height = 256;
	data = (char *)malloc(width * height *3);
	fopen_s(&file,filename,"rb");
	fread(data,width*height*3,1,file);
	fclose(file);
	
	//allocate a texture name(aka number)
	glGenTextures(1,&texture);
	//select our current texture
	glBindTexture(GL_TEXTURE_2D,texture);
	//select modulate to mix texture with colour for shading
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//when a texure area is small,bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	//when a texture area is large bilinear filter the original
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//the texture wraps over the edges
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//build mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);

	free(data);
	return texture;
}