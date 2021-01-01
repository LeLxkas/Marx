struct VS_INPUT
{
	float2 pos : POSITION;
	float3 color : COLOR;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : OUT_COLOR;
};

VS_OUTPUT main(VS_INPUT inp)
{
	VS_OUTPUT op;
	op.pos = float4(inp.pos, 0.0f, 1.0f);
	op.color = float4(inp.color, 1.0f);
	return op;
}