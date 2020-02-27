// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
using namespace std;

const char* option_desc = "\
first program\n\
\n\
Allowed options \
";


int main(int ac, char* av[])
{
    try {

//        po::options_description desc("Allowed options");
        po::options_description desc1("audio");
        desc1.add_options()
            ("help1,h1", "produce help message")
            ("compression1", po::value<double>(), "set compression level")
        ;
        
        po::options_description desc2("video");
        desc2.add_options()
            ("help2,h2", "produce help message")
            ("compression2", po::value<double>(), "set compression level")
        ;
        
        po::options_description desc("option_desc");
        desc.add_options()
            ("help,h", "produce help message")
            ("compression", po::value<double>(), "set compression level")
        ;

        desc.add(desc1);
        desc.add(desc2);

        po::variables_map vm;        
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        if (vm.count("compression")) {
            cout << "Compression level was set to " 
                 << vm["compression"].as<double>() << ".\n";
        } else {
            cout << "Compression level was not set.\n";
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return 0;
}
