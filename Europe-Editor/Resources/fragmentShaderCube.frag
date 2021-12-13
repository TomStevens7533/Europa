#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_TextureDir;
in vec4 v_Color;
	

uniform samplerCube u_Texture;


void main()
{

	vec4 tempColor = texture(u_Texture, v_TextureDir); 
	tempColor.a = 1.f;
	color = tempColor;

	

	
}