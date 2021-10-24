#type vertex
#version 330 core

	layout(location = 0) in vec3 _aPosition;
	layout(location = 1) in vec4 _aColor;
	layout(location = 2) in vec2 _aTexCoord;
	layout(location = 3) in float _aTexIndex;
	layout(location = 4) in float _aTiling;
	
	uniform mat4 _uViewProjectionMatrix;			

	out vec2 _vTexCoord;
	out vec4 _vColor;
	out float _vTexIndex;
	out float _vTiling;

	void main()
	{
		_vColor = _aColor;
		_vTexCoord = _aTexCoord;
		_vTexIndex = _aTexIndex;
		_vTiling = _aTiling;
		gl_Position = _uViewProjectionMatrix * vec4(_aPosition, 1.0);
	}

#type fragment
#version 330 core

	layout(location = 0) out vec4 color;
	
	in vec4 _vColor;
	in vec2 _vTexCoord;
	in float _vTexIndex;
	in float _vTiling;
	
	uniform sampler2D _uTextures[32];



	void main()
	{	
		color = texture(_uTextures[int(_vTexIndex)], _vTexCoord * _vTiling) * _vColor;
	}