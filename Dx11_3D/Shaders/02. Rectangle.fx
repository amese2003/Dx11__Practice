struct VertexInput
{
    float4 position : POSITION;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = input.position;

    return output;
}

float4 PS_R(VertexOutput input) : SV_Target
{
    return float4(1, 0, 0, 1);
}

RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_R()));
    }

    pass P1
    {
        SetRasterizerState(FillModeWireFrame);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_R()));
    }
}