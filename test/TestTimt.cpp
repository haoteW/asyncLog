
#include"Timestamp.hpp"
#include"LogMessage.hpp"
#include"LogCommon.hpp"
#include"Logger.hpp"
#include"LogFile.hpp"
#include "AsyncLogging.hpp"

#include<iostream>

using namespace std;

//async::LogFile *plog = nullptr;
void writefile(const string &info)
{
    //cout << "--------------------------------" << endl;
    async::AsyncLogging::GetInstance()->append(info);
}
void flushfile()
{
    async::AsyncLogging::GetInstance()->flush();
}
int main()
{
    //plog = new async::LogFile("yhping",1024*10*64);// 640k;
    async::Logger::setOutput(writefile);
    async::Logger::setFlush(flushfile);

    //cout << "--------------------------------" << endl;
    for(int i = 0;i<100000;++i)
    {
        LOG_INFO<<"wht main "<<i;
    }
    return 0;
}
#if 0 
int main()
{
    async::Logger::setLogLevel(async::LOG_LEVEL::TRACE);
    LOG_TRACE<<"yhping TRACE";
    LOG_DEBUG<<"main DEBUG";
    LOG_INFO<<" main INFO";
    LOG_WARN<<" main WARN";
    LOG_ERROR<<" main ERROR";
    return 0;
}


void fun(int age)
{
    //async::Logger log(async::LOG_LEVEL::INFO,__FILE__,__func__,__LINE__);
   // log.stream()<<"yheping hello";
   if(age >= 0 && age <= 20)
   {
        LOG_FATAL<<"age error : "<<age;
        //async::Logger(async::LOG_LEVEL::FATAL,__FILE__,__func__,__LINE__).stream()
   }

}
int main()
{
    fun(10);

    cout<<"main end ..."<<endl;
}

int main()
{
    async::LogMessage logmess(async::LOG_LEVEL::INFO,__FILE__,__func__,__LINE__);
    logmess<<"yhping log system";
    cout<<logmess.toString()<<endl;
    return 0;
}



int main()
{
    async::MicroTimestamp mit = async::MicroTimestamp::now();
    cout<<mit.toString()<<endl;
    cout<<mit.toFormattedString()<<endl;
    return 0;
}
#endif 