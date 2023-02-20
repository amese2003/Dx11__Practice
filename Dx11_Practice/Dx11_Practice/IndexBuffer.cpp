#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ComPtr<ID3D11Device> device) : _device(device)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const vector<uint32>& indecis)
{
	_stride = sizeof(uint32);
	_count = static_cast<uint32>(indecis.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = (uint32)(sizeof(Vertex) * indecis.size());

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &indecis[0];

	_device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
}
