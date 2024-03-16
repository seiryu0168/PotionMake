#include "InterSceneData.h"
#include"Engine/SAFE_DELETE_RELEASE.h"

#include<vector>
namespace InterSceneData
{
   // struct Data
   // {
   //     std::variant<bool, std::string, short, int, float > value_;
   //     std::string dataName_;
   // };
    std::vector<Data> interScenedatas_;
    //union Data
    //{
    //    bool varBool;
    //    char varChar;
    //    std::string varString;
    //    short varShort;
    //    int varInt;
    //    float varFloat;
    //};
    //struct Data
    //{
    //    std::string dataName = "";
    //    json data;
    //};

    //std::vector<Data*> dataList_;


   // void AddData(const std::string& dataName,const json& jsonData)
   // {
   //     for (Data& data : datas_)
   //     {
   //         if (data.dataName == dataName)
   //             return;
   //     }
   //     Data data;
   //     data.dataName = dataName;
   //     data.data = jsonData;
   //     datas_.push_back(data);
   // }

    //void DeleteData(const std::string& dataName)
    //{
    //    for (auto itr = datas_.begin(); itr < datas_.end();)
    //    {
    //        if ((*itr).dataName == dataName)
    //        {
    //            itr = datas_.erase(itr);
    //            return;
    //        }
    //        itr++;
    //    }
    //}

   // std::variant<bool, std::string, short, int, float > GetData(const std::string& dataName)
   // {
   //     for (Data& d :datas_)
   //     {
   //         if (d.dataName == dataName)
   //             return d.data;
   //     }
   // }
}
