set(SOIL_lib_src image_DXT.c image_helper.c SOIL.c stb_image_aug.c)

ADD_LIBRARY(SOIL STATIC ${SOIL_lib_src})
