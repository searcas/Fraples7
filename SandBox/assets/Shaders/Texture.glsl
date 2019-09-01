#type vertex
#version 330 core

	layout(location = 0) in vec3 _aPosition;
	layout(location = 1) in vec2 _aTexCoord;
	
	uniform mat4 _uViewProjectionMatrix;			
	uniform mat4 _uTransform;			

	out vec2 _vTexCoord;

	void main()
	{
		_vTexCoord = _aTexCoord;
		gl_Position = _uViewProjectionMatrix * _uTransform * vec4(_aPosition, 1.0);
	}
#type fragment
#version 330 core

	layout(location = 0) out vec4 color;
	in vec2 _vTexCoord;
	uniform sampler2D _uTexture;


	void main()
	{	
		color = texture(_uTexture, _vTexCoord);
	}