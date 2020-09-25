
namespace mvp
{
      class Ransac
      {
      private:
          /* data */
      public:
          Ransac(/* args */);
          ~Ransac();

          //---------算法流程-------------
          virtual int RunRansac()
          {
              while (!IsGoodEnough())
              {
                //step1: 随机抽取估计模型最小数据集
                SampleMnimumData();

                //step2: 使用最小数据集拟合模型
                FitModel();

                //step3: 将所有数据代入拟合模型，计算出内点外点的数目
                ComputeCurrentInliers();

                //step4: 比较当前模型和之前推出的最好的模型的“内点“的数量，记录最大“内点”数的模型参数和“内点”数
                RecordBestModel();
                
                //step5: 重复1-4步，直到迭代结束或者当前模型已经足够好了(取决于判断条件)
              }
          }

          virtual int SampleMnimumData() = 0;

          virtual int FitModel() = 0;

          virtual int ComputeCurrentInliers() = 0;
          
          virtual int RecordBestModel() = 0;

          virtual bool IsGoodEnough() = 0;
      };
      
      Ransac::Ransac(/* args */)
      {
      }
      
      Ransac::~Ransac()
      {
      }
      
}//namespace mvp