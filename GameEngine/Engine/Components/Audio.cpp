#include "Audio.h"

Audio::Audio()
{
}

Audio::Audio(GameObject* object)
    :attachObject_(object)
{
}

Audio::Audio(const std::string& fileName)
{
}

Audio::~Audio()
{
}

bool Audio::Load(const std::string& fileName, bool loopFlag, float volume, int svNum)
{
	audioData_ = AudioManager::Load_Component(fileName, loopFlag, volume, svNum);
	if (audioData_ == nullptr)
		return false;
	return true;
}

void Audio::Play()
{
    if (audioData_ == nullptr)
        return;
    for (int i = 0; i < audioData_->svNum; i++)
    {
        XAUDIO2_VOICE_STATE state;
        audioData_->pSourceVoice[i]->GetState(&state);

        if (state.BuffersQueued == 0)
        {
            audioData_->pSourceVoice[i]->SubmitSourceBuffer(&audioData_->buf);
            audioData_->pSourceVoice[i]->Start();
            break;
        }
    }
}

void Audio::Stop()
{
    if (audioData_ == nullptr)
        return;
    for (int i = 0; i < audioData_->svNum; i++)
    {
        audioData_->pSourceVoice[i]->Stop();
        audioData_->pSourceVoice[i]->FlushSourceBuffers();
    }
}
