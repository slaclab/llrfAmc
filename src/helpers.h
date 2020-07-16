#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <sstream>

#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

class IYamlSetIP : public IYamlFixup
{
    public:
        IYamlSetIP( std::string ip_addr ) : ip_addr_(ip_addr) {}

        virtual void operator()(YAML::Node &root, YAML::Node &top)
        {
            YAML::Node ipAddrNode = IYamlFixup::findByName(root, "ipAddr");

            if ( ! ipAddrNode )
                throw std::runtime_error("ERROR on IYamlSetIP::operator(): 'ipAddr' node was not found!");

            ipAddrNode = ip_addr_.c_str();
        }

        ~IYamlSetIP() {}

    private:
        std::string ip_addr_;
};

template <typename T>
bool allZeros(const std::vector<T>& vec)
{
    bool ret { true };

    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (*it)
        {
            ret = false;
            break;
        }
    }

    return ret;
}

template <typename T>
std::string vec2str(const std::string& name, const std::vector<T>& vec)
{
    std::stringstream ss;
    ss << name << " = ";
    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        ss << *it << " ";

    return ss.str();
}

template <typename T>
void printArray(const std::string& name, const std::vector<T>& vec)
{
    std::cout << vec2str(name, vec) << std::endl;
}

template <typename T>
T vec2word(const std::vector<T>& vec)
{
    T w {0};
    for (typename std::vector<T>::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
        w = ( w << 1 ) | !!(*it);

    return w;
}

template <typename T>
std::string to_string(const T& n)
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

void printRegValue(Path p);

#endif
