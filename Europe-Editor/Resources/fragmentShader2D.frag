#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;	
in vec3 v_Color;
in vec3 v_Light;





uniform sampler2DArray my_sampler;


void main()
{
	vec4 tempColor;
	int constantUV = int(round(v_Color.z * 255));


	tempColor = texture(my_sampler, vec3(v_TexCord.x,v_TexCord.y, v_Color.z)); 
	
	tempColor.xyz = vec3(tempColor.x * v_Light.x, tempColor.y * v_Light.y,tempColor.z);


	color = tempColor;

	

	
}