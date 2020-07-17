#include <yaml-cpp/yaml.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <Logger.h>
#include "Llrf.h"
#include "helpers.h"

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
        std::cout << "Must specify a YAML top path." << std::endl;
        exit(1);
    }

    IYamlSetIP setIP(ipAddr);
    Path root = IPath::loadYamlFile( yamlDoc.c_str(), "NetIODev", NULL, &setIP );

    if ( defaultsDoc.empty() )
    {
        std::cout << "Not defaults file was specified. Omitting..." << std::endl;
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

    // Create Gen2Llrf object
    std::cout << "Creating an Llrf object..." << std::endl;
    Llrf llrf { ILlrf::create(root) };
    std::cout << std::endl;

    // Initialize it
    std::cout << "Initializing the Llrf object..." << std::endl;
    bool success;
    if ( success =  llrf->init() )
    {
        success &= llrf->isInited();
    }
    std::cout << std::endl;

    // Check if the initialization succeed
    std::cout << std::endl;
    if ( !success )
    {
        std::cerr << "Initialization failed!" << std::endl;
        return 1;
    }

    std::cout << "Initialization succeed!" << std::endl;
    std::cout << std::endl;

    return 0;
}
