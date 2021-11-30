#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;	
in vec3 v_Color;
in vec3 v_Light;





uniform sampler2D u_Texture;


void main()
{
	vec4 tempColor;
		


	tempColor = texture(u_Texture, v_TexCord); 


	if(tempColor.a < 0.5f)
		discard;

	tempColor.xyz = vec3(tempColor.x * v_Light.x, tempColor.y * v_Light.y,tempColor.z);


	color = tempColor;

	

	
}