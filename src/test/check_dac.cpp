#include <yaml-cpp/yaml.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Gen2UpConverter.h"
#include "helpers.h"
#include "Logger.h"

void usage(const char* name)
{
    std::cout << "Usage: " << name << "-a <IP_address> -Y <Yaml_top> [-i <App_ID>] [-e <Enable>] [-c] [-h]" << std::endl;
    std::cout << "    -h                 : show this message." << std::endl;
    std::cout << "    -a <IP_address>    : IP address of the target FPGA." << std::endl;
    std::cout << "    -Y <yaml_file>     : Path to YAML top level file." << std::endl;
    std::cout << "    -d <defaults_file> : Path to YAML defaults file." << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    unsigned char buf[sizeof(struct in6_addr)];
    std::string ipAddr;
    std::string yamlDoc;
    std::string defaultsDoc;
    int c;

    while((c =  getopt(argc, argv, "a:Y:d:")) != -1)
    {
        switch (c)
        {
            case 'a':
                if (!inet_pton(AF_INET, optarg, buf))
                {
                    std::cout << "Invalid IP address..." << std::endl;
                    exit(1);
                }
                ipAddr = std::string(optarg);
                break;
            case 'Y':
                yamlDoc = std::string(optarg);
                break;
            case 'd':
                defaultsDoc = std::string(optarg);
                break;
            default:
                usage(argv[0]);
                exit(1);
                break;
        }
    }

    if (ipAddr.empty())
    {
        std::cout << "Must specify an IP address." << std::endl;
        exit(1);
    }

    if (yamlDoc.empty())
    {
        std::cout << "Must specify a Yaml top path." << std::endl;
        exit(1);
    }

    IYamlSetIP setIP(ipAddr);
    Path root = IPath::loadYamlFile( yamlDoc.c_str(), "NetIODev", NULL, &setIP );

    if ( defaultsDoc.empty() )
    {
        std::cout << "Not defaults file was specified. Omiting..." << std::endl;
    }
    else
    {
        std::string configPath { "mmio" };

        Path configRoot = root->findByName( configPath.c_str() );
        std::cout << "Loading '" << defaultsDoc << "'..." << std::endl;
        std::size_t n = configRoot->loadConfigFromYamlFile(defaultsDoc.c_str());
        std::cout << "Done. " << n << " entries were loaded" << std::endl;
    }

    std::cout << std::endl;

    // Set logger level to "Debug"
    ILogger::setLevel(LoggerLevel::Debug);

    // Create a Gen2UpConverter object
    std::cout << "Creating a Gen2UpConverter object..." << std::endl;
    Gen2UpConverter amc { IGen2UpConverter::create(root) };
    std::cout << std::endl;

    std::cout << "Initilizating the Gen2UpConverter object..." << std::endl;
    // Initilize it
    bool success;
    if ( success =  amc->init() )
    {
        success &= amc->isInited();
    }
    std::cout << std::endl;

    // Check if the initializtion succeed
    std::cout << std::endl;
    if ( !success )
    {
        std::cerr << "Initialization failed!" << std::endl;
        return 1;
    }

    std::cout << "Initialization succeed!" << std::endl;
    std::cout << std::endl;

    std::cout << "Reading demod values:" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::string regBase("/mmio/AppTop/AppCore/Sysgen/LlrfDemod/amp[");
    for (std::size_t i {6}; i <= 9; ++i)
    {
        std::stringstream reg;
        reg.str("");
        reg << regBase << i << "]";
        printRegValue(root->findByName(reg.str().c_str()));
    }
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;
    return 0;
}
