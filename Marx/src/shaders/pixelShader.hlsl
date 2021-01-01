struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : OUT_COLOR;
};

float4 main(VS_OUTPUT inp) : SV_TARGET
{
	return inp.color;
}