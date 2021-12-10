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
            << "Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4263.3 Safari/537.36"
            << "Mozilla/5.0 (Linux; Android 10; LM-K525 Build/QKQ1.200614.002; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/92.0.4515.131 Mobile Safari/537.36 [FB_IAB/FB4A;FBAV/332.0.0.23.111;]"
            << "Mozilla/5.0 (Linux; Android 11; SM-A315G Build/RP1A.200720.012; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/92.0.4515.159 Mobile Safari/537.36[FBAN/EMA;FBLC/pt_BR;FBAV/264.0.0.12.111;]"
            << "AppleCoreMedia/1.0.0.19A5325f (iPhone; U; CPU OS 15_0 like Mac OS X; fr_ch)"
            << "Mozilla/5.0 (iPhone; CPU iPhone OS 14_6 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148 Instagram 201.0.0.23.111 (iPhone8,1; iOS 14_6; ru_RU; ru-RU; scale=2.00; 750x1334; 311026220) NW/3"
            << "Mozilla/5.0 (Linux; Android 10; motorola one vision Build/QSAS30.62-24-25; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/92.0.4515.159 Mobile Safari/537.36"
            << "Mozilla/5.0 (Linux; Android 11; M2003J15SC Build/RP1A.200720.011; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/92.0.4515.131 Mobile Safari/537.36 [FB_IAB/FB4A;FBAV/332.0.0.23.111;]"
            << "Mozilla/5.0 (Linux; Android 11; SM-A107M Build/RP1A.200720.012; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/92.0.4515.159 Mobile Safari/537.36"
            << "Mozilla/5.0 (Linux; Android 10; SM-A015M Build/QP1A.190711.020; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/91.0.4472.120 Mobile Safari/537.36 [FB_IAB/FB4A;FBAV/324.0.0.48.120;]"
            << "Mozilla/5.0 (iPhone; CPU iPhone OS 14_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148 Instagram 197.0.0.20.119 (iPhone12,1; iOS 14_3; ru_RU; ru-RU; scale=2.00; 828x1792; 305020938) NW/3"
            << "Mozilla/5.0 (Linux; Android 10; 4087U_EEA Build/QP1A.190711.020; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/92.0.4515.159 Mobile Safari/537.36 [FB_IAB/FB4A;FBAV/323.0.0.46.119;]"
    ;
}

QString UserAgentGenerator::getRandomUserAgent()
{
    std::uniform_int_distribution<int> dist(0, userAgents.length() - 1);
    int random = dist(*QRandomGenerator::global());
    return userAgents.at(random);
}
