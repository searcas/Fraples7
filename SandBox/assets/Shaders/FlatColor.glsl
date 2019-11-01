//Flat color shader

#type vertex
#version 330 core

	layout(location = 0) in vec3 _aPosition;
	
	uniform mat4 _uViewProjectionMatrix;			
	uniform mat4 _uTransform;			


	void main()
	{
		gl_Position = _uViewProjectionMatrix * _uTransform * vec4(_aPosition, 1.0);
	}
#type fragment
#version 330 core

	layout(location = 0) out vec4 color;
	
	uniform vec4 _uColor;


	void main()
	{	
		color = _uColor;
	}