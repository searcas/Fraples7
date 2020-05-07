#type vertex
#version 330 core

	layout(location = 0) in vec3 _aPosition;
	layout(location = 1) in vec4 _aColor;
	layout(location = 2) in vec2 _aTexCoord;
	
	uniform mat4 _uViewProjectionMatrix;			

	out vec2 _vTexCoord;
	out vec4 _vColor;
	void main()
	{
		_vColor = _aColor;
		_vTexCoord = _aTexCoord;
		gl_Position = _uViewProjectionMatrix * vec4(_aPosition, 1.0);
	}

#type fragment
#version 330 core

	layout(location = 0) out vec4 color;
	
	in vec4 _vColor;
	in vec2 _vTexCoord;
	
	uniform vec4 _uColor;
	uniform float _uTiling;
	uniform sampler2D _uTexture;


	void main()
	{	
		//color = texture(_uTexture, _vTexCoord * _uTiling) * _uColor;
		color = _vColor;
	}