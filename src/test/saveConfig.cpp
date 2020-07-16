#include <yaml-cpp/yaml.h>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <string>

#include "helpers.h"

void usage(const char* name)
{
    std::cout << "Usage: " << name << "-a <IP_address> -Y <Yaml_top> -d <file>" << std::endl;
    std::cout << "    -h              : show this message." << std::endl;
    std::cout << "    -a <IP_address> : IP address of the target FPGA." << std::endl;
    std::cout << "    -Y <yaml_file>  : Path to YAML top level file." << std::endl;
    std::cout << "    -d <file>       : Path to output file." << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    unsigned char buf[sizeof(struct in6_addr)];
    std::string ipAddr;
    std::string yamlDoc;
    std::string dumpDoc;
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
                dumpDoc = std::string(optarg);
                break;
            default:
                usage(argv[0]);
                exit(1);
                break;
        }
    }

    if (ipAddr.empty())
    {
        std::cerr << "Must specify an IP address." << std::endl;
        exit(1);
    }

    if (yamlDoc.empty())
    {
        std::cerr << "Must specify a YAML top path." << std::endl;
        exit(1);
    }

    if (dumpDoc.empty())
    {
        std::cerr << "Must specify an output file." << std::endl;
        exit(1);
    }

    IYamlSetIP setIP(ipAddr);
    Path root = IPath::loadYamlFile( yamlDoc.c_str(), "NetIODev", NULL, &setIP );

    std::cout << std::endl;

    std::string saveConfigRootPath { "mmio" };
    Path configPath = root->findByName(saveConfigRootPath.c_str());

    std::ofstream dumpFile;
    dumpFile.open(dumpDoc.c_str());

    if (!dumpFile.is_open())
    {
        std::cerr << "Failed to open " << dumpDoc << ". Aborting." << std::endl;
        exit(1);
    }

    YAML::Node n;
    std::size_t entryCount = configPath->dumpConfigToYaml(n);

    dumpFile << n << std::endl;
    dumpFile.close();

    std::cout << "Number of entries saved: " << entryCount << std::endl;

    return 0;
}
