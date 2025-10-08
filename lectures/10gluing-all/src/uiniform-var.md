# Vertec Buffer Object 

VBO = [x1,y1,z1,r1,g1,b1, ....]
      [      v1       ]

blah = vec4(positon.x, position.y, position.z )
now how do we sen the change the xyz value like from cpu to gpu 

# INITIALIZE uniform 

vert.glsl -> uiform float u_Offset; // uinform var
frag.glsl -> uiform float u_Offset; // uinform var

next in vert.glsl
  post.x + u_Offset

main.cpp 
float g_uOffset = 0.0f;
now set in sdl 
sdl g_uOffset += 0.01f;
sdl g_uOffset -= 0.01f;
