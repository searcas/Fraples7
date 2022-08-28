#type vertex
#version 330 core

	layout(location = 0) in vec3 _aPosition;
	layout(location = 1) in vec4 _aColor;
	layout(location = 2) in vec2 _aTexCoord;
	layout(location = 3) in float _aTexIndex;
	layout(location = 4) in float _aTiling;
	layout(location = 5) in int _aEntityID ;
	
	uniform mat4 _uViewProjectionMatrix;			

	out vec2 _vTexCoord;
	out vec4 _vColor;
	out float _vTexIndex;
	out float _vTiling;
	out flat int _vEntityID;

	void main()
	{
		_vColor = _aColor;
		_vTexCoord = _aTexCoord;
		_vTexIndex = _aTexIndex;
		_vTiling = _aTiling;
		_vEntityID = _aEntityID; 
		gl_Position = _uViewProjectionMatrix * vec4(_aPosition, 1.0);
	}

#type fragment
#version 330 core

	layout(location = 0) out vec4 color;
	layout(location = 1) out int redInt;
	
	in vec4 _vColor;
	in vec2 _vTexCoord;
	in float _vTexIndex;
	in float _vTiling;
	in flat int _vEntityID;
	
	uniform sampler2D _uTextures[32];



	void main()
	{	
		vec4 texColor = _vColor;
		switch(int(_vTexIndex))
		{
			case 0: texColor *= texture(_uTextures[0], _vTexCoord * _vTiling); break;
			case 1: texColor *= texture(_uTextures[1], _vTexCoord * _vTiling); break;
			case 2: texColor *= texture(_uTextures[2], _vTexCoord * _vTiling); break;
			case 3: texColor *= texture(_uTextures[3], _vTexCoord * _vTiling); break;
			case 4: texColor *= texture(_uTextures[4], _vTexCoord * _vTiling); break;
			case 5: texColor *= texture(_uTextures[5], _vTexCoord * _vTiling); break;
			case 6: texColor *= texture(_uTextures[6], _vTexCoord * _vTiling); break;
			case 7: texColor *= texture(_uTextures[7], _vTexCoord * _vTiling); break;
			case 8: texColor *= texture(_uTextures[8], _vTexCoord * _vTiling); break;
			case 9: texColor *= texture(_uTextures[9], _vTexCoord * _vTiling); break;
			case 10: texColor *= texture(_uTextures[10], _vTexCoord * _vTiling); break;
			case 11: texColor *= texture(_uTextures[11], _vTexCoord * _vTiling); break;
			case 12: texColor *= texture(_uTextures[12], _vTexCoord * _vTiling); break;
			case 13: texColor *= texture(_uTextures[13], _vTexCoord * _vTiling); break;
			case 14: texColor *= texture(_uTextures[14], _vTexCoord * _vTiling); break;
			case 15: texColor *= texture(_uTextures[15], _vTexCoord * _vTiling); break;
			case 16: texColor *= texture(_uTextures[16], _vTexCoord * _vTiling); break;
			case 17: texColor *= texture(_uTextures[17], _vTexCoord * _vTiling); break;
			case 18: texColor *= texture(_uTextures[18], _vTexCoord * _vTiling); break;
			case 19: texColor *= texture(_uTextures[19], _vTexCoord * _vTiling); break;
			case 20: texColor *= texture(_uTextures[20], _vTexCoord * _vTiling); break;
			case 21: texColor *= texture(_uTextures[21], _vTexCoord * _vTiling); break;
			case 22: texColor *= texture(_uTextures[22], _vTexCoord * _vTiling); break;
			case 23: texColor *= texture(_uTextures[23], _vTexCoord * _vTiling); break;
			case 24: texColor *= texture(_uTextures[24], _vTexCoord * _vTiling); break;
			case 25: texColor *= texture(_uTextures[25], _vTexCoord * _vTiling); break;
			case 26: texColor *= texture(_uTextures[26], _vTexCoord * _vTiling); break;
			case 27: texColor *= texture(_uTextures[27], _vTexCoord * _vTiling); break;
			case 28: texColor *= texture(_uTextures[28], _vTexCoord * _vTiling); break;
			case 29: texColor *= texture(_uTextures[29], _vTexCoord * _vTiling); break;
			case 30: texColor *= texture(_uTextures[30], _vTexCoord * _vTiling); break;
			case 31: texColor *= texture(_uTextures[31], _vTexCoord * _vTiling); break;
		}
		color = texColor;
		redInt = _vEntityID;
	}