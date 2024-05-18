
cbuffer grobal
{
	float4 g_matWLP 
};

float4 VS( float4 pos : POSITION )
{
	float4 posWLP = mul(pos, g_matWLP);
	return posWLP;
}

float4 PS(float4 inData) : SV_Target
{
	float color = inData.z / inData.w;
	color.a = 1;
	return color;
}