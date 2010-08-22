/* Generates a generic texture with some parameters already set and returns
 * a pointer to it.
 *
 *  Example usage:
 *
 *  GLuint wall_texture = genTexture("images/textures/wall.raw")
 *  glBindTexture(GL_TEXTURE_2D,texture);
 *  glBegin(GL_QUADS);
 *   glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
 *   glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
 *   glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
 *   glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
 *  glEnd();

*/
#include <cstdio>
#include <SOIL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "globals.h"
#include "texture.h"

bool anisotropic_filtering;
float max_anistropy;

GLuint genTexture(const char *filename){
  /* load an image file directly as a new OpenGL texture */
  printf("%s\n",filename);
  GLuint tex_2d = SOIL_load_OGL_texture
    (
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y  
     /*SOIL_FLAG_NTSC_SAFE_RGB*/ /*| SOIL_FLAG_COMPRESS_TO_DXT !causes segfault on
			     *lab computers*/
     );

  /* check for an error during the load process */
  if( 0 == tex_2d )
    {
      fprintf(stderr,"SOIL loading error: '%s'\n", SOIL_last_result() );
    }
  if(anisotropic_filtering){
    glBindTexture(GL_TEXTURE_2D,tex_2d);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,
		    max_anistropy);
  }
  return tex_2d;
}
GLuint genMipMapTexture(const char *filename){
  /* load an image file directly as a new OpenGL texture */
  printf("%s\n",filename);
  GLuint tex_2d = SOIL_load_OGL_texture
    (
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y  | SOIL_FLAG_MIPMAPS 
     /*SOIL_FLAG_NTSC_SAFE_RGB*/ /*| SOIL_FLAG_COMPRESS_TO_DXT !causes segfault on
			     *lab computers*/
     );

  /* check for an error during the load process */
  if( 0 == tex_2d )
    {
      fprintf(stderr,"SOIL loading error: '%s'\n", SOIL_last_result() );
    }
  if(anisotropic_filtering){
    glBindTexture(GL_TEXTURE_2D,tex_2d);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,
		    max_anistropy);
  }
  return tex_2d;
}
