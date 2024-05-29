
cbuffer grobal
{
	float4x4	g_matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matW;				//ワールド行列
	float4x4	g_matWLP;			//光源からみた時のg_matWVP
	float4x4	g_matWLPT;			//↑にテクスチャ座標行列を合成した奴
	float4x4    g_matNormal;		//法線変形行列(回転行列と拡大行列の逆行列)
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
	float4 pos : SV_POSITION;
	float4 depth	: TEXCOORD0;
};

VS_OUT VS(float4 pos : POSITION)
{
	VS_OUT outWLP;
	outWLP.pos = mul(pos, g_matWLP);
	outWLP.depth = outWLP.pos;
	return outWLP;
}

float4 PS(VS_OUT inData) : SV_Target
{
	float4 color = float4(0,0,0,1);
	color.r = inData.depth.z / inData.depth.w;
	color.g = color.r * color.r;
	color.a = 1;
	return color;
	//return float4(1,1,1,1);
}