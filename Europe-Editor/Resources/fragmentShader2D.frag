#version 330 core

layout(location = 0) out vec4 color;

flat in uint v_TextureID;
flat in uint v_LighLevel;

in vec2 v_UV;

uniform sampler2DArray my_sampler;


void main()
{
	vec4 tempColor;

	tempColor = texture(my_sampler, vec3(v_UV.x, v_UV.y, v_TextureID)); 
	
	float lightColor = (v_LighLevel * 0.01f);
	tempColor.xyz = vec3(tempColor.x * (lightColor), tempColor.y * (lightColor),tempColor.z * (lightColor));

	color = tempColor;

	

	
}