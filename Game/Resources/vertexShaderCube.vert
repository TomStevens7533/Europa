#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec3 v_TextureDir;

uniform mat4 u_ViewProj;
uniform mat4 u_TranslationMat;

uniform int u_IsBackGround;




void main()
{
	if(u_IsBackGround > 0){
	
		v_TextureDir = a_Position;
		vec3 newPos = a_Position;
		newPos.x = -newPos.x;
		vec4 pos = u_ViewProj * (u_TranslationMat * vec4(newPos, 1.0));
		gl_Position = pos.xyww;

	}
	else{
		v_TextureDir = a_Position;
		vec4 pos = u_ViewProj  * u_TranslationMat * (vec4(a_Position, 1.0));
		gl_Position = pos;

	}
	
}