#include <vector>
#include <iostream>
#include <string>
#include "piatti.hpp"

void vmrun(std::stack<long> &s,
           std::vector<int> &codesection,
           std::vector<std::string> &datasection,
           std::vector<std::pair<int, int>> &pairtable)
{
        bool ifflag = false;
        bool elifflag = false;
        bool loopflag = false;
        bool repeatflag = false;
        bool debugprint = false;
        int offset = 0;
        std::string data;

        size_t i = 0;
        bool run = true;
        while (run)
        {
                if (i >= codesection.size())
                {
                        std::cout << "reaching end codesetion" << std::endl;
                        break;
                }
                int inst = codesection[i];
                // std::cout << "instruction " << inst << " i: " << i << std::endl;

                // printstack(s);

                switch (inst)
                {
                case OP_PUSH:
                        offset = get_offset(pairtable, i);
                        data = datasection[offset];
                        // std::cout << data << std::endl;
                        spush(s, stol(data), debugprint);
                        // std::cout << "hey" << std::endl;
                        break;

                case OP_SWAP:
                        sswap(s, debugprint);
                        break;

                case OP_SUB:
                        ssub(s, debugprint);
                        break;

                case OP_PUTC:
                        sputc(s, debugprint);
                        break;

                case OP_PUTNL:
                        printf("\n");
                        break;

                case OP_EXIT:
                        run = false;
                        break;

                default:
                        std::cout << "unsupport or invalid instrution: " << inst << std::endl;
                        break;
                }

                i++;
        }
}