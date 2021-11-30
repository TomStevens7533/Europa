#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_Uv;
layout(location = 3) in vec3 a_Light;


uniform mat4 u_TransForm;
uniform mat4 u_Proj;
uniform vec4 u_Color;


out vec2 v_TexCord;
out vec4 v_Color;
out vec3 v_Light;



void main()
{
	v_TexCord = a_Uv;
	v_Color = u_Color;
	v_Light = a_Light;
	gl_Position =  ((u_TransForm) * (vec4(a_Position , 1.0)));
	
}