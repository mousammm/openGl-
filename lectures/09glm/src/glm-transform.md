# TRANSFORMATION
so we are going to do some function in the xyz and make it transform so that it move or scale 

glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.0f)
                  x     y     z     w

w = POINT for determing a point or direction 
1=point 0=verctor 
point - point = verter 
point + point = nonsense
vec - vex     = vec


# ACTUAL TRANSFORM 

1 glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.0f)
2 glm::mat4 model(1.0f)
3 MULTIPLY
   x y z w
 [ 1 0 0 0 ]   [1]   [1]
 [ 0 1 0 0 ] x [5] = [5]
 [ 0 0 1 0 ]   ]1]   ]1]
 [ 0 0 0 1 ]   [1]   [1]
 
in GLM 

we multiply x y z by 2 
 glm::vec4 vertex(2.0f, 2.0f, 2.0f, 1.0f)

// for printing model
model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f)) 
model = glm::rotate(glm::mat4(1.0f), glm::radians(180.0), glm::vec3(0,1,0)) 
model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)) 

we get  for scale 
 [ 2 0 0 0 ]
 [ 0 2 0 0 ]
 [ 0 0 2 0 ]
 [ 0 0 0 2 ]

// to scale
glm::vec4 worldspace_vertex = (model * vertex)

# Trannsfoorm Transllate Scael 

glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f)) 
glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(180.0), glm::vec3(0,1,0)) 
glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)) 

// order of operation matter s->r->t
model = s*r*t;
