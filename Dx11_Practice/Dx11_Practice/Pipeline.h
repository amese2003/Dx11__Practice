#pragma once

class InputLayout;
class VertexShader;
class PixelShader;
class RasterizerState;
class BlendState;
class IndexBuffer;
class Texture;
class SamplerState;

struct PipelineInfo
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<VertexShader> vertexShader;
	shared_ptr<PixelShader> pixelShader;
	shared_ptr<RasterizerState> rasterizerState;
	shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};


class Pipeline
{
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);

	template<typename Ty>
	void SetConstantBuffer(uint32 slot, uint32 scope, shared_ptr<ConstantBuffer<Ty>> buffer)
	{
		if (scope == SS_VertexShader)
			_deviceContext->IASetVertexBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

		if (scope == SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
	}

	void SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> state);

	void Draw(uint32 vertexCount, uint32 startVertexLocation = 0);
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation = 0, uint32 baseVertexLocation = 0);

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

