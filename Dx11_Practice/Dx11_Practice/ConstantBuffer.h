#pragma once
template<typename Ty>
class ConstantBuffer
{
public:
	ConstantBuffer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : _device(device), _deviceContext(deviceContext) {}
	~ConstantBuffer() {}

	ComPtr<ID3D11Buffer> GetComPtr() { return _constantBuffer; }

	void Create() 
	{
		D3D11_BUFFER_DESC buffer;
		ZeroMemory(&buffer, sizeof(D3D11_BUFFER_DESC));
		buffer.Usage = D3D11_USAGE_DYNAMIC; // CPU:Write / GPU:Read
		buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		buffer.ByteWidth = sizeof(Ty);
		buffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = _device->CreateBuffer(&buffer, nullptr, _constantBuffer.GetAddressOf());
		CHECK(hr); 
	}

	void CopyData(const Ty& data)
	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		ZeroMemory(&subRes, sizeof(D3D11_MAPPED_SUBRESOURCE));

		_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, &data, sizeof(data));
		_deviceContext->Unmap(_constantBuffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _constantBuffer;
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

