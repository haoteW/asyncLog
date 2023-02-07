
#include "Timestamp.hpp"
#include "LogMessage.hpp"
#include "LogCommon.hpp"
#include "Logger.hpp"
#include <iostream>
using namespace std;

void fun(int age)
{
    // tulun::Logger log(tulun::LOG_LEVEL::INFO,__FILE__,__func__,__LINE__);
    // log.stream()<<"yheping hello";
    if (age >= 0 && age <= 20)
    {
        LOG_FATAL << "age error : " << age;
    }
}
int main()
{
    fun(10);

    cout << "main end ..." << endl;
}
#if 0 
int main()
{
    tulun::LogMessage logmess(tulun::LOG_LEVEL::INFO,__FILE__,__func__,__LINE__);
    logmess<<"yhping log system";
    cout<<logmess.toString()<<endl;
    return 0;
}



int main()
{
    tulun::MicroTimestamp mit = tulun::MicroTimestamp::now();
    cout<<mit.toString()<<endl;
    cout<<mit.toFormattedString()<<endl;
    return 0;
}
#endif