
#include <ICPPConfig.hpp>

#include <iostream>

int main()
{
    auto l_pConfig = __N_CPPCONFIG__::CreateCPPConfigXML();
    if (!l_pConfig->Initialize("config", "confix.xml"))
    {
        std::cout << l_pConfig->getLastError() << std::endl;
        return 1;
    }

    l_pConfig->Add("key_1", std::vector<std::string>{ "value_1", "value_2" });
    l_pConfig->Add("key_2", "value_2");
    l_pConfig->Add("key_3.key_4", "value_3");
    return 0;
}