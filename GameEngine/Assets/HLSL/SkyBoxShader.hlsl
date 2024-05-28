Texture2D	 g_texture:register(t0);//テクスチャ
SamplerState g_sampler:register(s0);//サンプラー
//コンスタントバッファ
cbuffer global
{
	float4x4	g_matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matW;				//ワールド行列
	float4x4    g_matNormal;		//法線変形行列(回転行列と拡大行列の逆行列)
	float4x4	g_matWLP;			//光源からみた時のg_matWVP
	float4x4	g_matWLPT;			//↑にテクスチャ座標行列を合成した奴
	float4		g_diffuseColor;		// ディフューズカラー（マテリアルの色）
	float4		g_ambient;			//アンビエント
	float4		g_speculer;			//スペキュラー
	float4		g_lightDirection;	//ライトの向き
	float4		g_cameraPosition;	//カメラの位置
	float4      g_customColor;		//プログラム側で色を変える場合の変数
	float		g_shininess;		//ハイライトの強さ
	bool		g_isTexture;		// テクスチャ貼ってあるかどうか
	bool		g_isNormal;  //プログラム側で変える色
};
struct VS_OUT
{
	float4 pos: SV_POSITION;
	float4 normal : TEXCOORD0;
	float2 uv:TEXCOORD1;
	float4 color:COLOR0;
};
VS_OUT VS( float4 pos : POSITION ,float4 uv:TEXCOORD,float4 normal:NORMAL)
{
	VS_OUT outData;
	//頂点の座標やノーマルに行列かけてピクセルシェーダーに渡す
	outData.pos = mul(pos, g_matWVP);
	normal.w = 0;
	outData.normal = mul(normal, g_matNormal);
	outData.uv = uv;

	return outData;
}

float4 PS(VS_OUT inData) : SV_Target
{
	inData.normal = normalize(inData.normal);
	//拡散反射光(ディフューズ)
	float4 diffuse;
	if (g_isTexture == true)
	{
		diffuse = g_texture.Sample(g_sampler, inData.uv);
	}
	else
	{
		diffuse = g_diffuseColor;
	}
	
	//環境光(アンビエント)
	float4 ambient = g_ambient;
	ambient.a = 1;

	float4 outColor;
	outColor = diffuse * ambient;
	return outColor;
}


