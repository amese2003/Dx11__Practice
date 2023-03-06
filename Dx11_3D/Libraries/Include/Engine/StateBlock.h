#pragma once

struct StateBlock
{
	ComPtr<ID3D11RasterizerState> RSRasterizerState;
	ComPtr<ID3D11BlendState> OMBlendState;
	FLOAT OMBlendFactor[4];
	UINT OMSampleMask;
	ComPtr<ID3D11DepthStencilState> OMDepthStencilState;
	UINT OMStencilRef;
};
