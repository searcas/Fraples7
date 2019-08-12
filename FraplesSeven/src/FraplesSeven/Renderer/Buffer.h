#pragma once




namespace Fraples
{
	enum class ShaderDataType : uint8_t
	{
		NONE		= 0,
		Float		= 1,
		Float2		= 2,
		Float3		= 3,
		Float4		= 5,
		Mat3		= 6,
		Mat4		= 7,
		Int,
		Int2,
		Int3,
		Int4,
		Boolean
	};
	static uint32_t	ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Fraples::ShaderDataType::NONE:
			FPL_CORE_ASSERTS(false, "None Shader.");
			return 0;
			break;
		case Fraples::ShaderDataType::Float:
			return 4;
			break;
		case Fraples::ShaderDataType::Float2:
			return 4 * 2;
			break;
		case Fraples::ShaderDataType::Float3:
			return 4 * 3;
			break;
		case Fraples::ShaderDataType::Float4:
			return 4 * 4;
			break;
		case Fraples::ShaderDataType::Mat3:
			return 4 * 3 * 3;
			break;
		case Fraples::ShaderDataType::Mat4:
			return 4 * 4 * 4;
			break;
		case Fraples::ShaderDataType::Int:
			return 4;
			break;
		case Fraples::ShaderDataType::Int2:
			return 4 * 2;
			break;
		case Fraples::ShaderDataType::Int3:
			return 4 * 3;
			break;
		case Fraples::ShaderDataType::Int4:
			return 4 * 4;
			break;
		case Fraples::ShaderDataType::Boolean:
			return 1;
			break;
		default:
			break;
		}
		FPL_CORE_ASSERTS(false, "Unkonwn Shader Type.");
		return 0;
	}
	struct BufferElements
	{
		std::string Name;
		ShaderDataType SDataType; 
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
		BufferElements(ShaderDataType type, const std::string& name,bool normlized = false) :SDataType(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normlized)
		{

		}
		uint32_t GetComponentCount() const
		{
			switch (SDataType)
			{
			case ShaderDataType::Float:
				return 1;
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Float4:
				return 4;
			case ShaderDataType::Mat3:
				return 4 * 3;
			case ShaderDataType::Mat4:
				return 4 * 4;
			case ShaderDataType::Int:
				return 1;
			case ShaderDataType::Int2:
				return 2;
			case ShaderDataType::Int3:
				return 3;
			case ShaderDataType::Int4:
				return 4;
			case ShaderDataType::Boolean: 
				return 1;
			default:
				FPL_CORE_ASSERTS(false, "Unkonwn Shader Type.");
				return 0;
			}
		}
	};
	class BufferLayout
	{
	public:
		inline const std::vector<BufferElements>& GetElements()const { return _mElements; }
		inline const uint32_t GetStride()const { return _mStride; }
		std::vector<BufferElements>::iterator begin() { return _mElements.begin(); }
		std::vector<BufferElements>::iterator end() { return _mElements.end(); }
		std::vector<BufferElements>::const_iterator begin()const { return _mElements.begin(); }
		std::vector<BufferElements>::const_iterator end() const { return _mElements.end(); }
		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElements>& elements) :_mElements(elements)
		{
			CalculateOffsetsAndStride();
		}
	private:
		inline void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			_mStride = 0;
			for (BufferElements& elements : _mElements)
			{
				elements.Offset = offset;
				offset += elements.Size;
				_mStride += elements.Size;
			}
		}
	private:
		std::vector<BufferElements>_mElements;
		uint32_t _mStride = 0;
	};
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;


		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer();
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const  = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);

	};
}