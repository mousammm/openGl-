# VECTOR 
vector - represent x,y,z 
vec3 A=(1.0f, 2,0f, 0.0f)

# UNIT VECTOR 
unit vector  
glm::to_string(glm::normalize(A))  // makes vector to 1  U = x2 + y2 = 1

# DOT PRODUCT 
dot product tell us how similar 2 vec are we can figure out the angle 
dot product of (A,B) 
glm::vec3 A(3.0f, 4.0f, 0.0f)
glm::vec3 B(0.0f, 4.0f, 0.0f)

dot = 3x0 + 4x4 + 0x0
dot = (Ax)x(Bx) + (Ay)x(By) + (Az)x(Bz)

to find the angle btw 2 vector 
1 dot normalize

float dot = (glm::dot(glm::normalize(A)),
                 dot(glm::normalize(B)));

2 find the angle 

 std::acos(dot) * 180.0 / M_PI 

# CROSS PRODUCT 
to get the perpendicular verctor from 2 other vector 

glm::vec3 A(4.0f, 0.0f, 0.0f)
glm::vec3 B(0.0f, 4.0f, 0.0f)

glm::vec3 C = glm::cross(A,B) // 0,0,16

glm::to_string(C)
