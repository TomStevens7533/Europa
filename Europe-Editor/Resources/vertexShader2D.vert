#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in int a_NormalTextureIDX;
layout(location = 2) in int a_UV;




uniform mat4 u_ViewProj;
uniform mat4 u_World;

flat out uint v_TextureID;
flat out uint v_LighLevel;
out vec2 v_UV;



void main()
{
	int lightLevel = (int(a_NormalTextureIDX) & 0x000000FF);
	int normal = (int(a_NormalTextureIDX) & 0x0000FF00) >> 8;
	int TextureID = (int(a_NormalTextureIDX) & 0x00FF0000) >> 16;


	int height =  int(a_UV & 0x0000FFFF);
    int width = int( (a_UV >> 16) & 0x0000FFFF);
	v_TextureID = uint(TextureID);
	v_LighLevel = uint(lightLevel);
	v_UV = vec2(width, height);
	gl_Position = (u_ViewProj * u_World) * (vec4(a_Position, 1.0));
	
}