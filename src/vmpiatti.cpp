#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "piatti.hpp"

void vmrun(std::vector<int> codesection,
        std::vector<std::string> datasection,
        std::vector<std::pair<int, int>> pairtable){
            bool ifflag = false;
            bool elifflag = false;
            bool loopflag = false;
            bool repeatflag = false;
            bool debugprint = true;

            std::stack<long> s;

            size_t i = 0;
            bool run = true;
            while(run){
                int inst = codesection[i];

                switch (inst)
                {
                case OP_PUSH:
                        spush(s, stol(datasection[get_offset(pairtable, i)]), debugprint);
                        std::cout << "hey" << std::endl;
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
                        std::cout << std::endl;
                        break;
                
                default:
                        std::cout << "unsupport or invalid instrution" << std::endl;
                        break;
                }





                i++;
            }
        }