#include "useragentgenerator.h"

UserAgentGenerator::UserAgentGenerator()
{
    userAgents
            << "Mozilla/5.0 (Windows NT 5.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36 SznProhlizec/4.5.2"
            << "Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0; 1CA27152-A546-CB58-96CF-07DC9D708291) like Gecko"
            << "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; eSobiSubscriber 1.0.0.40; .NET4.0C; .NET4.0E; MAAR; BRI/2; rv:11.0) like Gecko"
            << "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; .NET4.0C; InfoPath.2; .NET4.0E; SVD2; rv:11.0) like Gecko"
            << "Mozilla/5.0 (Windows NT 10.0; Trident/7.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727; .NET CLR 3.0.30729; .NET CLR 3.5.30729; InfoPath.3; SLCC2; Media Center PC 6.0; BRI/2; rv:11.0) like Gecko"
            << "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; .NET4.0C; HPDTDF; .NET4.0E; rv:11.0) like Gecko"
            << "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:26.0; WUID=3f970b7303dfc6f8e9e6ae8a4c03f806; WTB=3623) Gecko/20100101 Firefox/26.0"
            << "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.94 Safari/537.36 SznProhlizec/4.2.3"
            << "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.78 Safari/537.36"
            << "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4259.3 Safari/537.36"
            << "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4263.3 Safari/537.36";
}

QString UserAgentGenerator::getRandomUserAgent()
{
    std::uniform_int_distribution<int> dist(0, userAgents.length() - 1);
    int random = dist(*QRandomGenerator::global());
    return userAgents.at(random);
}
