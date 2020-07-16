#include "helpers.h"

void printRegValue(Path p)
{
    ScalVal_RO  reg  { IScalVal_RO::create(p) };
    std::size_t size { reg->getNelms()        };

    if (size == 1)
    {
        uint32_t u32;
        reg->getVal(&u32);

        std::cout << reg->getPath()->toString() << " = " << u32 << std::endl;
    }
    else
    {
        std::vector<uint32_t> u32(size);
        reg->getVal(u32.data(), u32.size());

        std::cout << reg->getPath()->toString() << " = ";
        for (std::vector<uint32_t>::const_iterator it = u32.begin(); it != u32.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
    }
}
