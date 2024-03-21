//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������


//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	g_matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matW;				//���[���h�s��	
	float4x4    g_matNormal;		//�@���ό`�s��(��]�s��Ɗg��s��̋t�s��)
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos		: SV_POSITION;	//�ʒu
	float4 normal	: TEXCOORD0;	//�@��
	float4 light	: TEXCOORD1;	//���C�g
	float4 eyeVector: TEXCOORD2;	//����
	float4 col		: COLOR0;		//�J���[
	float4 fog		: COLOR1;		//�t�H�O
	float4 wPos     : COLOR2;		//
	float2 uv		: TEXCOORD3;	//UV���W
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
float4 VS(float4 pos : POSITION, float4 uv : TEXCOORD) : SV_POSITION
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	//VS_OUT outData;
	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	//outData.pos = mul(pos, g_matWVP);

	////�����x�N�g��
	//outData.wPos = mul(pos, g_matW);
	////float4 wCameraPos = mul(g_cameraPosition, g_matW);
	////�����x�N�g��
	//
	//
	//tangent.w = 0;
	////�@���Ɛڐ����g���ď]�@�������
	////�]�@��
	//float3 biNormal = cross(normal, tangent);
	////�@��
	//outData.normal = mul(normal, g_matNormal);
	//outData.normal.w = 0;
	//
	////�@������]
	//normal = mul(normal, g_matNormal);
	//normal = normalize(normal);
	//
	////�]�@������]
	//biNormal = mul(biNormal, g_matNormal);
	//biNormal = normalize(biNormal);
	//
	////�ڐ�����]
	//tangent = mul(tangent, g_matNormal);
	//tangent = normalize(tangent);
	//
	////�ڋ�Ԃɂ����郉�C�g�̌��������C�g�x�N�g���Ɗe�x�N�g���ŋ��߂�
	//float4 light = float4(0, -1, 1, 0);
	////outData.light.x = dot(light, tangent);
	////outData.light.y = dot(light, biNormal);
	////outData.light.z = dot(light, normal);
	////outData.light.w	 = 0;
	//outData.light = normalize(light);

	//�ڋ�Ԃɂ����鎋���x�N�g���������x�N�g���Ɗe�x�N�g���ŋ��߂�
	//outData.eyeVector.x = dot(vecView, tangent);
	//outData.eyeVector.y = dot(vecView, biNormal);
	//outData.eyeVector.z = dot(vecView, normal);
	//outData.eyeVector.w = 0;
	//outData.eyeVector = vecView;

	//UV
	//outData.uv = uv;

	//�܂Ƃ߂ďo��
	return mul(pos, g_matWVP);
	//return outData;
}
//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	//���C�g�x�N�g��
	//���C�g�𐳋K��
	//float4 light = normalize(inData.light);
	//float4 normal;
	////�m�[�}���}�b�v�g���Ȃ�
	//if (g_isNormal)
	//{
	//	//�m�[�}���}�b�v�e�N�X�`������m�[�}���������
	//	//�m�[�}���}�b�v��RGB��0�`1�̏�񂾂��A�@���͊e�l��-1�`1�܂ł̒l���Ƃ�̂�
	//	//2�{����1�������Œ������Ă���
	//	 normal = g_normalTexture.Sample(g_sampler, inData.uv) * 2 - 1;
	//}
	////�g��Ȃ��Ȃ�|���S���̃m�[�}���g��
	////else
	//
	//normal = inData.normal;
	//
	////���K��
	//normal = normalize(normal);
	//normal.w = 0;
	//
	////�g�U���ˌ�(�f�B�t���[�Y)
	////�@���ƃ��C�g�̕����̓���
	//float4 shade = saturate(dot(-light, normal));
	//shade.a = 1;
	//
	//float4 diffuse;
	////�e�N�X�`���g���Ȃ�
	//if (g_isTexture == true)
	//{
	//	//�e�N�X�`�����������Ă���
	//	diffuse = g_texture.Sample(g_sampler, inData.uv) * g_customColor;
	//}
	////�g��Ȃ��Ȃ�
	//else
	//{
	//	diffuse = g_diffuseColor * g_customColor;
	//}
	//
	////����(�A���r�G���g)
	//float4 ambient = g_ambient;
	//ambient.a = 1;
	//
	////���ʔ��ˌ�(�X�y�L�����[)
	//float4 speculer = float4(0, 0, 0, 0);
	//if (g_speculer.a != 0)
	//{
	//	//���C�g�x�N�g���ƃm�[�}���Ő����˃x�N�g�������
	//	//�����˃x�N�g��
	//	float4 vecReflect = normalize(2 * normal * dot(normal, -light) - light);//reflect(light, normal);
	//	//�X�y�L����
	//	float4 vecView = normalize(g_cameraPosition - inData.wPos);
	//	speculer = pow(saturate(dot(vecReflect, vecView)), g_shininess) * g_speculer;
	//}
	//
	////speculer.w = 0;
	//outColor = diffuse * shade + diffuse * ambient + speculer;
	//
	////outColor = speculer;
	float4 outColor = float4(1,1,1,1);
	return outColor;
}